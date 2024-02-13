#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Responses
{
	typedef struct PlayerResults
	{
		static const char* k_username;
		static const char* k_correctAnswerCount;
		static const char* k_wrongAnswerCount;
		static const char* k_averageAnswerTime;
		std::string username;
		unsigned int correctAnswerCount;
		unsigned int wrongAnswerCount;
		double averageAnswerTime;
	} PlayerResults;
	void to_json(json& outputJson, const PlayerResults& playerResultsToConvert);
	void from_json(const json& jsonToConvert, PlayerResults& outputPlayerResults);
}
