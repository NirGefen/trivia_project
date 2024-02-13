#pragma once

#include <string>
#include <iostream>
#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Trivia
{
	typedef struct Question
	{
		static const std::string k_questionText;
		static const std::string k_correctAnswer;
		static const std::string k_category;
		static const std::string k_incorrectAnswers;
		std::string questionText;
		std::string category;
		std::string correctAnswer;
		std::vector<std::string> incorrectAnswers;

	} Question;
	void to_json(json& outputJson, const Question& questionToConvert);
	void from_json(const json& jsonToConvert, Question& outputQuestion);
}