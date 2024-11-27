#pragma once
#include "imgui.h"
#include "../Entities/RenderableObject.h"

class Button : public RenderableObject
{
public:
	Button();
	~Button();

	void OnKeyPressed() override;
	void Update(float elasedTime) override;
	void OnRender() override;
private:
};