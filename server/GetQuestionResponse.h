#pragma once
#include <string>
#include "GetQuestionResponseAnswer.h"
#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Responses
{
	typedef struct GetQuestionResponse
	{
		static const char* k_status;
		static const char* k_question;
		static const char* k_answers;
		static const char* k_category;
		unsigned int status;
		std::string question;
		std::vector<GetQuestionResponseAnswer> answers;
		std::string category;

	} GetQuestionResponse;
	void to_json(json& outputJson, const GetQuestionResponse& getQuestionResponseToConvert);
	void from_json(const json& jsonToConvert, GetQuestionResponse& outputGetQuestionResponse);
}
