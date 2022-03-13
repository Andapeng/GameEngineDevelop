#pragma once
#include <string>

class Label
{
public:
	Label(const char* text, int xpos, int ypos, int size);
private:
	std::string mText;
};