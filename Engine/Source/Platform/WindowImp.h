#pragma once
#include "IWindow.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace sadp
{
	class WindowImp : public IWindow
	{
	public:
		virtual ~WindowImp() = default;
	};

	class SfmlWindowImp : public WindowImp
	{
	public:
		~SfmlWindowImp() override = default;

		// Í¨¹ý WindowImp ¼Ì³Ð
		virtual int Create() override;
		virtual void Show() override;
		virtual bool IsOpen() override;

		virtual void ProcessEvent() override;
		virtual void OnResize(int x, int y, int width, int height) override;
		virtual void OnRenderBefore() override;

	private:
		sf::RenderWindow* m_Window = nullptr;
	};
}
