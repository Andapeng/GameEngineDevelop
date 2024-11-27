#include "Button.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "GLAD/glad.h"
#include "imgui-sfml/imgui-SFML.h"

Button::Button()
{

}

Button::~Button()
{
}

void Button::OnKeyPressed()
{
}

void Button::Update(float elasedTime)
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Hello, world!");
    if(ImGui::Button("Close Me"))
    {
        ImGui::Text("Yes!");
    }
    ImGui::End();

}

void Button::OnRender()
{
}
