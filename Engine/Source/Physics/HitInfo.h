#pragma once
class HitInfo
{
public:
	HitInfo();
	bool IsHit() { return mHit; }
private:
	bool mHit;
};