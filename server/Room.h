#pragma once
#include <string>
#include <vector>
#include "LoggedUser.h"
#include "RoomData.h"
#include "RoomMaxPlayersLimitReachedException.h"
using namespace Other;

class Room
{
public:
	Room();
	Room(const RoomData& data);
	void addUser(const LoggedUser& user);
	void removeUser(const LoggedUser& user);
	void setId(unsigned int id);
	std::vector<std::string> getAllUsernames() const;
	RoomData getData() const;
	void setActive(bool isActive);
	unsigned int getAmountOfPlayers() const;
	void setGameId(unsigned int gameId);
	unsigned int getGameId() const;
private:
	unsigned int m_gameId;
	RoomData m_metadata;
	std::vector<LoggedUser> m_users; // NOTE: this does not include the owner, the owner is stored in the room metadata.
};

