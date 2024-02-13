#pragma once

#include <unordered_set>
#include "typedefs.h"

enum class ProtocolResponseHeaderCode : bufdata 
{ 
	RESPONSE_LOGIN_CODE = 129, 
	RESPONSE_SIGNUP_CODE,
	RESPONSE_SIGNOUT_CODE,
	RESPONSE_GET_ROOMS_CODE,
	RESPONSE_PLAYERS_IN_ROOM_CODE,
	RESPONSE_JOIN_ROOM_CODE,
	RESPONSE_CREATE_ROOM_CODE,
	RESPONSE_GET_STATISTICS_CODE,
	RESPONSE_GET_ROOM_STATE_CODE,
	RESPONSE_LEAVE_ROOM_CODE,
	RESPONSE_CLOSE_ROOM_CODE,
	RESPONSE_START_GAME_CODE,
	RESPONSE_LEAVE_GAME_CODE,
	RESPONSE_GET_QUESTION_CODE,
	RESPONSE_SUBMIT_ANSWER_CODE,
	RESPONSE_GET_GAME_RESULTS_CODE,
	RESPONSE_ERROR_CODE = 255 };
enum class ProtocolRequestHeaderCode : bufdata 
{ 
	REQUEST_LOGIN_CODE = 1, 
	REQUEST_SIGNUP_CODE, 
	REQUEST_SIGNOUT_CODE,
	REQUEST_GET_ROOMS_CODE,
	REQUEST_PLAYERS_IN_ROOM_CODE,
	REQUEST_JOIN_ROOM_CODE,
	REQUEST_CREATE_ROOM_CODE,
	REQUEST_GET_STATISTICS_CODE,
	REQUEST_GET_ROOM_STATE_CODE,
	REQUEST_LEAVE_ROOM_CODE,
	REQUEST_CLOSE_ROOM_CODE,
	REQUEST_START_GAME_CODE,
	REQUEST_LEAVE_GAME_CODE,
	REQUEST_GET_QUESTION_CODE,
	REQUEST_SUBMIT_ANSWER_CODE,
	REQUEST_GET_GAME_RESULTS_CODE
};

const std::unordered_set<bufdata> requestHeaderCodes(
	{ (bufdata)ProtocolRequestHeaderCode::REQUEST_SIGNUP_CODE,
	(bufdata)ProtocolRequestHeaderCode::REQUEST_LOGIN_CODE,
	(bufdata)ProtocolRequestHeaderCode::REQUEST_SIGNOUT_CODE,
	(bufdata) ProtocolRequestHeaderCode::REQUEST_GET_ROOMS_CODE,
	(bufdata) ProtocolRequestHeaderCode::REQUEST_PLAYERS_IN_ROOM_CODE,
	(bufdata) ProtocolRequestHeaderCode::REQUEST_JOIN_ROOM_CODE,
	(bufdata) ProtocolRequestHeaderCode::REQUEST_CREATE_ROOM_CODE,
	(bufdata) ProtocolRequestHeaderCode::REQUEST_GET_STATISTICS_CODE,
	(bufdata) ProtocolRequestHeaderCode::REQUEST_GET_ROOM_STATE_CODE,
	(bufdata) ProtocolRequestHeaderCode::REQUEST_LEAVE_ROOM_CODE,
	(bufdata) ProtocolRequestHeaderCode::REQUEST_CLOSE_ROOM_CODE,
	(bufdata) ProtocolRequestHeaderCode::REQUEST_START_GAME_CODE,
	(bufdata) ProtocolRequestHeaderCode::REQUEST_LEAVE_GAME_CODE,
	(bufdata)ProtocolRequestHeaderCode::REQUEST_GET_QUESTION_CODE,
	(bufdata)ProtocolRequestHeaderCode::REQUEST_SUBMIT_ANSWER_CODE,
	(bufdata)ProtocolRequestHeaderCode::REQUEST_GET_GAME_RESULTS_CODE
	});
