#include "CreateRoomRequest.h"

using namespace Requests;

const char* CreateRoomRequest::k_roomName = "room_name";
const char* CreateRoomRequest::k_maxUsers = "max_users";
const char* CreateRoomRequest::k_questionCount = "question_count";
const char* CreateRoomRequest::k_answerTimeout = "answer_timeout";

/***************************************************************
 @ brief: nlohmann to_json for CreateRoomRequest
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Requests::to_json(json& outputJson, const CreateRoomRequest& CreateRoomRequestToConvert)
{
	outputJson = json{ { CreateRoomRequest::k_roomName, CreateRoomRequestToConvert.roomName }, 
                       { CreateRoomRequest::k_maxUsers, CreateRoomRequestToConvert.maxUsers },
                       { CreateRoomRequest::k_questionCount, CreateRoomRequestToConvert.questionCount },
                       { CreateRoomRequest::k_answerTimeout, CreateRoomRequestToConvert.answerTimeout } };
}

/***************************************************************
 @ brief: nlohmann from_json for CreateRoomRequest
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Requests::from_json(const json& jsonToConvert, CreateRoomRequest& outputLoginRequest)
{
	jsonToConvert.at(CreateRoomRequest::k_roomName).get_to(outputLoginRequest.roomName);
	jsonToConvert.at(CreateRoomRequest::k_maxUsers).get_to(outputLoginRequest.maxUsers);
	jsonToConvert.at(CreateRoomRequest::k_questionCount).get_to(outputLoginRequest.questionCount);
	jsonToConvert.at(CreateRoomRequest::k_answerTimeout).get_to(outputLoginRequest.answerTimeout);
}
