#include "BillBoard.h"
void BillBoard::AddHighestScore(const std::string& UserName, int Score)
{
	if (HighestScores.find(UserName) == HighestScores.end())
	{
		HighestScores[UserName] = Score;
	}
	else
	{
		if (HighestScores[UserName] < Score)
		{
			HighestScores[UserName] = Score;
		}
	}
}
