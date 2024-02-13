#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Requests
{
	typedef struct GetPlayersInRoomRequest
	{
		static const char* k_roomId;
		unsigned int roomId;
	} GetPlayersInRoomRequest;
	void to_json(json& outputJson, const GetPlayersInRoomRequest& GetPlayersInRoomRequestToConvert);
	void from_json(const json& jsonToConvert, GetPlayersInRoomRequest& outputGetPlayersInRoomRequest);
}
