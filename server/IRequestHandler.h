#pragma once
#include "RequestInfo.h"
#include "RequestResult.h"
#include "ErrorResponse.h"
#include "JsonResponsePacketSerializer.h"
#define ERR_REQ_NOT_RELAVANT "Request Not Relavant!"
#define ERR_INVALID_FORMAT "Invalid Format for Request!"

typedef struct RequestResult RequestResult;
class IRequestHandler
{
public:
	IRequestHandler() {};
	virtual ~IRequestHandler() {};
	virtual bool isRequestRelevant(const Requests::RequestInfo& reqInfo) const = 0;
	virtual RequestResult handleRequest(const Requests::RequestInfo& reqInfo) = 0;
	virtual void handleExit() = 0;
protected:
	RequestResult m_handleError(const std::string& errDetails, IRequestHandler* newHandler) const;
};