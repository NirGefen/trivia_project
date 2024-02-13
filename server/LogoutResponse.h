#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Responses
{
	typedef struct LogoutResponse
	{
		static const char* k_status;
		unsigned int status;
	} LogoutResponse;
	void to_json(json& outputJson, const LogoutResponse& logoutResponseToConvert);
	void from_json(const json& jsonToConvert, LogoutResponse& outputLogoutResponse);
}
