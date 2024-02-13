#include "LoginRequestHandler.h"

const std::unordered_map<ProtocolRequestHeaderCode, RequestResult(LoginRequestHandler::*)(const Requests::RequestInfo&)> LoginRequestHandler::m_caseFuncs({
	{ ProtocolRequestHeaderCode::REQUEST_LOGIN_CODE, &(LoginRequestHandler::m_login) },
	{ ProtocolRequestHeaderCode::REQUEST_SIGNUP_CODE, &(LoginRequestHandler::m_signup) }
});

/***************************************************************
 @ brief: ctor for LoginRequestHandler
 [>>] RequestHandlerFactory& handlerFactory: a reference to the handler factory
 [<<] X
****************************************************************/
LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) :
	IRequestHandler(), m_handlerFactory(handlerFactory)
{
}

/***************************************************************
 @ brief: isRequestRelevant for LoginRequestHandler
 [>>] const Requests::RequestInfo& reqInfo: the request info
 [<<] bool: whether or not the request is relavant to the handler
****************************************************************/
bool LoginRequestHandler::isRequestRelevant(const Requests::RequestInfo& reqInfo) const
{
	return LoginRequestHandler::m_caseFuncs.find(reqInfo.id) != LoginRequestHandler::m_caseFuncs.end();
}

/***************************************************************
 @ brief: handleRequest for LoginRequestHandler
 [>>] const Requests::RequestInfo& reqInfo: the request info
 [<<] RequestResult: the result of the request
****************************************************************/
RequestResult LoginRequestHandler::handleRequest(const Requests::RequestInfo& reqInfo)
{
	Responses::ErrorResponse errorResponse;
	RequestResult reqResult;
	if (!this->isRequestRelevant(reqInfo))
	{
		reqResult = this->m_handleError(ERR_REQ_NOT_RELAVANT, this->m_handlerFactory.createLoginRequestHandler());
	}
	else
	{
		reqResult = std::invoke(LoginRequestHandler::m_caseFuncs.at(reqInfo.id), this, reqInfo);
	}
	return reqResult;
}

void LoginRequestHandler::handleExit()
{
}

/***************************************************************
 @ brief: login case for the handler (login request)
 [>>] const Requests::RequestInfo& reqInfo: the request info
 [<<] RequestResult: the result of the request
****************************************************************/
RequestResult LoginRequestHandler::m_login(const Requests::RequestInfo& reqInfo)
{
	RequestResult reqResult;
	Responses::LoginResponse loginResult;
	Requests::LoginRequest loginReq;
	try
	{
		loginReq = JsonRequestPacketDeserializer::deserializeRequest<Requests::LoginRequest>(reqInfo.buffer);
	}
	catch (InvalidJsonException& e)
	{
		return this->m_handleError(e.what(), this->m_handlerFactory.createLoginRequestHandler());
	}
	loginResult.status = this->m_handlerFactory.getLoginManager().login(loginReq.username, loginReq.password) ? 1 : 0;
	if (loginResult.status)
	{
		reqResult.newHandler = this->m_handlerFactory.createMenuRequestHandler(LoggedUser(loginReq.username));
	}
	else
	{
		reqResult.newHandler = this->m_handlerFactory.createLoginRequestHandler();
	}
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(loginResult);
	return reqResult;
}

/***************************************************************
 @ brief: signup case for the handler (signup request)
 [>>] const Requests::RequestInfo& reqInfo: the request info
 [<<] RequestResult: the result of the request
****************************************************************/
RequestResult LoginRequestHandler::m_signup(const Requests::RequestInfo& reqInfo)
{
	RequestResult reqResult;
	Responses::SignupResponse signupResult;
	Requests::SignupRequest signupReq;
	try
	{
		signupReq = JsonRequestPacketDeserializer::deserializeRequest<Requests::SignupRequest>(reqInfo.buffer);
	}
	catch (InvalidJsonException& e)
	{
		return this->m_handleError(e.what(), this->m_handlerFactory.createLoginRequestHandler());
	}
	try
	{
		signupResult.status = this->m_handlerFactory.getLoginManager().signup(signupReq.username, signupReq.password, signupReq.email) ? 1 : 0;
	}
	catch (QueryFailureException & e)
	{
		return this->m_handleError("Signup Error! Error Details: " + std::string(e.what()) + "\nMost likely the email is already used.", this->m_handlerFactory.createLoginRequestHandler());
	}
	reqResult.newHandler = this->m_handlerFactory.createLoginRequestHandler();
	reqResult.response = JsonResponsePacketSerializer::serializeResponse(signupResult);
	return reqResult;
}