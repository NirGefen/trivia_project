#include "CloseRoomResponse.h"

using namespace Responses;

const char* CloseRoomResponse::k_status = "status";

/***************************************************************
 @ brief: nlohmann to_json for CloseRoomResponse
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const CloseRoomResponse& closeRoomResponseToConvert)
{
    outputJson = json{ { CloseRoomResponse::k_status, closeRoomResponseToConvert.status } };
}

/***************************************************************
 @ brief: nlohmann from_json for CloseRoomResponse
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, CloseRoomResponse& outputCloseRoomResponse)
{
    jsonToConvert.at(CloseRoomResponse::k_status).get_to(outputCloseRoomResponse.status);
}
