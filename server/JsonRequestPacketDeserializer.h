#pragma once

#include "typedefs.h"
#include "LoginRequest.h"
#include "SignupRequest.h"
#include "CreateRoomRequest.h"
#include "GetPlayersInRoomRequest.h"
#include "JoinRoomRequest.h"
#include "InvalidJsonException.h"
#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

class JsonRequestPacketDeserializer
{
public:
	template<class T> static T deserializeRequest(const buffer& serRequest);
};

/***************************************************************
 @ brief: deserializes a given json buffer to a struct
 [>>] const buffer&: the json buffer to be deserialized
 [<<] T: the deserialized request struct
****************************************************************/
template<class T> static T JsonRequestPacketDeserializer::deserializeRequest(const buffer& serRequest)
{
    try
    {
        return json::parse(serRequest).get<T>();
    }
    catch (json::exception & e)
    {
        throw InvalidJsonException(e.what());
    }
};