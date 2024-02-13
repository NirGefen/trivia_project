#include "GetPlayersInRoomRequest.h"

using namespace Requests;

const char* GetPlayersInRoomRequest::k_roomId = "room_id";

/***************************************************************
 @ brief: nlohmann to_json for GetPlayersInRoomRequest
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Requests::to_json(json& outputJson, const GetPlayersInRoomRequest& GetPlayersInRoomRequestToConvert)
{
	outputJson = json{ { GetPlayersInRoomRequest::k_roomId, GetPlayersInRoomRequestToConvert.roomId } };
}

/***************************************************************
 @ brief: nlohmann from_json for GetPlayersInRoomRequest
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Requests::from_json(const json& jsonToConvert, GetPlayersInRoomRequest& outputGetPlayersInRoomRequest)
{
	jsonToConvert.at(GetPlayersInRoomRequest::k_roomId).get_to(outputGetPlayersInRoomRequest.roomId);
}
