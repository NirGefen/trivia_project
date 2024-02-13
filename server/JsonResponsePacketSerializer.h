#pragma once
#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

#include "typedefs.h"
#include "ErrorResponse.h"
#include "LoginResponse.h"
#include "SignupResponse.h"
#include "LogoutResponse.h"
#include "GetRoomsResponse.h"
#include "GetPlayersInRoomResponse.h"
#include "GetStatisticsResponse.h"
#include "JoinRoomResponse.h"
#include "CreateRoomResponse.h"
#include "GetRoomStateResponse.h"
#include "LeaveRoomResponse.h"
#include "CloseRoomResponse.h"
#include "StartGameResponse.h"
#include "LeaveGameResponse.h"
#include "GetQuestionResponse.h"
#include "SubmitAnswerResponse.h"
#include "GetGameResultsResponse.h"
#include "protocolHeaderCodes.h"

class JsonResponsePacketSerializer
{
public:
	static buffer serializeResponse(const Responses::ErrorResponse& errorResponseToSer);
	static buffer serializeResponse(const Responses::LoginResponse& loginResponseToSer);
	static buffer serializeResponse(const Responses::SignupResponse& signupResponseToSer);
	static buffer serializeResponse(const Responses::LogoutResponse& logoutResponseToSer);
	static buffer serializeResponse(const Responses::GetRoomsResponse& getRoomsResponseToSer);
	static buffer serializeResponse(const Responses::GetPlayersInRoomResponse& getPlayerInRoomResponseToSer);
	static buffer serializeResponse(const Responses::JoinRoomResponse& joinRoomResponseToSer);
	static buffer serializeResponse(const Responses::CreateRoomResponse& createRoomResponseToSer);
	static buffer serializeResponse(const Responses::GetStatisticsResponse& getStatisticsResponseToSer);
	static buffer serializeResponse(const Responses::GetRoomStateResponse& getRoomStateResponseToSer);
	static buffer serializeResponse(const Responses::LeaveRoomResponse& leaveRoomResponseToSer);
	static buffer serializeResponse(const Responses::CloseRoomResponse& closeRoomResponseToSer);
	static buffer serializeResponse(const Responses::StartGameResponse& startGameResponseToSer);
	static buffer serializeResponse(const Responses::LeaveGameResponse& startGameResponseToSer);
	static buffer serializeResponse(const Responses::GetQuestionResponse& startGameResponseToSer);
	static buffer serializeResponse(const Responses::SubmitAnswerResponse& startGameResponseToSer);
	static buffer serializeResponse(const Responses::GetGameResultsResponse& startGameResponseToSer);
private:
	static void m_addSizeChunk(buffer& outBuffer, unsigned int size);
	static buffer serializeJsonResponse(const ProtocolResponseHeaderCode& headerCode, const json& jsonToSer);
};