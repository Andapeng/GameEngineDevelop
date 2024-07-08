#pragma once

#include <map>
#include <string>
class BillBoard
{
public:
	void AddHighestScore(const std::string& UserName, int Score);

private:
	std::map<std::string, int> HighestScores;
};

