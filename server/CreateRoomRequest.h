#pragma once
#include <string>

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace Requests
{
	typedef struct CreateRoomRequest
	{
		static const char* k_roomName;
		static const char* k_maxUsers;
		static const char* k_questionCount;
		static const char* k_answerTimeout;
		std::string roomName;
		unsigned int maxUsers;
		unsigned int questionCount;
		double answerTimeout;
		// TODO: add a function that checks the validity of the paramaeters and throws an exception of one of them is invalid with the reason of invalidness
	} CreateRoomRequest;
	void to_json(json& outputJson, const CreateRoomRequest& CreateRoomRequestToConvert);
	void from_json(const json& jsonToConvert, CreateRoomRequest& outputCreateRoomRequest);
}
