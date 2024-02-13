#include "RoomMaxPlayersLimitReachedException.h"

RoomMaxPlayersLimitReachedException::RoomMaxPlayersLimitReachedException(unsigned int maxLimit) :
	m_errMessage("Error! That room is full! (" + std::to_string(maxLimit) + "/" + std::to_string(maxLimit) + " players)")
{
}

const char* RoomMaxPlayersLimitReachedException::what() const
{
	return this->m_errMessage.c_str();
}
