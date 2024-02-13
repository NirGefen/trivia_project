#include "JoinRoomResponse.h"

using namespace Responses;

const char* JoinRoomResponse::k_status = "status";

/***************************************************************
 @ brief: nlohmann to_json for JoinRoomResponse
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const JoinRoomResponse& JoinRoomResponseToConvert)
{
	outputJson = json{ { JoinRoomResponse::k_status, JoinRoomResponseToConvert.status } };
}

/***************************************************************
 @ brief: nlohmann from_json for JoinRoomResponse
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, JoinRoomResponse& outputJoinRoomResponse)
{
	jsonToConvert.at(JoinRoomResponse::k_status).get_to(outputJoinRoomResponse.status);
}
