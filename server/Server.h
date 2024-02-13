/************************************************************
@ File: Server.h
@ Description: TODO
*************************************************************/

#pragma once

// INCLUDES
#include "include/nlohmann/json.hpp"
#include "Communicator.h"
#include <thread>
#include <fstream>
#include "TriviaQuestionsApi.h"
#include <iostream>
#include "ServerConfigurationLoadFileException.h"
#include "ServerConfigurationMissingKeyException.h"
#include "ServerConfigurationInvalidJsonException.h"
#include "configConstants.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"
#include "SqliteDatabase.h"
#include "QueryFailureException.h"

// USINGS
using json = nlohmann::json;

// DEFINE CONSTANTS
#define SERVER_CONFIGURATION_FILE_NAME "server_conf.json"

class Server
{
public:
	Server();
	~Server();
	void run();
private:
	Communicator m_communicator;
	json m_config;
	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;

	void m_loadConfig();
};

	
