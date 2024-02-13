#include "Room.h"

/***************************************************************
 @ brief: empty ctor for Room
 [>>] Void
 [<<] X
****************************************************************/
Room::Room()
{
}

/***************************************************************
 @ brief: ctor for room (given metadata)
 [>>] const RoomData& data: the metadata for the room
 [<<] X
****************************************************************/
Room::Room(const RoomData& data)
{
	this->m_metadata = data;
}

/***************************************************************
 @ brief: add a LoggedUser to the room member vector
 [>>] const LoggedUser& user: the user to be added to the room
 [<<] Void
****************************************************************/
void Room::addUser(const LoggedUser& user)
{
	if (this->getAmountOfPlayers() >= this->getData().maxPlayers)
	{
		throw RoomMaxPlayersLimitReachedException(this->getData().maxPlayers);
	}
	else
	{
		this->m_users.push_back(user);
	}
}

/***************************************************************
 @ brief: remove a LoggedUser from the room member vector
 [>>] const LoggedUser& user: the user to be removed from the room
 [<<] Void
 NOTE: you cannot remove the owner this way, only way to remove the owner is to disband the room
****************************************************************/
void Room::removeUser(const LoggedUser& user)
{
	for (size_t i = 0; i < this->m_users.size(); i++)
	{
		if (this->m_users[i].getUsername() == user.getUsername())
		{
			m_users.erase(this->m_users.begin() + i);
			break;
		}
	}
}

/***************************************************************
 @ brief: setter for the id stored in the room metadata
 [>>] unsigned int id: the id for the room
 [<<] Void
****************************************************************/
void Room::setId(unsigned int id)
{
	this->m_metadata.id = id;
}

/***************************************************************
 @ brief: get a vector of all the usernames of the users logged to the room (NOTE: this includes the owner)
 [>>] const LoggedUser& user: the user to be removed from the room
 [<<] Void
****************************************************************/
std::vector<std::string> Room::getAllUsernames() const
{
	std::vector<std::string> loggedUsernames;
	for (auto& user : this->m_users)
	{
		loggedUsernames.push_back(user.getUsername());
	}
	loggedUsernames.push_back(this->m_metadata.owner.getUsername());
	return loggedUsernames;
}

RoomData Room::getData() const
{
	return this->m_metadata;
}

void Room::setActive(bool isActive)
{
	this->m_metadata.isActive = isActive;
}

unsigned int Room::getAmountOfPlayers() const
{
	return this->m_users.size() + 1;
}

void Room::setGameId(unsigned int gameId)
{
	this->m_gameId = gameId;
}

unsigned int Room::getGameId() const
{
	return this->m_gameId;
}
