#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Responses
{
	typedef struct GetQuestionResponseAnswer
	{
		static const char* k_answerId;
		static const char* k_answer;
		unsigned int answerId;
		std::string answer;
	} GetQuestionResponseAnswer;
	void to_json(json& outputJson, const GetQuestionResponseAnswer& getQuestionResponseAnswerToConvert);
	void from_json(const json& jsonToConvert, GetQuestionResponseAnswer& outputGetQuestionResponseAnswer);
}
