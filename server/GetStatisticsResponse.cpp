#include "GetStatisticsResponse.h"

using namespace Responses;

const char* GetStatisticsResponse::k_userStats = "user_stats";
const char* GetStatisticsResponse::k_highscores = "highscores";

/***************************************************************
 @ brief: nlohmann to_json for GetStatisticsResponse
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const GetStatisticsResponse& getStatsResponseToConvert)
{
	outputJson = json{ { GetStatisticsResponse::k_userStats, getStatsResponseToConvert.userStats },
					   { GetStatisticsResponse::k_highscores , getStatsResponseToConvert.highscores } };
}

/***************************************************************
 @ brief: nlohmann from_json for GetStatisticsResponse
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, GetStatisticsResponse& outputGetStatsResponse)
{
	jsonToConvert.at(GetStatisticsResponse::k_userStats).get_to(outputGetStatsResponse.userStats);
	jsonToConvert.at(GetStatisticsResponse::k_highscores).get_to(outputGetStatsResponse.highscores);
}
