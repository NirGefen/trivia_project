#include "SocketManager.h"

/***************************************************************
 @ brief: get a request from a given socket
 [>>] SOCKET s: the socket to be used
 [<<] Requests::RequestInfo: a struct containing the request header code, the receival time & the pure serialized json chunk (without the header & size chunks)
****************************************************************/
Requests::RequestInfo SocketManager::getRequest(SOCKET s)
{
	Requests::RequestInfo recvReqInfo;
	recvReqInfo.id = SocketManager::m_getRequestHeaderCode(s);
	time(&recvReqInfo.receivalTime);
	unsigned int dataLength = SocketManager::m_getUint(s);
	if (dataLength > MAX_PACKET_LEN)
	{
		throw SocketManagerException("getRequest - suspisioucly long data (received length: " + std::to_string(dataLength) + ")");
	}
	recvReqInfo.buffer = SocketManager::m_getBuffer(s, dataLength);
	return recvReqInfo;
}

/***************************************************************
 @ brief: get a string of a given length from a given socket
 [>>] SOCKET s: the socket to be used
 [>>] unsigned int length: the length of the string to be extracted from the socket
 [<<] std::string: the extracted string
****************************************************************/
std::string SocketManager::getString(SOCKET s, unsigned int length)
{
	std::string outString = "";
	char* recvCharStr = nullptr;
	if (length)
	{
		char* recvCharStr = new char[length + 1];
		recvCharStr[length] = 0;
		try
		{
			SocketManager::m_recv(s, recvCharStr, length);
		}
		catch (...)
		{
			delete[] recvCharStr;
			throw SocketManagerException("m_send - Unknown error");
		}
		outString = std::string(recvCharStr);
	}
	return outString;
}

/***************************************************************
 @ brief: send a given string through a socket
 [>>] SOCKET s: the socket to be used
 [>>] const std::string& strToSend: the string to be sent
 [<<] Void
****************************************************************/
void SocketManager::sendString(SOCKET s, const std::string& strToSend)
{
	SocketManager::m_send(s, (char*)strToSend.c_str(), strToSend.length() * sizeof(char));
}

/***************************************************************
 @ brief: send a given buffer through a socket
 [>>] SOCKET s: the socket to be used
 [>>] const buffer& bufToSend: the buffer to be sent
 [<<] Void
****************************************************************/
void SocketManager::sendBuffer(SOCKET s, const buffer& bufToSend)
{
	SocketManager::m_send(s, (char*)bufToSend.data(), bufToSend.size() * sizeof(bufdata));
}

/***************************************************************
 @ brief: get a buffer of a given length from a given socket
 [>>] SOCKET s: the socket to be used
 [>>] unsigned int length: the length of the buffer to be extracted from the socket
 [<<] buffer: the extracted buffer
****************************************************************/
buffer SocketManager::m_getBuffer(SOCKET s, unsigned int length)
{
	buffer outBuffer = buffer();
	if (length)
	{
		outBuffer.resize(length);
		SocketManager::m_recv(s, (char*)(outBuffer.data()), sizeof(bufdata) * length);
	}
	return outBuffer;
}

/***************************************************************
 @ brief: get a request header code from a given socket
 [>>] SOCKET s: the socket to be used
 [<<] ProtocolRequestHeaderCode: the extracted header code from the socket
 NOTE: throws exception if received header is unknown
****************************************************************/
ProtocolRequestHeaderCode SocketManager::m_getRequestHeaderCode(SOCKET s)
{
	bufdata reqHeader = 0;
	SocketManager::m_recv(s, (char*)&reqHeader, sizeof(reqHeader));
	if (requestHeaderCodes.find(reqHeader) == requestHeaderCodes.end())
	{
		throw SocketManagerException("m_getRequestHeaderCode - Unkown Request Header");
	}
	return ProtocolRequestHeaderCode(reqHeader);
}

/***************************************************************
 @ brief: get a uint from a given socket
 [>>] SOCKET s: the socket to be used
 [<<] unsigned int: the etxracted uint
****************************************************************/
unsigned int SocketManager::m_getUint(SOCKET s)
{
	unsigned int recvUint = 0;
	SocketManager::m_recv(s, (char*)&recvUint, sizeof(recvUint));
	return recvUint;
}

/***************************************************************
 @ brief: recv a given amount of bytes to a given address
 [>>] SOCKET s: the socket to be used
 [>>] char* mem: a pointer to where to store the received bytes at
 [>>] unsigned int length: the amount of bytes to receive (extract) from the socket
 [<<] Void
****************************************************************/
void SocketManager::m_recv(SOCKET s, char* mem, unsigned int length)
{
	if (mem == nullptr)
	{
		throw SocketManagerException("m_recv - mem pointer was nullptr");
	}
	try
	{
		recv(s, mem, length, 0);
	}
	catch (...)
	{
		throw SocketManagerException("m_recv - Unknown error");
	}
}

/***************************************************************
 @ brief: send given bytes through a given socket
 [>>] SOCKET s: the socket to be used
 [>>] char* mem: a pointer to the bytes to be sent
 [>>] unsigned int length: the amount of bytes to send (from the memory block pointed to by mem)
 [<<] Void
****************************************************************/
void SocketManager::m_send(SOCKET s, char* mem, unsigned int length)
{
	if (mem == nullptr)
	{
		throw SocketManagerException("m_send - mem pointer was nullptr");
	}
	try
	{
		send(s, mem, length, 0);
	}
	catch (...)
	{
		throw SocketManagerException("m_send - Unknown error");
	}
}
