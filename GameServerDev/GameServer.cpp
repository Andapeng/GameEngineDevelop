#include "GameServer.h"
#include <fmt/printf.h>
#include <iostream>
#include <exception>

#ifdef _DEBUG
#pragma comment(lib,"fmtd.lib")
#else
#pragma comment(lib,"fmt.lib")
#endif

GameServer::GameServer()
{
}

void GameServer::Initialize()
{
	try {
		m_ioContext = std::make_shared<asio::io_context>();
		//m_resolver = std::make_shared<udp::resolver>(*m_ioContext);
		m_socket = std::make_shared<udp::socket>(*m_ioContext, udp::endpoint(asio::ip::address::from_string("127.0.0.1"), 55556));
		//m_endpoint = std::make_shared <udp::endpoint>(asio::ip::address::from_string("127.0.0.1"), 55556);
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
