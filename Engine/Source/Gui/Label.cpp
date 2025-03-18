#include "Label.h"
#include "../Managers/Managers.h"
#include "../Renderer/TextRenderer.h"

class TextRenderer;

Label::Label(const std::wstring& text, float xpos, float ypos, float size)
{
	mText = std::make_shared<Text>(text, xpos, ypos, 0, size, size, 1.0f, 0.0f, 0.0f);
}

Label::~Label()
{
}

void Label::SetText(const std::wstring& text)
{
	mText->SetText(text);
}

std::wstring Label::GetText()
{
	return mText->GetText();
}

void Label::OnKeyPressed()
{
}

void Label::Update(float elasedTime)
{
}

void Label::OnRender()
{
	if (IsVisible())
	{
		g_pGraphicsManager->GetTextRenderer()->AddText(mText);
	}
}

