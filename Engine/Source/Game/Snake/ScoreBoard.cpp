#include "ScoreBoard.h"
#include "../../Renderer/TextRenderer.h"
#include "../../Managers/Managers.h"

static const std::wstring hintWord = L"ตรทึ";
bool ScoreBoard::show()
{
	TextRenderer* textRenderer = g_pGraphicsManager->GetTextRenderer();
	textRenderer->RenderText(hintWord + std::to_wstring(mScore), 0.0f, 10.0f, 1.0f, Eigen::Vector3f(1.0f, 0.0f, 0.0f));
	return true;
}

void ScoreBoard::AddPoint()
{
	mScore += 50;
}

void ScoreBoard::OnRender()
{
	show();
}
