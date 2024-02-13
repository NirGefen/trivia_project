#include "Server.h"

/***************************************************************
 @ brief: a ctor for the Server class
 [>>] Void
 [<<] X
****************************************************************/
Server::Server() :
	m_database(new SqliteDatabase()), m_handlerFactory(nullptr), m_communicator(&this->m_config, this->m_handlerFactory)
{
	this->m_loadConfig();
	m_handlerFactory.setDatabase(this->m_database);

}

/***************************************************************
 @ brief: a dtor for the Server class
 [>>] Void
 [<<] X
****************************************************************/
Server::~Server()
{
	if (this->m_database != nullptr)
	{
		delete this->m_database;
	}
}

/***************************************************************
 @ brief: a method that starts up the server
 [>>] Void
 [<<] Void
 Note: contains a simple development console.
****************************************************************/
void Server::run()
{
	const std::string exitCommand = "EXIT";
	const std::string addCommand = "ADD";

	std::string currentCommand = "";
	std::vector<std::string> commandArgs;
	unsigned int amountToAdd = 0;
	std::thread t_communicator = std::thread(&Communicator::startHandleRequests, &this->m_communicator);
	t_communicator.detach();
	bool addValidArg = false;
	while (currentCommand != exitCommand)
	{
		std::getline(std::cin, currentCommand);
		std::istringstream iss(currentCommand);
		commandArgs = std::vector<std::string>(std::istream_iterator<std::string>(iss), {});
		if (commandArgs.size() == 2 && commandArgs[0] == addCommand) // temp interface for now
		{
			addValidArg = true;
			try
			{
				amountToAdd = std::stoi(commandArgs[1]);
			}
			catch (std::exception& e)
			{
				addValidArg = false;
				std::cerr << "Regular exception caught in server development console: " << e.what() << std::endl;
			}
			catch (...)
			{
				addValidArg = false;
				std::cerr << "unkown exception caught in server development console!" << std::endl;
			}
			if (addValidArg)
			{
				this->m_database->addQuestions(TriviaQuestionsApi::getQuestions(amountToAdd));
			}
		}
	}

}

/***************************************************************
 @ brief: a method that loads the configuration json file of the server
 [>>] Void
 [<<] Void
****************************************************************/
void Server::m_loadConfig()
{
	std::ifstream configFile;
	configFile.open(SERVER_CONFIGURATION_FILE_NAME);
	if (!configFile.is_open() || configFile.fail())
	{
		throw ServerConfigurationLoadFileException(SERVER_CONFIGURATION_FILE_NAME);
	}
	try
	{
		configFile >> this->m_config;
	}
	catch (json::exception & e)
	{
		throw ServerConfigurationInvalidJsonException(SERVER_CONFIGURATION_FILE_NAME, e.what());
	}

}
