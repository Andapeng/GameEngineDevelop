#include "NetworkClient.h"
#include <array>
#include <fmt/printf.h>

using asio::ip::udp;

NetworkClient::NetworkClient()
{
}
NetworkClient::~NetworkClient()
{
}
void NetworkClient::Initialize()
{
	m_ioContext = std::make_shared<asio::io_context>();
	m_resolver = std::make_shared<udp::resolver>(*m_ioContext);
	m_socket = std::make_shared<udp::socket>(*m_ioContext);
	m_endpoint = std::make_shared <udp::endpoint>(asio::ip::address::from_string("127.0.0.1"), 55556);
}

void NetworkClient::Send()
{
	m_socket->open(udp::v4());
	std::string send_buf = "hello world\n";
	m_socket->send_to(asio::buffer(send_buf), *m_endpoint);
	fmt::printf(send_buf.c_str());
	
}

void NetworkClient::Recv()
{
}