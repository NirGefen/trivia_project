#include "PlayerResults.h"

using namespace Responses;

const char* PlayerResults::k_username = "username";
const char* PlayerResults::k_correctAnswerCount = "correct_answer_count";
const char* PlayerResults::k_wrongAnswerCount = "wrong_answer_count";
const char* PlayerResults::k_averageAnswerTime = "average_answer_time";

/***************************************************************
 @ brief: nlohmann to_json for PlayerResults
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const PlayerResults& playerResultsToConvert)
{
    outputJson = json{ { PlayerResults::k_username, playerResultsToConvert.username },
                       { PlayerResults::k_correctAnswerCount, playerResultsToConvert.correctAnswerCount },
                       { PlayerResults::k_wrongAnswerCount, playerResultsToConvert.wrongAnswerCount }, 
                       { PlayerResults::k_averageAnswerTime, playerResultsToConvert.averageAnswerTime } };
}

/***************************************************************
 @ brief: nlohmann from_json for PlayerResults
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, PlayerResults& outputPlayerResults)
{
    jsonToConvert.at(PlayerResults::k_username).get_to(outputPlayerResults.username);
    jsonToConvert.at(PlayerResults::k_correctAnswerCount).get_to(outputPlayerResults.correctAnswerCount);
    jsonToConvert.at(PlayerResults::k_wrongAnswerCount).get_to(outputPlayerResults.wrongAnswerCount);
    jsonToConvert.at(PlayerResults::k_averageAnswerTime).get_to(outputPlayerResults.averageAnswerTime);
}
