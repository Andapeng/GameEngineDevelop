#pragma once
#include <dxgi1_4.h>
#include <wrl/client.h>
#include "D3dUtil.h"
#include "IGraphicsDevice.h"

class D3D12GraphicsDevice : public IGraphicsDevice
{
public:
	D3D12GraphicsDevice();
	~D3D12GraphicsDevice();
	void Initialize() override;
	void Draw() override;
	void Release() override;
private:
	void LogAdapters();
	void LogAdapterOutputs(IDXGIAdapter* adapter);
	void LogDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);

	void BuildRootSignature();
	void BuildMeshData();
	void BuildPSO();

	void CreateCommandObjects();
	void CreateSwapChain();
	void CreateRtvAndDsvDescriptorHeaps();
	void CreateRenderTargetViews();
	void CreateDepthStencilViews();
	void SetViewPorts();
	void SetScissorRects();

	void FlushCommandQueue();

	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView() const;
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView() const;

	ID3D12Resource* CurrentBackBuffer();

	Microsoft::WRL::ComPtr<ID3D12Device> mD3dDevice = nullptr;
	Microsoft::WRL::ComPtr<IDXGIFactory4> mDxgiFactory = nullptr;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> mCommandQueue = nullptr;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mDirectCmdListAlloc = nullptr;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRtvHeap = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mDsvHeap = nullptr;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> mPipelineState = nullptr;

	UINT64 mCurrentFence = 0;
	Microsoft::WRL::ComPtr<ID3D12Fence> mFence = nullptr;

	static const int SwapChainBufferCount = 2;
	int mCurrentBackBuffer = 0;
	Microsoft::WRL::ComPtr<ID3D12Resource> mSwapChainBuffer[SwapChainBufferCount];
	Microsoft::WRL::ComPtr<ID3D12Resource> mDepthStencilBuffer = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource> mVertexBuffer= nullptr;
	D3D12_VERTEX_BUFFER_VIEW mVertexBufferView;

	UINT mRtvDescriptorSize = 0;
	UINT mDsvDescriptorSize = 0;
	UINT mCbvUavDescriptorSize = 0;

	bool m4xMsaaState = false;
	UINT m4xMsaaQuality = 0;

	int mClientWidth = 800;
	int mClientHeight = 600;

	HWND mhMainWnd;

	DXGI_FORMAT mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGI_FORMAT mDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	D3D12_VIEWPORT mScreenViewPort;
	D3D12_RECT mScissorRect;
};
