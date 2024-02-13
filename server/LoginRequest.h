#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Requests
{
	typedef struct LoginRequest
	{
		static const char* k_username;
		static const char* k_password;
		std::string username;
		std::string password;
	} LoginRequest;
	void to_json(json& outputJson, const LoginRequest& LoginRequestToConvert);
	void from_json(const json& jsonToConvert, LoginRequest& outputLoginRequest);
}
