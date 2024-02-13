#include "GetGameResultsResponse.h"

using namespace Responses;

const char* GetGameResultsResponse::k_status = "status";
const char* GetGameResultsResponse::k_results = "results";

/***************************************************************
 @ brief: nlohmann to_json for GetGameResultsResponse
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const GetGameResultsResponse& getGameResultsResponseToConvert)
{
    outputJson = json{ { GetGameResultsResponse::k_status, getGameResultsResponseToConvert.status },
                       { GetGameResultsResponse::k_results, getGameResultsResponseToConvert.results } };
}

/***************************************************************
 @ brief: nlohmann from_json for GetGameResultsResponse
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, GetGameResultsResponse& outputGetGameResultsResponse)
{
    jsonToConvert.at(GetGameResultsResponse::k_status).get_to(outputGetGameResultsResponse.status);
    jsonToConvert.at(GetGameResultsResponse::k_results).get_to(outputGetGameResultsResponse.results);
}
