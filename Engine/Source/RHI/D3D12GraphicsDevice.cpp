#include "D3D12GraphicsDevice.h"

#include <cassert>
#include <format>
#include <string>
#include <vector>
#include <string> 
#include <list>
#include "../Log.h"
#include "D3dUtil.h"
#include "DirectXColors.h"
#include "d3dcompiler.h"
#include "d3dtypes.h"
#include "../Managers/WindowManager.h"

using namespace Microsoft::WRL;
using namespace DirectX;
struct cVertex
{
	cVertex(const XMFLOAT3& InPos, const XMFLOAT4& InColor)
	{
		m_mPosition = InPos;
		m_mColor = InColor;
	}

	XMFLOAT3 m_mPosition;
	XMFLOAT4 m_mColor;
};


D3D12GraphicsDevice::D3D12GraphicsDevice()
{
}

D3D12GraphicsDevice::~D3D12GraphicsDevice()
{
}

void D3D12GraphicsDevice::Initialize()
{
	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&mDxgiFactory));
	if (FAILED(hr))
	{
		return;
	}
	LogAdapters();

	// 创建设备
#if defined(DEBUG) || defined(_DEBUG)
	{
		ComPtr<ID3D12Debug> debugController;
		ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
		debugController->EnableDebugLayer();
	}
#endif
HRESULT hardwareResult = D3D12CreateDevice(
	nullptr,
	D3D_FEATURE_LEVEL_11_0,
	IID_PPV_ARGS(&mD3dDevice));

	if (FAILED(hardwareResult))
	{
		ComPtr<IDXGIAdapter> pWarpAdapter;
		ThrowIfFailed(mDxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter)));

		ThrowIfFailed(D3D12CreateDevice(
			pWarpAdapter.Get(),
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&mD3dDevice)));
	}

	// 创建围栏并获取描述符大小
	ThrowIfFailed(mD3dDevice->CreateFence(
		0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence)));

	mRtvDescriptorSize = mD3dDevice->GetDescriptorHandleIncrementSize(
		D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	mDsvDescriptorSize = mD3dDevice->GetDescriptorHandleIncrementSize(
		D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	mCbvUavDescriptorSize = mD3dDevice->GetDescriptorHandleIncrementSize(
		D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// 检测对4x msaa 质量级别支持
	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msQualityLevels;
	msQualityLevels.Format = mBackBufferFormat;
	msQualityLevels.SampleCount = 4;
	msQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	msQualityLevels.NumQualityLevels = 0;
	ThrowIfFailed(mD3dDevice->CheckFeatureSupport(
		D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
		&msQualityLevels,
		sizeof(msQualityLevels)));
	m4xMsaaQuality = msQualityLevels.NumQualityLevels;
	assert(m4xMsaaQuality > 0 && "Unexpected MSAA quality level");

	// 创建命令队列和命令列表
	CreateCommandObjects();


	mhMainWnd = (HWND)g_pWindowManager->GetMainWindowHandle();
	g_pWindowManager->GetMainWindowSize(mClientWidth, mClientHeight);
	// 描述并创建交换链
	CreateSwapChain();

	// 创建描述符堆
	CreateRtvAndDsvDescriptorHeaps();

	// 创建渲染目标视图
	CreateRenderTargetViews();

	// 创建深度/模板缓冲区及其视图
	CreateDepthStencilViews();

	//
	BuildRootSignature();

	//准备网格体
	BuildMeshData();

	//准备渲染管线
	BuildPSO();

	SetViewPorts();

	SetScissorRects();
}

void D3D12GraphicsDevice::Draw()
{
	ThrowIfFailed(mDirectCmdListAlloc->Reset());

	// 在通过ExecuteCommandList方法将某个命令列表加入命令队列后，我们便可以重置该命令列表。以此来复用命令列表及其内存
	ThrowIfFailed(mCommandList->Reset(
		mDirectCmdListAlloc.Get(), mPipelineState.Get()));

	CD3DX12_RESOURCE_BARRIER ResourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
		CurrentBackBuffer(),
		D3D12_RESOURCE_STATE_PRESENT,
		D3D12_RESOURCE_STATE_RENDER_TARGET);
	// 对资源的状态进行转换， 将资源从呈现状态转换为渲染目标状态
	mCommandList->ResourceBarrier(
		1, &ResourceBarrier);

	mCommandList->RSSetViewports(1, &mScreenViewPort);
	mCommandList->RSSetScissorRects(1, &mScissorRect);

	mCommandList->ClearRenderTargetView(
		CurrentBackBufferView(),
		DirectX::Colors::LightSteelBlue, 0, nullptr);
	mCommandList->ClearDepthStencilView(
		DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
		1.0f, 0, 0, nullptr);

	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferViews = CurrentBackBufferView();
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilViews = DepthStencilView();
	mCommandList->OMSetRenderTargets(1, &CurrentBackBufferViews,
		true, &DepthStencilViews);

	mCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mCommandList->IASetVertexBuffers(0, 1, &mVertexBufferView);
	mCommandList->DrawInstanced(3, 1, 0, 0);

	CD3DX12_RESOURCE_BARRIER AfterDrawResourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
		CurrentBackBuffer(),
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_PRESENT);
	mCommandList->ResourceBarrier(
		1, &AfterDrawResourceBarrier);

	ThrowIfFailed(mCommandList->Close());

	ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
	mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	ThrowIfFailed(mSwapChain->Present(0, 0));
	mCurrentBackBuffer = (mCurrentBackBuffer + 1) % SwapChainBufferCount;

	FlushCommandQueue();
}

void D3D12GraphicsDevice::Release()
{
}

void D3D12GraphicsDevice::LogAdapters()
{
	UINT i = 0;

	IDXGIAdapter* adapter = nullptr;
	std::vector<IDXGIAdapter*> adapterList;
	while(mDxgiFactory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC desc;
		adapter->GetDesc(&desc);

		std::wstring text = L"***Adapter: ";
		text += desc.Description;

		Logger::LogInfo(text.c_str());

		adapterList.push_back(adapter);
		++i;
	}

	for (size_t i = 0; i < adapterList.size(); ++i)
	{
		LogAdapterOutputs(adapterList[i]);
		//ReleaseCom(adapterList[i]);
		adapterList[i]->Release();
	}

}

void D3D12GraphicsDevice::LogAdapterOutputs(IDXGIAdapter* adapter)
{
	UINT i = 0;
	IDXGIOutput* output = nullptr;
	while(adapter->EnumOutputs(i, &output) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_OUTPUT_DESC desc;
		output->GetDesc(&desc);

		std::wstring text = L"***Output: ";
		text += desc.DeviceName;
		Logger::LogInfo(text.c_str());
		LogDisplayModes(output, DXGI_FORMAT_B8G8R8A8_UNORM);
		output->Release();
		++i;
	}
}

void D3D12GraphicsDevice::LogDisplayModes(IDXGIOutput* output, DXGI_FORMAT format)
{
	UINT count = 0;
	UINT flags = 0;

	output->GetDisplayModeList(format, flags, &count, nullptr);
	std::vector<DXGI_MODE_DESC> modeList(count);

	output->GetDisplayModeList(format, flags, &count, &modeList[0]);


	for(auto& x : modeList)
	{
		UINT n = x.RefreshRate.Numerator;
		UINT d = x.RefreshRate.Denominator;
		std::wstring text = std::format(L"Width {} Height = {} Refresh = {}/{}", x.Width, x.Height, n, d);
		Logger::LogInfo(text.c_str());
	}

}

void D3D12GraphicsDevice::BuildRootSignature()
{

}

void D3D12GraphicsDevice::BuildMeshData()
{
	cVertex triangleVertices[] =
	{
		{ { 0.0f, 0.5f, 0.0f }, XMFLOAT4(Colors::Red) },
		{ { 0.5f, -0.5f, 0.0f }, XMFLOAT4(Colors::Green)},
		{ { -0.5f, -0.5f, 0.0f }, XMFLOAT4(Colors::Blue) }
	};

	ComPtr<ID3D12Resource> vertexUploadBuffer;

	const UINT triangleVerticesSize = sizeof(triangleVertices);
	CD3DX12_RESOURCE_DESC BufferResourceDESC = CD3DX12_RESOURCE_DESC::Buffer(triangleVerticesSize);
	CD3DX12_HEAP_PROPERTIES BufferProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

	mD3dDevice->CreateCommittedResource(
		&BufferProperties,
		D3D12_HEAP_FLAG_NONE,
		&BufferResourceDESC,
		D3D12_RESOURCE_STATE_COMMON,
		nullptr,
		IID_PPV_ARGS(&mVertexBuffer));

	CD3DX12_HEAP_PROPERTIES UpdateBufferProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	mD3dDevice->CreateCommittedResource(
		&UpdateBufferProperties,
		D3D12_HEAP_FLAG_NONE,
		&BufferResourceDESC,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertexUploadBuffer));

	// 设置要传输的CPU数据
	D3D12_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pData = triangleVertices;
	subResourceData.RowPitch = triangleVerticesSize;
	subResourceData.SlicePitch = subResourceData.RowPitch;

	mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr); // 之前close了command list，这里要使用到，需要reset操作才可记录command

	CD3DX12_RESOURCE_BARRIER CopyDestBarrier = CD3DX12_RESOURCE_BARRIER::Transition(mVertexBuffer.Get(),
		D3D12_RESOURCE_STATE_COMMON,
		D3D12_RESOURCE_STATE_COPY_DEST);

	//传输前要更改resource的state
	mCommandList->ResourceBarrier(1, &CopyDestBarrier);

	//会先将CPU内存数据拷贝到upload heap中，然后再通过ID3D12CommandList::CopySubresourceRegion从upload heap中拷贝到default buffer中
	UpdateSubresources<1>(
		mCommandList.Get(),
		mVertexBuffer.Get(),
		vertexUploadBuffer.Get(),
		0,
		0,
		1,
		&subResourceData);

	// CD3DX12_RESOURCE_BARRIER ReadDestBarrier = CD3DX12_RESOURCE_BARRIER::Transition(mVertexBuffer.Get(),
	// 	D3D12_RESOURCE_STATE_COPY_DEST,
	// 	D3D12_RESOURCE_STATE_GENERIC_READ);

	//m_spGraphicsCommandList->ResourceBarrier(1, &ReadDestBarrier);


	mCommandList->Close();
	ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
	mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	FlushCommandQueue();

	mVertexBufferView.BufferLocation = mVertexBuffer->GetGPUVirtualAddress();
	mVertexBufferView.SizeInBytes = triangleVerticesSize;
	mVertexBufferView.StrideInBytes = sizeof(cVertex);
}

void D3D12GraphicsDevice::BuildPSO()
{
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};

	//InputLayout
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};
	D3D12_INPUT_LAYOUT_DESC inputLayout = { inputElementDescs, _countof(inputElementDescs) };
	psoDesc.InputLayout = inputLayout;

	//Root Signature
	CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> signature, error;
	D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);

	ComPtr<ID3D12RootSignature> rootSignature;
	mD3dDevice->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
	psoDesc.pRootSignature = rootSignature.Get();

	//Shader Compiler
	ComPtr<ID3DBlob> vsByteCode, psByteCode;

	vsByteCode = d3dUtil::CompileShader(L"Assets\\Shaders\\shaders.hlsl", nullptr,  "VSMain", "vs_5_0");
	psByteCode = d3dUtil::CompileShader(L"Assets\\Shaders\\shaders.hlsl", nullptr, "PSMain", "ps_5_0");

	//绑定顶点着色器代码
	psoDesc.VS.pShaderBytecode = reinterpret_cast<BYTE*>(vsByteCode->GetBufferPointer());
	psoDesc.VS.BytecodeLength = vsByteCode->GetBufferSize();
	 
	//绑定像素着色器
	psoDesc.PS.pShaderBytecode = reinterpret_cast<BYTE*>(psByteCode->GetBufferPointer());
	psoDesc.PS.BytecodeLength = psByteCode->GetBufferSize();

	//Other Setting
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	psoDesc.DepthStencilState.DepthEnable = FALSE;
	psoDesc.DepthStencilState.StencilEnable = FALSE;
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = mBackBufferFormat;
	psoDesc.DSVFormat = mDepthStencilFormat;
	psoDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	// psoDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;

	ThrowIfFailed(mD3dDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&mPipelineState)));
}

void D3D12GraphicsDevice::CreateCommandObjects()
{
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	ThrowIfFailed(mD3dDevice->CreateCommandQueue(
		&queueDesc, IID_PPV_ARGS(&mCommandQueue)));
	ThrowIfFailed(mD3dDevice->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(mDirectCmdListAlloc.GetAddressOf())));

	ThrowIfFailed(mD3dDevice->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		mDirectCmdListAlloc.Get(),
		nullptr,
		IID_PPV_ARGS(mCommandList.GetAddressOf())));
	mCommandList->Close();
}

void D3D12GraphicsDevice::CreateSwapChain()
{
	mSwapChain.Reset();

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = mClientWidth;
	sd.BufferDesc.Height = mClientHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = mBackBufferFormat;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	sd.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = SwapChainBufferCount;
	sd.OutputWindow = mhMainWnd;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	ThrowIfFailed(mDxgiFactory->CreateSwapChain(
		mCommandQueue.Get(),
		&sd,
		mSwapChain.GetAddressOf()));

}

void D3D12GraphicsDevice::CreateRtvAndDsvDescriptorHeaps()
{
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
	rtvHeapDesc.NumDescriptors = SwapChainBufferCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvHeapDesc.NodeMask = 0;
	ThrowIfFailed(mD3dDevice->CreateDescriptorHeap(
		&rtvHeapDesc, IID_PPV_ARGS(mRtvHeap.GetAddressOf())));

	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	dsvHeapDesc.NodeMask = 0;
	ThrowIfFailed(mD3dDevice->CreateDescriptorHeap(
		&dsvHeapDesc, IID_PPV_ARGS(mDsvHeap.GetAddressOf())));
}

void D3D12GraphicsDevice::CreateRenderTargetViews()
{
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(mRtvHeap->GetCPUDescriptorHandleForHeapStart());
	for (UINT i = 0; i < SwapChainBufferCount; i++)
	{
		// 获得交换链内的第i个缓冲区
		ThrowIfFailed(mSwapChain->GetBuffer(
			i, IID_PPV_ARGS(&mSwapChainBuffer[i])));

		// 为此缓冲区创建一个RTV
		mD3dDevice->CreateRenderTargetView(mSwapChainBuffer[i].Get(),
			nullptr, rtvHeapHandle);

		// 偏移到描述符堆中的下一个缓冲区
		rtvHeapHandle.Offset(1, mRtvDescriptorSize);
	}
}

void D3D12GraphicsDevice::CreateDepthStencilViews()
{
	// 创建深度/模板缓冲区及其视图
	D3D12_RESOURCE_DESC depthStencilDesc;
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = mClientWidth;
	depthStencilDesc.Height = mClientHeight;
	depthStencilDesc.DepthOrArraySize = 1;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.Format = mDepthStencilFormat;
	depthStencilDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	depthStencilDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	CD3DX12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

	D3D12_CLEAR_VALUE optClear;
	optClear.Format = mDepthStencilFormat;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;
	ThrowIfFailed(mD3dDevice->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&depthStencilDesc,
		D3D12_RESOURCE_STATE_COMMON,
		&optClear,
		IID_PPV_ARGS(mDepthStencilBuffer.GetAddressOf())));

	// 利用此资源的格式，为整个资源的第0mip层创建描述符
	mD3dDevice->CreateDepthStencilView(
		mDepthStencilBuffer.Get(),
		nullptr,
		DepthStencilView());

	CD3DX12_RESOURCE_BARRIER ResourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
		mDepthStencilBuffer.Get(),
		D3D12_RESOURCE_STATE_COMMON,
		D3D12_RESOURCE_STATE_DEPTH_WRITE);

	// 将资源从初始状态转换为深度缓冲区
	mCommandList->ResourceBarrier(
		1,
		&ResourceBarrier);
}

void D3D12GraphicsDevice::SetViewPorts()
{
	mScreenViewPort.TopLeftX = 0.0f;
	mScreenViewPort.TopLeftY = 0.0f;
	mScreenViewPort.Width = static_cast<float>(mClientWidth);
	mScreenViewPort.Height = static_cast<float>(mClientHeight);
	mScreenViewPort.MinDepth = 0.0f;
	mScreenViewPort.MaxDepth = 1.0f;

	mCommandList->RSSetViewports(1, &mScreenViewPort);
}

void D3D12GraphicsDevice::SetScissorRects()
{
	mScissorRect = {0, 0, mClientWidth, mClientHeight};
	mCommandList->RSSetScissorRects(1, &mScissorRect);
}

void D3D12GraphicsDevice::FlushCommandQueue()
{
	mCurrentFence++;

	ThrowIfFailed(mCommandQueue->Signal(mFence.Get(), mCurrentFence));

	if (mFence->GetCompletedValue() < mCurrentFence)
	{
		HANDLE eventHandle = CreateEventEx(nullptr, nullptr, 0, EVENT_ALL_ACCESS);

		ThrowIfFailed(mFence->SetEventOnCompletion(mCurrentFence, eventHandle));

		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}
}

D3D12_CPU_DESCRIPTOR_HANDLE D3D12GraphicsDevice::CurrentBackBufferView() const
{
	return CD3DX12_CPU_DESCRIPTOR_HANDLE(
		mRtvHeap->GetCPUDescriptorHandleForHeapStart(),
		mCurrentBackBuffer,
		mRtvDescriptorSize
	);
}

D3D12_CPU_DESCRIPTOR_HANDLE D3D12GraphicsDevice::DepthStencilView() const
{
	return mDsvHeap->GetCPUDescriptorHandleForHeapStart();
}

ID3D12Resource* D3D12GraphicsDevice::CurrentBackBuffer()
{
	return mSwapChainBuffer[mCurrentBackBuffer].Get();
}
