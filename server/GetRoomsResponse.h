#pragma once
#include <string>
#include "Room.h"

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Responses
{
	typedef struct GetRoomsResponse
	{
		static const char* k_room_list;
		std::vector<RoomData> rooms;
	} GetRoomsResponse;
	void to_json(json& outputJson, const GetRoomsResponse& getRoomsResponseToConvert);
	void from_json(const json& jsonToConvert, GetRoomsResponse& outputGetRoomsResponse);
}
