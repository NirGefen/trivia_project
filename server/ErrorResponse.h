#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Responses
{
	typedef struct ErrorResponse
	{
		static const char* k_message;
		std::string message;
	} ErrorResponse;
	void to_json(json& outputJson, const ErrorResponse& ErrorResponseToConvert);
	void from_json(const json& jsonToConvert, ErrorResponse& outputErrorResponse);
}
