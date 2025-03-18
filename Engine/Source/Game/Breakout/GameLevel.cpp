#include "GameLevel.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <Eigen/Eigen>

void GameLevel::Load(const char* file, unsigned levelWidth, unsigned levelHeight)
{
	// clear old data
    this->mBricks.clear();
    // load from file
    std::string tileCode;
    GameLevel level;
    std::string line;
    std::ifstream in(file);
    if (in.is_open())
    {
        std::vector<std::vector<unsigned int>> tileData;
        while (std::getline(in, line)) // read each line from level file
        {
            std::stringstream ss(line);
            std::vector<unsigned int> row;
            while (ss >> tileCode) // read each word separated by spaces
                row.push_back(std::stoi(tileCode));
            tileData.push_back(row);
        }
        if (!tileData.empty())
        {
            this->init(tileData, levelWidth, levelHeight);
            mLevelFile = file;
            mLevelWidth = levelWidth;
            mLevelHeight = levelHeight;
        }
    }
}

void GameLevel::Reload()
{
    if (!mLevelFile.empty())
    {
        Load(mLevelFile.c_str(), mLevelWidth, mLevelHeight);
    }
}

bool GameLevel::IsCompleted()
{
    for (const auto& tile : this->mBricks)
        if (!tile->IsSolid() && !tile->IsDestroyed())
            return false;
    return true;
}

void GameLevel::OnRender()
{
    for (const auto& tile : this->mBricks)
    {
        tile->OnRender();
    }
}

void GameLevel::init(std::vector<std::vector<unsigned>> tileData, unsigned levelWidth, unsigned levelHeight)
{
    // calculate dimensions
    size_t height = tileData.size();
    size_t width = tileData[0].size(); // note we can index vector at [0] since this function is only called if height > 0
    float unitWidth = levelWidth / static_cast<float>(width), unit_height = levelHeight / height;
    // initialize level tiles based on tileData		
    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            // check block type from level data (2D level array)
            if (tileData[y][x] == 1) // solid
            {
                Eigen::Vector2f pos(unitWidth * x, unit_height * y);
                Eigen::Vector2f size(unitWidth, unit_height);
                std::shared_ptr<Brick> obj = std::make_shared<Brick>("block_solid", pos.x(), pos.y(), size.x(), size.y(), Eigen::Vector3f{0.8f, 0.8f, 0.7f});
                obj->SetSolid(true);
                mBricks.push_back(obj);
            }
            else if (tileData[y][x] > 1)	// non-solid; now determine its color based on level data
            {
                Eigen::Vector3f color = Eigen::Vector3f(1.0f, 1.0f, 1.0f); // original: white
                if (tileData[y][x] == 2)
                    color = Eigen::Vector3f(0.2f, 0.6f, 1.0f);
                else if (tileData[y][x] == 3)
                    color = Eigen::Vector3f(0.0f, 0.7f, 0.0f);
                else if (tileData[y][x] == 4)
                    color = Eigen::Vector3f(0.8f, 0.8f, 0.4f);
                else if (tileData[y][x] == 5)
                    color = Eigen::Vector3f(1.0f, 0.5f, 0.0f);

                Eigen::Vector2f pos(unitWidth * x, unit_height * y);
                Eigen::Vector2f size(unitWidth, unit_height);
                mBricks.push_back(std::make_shared<Brick>("block", pos.x(), pos.y(), size.x(), size.y(), color));
            }
        }
    }
}
