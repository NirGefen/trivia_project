#include "LoginResponse.h"

using namespace Responses;

const char* LoginResponse::k_status = "status";

/***************************************************************
 @ brief: nlohmann to_json for LoginResponse
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const LoginResponse& LoginResponseToConvert)
{
	outputJson = json{ { LoginResponse::k_status, LoginResponseToConvert.status } };
}

/***************************************************************
 @ brief: nlohmann from_json for LoginResponse
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, LoginResponse& outputLoginResponse)
{
	jsonToConvert.at(LoginResponse::k_status).get_to(outputLoginResponse.status);
}
