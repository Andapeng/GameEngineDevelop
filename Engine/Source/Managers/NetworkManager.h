#pragma once
#include "IManager.h"
#include <string>

class UdpSocketClient;

class NetworkManager
	: public IManager
{
public:

	int Initialize() override;
	void Tick() override;
	void Release() override;

	void Upload(std::string content);

	static NetworkManager* Get();
private:
	NetworkManager() = default;
	~NetworkManager() = default ;
	//管理多个connection
	UdpSocketClient* m_udpSocketClient = nullptr;

	static NetworkManager* m_singleNetworkManager;
};

extern NetworkManager* g_pNetworkManager;