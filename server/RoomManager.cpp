#include "RoomManager.h"

/***************************************************************
 @ brief: create a new room with given RoomData and an initial user
 [>>] const RoomData& data: the room data of the created room
 [<<] unsigned int: the created room's id
****************************************************************/
unsigned int RoomManager::createRoom(const RoomData& data)
{
	std::lock_guard<std::mutex> lck(this->m_mtxRooms);
	this->m_idCounter++;
	Room newRoom(data);
	this->m_rooms.insert(std::make_pair(this->m_idCounter++, newRoom));
	this->m_rooms[this->m_idCounter - 1].setId(this->m_idCounter - 1);
	return this->m_idCounter - 1;
}

/***************************************************************
 @ brief: deletes a room
 [>>] unsigned int id: the id of the room to be deleted
 [<<] Void
****************************************************************/
void RoomManager::deleteRoom(unsigned int id)
{
	std::lock_guard<std::mutex> lck(this->m_mtxRooms);
	if (this->m_rooms.find(id) != this->m_rooms.end())
	{
		this->m_rooms.erase(id);
	}
	else
	{
		throw RoomDoesNotExistException(id);
	}
}

/***************************************************************
 @ brief: gets the active state of a room
 [>>] unsigned int id: the id of the queried room
 [<<] Void
****************************************************************/
bool RoomManager::getRoomState(unsigned int id)
{
	std::lock_guard<std::mutex> lck(this->m_mtxRooms);
	bool roomState = false;
	if (this->m_rooms.find(id) != this->m_rooms.end())
	{
		roomState = this->m_rooms[id].getData().isActive;
	}
	else
	{
		throw RoomDoesNotExistException(id);
	}
	return roomState;
}

/***************************************************************
 @ brief: sets the active state of a room
 [>>] unsigned int id: the id of the room the state of which is to be set
 [>>] state: the state for the room
 [<<] Void
****************************************************************/
void RoomManager::setRoomState(unsigned int id, bool state)
{
	std::lock_guard<std::mutex> lck(this->m_mtxRooms);
	if (this->m_rooms.find(id) != this->m_rooms.end())
	{
		this->m_rooms[id].setActive(state);
	}
	else
	{
		throw RoomDoesNotExistException(id);
	}
}

/***************************************************************
 @ brief: gets all the room metadatas
 [>>] Void
 [<<] std::vector<RoomData>: the room metadatas
****************************************************************/
std::vector<RoomData> RoomManager::getRoomMetadatas()
{
	std::lock_guard<std::mutex> lck(this->m_mtxRooms);
	std::vector<RoomData> roomMetadatas;
	for (auto& room : this->m_rooms)
	{
		roomMetadatas.push_back(room.second.getData());
	}
	return roomMetadatas;
}

/***************************************************************
 @ brief: get a room with a given id
 [>>] unsigned int id: the queried id
 [<<] Room: the room with the given id
****************************************************************/
Room RoomManager::getRoom(unsigned int id)
{
	std::lock_guard<std::mutex> lck(this->m_mtxRooms);
	if (this->m_rooms.find(id) != this->m_rooms.end())
	{
		return this->m_rooms[id];
	}
	else
	{
		throw RoomDoesNotExistException(id);
	}
}

/***************************************************************
 @ brief: get a room's connected usernames list
 [>>] unsigned int id: the queried room's id
 [<<] std::vector<std::string>: the list of connected usernames (including owner)
****************************************************************/
std::vector<std::string> RoomManager::getRoomPlayerUsernames(unsigned int id)
{
	std::lock_guard<std::mutex> lck(this->m_mtxRooms);
	if (this->m_rooms.find(id) != this->m_rooms.end())
	{
		return this->m_rooms[id].getAllUsernames();
	}
	else
	{
		throw RoomDoesNotExistException(id);
	}
}

/***************************************************************
 @ brief: add a user to a room with a given id
 [>>] unsigned int id: the id of the room to add the user to
 [>>] const LoggedUser& userToAdd: the user to be added
 [<<] Void
****************************************************************/
void RoomManager::addUserToRoom(unsigned int id, const LoggedUser& userToAdd)
{
	std::lock_guard<std::mutex> lck(this->m_mtxRooms);
	if (this->m_rooms.find(id) != this->m_rooms.end())
	{
		return this->m_rooms[id].addUser(userToAdd);
	}
	else
	{
		throw RoomDoesNotExistException(id);
	}
}

/***************************************************************
 @ brief: delete a user from a room with a given id
 [>>] unsigned int id: the id of the room to remove the user from
 [>>] const LoggedUser& userToAdd: the user to be removed
 [<<] Void
****************************************************************/
void RoomManager::deleteUserFromRoom(unsigned int id, const LoggedUser& userToDelete)
{
	std::lock_guard<std::mutex> lck(this->m_mtxRooms);
	if (this->m_rooms.find(id) != this->m_rooms.end())
	{
		return this->m_rooms[id].removeUser(userToDelete);
	}
	else
	{
		throw RoomDoesNotExistException(id);
	}
}

unsigned int RoomManager::getGameId(unsigned int roomId)
{
	std::lock_guard<std::mutex> lck(this->m_mtxRooms);
	if (this->m_rooms.find(roomId) != this->m_rooms.end())
	{
		return this->m_rooms[roomId].getGameId();
	}
	else
	{
		throw RoomDoesNotExistException(roomId);
	}
}

void RoomManager::setGameId(unsigned int roomId, unsigned int gameId)
{
	std::lock_guard<std::mutex> lck(this->m_mtxRooms);
	if (this->m_rooms.find(roomId) != this->m_rooms.end())
	{
		this->m_rooms[roomId].setGameId(gameId);
	}
	else
	{
		throw RoomDoesNotExistException(roomId);
	}
}
