#include "CreateRoomResponse.h"

using namespace Responses;

const char* CreateRoomResponse::k_status = "status";

/***************************************************************
 @ brief: nlohmann to_json for CreateRoomResponse
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const CreateRoomResponse& CreateRoomResponseToConvert)
{
	outputJson = json{ { CreateRoomResponse::k_status, CreateRoomResponseToConvert.status } };
}

/***************************************************************
 @ brief: nlohmann from_json for CreateRoomResponse
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, CreateRoomResponse& outputCreateRoomResponse)
{
	jsonToConvert.at(CreateRoomResponse::k_status).get_to(outputCreateRoomResponse.status);
}
