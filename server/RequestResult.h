#pragma once


#include "IRequestHandler.h"
#include "typedefs.h"

class IRequestHandler;
typedef struct RequestResult
{
	buffer response;
	IRequestHandler* newHandler=nullptr;
} RequestResult;
