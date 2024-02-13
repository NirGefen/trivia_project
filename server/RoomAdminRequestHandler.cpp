#include "RoomAdminRequestHandler.h"

const std::unordered_map<ProtocolRequestHeaderCode, RequestResult(RoomAdminRequestHandler::*)(const Requests::RequestInfo&)> RoomAdminRequestHandler::m_caseFuncs({
	{ ProtocolRequestHeaderCode::REQUEST_GET_ROOM_STATE_CODE, &(RoomAdminRequestHandler::m_getRoomState) },
	{ ProtocolRequestHeaderCode::REQUEST_CLOSE_ROOM_CODE, &(RoomAdminRequestHandler::m_closeRoom) },
	{ ProtocolRequestHeaderCode::REQUEST_START_GAME_CODE, &(RoomAdminRequestHandler::m_startGame) }
	});

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& loggedUser, unsigned int roomId) :
	m_handlerFactory(handlerFactory), m_loggedUser(loggedUser), m_roomId(roomId)
{
}

RoomAdminRequestHandler::~RoomAdminRequestHandler()
{
}

bool RoomAdminRequestHandler::isRequestRelevant(const Requests::RequestInfo& reqInfo) const
{
	return RoomAdminRequestHandler::m_caseFuncs.find(reqInfo.id) != RoomAdminRequestHandler::m_caseFuncs.end();
}

RequestResult RoomAdminRequestHandler::handleRequest(const Requests::RequestInfo& reqInfo)
{
	Responses::ErrorResponse errorResponse;
	RequestResult reqResult;
	if (!this->isRequestRelevant(reqInfo))
	{
		reqResult = this->m_handleError(ERR_REQ_NOT_RELAVANT, this->m_handlerFactory.createRoomAdminRequestHandler(this->m_loggedUser, this->m_roomId));
	}
	else
	{
		reqResult = std::invoke(RoomAdminRequestHandler::m_caseFuncs.at(reqInfo.id), this, reqInfo);
	}
	return reqResult;
}

void RoomAdminRequestHandler::handleExit()
{
	try
	{
		this->m_handlerFactory.getRoomManager().deleteRoom(this->m_roomId);
	}
	catch (RoomDoesNotExistException) // if it did not exist we do not care, we wanted to close it anyways
	{
	}
	this->m_handlerFactory.getLoginManager().logout(this->m_loggedUser.getUsername());
}

RequestResult RoomAdminRequestHandler::m_closeRoom(const Requests::RequestInfo& reqInfo)
{
	RequestResult reqResult;
	try
	{
		this->m_handlerFactory.getRoomManager().deleteRoom(this->m_roomId);
	}
	catch (RoomDoesNotExistException) // if it did not exist we do not care, we wanted to close it anyways
	{
	}
	reqResult.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser);
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(Responses::CloseRoomResponse{ 1 });
	return reqResult;

}

RequestResult RoomAdminRequestHandler::m_startGame(const Requests::RequestInfo& reqInfo)
{
	RequestResult reqResult;
	// the actual handler will be implemented in version 4
	unsigned int createdGameId = 0;
	try
	{
		createdGameId = this->m_handlerFactory.getGameManager().createGame(this->m_handlerFactory.getRoomManager().getRoom(this->m_roomId));
	}
	catch (std::exception & e)
	{
		return this->m_handleError(e.what(), this->m_handlerFactory.createRoomAdminRequestHandler(this->m_loggedUser, this->m_roomId));
	}
	try
	{

		this->m_handlerFactory.getRoomManager().setGameId(this->m_roomId, createdGameId);
	}
	catch (std::exception& e)
	{ 
		return this->m_handleError(e.what(), this->m_handlerFactory.createRoomAdminRequestHandler(this->m_loggedUser, this->m_roomId));
	}

	try
	{
		this->m_handlerFactory.getRoomManager().setRoomState(this->m_roomId, true);
	}
	catch (RoomDoesNotExistException & e)  // somehow the room got removed
	{
		return this->m_handleError(e.what(), this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser));
	}
	reqResult.newHandler = this->m_handlerFactory.createGameRequestHandler(this->m_loggedUser, this->m_roomId);
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(Responses::StartGameResponse{ 1 });
	return reqResult;
}

RequestResult RoomAdminRequestHandler::m_getRoomState(const Requests::RequestInfo& reqInfo)
{
	RequestResult reqResult;
	Responses::GetRoomStateResponse roomStateResponse;
	try
	{
		roomStateResponse.players = this->m_handlerFactory.getRoomManager().getRoomPlayerUsernames(this->m_roomId);
		roomStateResponse.roomData = this->m_handlerFactory.getRoomManager().getRoom(this->m_roomId).getData();
	}
	catch (RoomDoesNotExistException & e)  // somehow the room got removed
	{
		return this->m_handleError(e.what(), this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser));
	}
	reqResult.newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(this->m_loggedUser, this->m_roomId);
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(roomStateResponse);
	return reqResult;
}
