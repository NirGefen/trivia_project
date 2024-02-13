#include "LeaveRoomResponse.h"

using namespace Responses;

const char* LeaveRoomResponse::k_status = "status";

/***************************************************************
 @ brief: nlohmann to_json for LeaveRoomResponse
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const LeaveRoomResponse& leaveRoomResponseToConvert)
{
    outputJson = json{ { LeaveRoomResponse::k_status, leaveRoomResponseToConvert.status } };
}

/***************************************************************
 @ brief: nlohmann from_json for LeaveRoomResponse
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, LeaveRoomResponse& outputLeaveRoomResponse)
{
    jsonToConvert.at(LeaveRoomResponse::k_status).get_to(outputLeaveRoomResponse.status);
}
