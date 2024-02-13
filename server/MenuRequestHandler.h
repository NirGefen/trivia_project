#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
class MenuRequestHandler :
	public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& loggedUser);
	virtual ~MenuRequestHandler();
	virtual bool isRequestRelevant(const Requests::RequestInfo& reqInfo) const override;
	virtual RequestResult handleRequest(const Requests::RequestInfo& reqInfo) override;
	virtual void handleExit() override;
private:
	LoggedUser m_loggedUser;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult m_signout(const Requests::RequestInfo& reqInfo);
	RequestResult m_getRooms(const Requests::RequestInfo& reqInfo);
	RequestResult m_getPlayersInRoom(const Requests::RequestInfo& reqInfo);
	RequestResult m_getStatistics(const Requests::RequestInfo& reqInfo);
	RequestResult m_joinRoom(const Requests::RequestInfo& reqInfo);
	RequestResult m_createRoom(const Requests::RequestInfo& reqInfo);
	static const std::unordered_map<ProtocolRequestHeaderCode, RequestResult(MenuRequestHandler::*)(const Requests::RequestInfo&)> m_caseFuncs;
};
