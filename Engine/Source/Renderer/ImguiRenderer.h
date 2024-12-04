#pragma once
#include <memory>
#include <vector>

class ButtonDescription;

class ImguiRenderer
{
public:
	void Initialize();
	void Release();

	void AddButton(std::shared_ptr<ButtonDescription> button);
	void Clear();

	void OnRender();
private:
	std::vector<std::shared_ptr<ButtonDescription>> mButtons;
};
