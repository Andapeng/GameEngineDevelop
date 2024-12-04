#pragma once
#include <string>
#include "../../Entities/RenderableObject.h"

class Ball : public RenderableObject
{
public:
    Ball(std::string texture, int xpos = 0, int ypos = 0, int xsize = 50, int ysize = 50, Eigen::Vector3f color = { 1.0f, 1.0f, 1.0f });

private:
    // ball state	
    float     Radius;
    bool      Stuck;
};
