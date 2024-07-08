#pragma once
#include "IManager.h"
class StatisticsManager : public IManager
{
public:
	static StatisticsManager* Get();

	void UpdateFPS(float elapsedTime);
	int GetFPS();
	int GetPing();

	// Í¨¹ý IManager ¼Ì³Ð
	virtual int Initialize() override;
	virtual void Release() override;
	virtual void Tick() override;


private:
	StatisticsManager();
	static StatisticsManager* m_statisticsMgr;
	float m_elapsedTime;
	int m_frameCount;
	int m_fps;
};

extern StatisticsManager* g_pStatisticsManager;