#include "SignupResponse.h"

using namespace Responses;

const char* SignupResponse::k_status = "status";

/***************************************************************
 @ brief: nlohmann to_json for SignupResponse
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const SignupResponse& signupResponseToConvert)
{
	outputJson = json{ { SignupResponse::k_status, signupResponseToConvert.status } };
}

/***************************************************************
 @ brief: nlohmann from_json for SignupResponse
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, SignupResponse& outputSignupResponse)
{
	jsonToConvert.at(SignupResponse::k_status).get_to(outputSignupResponse.status);
}
