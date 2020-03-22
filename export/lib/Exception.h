#pragma once
#include <exception>
#include <string>
#include "export/lib/GeometryShape.h"

using namespace std;

/*
 * ���귶Χ�쳣 For ADD
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
 * Line�������غϳ�ͻ�쳣 For ADD
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
 * Line�ͼ��ζ����ͻ�쳣 For ADD
 *       ֱ��      ����      �߶�    
 * ֱ��   x         x         x
 * ����   x         o         o
 * �߶�   x         o         o
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
 * Circle�ͼ��ζ����ͻ�쳣 For ADD
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
 * Circle�ͼ��ζ�������Ƿ��쳣 For ADD
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
 * δ�����Line�͵ľ�������δ֪�쳣 For REMOVE
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
 * todo: ��UndefinedLineException�Ĺ�ϵ��
 * δ����ļ��ζ����쳣 For REMOVE
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
 * ����object���Ͳ���
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

