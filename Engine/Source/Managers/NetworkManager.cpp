#include "NetworkManager.h"
#include "../Network/NetworkClient.h"

NetworkManager* NetworkManager::mSingleNetworkManager = nullptr;

int NetworkManager::Initialize()
{
    if (mUdpSocketClient == nullptr)
    {
        mUdpSocketClient = new UdpSocketClient;
    }

    if (mUdpSocketClient != nullptr)
    {
        mUdpSocketClient->Initialize();
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
    assert(mUdpSocketClient);
    mUdpSocketClient->SendMessages(content);
}

NetworkManager* NetworkManager::Get()
{
    if (mSingleNetworkManager == nullptr)
    {
        mSingleNetworkManager = new NetworkManager;
    }
    return mSingleNetworkManager;
}
