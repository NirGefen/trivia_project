#pragma once

#include <string>
#include "UserStatistics.h"
#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Responses
{
	typedef struct GetStatisticsResponse
	{
		static const char* k_userStats; // containes serialized user stats
		static const char* k_highscores;// containes array of serialized user stats
		UserStatistics userStats;
		std::vector<UserStatistics> highscores;
	} GetStatisticsResponse;
	void to_json(json& outputJson, const GetStatisticsResponse& getStatsResponseToConvert);
	void from_json(const json& jsonToConvert, GetStatisticsResponse& outputGetStatsResponse);
}
