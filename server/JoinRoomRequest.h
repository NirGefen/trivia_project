#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Requests
{
	typedef struct JoinRoomRequest
	{
		static const char* k_roomId;
		unsigned int roomId;
	} JoinRoomRequest;
	void to_json(json& outputJson, const JoinRoomRequest& JoinRoomRequestToConvert);
	void from_json(const json& jsonToConvert, JoinRoomRequest& outputJoinRoomRequest);
}
