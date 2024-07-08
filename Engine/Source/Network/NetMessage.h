#pragma once
#include <string>

class NetworkMessage
{
public:
	NetworkMessage() = default;
	~NetworkMessage() = default;

	NetworkMessage(const std::string& msg);



private:
	std::string m_msg;
};
