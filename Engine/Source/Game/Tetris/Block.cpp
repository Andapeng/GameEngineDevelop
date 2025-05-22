#include "Block.h"

Block::Block(std::string texture, int xpos, int ypos, int xsize, int ysize, Eigen::Vector3f color)
    : RenderableObject(texture, xpos, ypos, 0.01f, xsize, ysize, color)
{
}

void Block::OnRender()
{
    RenderableObject::OnRender();
}
