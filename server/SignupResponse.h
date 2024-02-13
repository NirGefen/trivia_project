#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Responses
{
	typedef struct SignupResponse
	{
		static const char* k_status;
		unsigned int status;
	} SignupResponse;
	void to_json(json& outputJson, const SignupResponse& signupResponseToConvert);
	void from_json(const json& jsonToConvert, SignupResponse& outputSignupResponse);
}
