#pragma once
#include "Entities/RenderableObject.h"
class ScoreBoard : public RenderableObject
{
public:
	ScoreBoard();
	~ScoreBoard() override;

	void AddPoint();
	void Clear();
	void UploadHighestScore();
	int GetScore();

public:
	void OnRender() override;
	void OnKeyPressed() override;

private:
	bool show();

private:
	int m_score;
	int m_highestScore;
};