#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
class RoomMemberRequestHandler :
	public IRequestHandler
{
public:
	RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& loggedUser, unsigned int roomId);
	virtual ~RoomMemberRequestHandler();
	virtual bool isRequestRelevant(const Requests::RequestInfo& reqInfo) const override;
	virtual RequestResult handleRequest(const Requests::RequestInfo& reqInfo) override;
	virtual void handleExit() override;
private:
	LoggedUser m_loggedUser;
	unsigned int m_roomId;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult m_leaveRoom(const Requests::RequestInfo& reqInfo);
	RequestResult m_getRoomState(const Requests::RequestInfo& reqInfo);
	static const std::unordered_map<ProtocolRequestHeaderCode, RequestResult(RoomMemberRequestHandler::*)(const Requests::RequestInfo&)> m_caseFuncs;
};
