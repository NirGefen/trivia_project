#include "MenuRequestHandler.h"

const std::unordered_map<ProtocolRequestHeaderCode, RequestResult(MenuRequestHandler::*)(const Requests::RequestInfo&)> MenuRequestHandler::m_caseFuncs({
	{ ProtocolRequestHeaderCode::REQUEST_SIGNOUT_CODE, &(MenuRequestHandler::m_signout) },
	{ ProtocolRequestHeaderCode::REQUEST_GET_ROOMS_CODE, &(MenuRequestHandler::m_getRooms) },
	{ ProtocolRequestHeaderCode::REQUEST_JOIN_ROOM_CODE, &(MenuRequestHandler::m_joinRoom) },
	{ ProtocolRequestHeaderCode::REQUEST_CREATE_ROOM_CODE, &(MenuRequestHandler::m_createRoom) },
	{ ProtocolRequestHeaderCode::REQUEST_PLAYERS_IN_ROOM_CODE, &(MenuRequestHandler::m_getPlayersInRoom) },
	{ ProtocolRequestHeaderCode::REQUEST_GET_STATISTICS_CODE, &(MenuRequestHandler::m_getStatistics) }
});
MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& loggedUser) :
	m_handlerFactory(handlerFactory), m_loggedUser(loggedUser)
{

}

MenuRequestHandler::~MenuRequestHandler()
{
}

bool MenuRequestHandler::isRequestRelevant(const Requests::RequestInfo& reqInfo) const
{
	return MenuRequestHandler::m_caseFuncs.find(reqInfo.id) != MenuRequestHandler::m_caseFuncs.end();
}

RequestResult MenuRequestHandler::handleRequest(const Requests::RequestInfo& reqInfo)
{
	Responses::ErrorResponse errorResponse;
	RequestResult reqResult;
	if (!this->isRequestRelevant(reqInfo))
	{
		reqResult = this->m_handleError(ERR_REQ_NOT_RELAVANT, this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser));
	}
	else
	{
		reqResult = std::invoke(MenuRequestHandler::m_caseFuncs.at(reqInfo.id), this, reqInfo);
	}
	return reqResult;
}

void MenuRequestHandler::handleExit()
{
	this->m_handlerFactory.getLoginManager().logout(this->m_loggedUser.getUsername());
}

RequestResult MenuRequestHandler::m_signout(const Requests::RequestInfo& reqInfo)
{
	RequestResult reqResult;
	this->m_handlerFactory.getLoginManager().logout(this->m_loggedUser.getUsername());
	reqResult.newHandler = this->m_handlerFactory.createLoginRequestHandler();
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(Responses::LogoutResponse{ 1 });
	return reqResult;
}

RequestResult MenuRequestHandler::m_getRooms(const Requests::RequestInfo& reqInfo)
{
	RequestResult reqResult;
	reqResult.newHandler = new MenuRequestHandler(this->m_handlerFactory, this->m_loggedUser);
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(Responses::GetRoomsResponse{ this->m_handlerFactory.getRoomManager().getRoomMetadatas() });
	return reqResult;
}

RequestResult MenuRequestHandler::m_getPlayersInRoom(const Requests::RequestInfo& reqInfo)
{
	RequestResult reqResult;
	Requests::GetPlayersInRoomRequest request;
	std::vector<std::string> playersInRoom;
	try
	{
		request = JsonRequestPacketDeserializer::deserializeRequest<Requests::GetPlayersInRoomRequest>(reqInfo.buffer);
	}
	catch (InvalidJsonException& e)
	{
		return this->m_handleError(e.what(), this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser));
	}
	try
	{
		playersInRoom = this->m_handlerFactory.getRoomManager().getRoomPlayerUsernames(request.roomId);
	}
	catch (RoomDoesNotExistException & e)
	{
		return this->m_handleError(e.what(), this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser));
	}
	reqResult.newHandler = new MenuRequestHandler(this->m_handlerFactory, this->m_loggedUser);
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(Responses::GetPlayersInRoomResponse{ playersInRoom });
	return reqResult;

}

RequestResult MenuRequestHandler::m_getStatistics(const Requests::RequestInfo& reqInfo)
{
	RequestResult reqResult;
	reqResult.newHandler = new MenuRequestHandler(this->m_handlerFactory, this->m_loggedUser);
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(this->m_handlerFactory.getStatisticsManager().getStatistics(this->m_loggedUser.getUsername()));
	return reqResult;
}

RequestResult MenuRequestHandler::m_joinRoom(const Requests::RequestInfo& reqInfo)
{
	RequestResult reqResult;
	Requests::JoinRoomRequest request;
	try
	{
		request = JsonRequestPacketDeserializer::deserializeRequest<Requests::JoinRoomRequest>(reqInfo.buffer);
	}
	catch (InvalidJsonException& e)
	{
		return this->m_handleError(e.what(), this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser));
	}

	try
	{
		if (this->m_handlerFactory.getRoomManager().getRoomState(request.roomId))
		{
			return this->m_handleError("The game in that room has already started!", this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser));
		}
		else
		{
			this->m_handlerFactory.getRoomManager().addUserToRoom(request.roomId, this->m_loggedUser);
		}
	}
	catch (RoomDoesNotExistException& e)
	{
		return this->m_handleError(e.what(), this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser));
	}
	catch (RoomMaxPlayersLimitReachedException& e)
	{
		return this->m_handleError(e.what(), this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser));
	}
	reqResult.newHandler = this->m_handlerFactory.createRoomMemberRequestHandler(this->m_loggedUser, request.roomId);
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(Responses::JoinRoomResponse{ 1 });
	return reqResult;
}

RequestResult MenuRequestHandler::m_createRoom(const Requests::RequestInfo& reqInfo)
{
	RequestResult reqResult;
	Requests::CreateRoomRequest request;
	RoomData createdRoomData;
	try
	{
		request = JsonRequestPacketDeserializer::deserializeRequest<Requests::CreateRoomRequest>(reqInfo.buffer);
	}
	catch (InvalidJsonException& e)
	{
		return this->m_handleError(e.what(), this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser));
	}
	createdRoomData.isActive = false;
	createdRoomData.maxPlayers = request.maxUsers;
	createdRoomData.numOfQuestionsInGame = request.questionCount;
	createdRoomData.owner = this->m_loggedUser;
	createdRoomData.roomName = request.roomName;
	createdRoomData.secondsPerQuestion = request.answerTimeout;
	if (createdRoomData.roomName.size() < 1 || createdRoomData.roomName.size() > MAX_ROOM_NAME_LENGTH)
	{
		return this->m_handleError("Invalid room name length! (must be between 1 to " + std::to_string(MAX_ROOM_NAME_LENGTH) +")", this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser));
	}
	if (createdRoomData.maxPlayers < 1 || createdRoomData.maxPlayers > MAX_ROOM_MAX_PLAYERS)
	{
		return this->m_handleError("Invalid max amount of players! (must be between 1 to " + std::to_string(MAX_ROOM_MAX_PLAYERS) + ")", this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser));
	}
	if (createdRoomData.numOfQuestionsInGame < 1 || createdRoomData.numOfQuestionsInGame > MAX_ROOM_AMOUNT_OF_QUESTION)
	{
		return this->m_handleError("Invalid amount of questions! (must be between 1 to " + std::to_string(MAX_ROOM_AMOUNT_OF_QUESTION) + ")", this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser));
	}
	if (createdRoomData.secondsPerQuestion < 1 || createdRoomData.secondsPerQuestion > MAX_ROOM_SECONDS_PER_QUESTION)
	{
		return this->m_handleError("Invalid amount of questions! (must be between 1 to " + std::to_string(MAX_ROOM_SECONDS_PER_QUESTION) + ")", this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser));
	}
	unsigned int roomId = this->m_handlerFactory.getRoomManager().createRoom(createdRoomData);

	reqResult.newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(this->m_loggedUser, roomId);
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(Responses::CreateRoomResponse{ 1 });
	return reqResult;
}
