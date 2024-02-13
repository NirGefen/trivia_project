#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Responses
{
	typedef struct LeaveRoomResponse
	{
		static const char* k_status;
		unsigned int status;
	} LeaveRoomResponse;
	void to_json(json& outputJson, const LeaveRoomResponse& leaveRoomResponseToConvert);
	void from_json(const json& jsonToConvert, LeaveRoomResponse& outputLeaveRoomResponse);
}
