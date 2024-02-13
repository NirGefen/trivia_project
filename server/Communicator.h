/************************************************************
@ File: Communicator.h
@ Description: TODO
*************************************************************/

#pragma once

// INCLUDES
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include <WinSock2.h>
#include "include/nlohmann/json.hpp"
#include <thread>
#include <mutex>
#include "HandshakeException.h"
#include <iostream>
#include <map>
#include "configConstants.h"
#include "SocketManager.h"
#include "RequestResult.h"
#include  "RequestInfo.h"
#include "RequestHandlerFactory.h"

// USINGS
using json = nlohmann::json;

// DEFINES


class Communicator
{
public:
	Communicator(json* pConfig, RequestHandlerFactory& handlerFactory);
	~Communicator();
	void setConfig(json* pConfig);
	void startHandleRequests();
	void handleNewClient(SOCKET clientSock);

private:
	json* m_pConfig;
	RequestHandlerFactory& m_handlerFactory;
	SOCKET m_listeningSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	mutable std::mutex mtx_mClients;
	void bindAndListen();
	void handshake(SOCKET clientSock);
};

