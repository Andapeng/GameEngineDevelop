#pragma once
#include "IWindow.h"
#include "WindowImp.h"

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

		virtual void OnResize(int x, int y, int width, int height) override;
		virtual void OnRenderBefore() override;

	private:
		WindowImp* m_windowImp;
	};

}