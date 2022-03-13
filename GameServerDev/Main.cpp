#include "GameServer.h"

int main()
{
	GameServer server;
	server.Initialize();
	server.Run();
	server.Close();
}