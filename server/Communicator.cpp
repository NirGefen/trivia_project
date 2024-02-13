#include "Communicator.h"

/***************************************************************
 @ brief: a ctor for Communicator
 [>>] json* pConfig: the config pointer for the communicator
 [>>] RequestHandlerFactory& handlerFactory: a reference to the handle factory to be used by the communicator
 [<<] X
****************************************************************/
Communicator::Communicator(json* pConfig, RequestHandlerFactory& handlerFactory) :
	m_pConfig(pConfig),  m_handlerFactory(handlerFactory)
{
	this->m_listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->m_listeningSocket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}
}

/***************************************************************
 @ brief: a dtor for Communicator
 [>>] Void
 [<<] X
****************************************************************/
Communicator::~Communicator()
{
	std::lock_guard<std::mutex> lck(this->mtx_mClients);
	for (auto& clientStatePair : this->m_clients)
	{
		delete clientStatePair.second;
	}
	this->m_clients.clear();
}

/***************************************************************
 @ brief: sets the config pointer of the communicator
 [>>] json* pConfig: the address to set the config pointer to
 [<<] Void
****************************************************************/
void Communicator::setConfig(json* pConfig)
{
	this->m_pConfig = pConfig;
}

/***************************************************************
 @ brief: a method for starting the listening and the actual server funcitonality, starting to handle requests
 [>>] Void
 [<<] Void
****************************************************************/
void Communicator::startHandleRequests()
{
	if (this->m_pConfig == nullptr)  // should never happen
	{
		throw std::runtime_error("missing config json");
	}
	this->bindAndListen();

	while (true)
	{
		SOCKET clientSocket = accept(this->m_listeningSocket, NULL, NULL);

		if (clientSocket == INVALID_SOCKET)
		{
			throw std::exception(__FUNCTION__);
		}
		std::lock_guard<std::mutex> lck(this->mtx_mClients);
		this->m_clients.insert({ clientSocket, this->m_handlerFactory.createLoginRequestHandler() });
		std::thread t_Client = std::thread(&Communicator::handleNewClient, this, clientSocket);
		t_Client.detach();
	}
}

/***************************************************************
 @ brief: client handler
 [>>] SOCKET clientSock: the client communication socket
 [<<] Void
****************************************************************/
void Communicator::handleNewClient(SOCKET clientSock)
{
	Requests::RequestInfo currentRequest;
	Responses::ErrorResponse errorResponse;
	RequestResult reqResult;
	bool shouldRun = true;
	try
	{
		this->handshake(clientSock);
	}
	catch (HandshakeException &)
	{
		shouldRun = false;
	}
	catch (...)
	{
		shouldRun = false;
	}
	while (shouldRun)
	{
		try
		{
			currentRequest = SocketManager::getRequest(clientSock);
		}
		catch (...)
		{
			shouldRun = false;
			break;
		}
		std::lock_guard<std::mutex> lck(this->mtx_mClients);
		try
		{
			reqResult = this->m_clients[clientSock]->handleRequest(currentRequest);
		}
		catch (...)
		{
			shouldRun = false;
			break;
		}
		try
		{
			SocketManager::sendBuffer(clientSock, reqResult.response);
		}
		catch (...)
		{
			delete reqResult.newHandler;
			shouldRun = false;
			break;
		}
		delete this->m_clients[clientSock];
		this->m_clients[clientSock] = reqResult.newHandler;
	}
	std::lock_guard<std::mutex> lck(this->mtx_mClients);
	this->m_clients[clientSock]->handleExit();
	delete this->m_clients[clientSock];
	this->m_clients.erase(clientSock);
	closesocket(clientSock);
}

/***************************************************************
 @ brief: setting up the listening socket & binding
 [>>] Void
 [<<] Void
****************************************************************/
void Communicator::bindAndListen()
{
	unsigned int port = 0;
	try
	{
		port = (*this->m_pConfig)[PORT_KEY];
	}
	catch (json::exception &)
	{
		port = PORT_DEFAULT;
	}

	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(this->m_listeningSocket, (struct sockaddr*) & sa, sizeof(sa)) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - bind");
	}

	// Start listening for incoming requests of clients
	if (listen(this->m_listeningSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - listen");
	}
}

// performing a handshake
void Communicator::handshake(SOCKET clientSock)
{
	std::string handshakeString = "";
	std::string reply = "no reply";
	try
	{
		handshakeString = (*this->m_pConfig)[HANDSHAKE_MESSAGE_KEY];
	}
	catch (json::exception &)
	{
		handshakeString = HANDSHAKE_MESSAGE_DEFAULT;
	}
	try
	{
		SocketManager::sendString(clientSock, handshakeString);
		reply = SocketManager::getString(clientSock, handshakeString.length());
		std::cout << clientSock << ": " << reply << std::endl;
	}
	catch (...)
	{
		throw HandshakeException("Socket Error!");
	}
	if (reply != handshakeString)
	{
		throw HandshakeException("Invalid Handshake Reply!");
	}
}