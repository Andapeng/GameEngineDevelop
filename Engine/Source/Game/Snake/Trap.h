#pragma once
#include "../../Entities/RenderableObject.h"
class Trap : public RenderableObject
{
public:
    Trap(std::string texture,
         int xpos = 0,
         int ypos = 0,
         int xsize = 50,
         int ysize = 50);
  ~Trap() override;
};