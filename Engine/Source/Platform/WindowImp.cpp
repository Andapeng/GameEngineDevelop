#include "WindowImp.h"
#include "SFML/Window.hpp"
#include "../Managers/InputManager.h"
#include "../Config/GlobalConfiguration.h"
#include "glad/glad.h"
namespace sadp
{
	int SfmlWindowImp::Create()
	{
		auto config = Configuration::Get();
		config->Load("Assets/Conf/gConfig.xml");

		sf::ContextSettings settings;
		settings.depthBits = config->GetDepthBits();
		settings.stencilBits = config->GetStencilBits();
		settings.majorVersion = config->GetMajorVersion();
		settings.minorVersion = config->GetMinorVersion();

		m_Window = new sf::RenderWindow(sf::VideoMode(config->GetWidth(), config->GetHeight()), "OpenGL with SFML", sf::Style::Default, settings);
		return 0;
	}
	void SfmlWindowImp::Show()
	{
		// m_Window->display();
	}
	void SfmlWindowImp::ProcessEvent()
	{
		sf::Event event;
		while (m_Window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_Window->close();
			}
			if (event.type == sf::Event::EventType::KeyPressed) {
				g_pInputManager->KeyPressed(event.key.code);
			}
			if (event.type == sf::Event::EventType::KeyReleased) {
				g_pInputManager->KeyRelease(event.key.code);
			}
			if (event.type == sf::Event::Resized)
			{
				OnResize(0, 0, event.size.width, event.size.height);
			}
		}
	}
	void SfmlWindowImp::OnResize(int x, int y, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	void SfmlWindowImp::OnRenderBefore()
	{
		// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// glClear(GL_COLOR_BUFFER_BIT);
	}

	long long SfmlWindowImp::GetHandle()
	{
		return (long long)m_Window->getSystemHandle();
	}

	void SfmlWindowImp::GetSize(int& x, int& y)
	{
		x = m_Window->getSize().x;
		y = m_Window->getSize().y;
	}

	bool SfmlWindowImp::IsOpen()
	{
		return m_Window->isOpen();
	}
}