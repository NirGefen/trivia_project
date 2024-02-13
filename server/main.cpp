#pragma once
#pragma comment (lib, "ws2_32.lib")

#include <WinSock2.h>
#include "WSAInitializer.h"
#include "Server.h"
#include <iostream>
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "QueryFailureException.h"


int main()
{
	try
	{
		WSAInitializer wasInit;
		Server server;
		server.run();
	}
	catch (QueryFailureException& e)  // should never happen!
	{
		std::cerr << "CRITICAL: QUERY FAILED IN DATABASE, ERROR: " << e.what() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Unknown Exception :(" << std::endl;
	}
	return 0;
}