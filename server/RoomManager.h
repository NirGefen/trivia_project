#pragma once
#include <map>
#include <mutex>
#include "Room.h"
#include "RoomDoesNotExistException.h"

class RoomManager
{
public:
	RoomManager() : m_idCounter(0) {};
	unsigned int createRoom(const RoomData& data);
	void deleteRoom(unsigned int id);
	bool getRoomState(unsigned int id);
	void setRoomState(unsigned int id, bool state);
	std::vector<RoomData> getRoomMetadatas();
	Room getRoom(unsigned int id);
	std::vector<std::string> getRoomPlayerUsernames(unsigned int id);
	void addUserToRoom(unsigned int id, const LoggedUser& userToAdd);
	void deleteUserFromRoom(unsigned int id, const LoggedUser& userToDelete);
	unsigned int getGameId(unsigned int roomId);
	void setGameId(unsigned int roomId, unsigned int gameId);
private:
	mutable std::mutex m_mtxRooms;
	std::map<unsigned int, Room> m_rooms;
	unsigned int m_idCounter;
};

