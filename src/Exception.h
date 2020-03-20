#pragma once
#include "stdafx.h"
#include <exception>
#include <string>
#include "GeometryShape.h"

using namespace std;

/*
 * 坐标范围异常 For ADD
*/
class CoordinateRangeException : public exception {
public:
	CoordinateRangeException();
	CoordinateRangeException(string msg);
	~CoordinateRangeException() throw();
	virtual const char* what() const throw ();
private:
	string message;
};

/*
 * Line型坐标重合冲突异常 For ADD
*/
class CoordinateCoincidenceException : public exception {
public:
	CoordinateCoincidenceException();
	CoordinateCoincidenceException(string msg);
	~CoordinateCoincidenceException() throw();
	virtual const char* what() const throw ();
private:
	string message;
};

/*
 * Line型几何对象冲突异常 For ADD
 *       直线      射线      线段    
 * 直线   x         x         x
 * 射线   x         o         o
 * 线段   x         o         o
*/
class LineCoincidenceException : public exception {
public:
	LineCoincidenceException();
	LineCoincidenceException(string msg);
	~LineCoincidenceException() throw();
	virtual const char* what() const throw ();
	Line coincidence;
private:
	string message;
};

/*
 * Circle型几何对象冲突异常 For ADD
*/
class CircleCoincidenceException : public exception {
public:
	CircleCoincidenceException();
	CircleCoincidenceException(string msg);
	~CircleCoincidenceException() throw();
	virtual const char* what() const throw ();
	Circle coincidence;
private:
	string message;
};

/*
 * Circle型几何对象参数非法异常 For ADD
*/
class NegativeRadiusException : public exception {
public:
	NegativeRadiusException();
	NegativeRadiusException(string msg);
	~NegativeRadiusException() throw();
	virtual const char* what() const throw ();
private:
	string message;
};

/*
 * 未定义的Line型的具体类型未知异常 For REMOVE
*/
class UndefinedLineException : public exception {
public:
	UndefinedLineException();
	UndefinedLineException(string msg);
	~UndefinedLineException() throw();
	virtual const char* what() const throw ();
private:
	string message;
};

/*
 * todo: 与UndefinedLineException的关系。
 * 未定义的几何对象异常 For REMOVE
*/
class ObjectNotFoundException : public exception {
public:
	ObjectNotFoundException();
	ObjectNotFoundException(string msg);
	~ObjectNotFoundException() throw();
	virtual const char* what() const throw ();
private:
	string message;
};

//-------------------------------------------------------------------------------------

/*
 * 输入object类型不对
*/
class WrongFormatException : public exception {
public:
	WrongFormatException();
	WrongFormatException(string msg);
	~WrongFormatException() throw();
	virtual const char* what() const throw ();
private:
	string message;
};

