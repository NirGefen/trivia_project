#include "GetRoomStateResponse.h"

using namespace Responses;

const char* GetRoomStateResponse::k_roomData = "room_data";
const char* GetRoomStateResponse::k_players = "players";

/***************************************************************
 @ brief: nlohmann to_json for GetRoomStateResponse
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const GetRoomStateResponse& getRoomStateResponseToConvert)
{
    // outputJson = json{ { GetRoomStateResponse::k_status, closeRoomResponseToConvert.status } };
    outputJson = json{ { GetRoomStateResponse::k_roomData, getRoomStateResponseToConvert.roomData },
                        { GetRoomStateResponse::k_players, getRoomStateResponseToConvert.players } };
}

/***************************************************************
 @ brief: nlohmann from_json for GetRoomStateResponse
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, GetRoomStateResponse& outputGetRoomStateResponse)
{
    jsonToConvert.at(GetRoomStateResponse::k_roomData).get_to(outputGetRoomStateResponse.roomData);
    jsonToConvert.at(GetRoomStateResponse::k_players).get_to(outputGetRoomStateResponse.players);
}
