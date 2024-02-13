#include "RoomMemberRequestHandler.h"

const std::unordered_map<ProtocolRequestHeaderCode, RequestResult(RoomMemberRequestHandler::*)(const Requests::RequestInfo&)> RoomMemberRequestHandler::m_caseFuncs({
	{ ProtocolRequestHeaderCode::REQUEST_GET_ROOM_STATE_CODE, &(RoomMemberRequestHandler::m_getRoomState) },
	{ ProtocolRequestHeaderCode::REQUEST_LEAVE_ROOM_CODE, &(RoomMemberRequestHandler::m_leaveRoom) }
	});

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& loggedUser, unsigned int roomId) :
	m_handlerFactory(handlerFactory), m_loggedUser(loggedUser), m_roomId(roomId)
{
}

RoomMemberRequestHandler::~RoomMemberRequestHandler()
{
}

bool RoomMemberRequestHandler::isRequestRelevant(const Requests::RequestInfo& reqInfo) const
{
	return RoomMemberRequestHandler::m_caseFuncs.find(reqInfo.id) != RoomMemberRequestHandler::m_caseFuncs.end();
}

RequestResult RoomMemberRequestHandler::handleRequest(const Requests::RequestInfo& reqInfo)
{
	Responses::ErrorResponse errorResponse;
	RequestResult reqResult;
	if (!this->isRequestRelevant(reqInfo))
	{
		reqResult = this->m_handleError(ERR_REQ_NOT_RELAVANT, this->m_handlerFactory.createRoomMemberRequestHandler(this->m_loggedUser, this->m_roomId));
	}
	else
	{
		reqResult = std::invoke(RoomMemberRequestHandler::m_caseFuncs.at(reqInfo.id), this, reqInfo);
	}
	return reqResult;
}

void RoomMemberRequestHandler::handleExit()
{
	try
	{
		this->m_handlerFactory.getRoomManager().deleteUserFromRoom(this->m_roomId, this->m_loggedUser);
	}
	catch (RoomDoesNotExistException) // if it did not exist we do not care, we want to used to not be present in a room
	{
	}
	this->m_handlerFactory.getLoginManager().logout(this->m_loggedUser.getUsername());
}

RequestResult RoomMemberRequestHandler::m_leaveRoom(const Requests::RequestInfo& reqInfo)
{
	RequestResult reqResult;
	try
	{
		if (this->m_handlerFactory.getRoomManager().getRoom(this->m_roomId).getData().isActive) // if the game started
		{
			try
			{
				this->m_handlerFactory.getGameManager().removePlayer(this->m_loggedUser.getUsername(), this->m_handlerFactory.getRoomManager().getGameId(this->m_roomId));
			}
			catch (...){}
		}
		this->m_handlerFactory.getRoomManager().deleteUserFromRoom(this->m_roomId, this->m_loggedUser);
	}
	catch (...) {}
	reqResult.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser);
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(Responses::LeaveRoomResponse{ 1 });
	return reqResult;

}

RequestResult RoomMemberRequestHandler::m_getRoomState(const Requests::RequestInfo& reqInfo)
{
	RequestResult reqResult;
	Responses::GetRoomStateResponse roomStateResponse;
	try
	{
		roomStateResponse.players = this->m_handlerFactory.getRoomManager().getRoomPlayerUsernames(this->m_roomId);
		roomStateResponse.roomData = this->m_handlerFactory.getRoomManager().getRoom(this->m_roomId).getData();
	}
	catch (RoomDoesNotExistException &)  // somehow the room got removed
	{
		reqResult.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser);
		reqResult.response = JsonResponsePacketSerializer::serializeResponse(Responses::LeaveRoomResponse{ 1 });
		return reqResult;
	}
	if (roomStateResponse.roomData.isActive) // game started
	{
		reqResult.newHandler = this->m_handlerFactory.createGameRequestHandler(this->m_loggedUser, this->m_roomId);
		reqResult.response = JsonResponsePacketSerializer::serializeResponse(Responses::StartGameResponse{ 1 });
		return reqResult;

	}
	reqResult.newHandler = this->m_handlerFactory.createRoomMemberRequestHandler(this->m_loggedUser, this->m_roomId);
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(roomStateResponse);
	return reqResult;
}
