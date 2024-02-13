#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Requests
{
	typedef struct SubmitAnswerRequest
	{
		static const char* k_answerId;
		unsigned int answerId;
	} SubmitAnswerRequest;
	void to_json(json& outputJson, const SubmitAnswerRequest& SubmitAnswerRequestToConvert);
	void from_json(const json& jsonToConvert, SubmitAnswerRequest& outputSubmitAnswerRequest);
}
