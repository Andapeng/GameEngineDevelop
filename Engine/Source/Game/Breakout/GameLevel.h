#pragma once
#include <memory>
#include <vector>
#include "../../Entities/RenderableObject.h"
#include "Brick.h"
class GameObject;

class GameLevel : public RenderableObject
{
public:
	void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
	bool IsCompleted();

	void OnRender() override;
private:
	// initialize level from tile data
	void init(std::vector<std::vector<unsigned int>> tileData,
		unsigned int levelWidth, unsigned int levelHeight);

	std::vector<std::shared_ptr<Brick>> mBricks;
};
