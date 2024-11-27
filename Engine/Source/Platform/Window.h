#pragma once
#include "IWindow.h"

namespace sadp
{

	class Window : public IWindow
	{
	public:
		Window();
		virtual ~Window();


		// Í¨¹ý IWindow ¼Ì³Ð
		virtual int Create() override;
		virtual void Show() override;
		virtual void ProcessEvent() override;
		virtual bool IsOpen() override;

		virtual void Update(float elapsedTime) override;
		virtual void OnResize(int x, int y, int width, int height) override;
		virtual void OnRenderBefore() override;
		virtual long long  GetHandle() override;
		virtual void GetSize(int& x, int& y) override;

	private:
		IWindow* m_windowImp;
	};
}