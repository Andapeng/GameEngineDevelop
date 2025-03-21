#pragma once
#include "../../Entities/RenderableObject.h"
class Brick : public RenderableObject
{
public:
	Brick(std::string texture, int xpos = 0, int ypos = 0, int xsize = 50, int ysize = 50, Eigen::Vector3f color = {1.0f, 1.0f, 1.0f});

	virtual void OnRender() override;
	void SetSolid(bool bIsSolid) { mIsSolid = bIsSolid; }
	void SetDestroyed(bool bIsDestroyed) { mIsDestroyed = bIsDestroyed; }
	bool IsSolid() { return mIsSolid; }
	bool IsDestroyed() { return mIsDestroyed; }

private:
	bool mIsSolid = false;
	bool mIsDestroyed = false;
};

