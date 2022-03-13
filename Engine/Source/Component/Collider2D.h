#pragma once
class Collider2D
{
public:
	virtual int GetType() { return 1; }
	virtual bool IsType() { return true; }
	virtual void Update() {}

private:

};