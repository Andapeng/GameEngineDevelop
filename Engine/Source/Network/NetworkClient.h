#pragma once
#include <asio.hpp>
#include <memory>

class NetworkMessage;

class UdpSocketClient
{
public:
	UdpSocketClient();
	~UdpSocketClient();
	void Initialize();

	bool SendMessages(const NetworkMessage& msg);
	bool SendMessages(const std::string& msg);

	void Close();
private:
	
	std::shared_ptr<asio::io_context> m_ioContext;
	std::shared_ptr<asio::ip::udp::resolver> m_resolver;
	std::shared_ptr<asio::ip::udp::endpoint> m_destinationEndpoint;
	std::shared_ptr<asio::ip::udp::socket> m_socket;

	size_t Send(const std::string& msg);
	size_t Recv(std::string msg);
};
