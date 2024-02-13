#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Responses
{
	typedef struct StartGameResponse
	{
		static const char* k_status;
		unsigned int status;
	} StartGameResponse;
	void to_json(json& outputJson, const StartGameResponse& startGameResponseToConvert);
	void from_json(const json& jsonToConvert, StartGameResponse& outputStartGameResponse);
}
