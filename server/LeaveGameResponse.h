#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Responses
{
	typedef struct LeaveGameResponse
	{
		static const char* k_status;
		unsigned int status;
	} LeaveGameResponse;
	void to_json(json& outputJson, const LeaveGameResponse& leaveGameResponseToConvert);
	void from_json(const json& jsonToConvert, LeaveGameResponse& outputLeaveGameResponse);
}
