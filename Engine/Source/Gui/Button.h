#pragma once
#include "imgui.h"
#include "../Entities/RenderableObject.h"
#include "ButtonDescript.h"

class Button : public RenderableObject
{
public:
	Button(const std::string& text, Eigen::Vector2f pos, Eigen::Vector2f size);
	~Button();

	void OnKeyPressed() override;
	void Update(float elasedTime) override;
	void OnRender() override;
private:
	std::shared_ptr<ButtonDescription> mButtonDescription;
	bool bClicked = false;
	bool bHidden = false;
};