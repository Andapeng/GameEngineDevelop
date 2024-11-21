#include "Window.h"

sadp::Window::Window()
	: m_windowImp(new sadp::SfmlWindowImp)
{
}

sadp::Window::~Window()
{
	delete m_windowImp;
}

int sadp::Window::Create()
{
	m_windowImp->Create();
	return 0;
}

void sadp::Window::Show()
{
	m_windowImp->Show();
}

void sadp::Window::ProcessEvent()
{
	m_windowImp->ProcessEvent();
}

bool sadp::Window::IsOpen()
{
	return m_windowImp->IsOpen();
}

void sadp::Window::OnResize(int x, int y, int width, int height)
{
	m_windowImp->OnResize(x, y, width, height);
}

void sadp::Window::OnRenderBefore()
{
	m_windowImp->OnRenderBefore();
}

long long sadp::Window::GetHandle()
{
	return m_windowImp->GetHandle();
}

void sadp::Window::GetSize(int& x, int& y)
{
	return m_windowImp->GetSize(x, y);
}
