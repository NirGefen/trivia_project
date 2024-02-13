#pragma once
#include <string>
#include "RoomData.h"

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;
using namespace Other;

namespace Responses
{
	typedef struct GetRoomStateResponse
	{
		static const char* k_roomData;
		static const char* k_players;
		RoomData roomData;
		std::vector<std::string> players;

	} GetRoomStateResponse;
	void to_json(json& outputJson, const GetRoomStateResponse& getRoomStateResponseToConvert);
	void from_json(const json& jsonToConvert, GetRoomStateResponse& outputGetRoomStateResponse);
}
