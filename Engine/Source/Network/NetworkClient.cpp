#include "NetworkClient.h"
#include "NetMessage.h"
#include "../Log.h"

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
	m_ioContext = new asio::io_context();
	m_resolver = new asio::ip::udp::resolver(*m_ioContext);
	m_socket = new udp::socket(*m_ioContext);
	m_destinationEndpoint = new udp::endpoint(asio::ip::address::from_string(NET_IP), NET_DESTINATION_PORT);

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
		Logger::LogError("UdpSocketClient SendMessages failed. ");
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
		Logger::LogInfo(msg);
	}
	else
	{
		Logger::LogError("UdpSocketClient Send failed. ");
	}
	return ret;
}

size_t UdpSocketClient::Recv(std::string msg)
{
	const size_t ret = m_socket->receive_from(asio::buffer(msg), *m_destinationEndpoint);
	if (ret > 0)
	{
		Logger::LogInfo(msg);
	}
	else
	{
		Logger::LogError("Client Receive Message failed. ");
	}
	return ret;
}