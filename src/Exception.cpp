#include "Exception.h"

CoordinateRangeException::CoordinateRangeException() : message("Error: ") {}

CoordinateRangeException::CoordinateRangeException(string msg) : message("Error: " + msg) {}

CoordinateRangeException::~CoordinateRangeException() throw() {}

const char * CoordinateRangeException::what() const throw()
{
	return message.c_str;
}

//------------------------------------------------------------------------------------------------------

CoordinateCoincidenceException::CoordinateCoincidenceException() : message("Error: ") {}

CoordinateCoincidenceException::CoordinateCoincidenceException(string msg) : message("Error: " + msg) {}

CoordinateCoincidenceException::~CoordinateCoincidenceException() throw() {}

const char * CoordinateCoincidenceException::what() const throw()
{
	return message.c_str;
}

//------------------------------------------------------------------------------------------------------

LineCoincidenceException::LineCoincidenceException() : message("Error: ") {}

LineCoincidenceException::LineCoincidenceException(string msg) : message("Error: " + msg) {}

LineCoincidenceException::~LineCoincidenceException() throw() {}

const char * LineCoincidenceException::what() const throw()
{
	return message.c_str;
}

//------------------------------------------------------------------------------------------------------

CircleCoincidenceException::CircleCoincidenceException() : message("Error: ") {}

CircleCoincidenceException::CircleCoincidenceException(string msg) : message("Error: " + msg) {}

CircleCoincidenceException::~CircleCoincidenceException() throw() {}

const char * CircleCoincidenceException::what() const throw()
{
	return message.c_str;
}

//------------------------------------------------------------------------------------------------------

NegativeRadiusException::NegativeRadiusException() : message("Error: ") {}

NegativeRadiusException::NegativeRadiusException(string msg) : message("Error: " + msg) {}

NegativeRadiusException::~NegativeRadiusException() throw() {}

const char * NegativeRadiusException::what() const throw()
{
	return message.c_str;
}

//------------------------------------------------------------------------------------------------------

UndefinedLineException::UndefinedLineException() : message("Error: ") {}

UndefinedLineException::UndefinedLineException(string msg) : message("Error: " + msg) {}

UndefinedLineException::~UndefinedLineException() throw() {}

const char * UndefinedLineException::what() const throw()
{
	return message.c_str;
}

