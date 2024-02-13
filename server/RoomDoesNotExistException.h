#pragma once

#include <exception>
#include <string>
class RoomDoesNotExistException : public std::exception
{
public:
	RoomDoesNotExistException(unsigned int id);
	virtual const char* what() const override;
private:
	std::string m_errMessage;
};


