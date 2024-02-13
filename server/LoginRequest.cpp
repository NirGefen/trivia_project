#include "LoginRequest.h"

using namespace Requests;

const char* LoginRequest::k_username = "username";
const char* LoginRequest::k_password = "password";

/***************************************************************
 @ brief: nlohmann to_json for LoginRequest
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Requests::to_json(json& outputJson, const LoginRequest& LoginRequestToConvert)
{
	outputJson = json{ { LoginRequest::k_username, LoginRequestToConvert.username }, 
	                   { LoginRequest::k_password, LoginRequestToConvert.password } };
}

/***************************************************************
 @ brief: nlohmann from_json for LoginRequest
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Requests::from_json(const json& jsonToConvert, LoginRequest& outputLoginRequest)
{
	jsonToConvert.at(LoginRequest::k_username).get_to(outputLoginRequest.username);
	jsonToConvert.at(LoginRequest::k_password).get_to(outputLoginRequest.password);
}
