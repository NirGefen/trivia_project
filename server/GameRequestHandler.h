#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "SubmitAnswerRequest.h"
class RequestHandlerFactory;
class GameRequestHandler :
	public IRequestHandler
{
public:
	GameRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& loggedUser, unsigned int roomId);
	virtual ~GameRequestHandler();
	virtual bool isRequestRelevant(const Requests::RequestInfo& reqInfo) const override;
	virtual RequestResult handleRequest(const Requests::RequestInfo& reqInfo) override;
	virtual void handleExit() override;
private:
	unsigned int m_roomId;
	LoggedUser m_loggedUser;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult m_leaveGame(const Requests::RequestInfo& reqInfo);
	RequestResult m_getQuestion(const Requests::RequestInfo& reqInfo);
	RequestResult m_submitAnswer(const Requests::RequestInfo& reqInfo);
	RequestResult m_getGameResults(const Requests::RequestInfo& reqInfo);
	static const std::unordered_map<ProtocolRequestHeaderCode, RequestResult(GameRequestHandler::*)(const Requests::RequestInfo&)> m_caseFuncs;
};
