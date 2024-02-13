#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Responses
{	
	typedef struct LoginResponse
	{
		static const char* k_status;
		unsigned int status;
	} LoginResponse;
	void to_json(json& outputJson, const LoginResponse& LoginResponseToConvert);
	void from_json(const json& jsonToConvert, LoginResponse& outputLoginResponse);
}
