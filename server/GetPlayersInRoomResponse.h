#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Responses
{
	typedef struct GetPlayersInRoomResponse
	{
		static const char* k_room_player_list;
		std::vector<std::string> players;
	} GetPlayersInRoomResponse;
	void to_json(json& outputJson, const GetPlayersInRoomResponse& getPlayersInRoomResponseToConvert);
	void from_json(const json& jsonToConvert, GetPlayersInRoomResponse& outputGetPlayersInRoomResponse);
}
