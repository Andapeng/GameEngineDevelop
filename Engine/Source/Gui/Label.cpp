#include "Label.h"
#include "../Managers/Managers.h"
#include "../Renderer/TextRenderer.h"
class TextRenderer;

Label::Label(const std::wstring& text, float xpos, float ypos, float size)
	: m_xPos(xpos)
	, m_yPos(ypos)
	, m_size(size)
	, m_color(Eigen::Vector3f(1.0f, 0.0f, 0.0f))
{
	m_text = text;
}

Label::~Label()
{
}

void Label::SetText(const std::wstring& text)
{
	m_text = text;
}

const std::wstring& Label::GetText()
{
	return m_text;
}

void Label::OnKeyPressed()
{
}

void Label::Update(float elasedTime)
{
}

void Label::OnRender()
{
	TextRenderer* textRenderer = g_pGraphicsManager->GetTextRenderer();
	textRenderer->RenderText(m_text, m_xPos, m_yPos, m_size, m_color);
}

