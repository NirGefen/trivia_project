#pragma once
#include <string>
#include "LoggedUser.h"
#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

#define MAX_ROOM_NAME_LENGTH 24
#define MAX_ROOM_MAX_PLAYERS 9
#define MAX_ROOM_AMOUNT_OF_QUESTION 99
#define MAX_ROOM_SECONDS_PER_QUESTION 99
namespace Other
{
	typedef struct RoomData
	{
		static const char* k_roomId;
		static const char* k_roomName;
		static const char* k_ownerUsername;
		static const char* k_maxPlayers;
		static const char* k_secondsPerQuestion;
		static const char* k_isActive;
		static const char* k_numOfQuestionsInGame;
		unsigned int id;
		std::string roomName;
		LoggedUser owner;
		unsigned int maxPlayers;
		double secondsPerQuestion;
		bool isActive;
		unsigned int numOfQuestionsInGame;
	} RoomData;
	void to_json(json& outputJson, const RoomData& roomDataToConvert);
	void from_json(const json& jsonToConvert, RoomData& outputRoomData);

}
