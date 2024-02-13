#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) :
	m_database(database), m_loginManager(database), m_statisticsManager(database), m_gameManager(database)
{
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}

GameManager& RequestHandlerFactory::getGameManager()
{
	return this->m_gameManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_statisticsManager;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(const LoggedUser& loggedUser)
{
	return new MenuRequestHandler(*this, loggedUser);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(const LoggedUser& loggedUser, unsigned int roomId)
{
	return new RoomAdminRequestHandler(*this, loggedUser, roomId);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(const LoggedUser& loggedUser, unsigned int roomId)
{
	return new RoomMemberRequestHandler(*this, loggedUser, roomId);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(const LoggedUser& loggedUser, unsigned int roomId)
{
	return new GameRequestHandler(*this, loggedUser, roomId);
}

void RequestHandlerFactory::setDatabase(IDatabase* database)
{
	this->m_database = database;
	this->m_loginManager.setDatabase(database);
	this->m_statisticsManager.setDatabase(database);
	this->m_gameManager.setDatabase(database);
}
