#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Responses
{
	typedef struct SubmitAnswerResponse
	{
		static const char* k_status;
		static const char* k_correctAnswerId;
		unsigned int status;
		unsigned int correctAnswerId;
	} SubmitAnswerResponse;
	void to_json(json& outputJson, const SubmitAnswerResponse& submitAnswerResponseToConvert);
	void from_json(const json& jsonToConvert, SubmitAnswerResponse& outputSubmitAnswerResponse);
}
