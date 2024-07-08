#include "NetworkClient.h"
#include <array>
#include <boost/log/trivial.hpp>
#include <fmt/printf.h>

#include "NetMessage.h"

using asio::ip::udp;

const std::string NET_IP = "127.0.0.1";
constexpr int NET_DESTINATION_PORT = 55556;

UdpSocketClient::UdpSocketClient()
{
}
UdpSocketClient::~UdpSocketClient()
{
}
void UdpSocketClient::Initialize()
{
	m_ioContext = std::make_shared<asio::io_context>();
	m_resolver = std::make_shared<udp::resolver>(*m_ioContext);
	m_socket = std::make_shared<udp::socket>(*m_ioContext);
	m_destinationEndpoint = std::make_shared <udp::endpoint>(asio::ip::address::from_string(NET_IP), NET_DESTINATION_PORT);

	m_socket->open(udp::v4());
}

bool UdpSocketClient::SendMessages(const NetworkMessage& msg)
{
	return false;
}

bool UdpSocketClient::SendMessages(const std::string& msg)
{
	if (!Send(msg))
	{
		BOOST_LOG_TRIVIAL(error) << "UdpSocketClient SendMessages failed. ";
		return false;
	}
	return true;
}

void UdpSocketClient::Close()
{
	m_socket->close();
}

size_t UdpSocketClient::Send(const std::string& msg)
{
	const size_t ret = m_socket->send_to(asio::buffer(msg), *m_destinationEndpoint);
	if (ret > 0)
	{
		BOOST_LOG_TRIVIAL(info) << msg;
	}
	else
	{
		BOOST_LOG_TRIVIAL(error) << "UdpSocketClient Send failed. ";
	}
	return ret;
}

size_t UdpSocketClient::Recv(std::string msg)
{
	const size_t ret = m_socket->receive_from(asio::buffer(msg), *m_destinationEndpoint);
	if (ret > 0)
	{
		BOOST_LOG_TRIVIAL(info) << msg;
	}
	else
	{
		BOOST_LOG_TRIVIAL(error) << "Client Receive Message failed. ";
	}
	return ret;
}