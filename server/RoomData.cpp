#include "RoomData.h"

using namespace Other;

const char* RoomData::k_roomId = "room_id";
const char* RoomData::k_roomName = "room_name";
const char* RoomData::k_ownerUsername = "owner_username";
const char* RoomData::k_maxPlayers = "max_players";
const char* RoomData::k_secondsPerQuestion = "seconds_per_question";
const char* RoomData::k_isActive = "is_active";
const char* RoomData::k_numOfQuestionsInGame = "num_of_questions";
/***************************************************************
 @ brief: nlohmann to_json for RoomData
 [>>] (regular to_json args)
 [<<] Void
****************************************************************/
void Other::to_json(json& outputJson, const RoomData& roomDataToConvert)
{
	outputJson = json{ { RoomData::k_roomId, roomDataToConvert.id },
					   { RoomData::k_roomName, roomDataToConvert.roomName },
					   { RoomData::k_ownerUsername, roomDataToConvert.owner.getUsername() },
					   { RoomData::k_maxPlayers, roomDataToConvert.maxPlayers },
					   { RoomData::k_secondsPerQuestion, roomDataToConvert.secondsPerQuestion },
					   { RoomData::k_isActive, roomDataToConvert.isActive },
					   { RoomData::k_numOfQuestionsInGame, roomDataToConvert.numOfQuestionsInGame } };
}

/***************************************************************
 @ brief: nlohmann from_json for RoomData
 [>>] (regular from_json args)
 [<<] Void
****************************************************************/
void Other::from_json(const json& jsonToConvert, RoomData& outputRoomData)
{
	std::string ownerUsername;
	jsonToConvert.at(RoomData::k_roomId).get_to(outputRoomData.id);
	jsonToConvert.at(RoomData::k_roomName).get_to(outputRoomData.roomName);
	jsonToConvert.at(RoomData::k_maxPlayers).get_to(outputRoomData.maxPlayers);
	jsonToConvert.at(RoomData::k_secondsPerQuestion).get_to(outputRoomData.secondsPerQuestion);
	jsonToConvert.at(RoomData::k_isActive).get_to(outputRoomData.isActive);
	jsonToConvert.at(RoomData::k_ownerUsername).get_to(ownerUsername);
	jsonToConvert.at(RoomData::k_numOfQuestionsInGame).get_to(outputRoomData.numOfQuestionsInGame);
	outputRoomData.owner.setUsername(ownerUsername);
}
