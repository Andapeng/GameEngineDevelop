#include "StatisticsManager.h"


StatisticsManager* StatisticsManager::m_statisticsMgr = nullptr;

void StatisticsManager::UpdateFPS(float elapsedTime)
{
    m_elapsedTime += elapsedTime;
    m_frameCount++;
    if (m_elapsedTime > 1.0)
    {
        m_fps = m_frameCount;
        m_elapsedTime = 0;
        m_frameCount = 0;
    }
}

int StatisticsManager::GetFPS()
{
    return m_fps;
}

StatisticsManager* StatisticsManager::Get()
{
    if (m_statisticsMgr == nullptr)
    {
        m_statisticsMgr = new StatisticsManager();
    }
    return m_statisticsMgr;
}

int StatisticsManager::Initialize()
{
    m_elapsedTime = 0.0f;
    m_frameCount = 0;
    m_fps = 0;

    return 0;
}

void StatisticsManager::Release()
{
}

void StatisticsManager::Tick()
{
}

StatisticsManager::StatisticsManager()
    : m_elapsedTime(0.0f)
    , m_frameCount(0)
    , m_fps(0)
{
}
