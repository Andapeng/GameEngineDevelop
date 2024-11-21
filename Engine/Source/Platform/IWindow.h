#pragma once
namespace sadp 
{
	class IWindow
	{
	public:
		//	TODO ����Ӧ������Щ��������Ϊ��

		// ��������
		virtual int Create() = 0;
		virtual void Show() = 0;
		virtual bool IsOpen() = 0;
		virtual void ProcessEvent() = 0;

		virtual void OnResize(int x, int y, int width, int height) = 0;
		virtual void OnRenderBefore() = 0;
		virtual long long  GetHandle() = 0;

		virtual void GetSize(int& x, int& y) = 0;
	};

}