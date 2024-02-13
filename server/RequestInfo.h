#pragma once

#include "protocolHeaderCodes.h"
#include "typedefs.h"
#include <ctime>
namespace Requests
{
	typedef struct RequestInfo
	{
		ProtocolRequestHeaderCode id;
		time_t receivalTime;
		buffer buffer;
	} RequestInfo;
}