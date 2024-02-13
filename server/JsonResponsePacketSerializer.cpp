#include "JsonResponsePacketSerializer.h"

/***************************************************************
 @ brief: serialize a response struct (yes, this is bad design but we were specifically asked to implement it this way in the UML)
 [>>] const Responses::<Response Type>: the response struct to be serialized
 [<<] buffer: the serialized buffer, including header and json length parts
****************************************************************/
buffer JsonResponsePacketSerializer::serializeResponse(const Responses::ErrorResponse& errorResponseToSer)
{
	return JsonResponsePacketSerializer::serializeJsonResponse(ProtocolResponseHeaderCode::RESPONSE_ERROR_CODE, errorResponseToSer);
}
buffer JsonResponsePacketSerializer::serializeResponse(const Responses::LoginResponse& loginResponseToSer)
{
	return JsonResponsePacketSerializer::serializeJsonResponse(ProtocolResponseHeaderCode::RESPONSE_LOGIN_CODE, loginResponseToSer);
}
buffer JsonResponsePacketSerializer::serializeResponse(const Responses::SignupResponse& signupResponseToSer)
{
	return JsonResponsePacketSerializer::serializeJsonResponse(ProtocolResponseHeaderCode::RESPONSE_SIGNUP_CODE, signupResponseToSer);
}
buffer JsonResponsePacketSerializer::serializeResponse(const Responses::LogoutResponse& logoutResponseToSer)
{
	return JsonResponsePacketSerializer::serializeJsonResponse(ProtocolResponseHeaderCode::RESPONSE_SIGNOUT_CODE, logoutResponseToSer);
}
buffer JsonResponsePacketSerializer::serializeResponse(const Responses::GetRoomsResponse& getRoomsResponseToSer)
{
	return JsonResponsePacketSerializer::serializeJsonResponse(ProtocolResponseHeaderCode::RESPONSE_GET_ROOMS_CODE, getRoomsResponseToSer);
}
buffer JsonResponsePacketSerializer::serializeResponse(const Responses::GetPlayersInRoomResponse& getPlayerInRoomResponseToSer)
{
	return JsonResponsePacketSerializer::serializeJsonResponse(ProtocolResponseHeaderCode::RESPONSE_PLAYERS_IN_ROOM_CODE, getPlayerInRoomResponseToSer);
}
buffer JsonResponsePacketSerializer::serializeResponse(const Responses::JoinRoomResponse& joinRoomResponseToSer)
{
	return JsonResponsePacketSerializer::serializeJsonResponse(ProtocolResponseHeaderCode::RESPONSE_JOIN_ROOM_CODE, joinRoomResponseToSer);
}
buffer JsonResponsePacketSerializer::serializeResponse(const Responses::CreateRoomResponse& createRoomResponseToSer)
{
	return JsonResponsePacketSerializer::serializeJsonResponse(ProtocolResponseHeaderCode::RESPONSE_CREATE_ROOM_CODE, createRoomResponseToSer);
}
buffer JsonResponsePacketSerializer::serializeResponse(const Responses::GetStatisticsResponse& getStatisticsResponseToSer)
{
	return JsonResponsePacketSerializer::serializeJsonResponse(ProtocolResponseHeaderCode::RESPONSE_GET_STATISTICS_CODE, getStatisticsResponseToSer);
}

buffer JsonResponsePacketSerializer::serializeResponse(const Responses::GetRoomStateResponse& getRoomStateResponseToSer)
{
	return JsonResponsePacketSerializer::serializeJsonResponse(ProtocolResponseHeaderCode::RESPONSE_GET_ROOM_STATE_CODE, getRoomStateResponseToSer);
}

buffer JsonResponsePacketSerializer::serializeResponse(const Responses::LeaveRoomResponse& leaveRoomResponseToSer)
{
	return JsonResponsePacketSerializer::serializeJsonResponse(ProtocolResponseHeaderCode::RESPONSE_LEAVE_ROOM_CODE, leaveRoomResponseToSer);
}

buffer JsonResponsePacketSerializer::serializeResponse(const Responses::CloseRoomResponse& closeRoomResponseToSer)
{
	return JsonResponsePacketSerializer::serializeJsonResponse(ProtocolResponseHeaderCode::RESPONSE_CLOSE_ROOM_CODE, closeRoomResponseToSer);
}

buffer JsonResponsePacketSerializer::serializeResponse(const Responses::StartGameResponse& startGameResponseToSer)
{
	return JsonResponsePacketSerializer::serializeJsonResponse(ProtocolResponseHeaderCode::RESPONSE_START_GAME_CODE, startGameResponseToSer);
}

buffer JsonResponsePacketSerializer::serializeResponse(const Responses::LeaveGameResponse& leaveGameResponseToSer)
{
	return JsonResponsePacketSerializer::serializeJsonResponse(ProtocolResponseHeaderCode::RESPONSE_LEAVE_GAME_CODE, leaveGameResponseToSer);
}

buffer JsonResponsePacketSerializer::serializeResponse(const Responses::GetQuestionResponse& getQuestionResponseToSer)
{
	return JsonResponsePacketSerializer::serializeJsonResponse(ProtocolResponseHeaderCode::RESPONSE_GET_QUESTION_CODE, getQuestionResponseToSer);
}

buffer JsonResponsePacketSerializer::serializeResponse(const Responses::SubmitAnswerResponse& submitAnswerResponseToSer)
{
	return JsonResponsePacketSerializer::serializeJsonResponse(ProtocolResponseHeaderCode::RESPONSE_SUBMIT_ANSWER_CODE, submitAnswerResponseToSer);
}

buffer JsonResponsePacketSerializer::serializeResponse(const Responses::GetGameResultsResponse& getGameResultsResponseToSer)
{
	return JsonResponsePacketSerializer::serializeJsonResponse(ProtocolResponseHeaderCode::RESPONSE_GET_GAME_RESULTS_CODE, getGameResultsResponseToSer);
}

/***************************************************************
 @ brief: adds a size chunk to a given response buffer (4 bytes - given unsigned integer)
 [>>] buffer& outBuffer: the buffer to add the size chunk to
 [>>] unsigned int size: the size unsigned integer to set the added chunk to
 [<<] Void
****************************************************************/
void JsonResponsePacketSerializer::m_addSizeChunk(buffer& outBuffer, unsigned int size)
{
	for (unsigned short i = 0; i < sizeof(unsigned int); ++i)
	{
		outBuffer.push_back(*(((bufdata*)&size + (sizeof(unsigned int) - i - 1))));
	}
}

/***************************************************************
 @ brief: serialize a response the header code & json of which is given
 [>>] const ProtocolResponseHeaderCode& headerCode: the header code of the response
 [>>] const json& jsonToSer: the json of the response
 [<<] buffer: the serialized response buffer
****************************************************************/
buffer JsonResponsePacketSerializer::serializeJsonResponse(const ProtocolResponseHeaderCode& headerCode, const json& jsonToSer)
{
	buffer outBuffer = buffer();
	outBuffer.push_back((bufdata)headerCode);
	std::string serializedJson = jsonToSer.dump();
	JsonResponsePacketSerializer::m_addSizeChunk(outBuffer, serializedJson.length());
	std::copy(serializedJson.begin(), serializedJson.end(), std::back_inserter(outBuffer));
	return outBuffer;
}
