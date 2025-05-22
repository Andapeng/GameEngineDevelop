#pragma once
#include "../../GameInstance.h"

#include <memory>

class Camera2D;
class Scene;

class TetrisGame : public GameInstance
{
  public:
    TetrisGame() = default;
    ~TetrisGame() override = default;

  private:
    // runtime
    int Initialize() override;
    int Tick() override;
    int Release() override;

    // manage event
    void ProcessInput() override;

    // manage render
    void Render() override;

    // game state update
    void Update(float elapsedTime) override;

    // manage physics
    void DetectCollide() override;

    // manage game state
    bool IsRunning();
    int Stop() override;
    int Pause() override;
    int Start() override;

private:
    std::shared_ptr<Scene> mCurrentScene;
    Camera2D* camera = nullptr;
};