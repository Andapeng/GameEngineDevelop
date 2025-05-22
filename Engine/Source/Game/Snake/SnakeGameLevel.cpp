#include "SnakeGameLevel.h"

#include "Trap.h"

#include <fstream>

void SnakeGameLevel::Load(const char* file, unsigned int levelWidth,
  unsigned int levelHeight)
{ // Load level data from file
    // Initialize level with loaded data

    // clear old data
    this->mTraps.clear();

    // load from file
    std::ifstream in(file);
    if (in.is_open()) {
        std::string tileCode;
        std::string line;
        std::vector<std::vector<unsigned int>> tileData;
        while (std::getline(in, line)) // read each line from level file
        {
            std::stringstream ss(line);
            std::vector<unsigned int> row;
            while (ss >> tileCode) // read each word separated by spaces
                row.push_back(std::stoi(tileCode));
            tileData.push_back(row);
        }
        if (!tileData.empty()) {
            this->init(tileData, levelWidth, levelHeight);
            mLevelFile = file;
            mLevelWidth = levelWidth;
            mLevelHeight = levelHeight;
        }
    }
}

void SnakeGameLevel::Reload()
{ // Reload level data from file
}

bool SnakeGameLevel::IsCompleted()
{ // Check if level is completed
  return false;
}

void SnakeGameLevel::OnRender()
{
    for (const auto& tile : this->mTraps) {
        tile->OnRender();
    }
}

void
SnakeGameLevel::init(std::vector<std::vector<unsigned int>>& tileData,
                     unsigned int levelWidth,
                     unsigned int levelHeight)
{ // Initialize level with loaded data
    mLevelWidth = levelWidth;
    mLevelHeight = levelHeight;
    for (unsigned int y = 0; y < tileData.size(); ++y) {
        for (unsigned int x = 0; x < tileData[y].size(); ++x) {
            if (tileData[y][x] == 1) {
                auto trap =
                  std::make_shared<Trap>("mine", x * 50, y * 50, 50, 50);
                mTraps.push_back(trap);
            }
        }
    }
}