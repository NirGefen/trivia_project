#pragma once

#include "IRequestHandler.h"
#include "ErrorResponse.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "ErrorResponse.h"
#include "RequestHandlerFactory.h"
#include <unordered_map>

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& handlerFactory);
	virtual ~LoginRequestHandler() {};
	virtual bool isRequestRelevant(const Requests::RequestInfo& reqInfo) const override;
	virtual RequestResult handleRequest(const Requests::RequestInfo& reqInfo) override;
	virtual void handleExit() override;
private:
	RequestHandlerFactory& m_handlerFactory;
	RequestResult m_login(const Requests::RequestInfo& reqInfo);
	RequestResult m_signup(const Requests::RequestInfo& reqInfo);
	static const std::unordered_map<ProtocolRequestHeaderCode, RequestResult(LoginRequestHandler::*)(const Requests::RequestInfo&)> m_caseFuncs;

};
