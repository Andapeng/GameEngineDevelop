#pragma once
#include <asio.hpp>
#include <map>
using asio::ip::udp;

class GameServer
{
public:
	GameServer();

	void Initialize();
	void Run();
	void Close();

private:

	void Send();
	void Recv();

	void SaveToFile(const std::string& msgString);

	std::shared_ptr<asio::io_context> m_ioContext;
	std::shared_ptr<udp::resolver> m_resolver;
	//std::shared_ptr<udp::endpoint> m_endpoint;
	std::map<std::shared_ptr<udp::endpoint>, int> m_endpointToClientMap;
	std::shared_ptr<udp::socket> m_socket;
};