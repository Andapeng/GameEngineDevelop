#include "ImguiRenderer.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "GLAD/glad.h"
#include "imgui-sfml/imgui-SFML.h"
#include "../Managers/WindowManager.h"
#include "../Gui/ButtonDescript.h"

void ImguiRenderer::Initialize()
{
	
}

void ImguiRenderer::Release()
{
	
}

void ImguiRenderer::AddButton(std::shared_ptr<ButtonDescription> button)
{
	if (button != nullptr)
	{
		mButtons.push_back(button);
	}
}

void ImguiRenderer::Clear()
{
	mButtons.clear();
}

void ImguiRenderer::OnRender()
{
	ImGui_ImplOpenGL3_NewFrame();
	int width, height;
	g_pWindowManager->GetMainWindowSize(width, height);
	ImGui::SetNextWindowPos({ 0.0f, 0.0f });
	ImGui::SetNextWindowSize(ImVec2(width, height));
	// Start the Dear ImGui frame
	ImGui::Begin("Hello, world!", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize);

	for (const auto& button : mButtons)
	{
		ImGui::SetCursorPos(ImVec2(button->GetPosX(), button->GetPosY()));
		if (ImGui::Button(button->GetText().c_str(), { button->GetSizeX(), button->GetSizeY() }))
		{
			button->Click();
		}
	}

	ImGui::End();
}

