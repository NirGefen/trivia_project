#pragma once

#include <string>

#include "UserStatistics.h"
#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Responses
{
	typedef struct UserStatistics
	{
		static const char* k_averageAnswerTime;
		static const char* k_totalAnswers;
		static const char* k_totalCorrectAnswers;
		static const char* k_totalGamesPlayed;
		static const char* k_score;
		static const char* k_username;
		double averageAnswerTime = 0;
		int totalGamesPlayed = 0;
		int totalCorrectAnswers = 0;
		int totalAnswers = 0;
		int score = 0;
		std::string username;
	} UserStatistics;
	void to_json(json& outputJson, const  UserStatistics& userStatsToConvert);
	void from_json(const json& jsonToConvert, UserStatistics& outputUserStats);
}
