#include "ScoreBoard.h"
#include "Renderer/TextRenderer.h"
#include "Managers/Managers.h"
#include <nlohmann/json.hpp>

static const std::wstring hintWord = L"ตรทึ";
bool ScoreBoard::show()
{
	TextRenderer* textRenderer = g_pGraphicsManager->GetTextRenderer();
	textRenderer->RenderText(hintWord + std::to_wstring(m_score), 0.0f, 10.0f, 1.0f, Eigen::Vector3f(1.0f, 0.0f, 0.0f));
	return true;
}

void ScoreBoard::OnKeyPressed()
{
	if (g_pInputManager->IsKeyPressed("Upload"))
	{
		UploadHighestScore();
	}
}

ScoreBoard::ScoreBoard()
	: m_score(0)
	, m_highestScore(0)
{
}

ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::AddPoint()
{
	m_score += 50;
	if (m_score > m_highestScore)
	{
		m_highestScore = m_score;
	}
}

void ScoreBoard::OnRender()
{
	show();
}

void ScoreBoard::Clear()
{
	m_score = 0;
}

void ScoreBoard::UploadHighestScore()
{
	nlohmann::json highestScore;
	highestScore["UserName"] = "Anonymous";
	highestScore["HighestScore"] = m_score;
	g_pNetworkManager->Upload(highestScore.dump());
}

int ScoreBoard::GetScore()
{
	return m_score;
}
