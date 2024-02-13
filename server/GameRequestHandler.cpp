#include "GameRequestHandler.h"

const std::unordered_map<ProtocolRequestHeaderCode, RequestResult(GameRequestHandler::*)(const Requests::RequestInfo&)> GameRequestHandler::m_caseFuncs({
	{ ProtocolRequestHeaderCode::REQUEST_LEAVE_GAME_CODE, &(GameRequestHandler::m_leaveGame) },
	{ ProtocolRequestHeaderCode::REQUEST_SUBMIT_ANSWER_CODE, &(GameRequestHandler::m_submitAnswer) },
	{ ProtocolRequestHeaderCode::REQUEST_GET_QUESTION_CODE, &(GameRequestHandler::m_getQuestion) },
	{ ProtocolRequestHeaderCode::REQUEST_GET_GAME_RESULTS_CODE, &(GameRequestHandler::m_getGameResults) },
	});
GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& loggedUser, unsigned int roomId) :
	m_handlerFactory(handlerFactory), m_loggedUser(loggedUser), m_roomId(roomId)
{

}

GameRequestHandler::~GameRequestHandler()
{
}

bool GameRequestHandler::isRequestRelevant(const Requests::RequestInfo& reqInfo) const
{
	return GameRequestHandler::m_caseFuncs.find(reqInfo.id) != GameRequestHandler::m_caseFuncs.end();
}

RequestResult GameRequestHandler::handleRequest(const Requests::RequestInfo& reqInfo)
{
	Responses::ErrorResponse errorResponse;
	RequestResult reqResult;
	if (!this->isRequestRelevant(reqInfo))
	{
		reqResult = this->m_handleError(ERR_REQ_NOT_RELAVANT, this->m_handlerFactory.createGameRequestHandler(this->m_loggedUser, this->m_roomId));
	}
	else
	{
		reqResult = std::invoke(GameRequestHandler::m_caseFuncs.at(reqInfo.id), this, reqInfo);
	}
	return reqResult;
}

void GameRequestHandler::handleExit()
{
	try
	{
		this->m_handlerFactory.getRoomManager().deleteUserFromRoom(this->m_roomId, this->m_loggedUser.getUsername());
	}
	catch (...)
	{
	}
	try
	{
		if (this->m_handlerFactory.getGameManager().removePlayer(this->m_loggedUser.getUsername(), this->m_handlerFactory.getRoomManager().getGameId(this->m_roomId)))
		{
			this->m_handlerFactory.getRoomManager().deleteRoom(this->m_roomId);
		}
	}
	catch (...)
	{
	}
	this->m_handlerFactory.getLoginManager().logout(this->m_loggedUser.getUsername());
}

RequestResult GameRequestHandler::m_leaveGame(const Requests::RequestInfo& reqInfo)
{
	RequestResult reqResult;
	Responses::LeaveGameResponse response;
	try
	{
		this->m_handlerFactory.getRoomManager().deleteUserFromRoom(this->m_roomId, this->m_loggedUser);
	}
	catch (...)
	{
	}
	try
	{
		if (this->m_handlerFactory.getGameManager().removePlayer(this->m_loggedUser.getUsername(), this->m_handlerFactory.getRoomManager().getGameId(this->m_roomId)))
		{
			this->m_handlerFactory.getRoomManager().deleteRoom(this->m_roomId);
		}
	}
	catch (...)
	{
	}

	response.status = 1;
	reqResult.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser);
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return reqResult;
	
}

RequestResult GameRequestHandler::m_getQuestion(const Requests::RequestInfo& reqInfo)
{
	RequestResult reqResult;
	Responses::GetQuestionResponse response;
	try
	{
		response = this->m_handlerFactory.getGameManager().getQuestionForUser(this->m_loggedUser.getUsername(), this->m_handlerFactory.getRoomManager().getGameId(this->m_roomId));
	}
	catch (std::exception & e)
	{
		return this->m_handleError(e.what(), this->m_handlerFactory.createGameRequestHandler(this->m_loggedUser, this->m_roomId));
	}
	reqResult.newHandler = this->m_handlerFactory.createGameRequestHandler(this->m_loggedUser, this->m_roomId);
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return reqResult;
}

RequestResult GameRequestHandler::m_submitAnswer(const Requests::RequestInfo& reqInfo)
{
	RequestResult reqResult;
	Requests::SubmitAnswerRequest request;
	Responses::SubmitAnswerResponse response;
	try
	{
		request = JsonRequestPacketDeserializer::deserializeRequest<Requests::SubmitAnswerRequest>(reqInfo.buffer);
	}
	catch (InvalidJsonException & e)
	{
		return this->m_handleError(e.what(), this->m_handlerFactory.createGameRequestHandler(this->m_loggedUser, this->m_roomId));
	}
	try
	{
		response = this->m_handlerFactory.getGameManager().submitAnswer(this->m_loggedUser.getUsername(), request.answerId, this->m_handlerFactory.getRoomManager().getGameId(this->m_roomId));

	}
	catch (std::exception & e)
	{
		return this->m_handleError(e.what(), this->m_handlerFactory.createGameRequestHandler(this->m_loggedUser, this->m_roomId));
	}
	reqResult.newHandler = this->m_handlerFactory.createGameRequestHandler(this->m_loggedUser, this->m_roomId);
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return reqResult;

}

RequestResult GameRequestHandler::m_getGameResults(const Requests::RequestInfo& reqInfo)
{
	RequestResult reqResult;
	Responses::GetGameResultsResponse response;
	try
	{
		response = this->m_handlerFactory.getGameManager().getGameResults(this->m_handlerFactory.getRoomManager().getGameId(this->m_roomId));

	}
	catch (std::exception & e)
	{
		return this->m_handleError(e.what(), this->m_handlerFactory.createGameRequestHandler(this->m_loggedUser, this->m_roomId));
	}
	if (response.status == 1)
	{
		try
		{
			this->m_handlerFactory.getRoomManager().deleteUserFromRoom(this->m_roomId, this->m_loggedUser);
		}
		catch (...)
		{
		}
		try
		{
			if (this->m_handlerFactory.getGameManager().removePlayer(this->m_loggedUser.getUsername(), this->m_handlerFactory.getRoomManager().getGameId(this->m_roomId)))
			{
				// no players left, remove the room
				this->m_handlerFactory.getRoomManager().deleteRoom(this->m_roomId);
			}
		}
		catch (...)
		{
		}
		reqResult.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser);
	}
	else
	{
		reqResult.newHandler = this->m_handlerFactory.createGameRequestHandler(this->m_loggedUser, this->m_roomId);
	}
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return reqResult;

}

