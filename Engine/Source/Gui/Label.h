#pragma once
#include <string>
#include "../Entities/RenderableObject.h"

class Label : public RenderableObject
{
public:
	Label(const std::wstring& text, float xpos, float ypos, float size);
	~Label() override;

	void SetText(const std::wstring& text);
	const std::wstring& GetText();

	void OnKeyPressed() override;
	void Update(float elasedTime) override;
	void OnRender() override;
private:
	float m_xPos;
	float m_yPos;
	float m_size;
	Eigen::Vector3f m_color;
	std::wstring m_text;
};