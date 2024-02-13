#include "GetRoomsResponse.h"

using namespace Responses;

const char* GetRoomsResponse::k_room_list = "room_list";

/***************************************************************
 @ brief: nlohmann to_json for GetRoomsResponse
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Responses::to_json(json& outputJson, const GetRoomsResponse& GetRoomsResponseToConvert)
{
	outputJson = json{ { GetRoomsResponse::k_room_list, GetRoomsResponseToConvert.rooms } };
}

/***************************************************************
 @ brief: nlohmann from_json for GetRoomsResponse
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Responses::from_json(const json& jsonToConvert, GetRoomsResponse& outputGetRoomsResponse)
{
	jsonToConvert.at(GetRoomsResponse::k_room_list).get_to(outputGetRoomsResponse.rooms);
}
