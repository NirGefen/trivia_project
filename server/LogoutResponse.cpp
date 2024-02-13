#include "LogoutResponse.h"

using namespace Responses;

const char* LogoutResponse::k_status = "status";

/***************************************************************
 @ brief: nlohmann to_json for LogoutResponse
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const LogoutResponse& LogoutResponseToConvert)
{
	outputJson = json{ { LogoutResponse::k_status, LogoutResponseToConvert.status } };
}

/***************************************************************
 @ brief: nlohmann from_json for LogoutResponse
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, LogoutResponse& outputLogoutResponse)
{
	jsonToConvert.at(LogoutResponse::k_status).get_to(outputLogoutResponse.status);
}
