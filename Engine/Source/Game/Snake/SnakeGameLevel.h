#pragma once
#include <memory>
#include <vector>
#include "../../Entities/RenderableObject.h"
class GameObject;

class SnakeGameLevel : public RenderableObject
{
public:
  void Load(const char* file,
            unsigned int levelWidth,
            unsigned int levelHeight);
  void Reload();
  bool IsCompleted();
  void OnRender() override;
  std::vector<std::shared_ptr<RenderableObject>> GetTraps() { return mTraps; }

private:
  std::vector<std::shared_ptr<RenderableObject>> mTraps;

  	// initialize level from tile data
  void init(std::vector<std::vector<unsigned int>>& tileData,
            unsigned int levelWidth,
            unsigned int levelHeight);

  std::string mLevelFile;
  unsigned int mLevelWidth = 0;
  unsigned int mLevelHeight = 0;
};