#pragma once
#include <string>
#include <memory>
#include "../Entities/RenderableObject.h"
#include "../Entities/Text.h"
class Label : public RenderableObject
{
public:
	Label(const std::wstring& text, float xpos, float ypos, float size);
	~Label() override;

	void SetText(const std::wstring& text);
	std::wstring GetText();

	void OnKeyPressed() override;
	void Update(float elasedTime) override;
	void OnRender() override;
private:

	std::shared_ptr<Text> mText;
};