#include "TetrisGame.h"

#include "Block.h"
#include "../../Managers/Managers.h"
#include "../../RHI/Shader.h"
#include "../../Entities/Camera2D.h"
#include "../../Config/GlobalConfiguration.h"
#include "../../Scene/Scene.h"
#include "../../Renderer/SpriteRenderer.h"
#include "../../Renderer/ImguiRenderer.h"
#include "../../Renderer/TextRenderer.h"

int TetrisGame::Initialize()
{
    // Pre Load Resource
    g_pResourceManager->LoadTexture("Assets/Textures/block_yellow.png", "block_yellow");
    g_pResourceManager->LoadTexture("Assets/Textures/block_red.png", "block_red");
    g_pResourceManager->LoadTexture("Assets/Textures/block_purple.png", "block_purple");
    g_pResourceManager->LoadTexture("Assets/Textures/block_green.png", "block_green");
    g_pResourceManager->LoadTexture("Assets/Textures/block_orange.png", "block_orange");
    g_pResourceManager->LoadTexture("Assets/Textures/block_blue.png", "block_blue");
    g_pResourceManager->LoadTexture("Assets/Textures/block_lightblue.png", "block_lightblue");

    g_pResourceManager->LoadShader(
        "Assets/Shaders/texture.vertex", "Assets/Shaders/texture.fragment", "texture_shader");
    g_pResourceManager->LoadShader("Assets/Shaders/sprite.vertex", "Assets/Shaders/sprite.fragment", "sprite_shader");
    g_pResourceManager->LoadShader("Assets/Shaders/text.vertex", "Assets/Shaders/text.fragment", "text_shader");
    g_pResourceManager->LoadShader(
        "Assets/Shaders/particle.vertex", "Assets/Shaders/particle.fragment", "particle_shader");
    g_pResourceManager->LoadShader(
        "Assets/Shaders/postprocessing.vertex", "Assets/Shaders/postprocessing.fragment", "postprocessing_shader");

    g_pFontManager->LoadFont("Assets/Fonts/simsun.ttc"); // 新宋体

    auto gConfig = Configuration::Get();
    camera = new Camera2D(gConfig->GetWidth(), gConfig->GetHeight());

    // Set Shader Uniform
    g_pResourceManager->GetShader("sprite_shader").Use()->SetInt("texture1", 0);
    g_pResourceManager->GetShader("sprite_shader").SetMatrix4f("projection", camera->GetProjectMatrix());

    g_pResourceManager->GetShader("text_shader").Use()->SetInt("text", 0);
    g_pResourceManager->GetShader("text_shader").SetMatrix4f("projection", camera->GetProjectMatrix());

    g_pResourceManager->GetShader("texture_shader").Use()->SetInt("texture1", 0);

    std::shared_ptr<Block> block = std::make_shared<Block>("block_yellow", 100, 100, 50, 50, Eigen::Vector3f(1.0f, 1.0f, 1.0f));
    std::shared_ptr<Scene> GameScene = std::make_shared<Scene>("GameScene");
    GameScene->AddGameObject("block", block);

    g_pSceneManager->AddScene("GameScene", GameScene);
    mCurrentScene = g_pSceneManager->LoadScene("GameScene");
    Start();
    return 0;
}

int TetrisGame::Tick()
{
    return 0;
}

int TetrisGame::Release()
{
    return 0;
}

void TetrisGame::ProcessInput() {}

void TetrisGame::Render()
{
    g_pGraphicsManager->GetSpriteRenderer()->Clear();
    g_pGraphicsManager->GetTextRenderer()->Clear();
    g_pGraphicsManager->GetImguiRenderer()->Clear();
    for (const auto& obj : mCurrentScene->GetSceneObjects()) {
        obj.second->OnRender();
    }
    g_pGraphicsManager->GetSpriteRenderer()->OnRender();
    g_pGraphicsManager->GetTextRenderer()->OnRender();
    g_pGraphicsManager->GetImguiRenderer()->OnRender();
}

void TetrisGame::Update(float elapsedTime) {}

void TetrisGame::DetectCollide() {}

bool TetrisGame::IsRunning()
{
    return g_pStateManager->IsGameRunning();
}

int TetrisGame::Stop()
{
    g_pStateManager->GameOver();
    return 0;
}

int TetrisGame::Pause()
{
    g_pStateManager->GamePause();
    return 0;
}

int TetrisGame::Start()
{
    g_pStateManager->GameStart();
    return 0;
}
