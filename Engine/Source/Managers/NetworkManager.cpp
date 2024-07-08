#include "NetworkManager.h"
#include "../Network/NetworkClient.h"

NetworkManager* NetworkManager::m_singleNetworkManager = nullptr;

int NetworkManager::Initialize()
{
    if (m_udpSocketClient == nullptr)
    {
        m_udpSocketClient = new UdpSocketClient;
    }

    if (m_udpSocketClient != nullptr)
    {
        m_udpSocketClient->Initialize();
    }

    return 0;
}

void NetworkManager::Tick()
{
}

void NetworkManager::Release()
{
}

void NetworkManager::Upload(std::string content)
{
    assert(m_udpSocketClient);
    m_udpSocketClient->SendMessages(content);
}

NetworkManager* NetworkManager::Get()
{
    if (m_singleNetworkManager == nullptr)
    {
        m_singleNetworkManager = new NetworkManager;
    }
    return m_singleNetworkManager;
}
