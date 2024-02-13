#pragma once

#include <vector>
#include <string>
#include <WinSock2.h>
#include "typedefs.h"
#include "protocolHeaderCodes.h"
#include <ctime>
#include "SocketManagerException.h"
#include "RequestInfo.h"
#define MAX_PACKET_LEN 65536

class SocketManager
{
public:
	static Requests::RequestInfo getRequest(SOCKET s);
	static std::string getString(SOCKET s, unsigned int length);
	static void sendBuffer(SOCKET s, const buffer& bufToSend);
	static void sendString(SOCKET s, const std::string& strToSend);
private:
	static buffer m_getBuffer(SOCKET s, unsigned int length);
	static ProtocolRequestHeaderCode m_getRequestHeaderCode(SOCKET s);
	static unsigned int m_getUint(SOCKET s);
	static void m_recv(SOCKET s, char* mem, unsigned int length);
	static void m_send(SOCKET s, char* mem, unsigned int length);
};

