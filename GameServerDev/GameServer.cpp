#include "GameServer.h"
#include <fmt/printf.h>
#include <boost/log/trivial.hpp>
#include <iostream>
#include <exception>
#include "FileHelper.h"

#ifdef _DEBUG
#pragma comment(lib,"fmtd.lib")
#else
#pragma comment(lib,"fmt.lib")
#endif

const std::string NET_IP = "127.0.0.1";
constexpr int NET_PORT = 55556;

GameServer::GameServer()
{
}

void GameServer::Initialize()
{
	try {
		m_ioContext = std::make_shared<asio::io_context>();
		m_socket = std::make_shared<udp::socket>(*m_ioContext, udp::endpoint(asio::ip::address::from_string(NET_IP), NET_PORT));
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void GameServer::Run()
{
	try {
		char recv_buf[100] = { 0 };
		for (;;)
		{
			udp::endpoint promote_endpoint;
			m_socket->receive_from(asio::buffer(recv_buf), promote_endpoint);
			FileHelper::SaveContentToFile("HigestScore.txt", recv_buf);
			fmt::printf(recv_buf);
		}
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void GameServer::Close()
{
}

void GameServer::Send()
{
}

void GameServer::Recv()
{
}

void GameServer::SaveToFile(const std::string& msgString)
{
	

}
