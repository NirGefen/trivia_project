#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Responses
{
	typedef struct CloseRoomResponse
	{
		static const char* k_status;
		unsigned int status;
	} CloseRoomResponse;
	void to_json(json& outputJson, const CloseRoomResponse& closeRoomResponseToConvert);
	void from_json(const json& jsonToConvert, CloseRoomResponse& outputCloseRoomResponse);
}
