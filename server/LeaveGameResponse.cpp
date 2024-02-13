#include "LeaveGameResponse.h"

using namespace Responses;

const char* LeaveGameResponse::k_status = "status";

/***************************************************************
 @ brief: nlohmann to_json for LeaveGameResponse
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const LeaveGameResponse& leaveGameResponseToConvert)
{
    outputJson = json{ { LeaveGameResponse::k_status, leaveGameResponseToConvert.status } };
}

/***************************************************************
 @ brief: nlohmann from_json for LeaveGameResponse
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, LeaveGameResponse& outputLeaveGameResponse)
{
    jsonToConvert.at(LeaveGameResponse::k_status).get_to(outputLeaveGameResponse.status);
}
