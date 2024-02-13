#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Responses
{
	typedef struct CreateRoomResponse
	{
		static const char* k_status;
		unsigned int status;
	} CreateRoomResponse;
	void to_json(json& outputJson, const CreateRoomResponse& getCreateRoomResponseToConvert);
	void from_json(const json& jsonToConvert, CreateRoomResponse& outputCreateRoomResponse);
}
