#include "UserStatistics.h"

using namespace Responses;

const char* UserStatistics::k_averageAnswerTime = "average_answer_time";
const char* UserStatistics::k_totalAnswers = "total_answers";
const char* UserStatistics::k_totalCorrectAnswers = "total_correct_answers";
const char* UserStatistics::k_totalGamesPlayed = "total_games_played";
const char* UserStatistics::k_score = "score";
const char* UserStatistics::k_username = "username";

/***************************************************************
 @ brief: nlohmann to_json for UserStatistics
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const UserStatistics& userStatsToConvert)
{
	outputJson = json{ { UserStatistics::k_averageAnswerTime, userStatsToConvert.averageAnswerTime },
					   { UserStatistics::k_totalAnswers, userStatsToConvert.totalAnswers },
					   { UserStatistics::k_totalCorrectAnswers, userStatsToConvert.totalCorrectAnswers },
					   { UserStatistics::k_totalGamesPlayed, userStatsToConvert.totalGamesPlayed },
					   { UserStatistics::k_score, userStatsToConvert.score },
					   { UserStatistics::k_username, userStatsToConvert.username } };
}

/***************************************************************
 @ brief: nlohmann from_json for UserStatistics
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, UserStatistics& outputUserStats)
{
	jsonToConvert.at(UserStatistics::k_averageAnswerTime).get_to(outputUserStats.averageAnswerTime);
	jsonToConvert.at(UserStatistics::k_totalAnswers).get_to(outputUserStats.totalAnswers);
	jsonToConvert.at(UserStatistics::k_totalCorrectAnswers).get_to(outputUserStats.totalCorrectAnswers);
	jsonToConvert.at(UserStatistics::k_totalGamesPlayed).get_to(outputUserStats.totalGamesPlayed);
	jsonToConvert.at(UserStatistics::k_score).get_to(outputUserStats.score);
	jsonToConvert.at(UserStatistics::k_username).get_to(outputUserStats.username);
}
