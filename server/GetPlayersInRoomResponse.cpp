#include "GetPlayersInRoomResponse.h"

using namespace Responses;

const char* GetPlayersInRoomResponse::k_room_player_list = "room_player_list";

/***************************************************************
 @ brief: nlohmann to_json for GetPlayersInRoomResponse
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const GetPlayersInRoomResponse& GetPlayersInRoomResponseToConvert)
{
	outputJson = json{ { GetPlayersInRoomResponse::k_room_player_list, GetPlayersInRoomResponseToConvert.players } };
}

/***************************************************************
 @ brief: nlohmann from_json for GetPlayersInRoomResponse
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, GetPlayersInRoomResponse& outputGetPlayersInRoomResponse)
{
	jsonToConvert.at(GetPlayersInRoomResponse::k_room_player_list).get_to(outputGetPlayersInRoomResponse.players);
}
