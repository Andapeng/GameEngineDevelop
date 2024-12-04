#include "Button.h"
#include "../Managers/GraphicsManager.h"
#include "../Renderer/ImguiRenderer.h"

Button::Button(const std::string& text, Eigen::Vector2f pos, Eigen::Vector2f size)
{
    mButtonDescription = std::make_shared<ButtonDescription>(text, pos.x(), pos.y(), 0, size.x(), size.y(), 1.0f, 0.0f, 0.0f);
}

Button::~Button()
{
}

void Button::OnKeyPressed()
{
}

void Button::Update(float elasedTime)
{

}

void Button::OnRender()
{
    g_pGraphicsManager->GetImguiRenderer()->AddButton(mButtonDescription);
}
