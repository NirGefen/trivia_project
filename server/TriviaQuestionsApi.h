#pragma once

#include <string>
#include <list>
#include <algorithm>
#include <iostream>
#include "include/nlohmann/json.hpp"
using json = nlohmann::json;
#include "include/cpprest/filestream.h"
#include "include/cpprest/http_client.h"
#include "Question.h"

class TriviaQuestionsApi
{
public:
	static std::list<Trivia::Question> getQuestions(unsigned int amount);
private:
	static const std::wstring URL;
	static const std::wstring API_PATH;
	static const std::wstring PARAM_AMOUNT;
	static const std::wstring PARAM_DIFFICULTY;
	static const std::wstring PARAM_TYPE;
	static const std::wstring TYPE;
	static const unsigned int MAX_AMOUNT;
	static json query(unsigned int amount, const std::wstring& difficulty = L"medium");

};