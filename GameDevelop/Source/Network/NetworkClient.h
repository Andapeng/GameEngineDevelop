#pragma once
#include <asio.hpp>
#include <memory>

class NetworkClient
{
public:
	NetworkClient();
	~NetworkClient();
	void Initialize();
	void Send();
	void SendScore(int score);
	void Recv();

private:
	
	std::shared_ptr<asio::io_context> m_ioContext;
	std::shared_ptr<asio::ip::udp::resolver> m_resolver;
	std::shared_ptr<asio::ip::udp::endpoint> m_endpoint;
	std::shared_ptr<asio::ip::udp::socket> m_socket;

	
};