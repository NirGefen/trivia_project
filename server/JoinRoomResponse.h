#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Responses
{
	typedef struct JoinRoomResponse
	{
		static const char* k_status;
		unsigned int status;
	} JoinRoomResponse;
	void to_json(json& outputJson, const JoinRoomResponse& joinRoomResponseToConvert);
	void from_json(const json& jsonToConvert, JoinRoomResponse& outputJoinRoomResponse);
}
