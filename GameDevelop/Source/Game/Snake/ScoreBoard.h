#pragma once
#include "../../Entities/RenderableObject.h"
class ScoreBoard : public RenderableObject
{
public:
	void AddPoint();
	void OnRender() override;

private:
	bool show();

private:
	int mScore;
};