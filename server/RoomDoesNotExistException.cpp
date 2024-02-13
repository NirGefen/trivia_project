#include "RoomDoesNotExistException.h"

RoomDoesNotExistException::RoomDoesNotExistException(unsigned int id) :
	m_errMessage("Error! there is no room with id " + std::to_string(id) + " !")
{
}

const char* RoomDoesNotExistException::what() const
{
	return this->m_errMessage.c_str();
}
