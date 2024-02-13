#include "JoinRoomRequest.h"

using namespace Requests;

const char* JoinRoomRequest::k_roomId = "room_id";

/***************************************************************
 @ brief: nlohmann to_json for JoinRoomRequest
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Requests::to_json(json& outputJson, const JoinRoomRequest& JoinRoomRequestToConvert)
{
	outputJson = json{ { JoinRoomRequest::k_roomId, JoinRoomRequestToConvert.roomId } };
}

/***************************************************************
 @ brief: nlohmann from_json for JoinRoomRequest
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Requests::from_json(const json& jsonToConvert, JoinRoomRequest& outputJoinRoomRequest)
{
	jsonToConvert.at(JoinRoomRequest::k_roomId).get_to(outputJoinRoomRequest.roomId);
}
