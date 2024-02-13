#include "StartGameResponse.h"

using namespace Responses;

const char* StartGameResponse::k_status = "status";

/***************************************************************
 @ brief: nlohmann to_json for StartGameResponse
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const StartGameResponse& startGameResponseToConvert)
{
    outputJson = json{ { StartGameResponse::k_status, startGameResponseToConvert.status } };
}

/***************************************************************
 @ brief: nlohmann from_json for StartGameResponse
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, StartGameResponse& outputStartGameResponse)
{
    jsonToConvert.at(StartGameResponse::k_status).get_to(outputStartGameResponse.status);
}
