#pragma once
#include "../../Entities/RenderableObject.h"
class Block : public RenderableObject
{
  public:
    Block(std::string texture,
          int xpos = 0,
          int ypos = 0,
          int xsize = 50,
          int ysize = 50,
          Eigen::Vector3f color = { 1.0f, 1.0f, 1.0f });
    ~Block() override = default;
    void OnRender() override;

};