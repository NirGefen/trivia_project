#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Requests
{
	typedef struct SignupRequest
	{
		static const char* k_username;
		static const char* k_password;
		static const char* k_email;
		std::string username;
		std::string password;
		std::string email;
	} SignupRequest;
	void to_json(json& outputJson, const SignupRequest& signupRequestToConvert);
	void from_json(const json& jsonToConvert, SignupRequest& outputSignupRequest);
}
