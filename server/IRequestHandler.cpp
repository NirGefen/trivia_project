#include "IRequestHandler.h"

RequestResult IRequestHandler::m_handleError(const std::string& errDetails, IRequestHandler* newHandler) const
{
	Responses::ErrorResponse errorResponse;
	RequestResult errResult;
	errorResponse.message = errDetails;
	errResult.newHandler = newHandler;
	errResult.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);
	return errResult;
}
