#include "SignupRequest.h"

using namespace Requests;

const char* SignupRequest::k_username = "username";
const char* SignupRequest::k_password = "password";
const char* SignupRequest::k_email = "email";

/***************************************************************
 @ brief: nlohmann to_json for SignupRequest
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Requests::to_json(json& outputJson, const SignupRequest& signupRequestToConvert)
{
	outputJson = json{ { SignupRequest::k_username, signupRequestToConvert.username },
	                   { SignupRequest::k_password, signupRequestToConvert.username }, 
	                   { SignupRequest::k_email, signupRequestToConvert.email } };
}

/***************************************************************
 @ brief: nlohmann to_json for SignupRequest
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Requests::from_json(const json& jsonToConvert, SignupRequest& outputSignupRequest)
{
	jsonToConvert.at(SignupRequest::k_username).get_to(outputSignupRequest.username);
	jsonToConvert.at(SignupRequest::k_password).get_to(outputSignupRequest.password);
	jsonToConvert.at(SignupRequest::k_email).get_to(outputSignupRequest.email);
}
