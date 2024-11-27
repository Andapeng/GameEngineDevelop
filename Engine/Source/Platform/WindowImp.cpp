#include "WindowImp.h"
#include "SFML/Window.hpp"
#include "../Managers/InputManager.h"
#include "../Config/GlobalConfiguration.h"
#include "glad/glad.h"
#include "imgui-sfml/imgui-SFML.h"
#include "imgui_impl_opengl3.h"

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

		m_Window = std::make_unique<sf::RenderWindow>(sf::VideoMode(config->GetWidth(), config->GetHeight()), "OpenGL with SFML", sf::Style::Default, settings) ;
		ImGui::SFML::Init(*m_Window);
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui_ImplOpenGL3_Init("#version 150");
		return 0;
	}
	void SfmlWindowImp::Show()
	{
#ifdef OPENGL_RENDERING
		ImGui::SFML::Render(*m_Window);
		m_Window->display();
#endif
	}
	void SfmlWindowImp::ProcessEvent()
	{
		sf::Event event;
		while (m_Window->pollEvent(event)) {
			ImGui::SFML::ProcessEvent(*m_Window, event);
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
#ifdef OPENGL_RENDERING
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
#endif
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

	void SfmlWindowImp::Update(float elapsedTime)
	{
		ImGui::SFML::Update(*m_Window, sf::seconds(elapsedTime));
	}
}
