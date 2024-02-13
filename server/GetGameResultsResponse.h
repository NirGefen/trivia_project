#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
#include "PlayerResults.h"
using json = nlohmann::json;

namespace Responses
{
	typedef struct GetGameResultsResponse
	{
		static const char* k_status;
		static const char* k_results;
		unsigned int status;
		std::vector<PlayerResults> results;
	} GetGameResultsResponse;
	void to_json(json& outputJson, const GetGameResultsResponse& getGameResultsResponseToConvert);
	void from_json(const json& jsonToConvert, GetGameResultsResponse& outputGetGameResultsResponse);
}
