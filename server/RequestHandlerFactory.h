#pragma once

#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "IDatabase.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"
#include "GameManager.h"
#include <mutex>

class MenuRequestHandler;
class LoginRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;
class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);
	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	GameManager& getGameManager();
	StatisticsManager& getStatisticsManager();
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(const LoggedUser& loggedUser);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(const LoggedUser& loggedUser, unsigned int roomId);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(const LoggedUser& loggedUser, unsigned int roomId);
	GameRequestHandler* createGameRequestHandler(const LoggedUser& loggedUser, unsigned int roomId);
	void setDatabase(IDatabase* database);
private:
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	GameManager m_gameManager;
	StatisticsManager m_statisticsManager;
	IDatabase* m_database;

};

