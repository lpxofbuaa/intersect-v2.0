#pragma once
#include <exception>
#include <string>

using namespace std;

class CoordinateRangeException : public exception {
public:
	CoordinateRangeException();
	CoordinateRangeException(string msg);
	~CoordinateRangeException() throw();
	virtual const char* what() const throw ();
private:
	string message;
};

class CoordinateCoincidenceException : public exception {
public:
	CoordinateCoincidenceException();
	CoordinateCoincidenceException(string msg);
	~CoordinateCoincidenceException() throw();
	virtual const char* what() const throw ();
private:
	string message;
};

class LineCoincidenceException : public exception {
public:
	LineCoincidenceException();
	LineCoincidenceException(string msg);
	~LineCoincidenceException() throw();
	virtual const char* what() const throw ();
private:
	string message;
};

class NegativeRadiusException : public exception {
public:
	NegativeRadiusException();
	NegativeRadiusException(string msg);
	~NegativeRadiusException() throw();
	virtual const char* what() const throw ();
private:
	string message;
};

class UndefinedLineException : public exception {
public:
	UndefinedLineException();
	UndefinedLineException(string msg);
	~UndefinedLineException() throw();
	virtual const char* what() const throw ();
private:
	string message;
};