#include "StdInterface.h"
#include "DoubleUtils.h"
#include "Constant.h"
#include "GeometryStatistic.h"
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

static vector<GeometryFactory*> myFactors;
static vector<vector<int>> myShapeIds;

gFigure* addFigure()
{
	gFigure *fig = new gFigure();
	fig->figureId = myFactors.size();
	fig->points = NULL;
	fig->shapes = NULL;
	myFactors.push_back(new GeometryFactory());
	myShapeIds.push_back(vector<int>());
	fig->upperleft = { 0.0, 0.0 };
	fig->lowerright = { 0.0, 0.0 };
	return fig;
}

void deleteFigure(gFigure * fig)
{
	delete myFactors[fig->figureId];
	myShapeIds[fig->figureId].clear();
	delete fig;
}

void cleanFigure(gFigure * fig)
{
	delete myFactors[fig->figureId];
	myFactors[fig->figureId] = new GeometryFactory();
	myShapeIds[fig->figureId].clear();
	fig->points = NULL;
	fig->shapes = NULL;
	fig->upperleft = { 0.0, 0.0 };
	fig->lowerright = { 0.0, 0.0 };
}

ERROR_INFO __addLine(int type, long long x1, long long x2, long long y1, long long y2, gFigure *fig) {
	ERROR_INFO info;
	int id;
	try {
		id = myFactors[fig->figureId]->addLine(type, x1, x2, y1, y2);
		myShapeIds[fig->figureId].push_back(id);
		vector<double> ret;
		myFactors[fig->figureId]->getBounder(ret);
		fig->upperleft = { ret[0], ret[1] };
		fig->lowerright = { ret[2], ret[3] };
	}
	catch (CoordinateRangeException &e) {
		info.code = VALUE_OUT_OF_RANGE;
		strcpy_s(info.messages, e.what());
	}
	catch (CoordinateCoincidenceException &e) {
		info.code = INVALID_LINE;
		strcpy_s(info.messages, e.what());
	}
	catch (LineCoincidenceException &e) {
		info.code = LINE_OVERLAP;
		strcpy_s(info.messages, e.what());
	}
	
	return info;
}

ERROR_INFO __addCircle(long long a, long long b, long long r, gFigure *fig) {
	ERROR_INFO info;
	int id;
	try {
		id = myFactors[fig->figureId]->addCircle(a, b, r);
		myShapeIds[fig->figureId].push_back(id);
		vector<double> ret;
		myFactors[fig->figureId]->getBounder(ret);
		fig->upperleft = { ret[0], ret[1] };
		fig->lowerright = { ret[2], ret[3] };
	}
	catch (CoordinateRangeException &e) {
		info.code = VALUE_OUT_OF_RANGE;
		strcpy_s(info.messages, e.what());
	}
	catch (CircleCoincidenceException &e) {
		info.code = CIRCLE_OVERLAP;
		strcpy_s(info.messages, e.what());
	}
	catch (NegativeRadiusException &e) {
		info.code = INVALID_CIRCLE;
		strcpy_s(info.messages, e.what());
	}
	return info;
}

ERROR_INFO addShapeToFigure(gFigure * fig, gShape obj)
{
	int type = DOUBLE_INFINITE_LINE;
	switch (obj.type)
	{
	case 'L':
		type = DOUBLE_INFINITE_LINE;
		return __addLine(type, obj.x1, obj.x2, obj.y1, obj.y2, fig);
	case 'S':
		type = LIMITED_LINE;
		return __addLine(type, obj.x1, obj.x2, obj.y1, obj.y2, fig);
	case 'R':
		type = SINGLE_INFINITE_LINE;
		return __addLine(type, obj.x1, obj.x2, obj.y1, obj.y2, fig);
	case 'C':
		return __addCircle(obj.x1, obj.y1, obj.x2, fig);
	default:
		return ERROR_INFO();
	}
	return ERROR_INFO();
}

ERROR_INFO addShapeToFigureString(gFigure * fig,const char * desc)
{
	GeometryFactory *f = myFactors[fig->figureId];
	string message(desc);
	ERROR_INFO info;
	try {
		int id = f->addObjectFromFile(message);
		myShapeIds[fig->figureId].push_back(id);
		vector<double> ret;
		myFactors[fig->figureId]->getBounder(ret);
		fig->upperleft = { ret[0], ret[1] };
		fig->lowerright = { ret[2], ret[3] };
	} 
	catch (CoordinateRangeException &e) {
		info.code = VALUE_OUT_OF_RANGE;
		strcpy_s(info.messages, e.what());
	}
	catch (CircleCoincidenceException &e) {
		info.code = CIRCLE_OVERLAP;
		strcpy_s(info.messages, e.what());
	}
	catch (NegativeRadiusException &e) {
		info.code = INVALID_CIRCLE;
		strcpy_s(info.messages, e.what());
	}
	catch (CoordinateCoincidenceException &e) {
		info.code = INVALID_LINE;
		strcpy_s(info.messages, e.what());
	}
	catch (LineCoincidenceException &e) {
		info.code = LINE_OVERLAP;
		strcpy_s(info.messages, e.what());
	}
	catch (WrongFormatException &e) {
		info.code = WRONG_FORMAT;
		strcpy_s(info.messages, e.what());
	}
	return info;
}

ERROR_INFO addShapesToFigureFile(gFigure * fig,const char * filename)
{
	ERROR_INFO info;
	streambuf *cinbackup = NULL;
	ifstream *input = NULL;
	if (filename != NULL) {
		string name = string(filename);
		input = new ifstream(name);
		cinbackup = cin.rdbuf(input->rdbuf());
	}
	GeometryFactory *f = myFactors[fig->figureId];
	regex number("^\\d+$");
	int n = 0;
	string line;
	getline(cin, line);
	if (regex_match(line, number)) {
		stringstream s(line);
		s >> n;
	}
	else {
		info.code = WRONG_FORMAT;
		info.lineNoStartedWithZero = 1;
		strcpy_s(info.messages, "Please input a number!");
		return info;
	}
	for (int i = 0; i < n; ++i) {
		string message;
		getline(cin, message);
		if ((info = addShapeToFigureString(fig, (char*)message.data())).code != SUCCESS) {
			return info;
		}
	}
	if (cinbackup != NULL) {
		cin.rdbuf(cinbackup);
	}
	return info;
}

ERROR_INFO addShapesToFigureStdin(gFigure * fig)
{
	return addShapesToFigureFile(fig, NULL);
}

void removeShapeByIndex(gFigure * fig, unsigned int index)
{
	GeometryFactory *f = myFactors[fig->figureId];
	f->remove(myShapeIds[fig->figureId][index]);
	myShapeIds[fig->figureId].erase(myShapeIds[fig->figureId].begin() + index);
	
	vector<double> ret;
	f->getBounder(ret);
	fig->upperleft = { ret[0], ret[1] };
	fig->lowerright = { ret[2], ret[3] };
}

void updatePoints(gFigure * fig)
{
	vector<Point> points = myFactors[fig->figureId]->getPoints();
	if (fig->points != NULL) {
		delete fig->points;
	}
	fig->points = new gPoint[points.size()];
	int j = 0;
	for (auto i = points.begin(); i != points.end(); ++i) {
		fig->points[j] = gPoint{ i->x, i->y };
		++j;
	}
}

void updateShapes(gFigure * fig)
{
	if (fig->shapes != NULL) {
		delete fig->shapes;
	}
	fig->shapes = new gShape[myShapeIds[fig->figureId].size()];
	int j = 0;
	int id = 0;
	for (int i = 0; i != myShapeIds[fig->figureId].size(); ++i) {
		id = myShapeIds[fig->figureId][i];
		if (id % 2 == 0) {
			Circle c = myFactors[fig->figureId]->getCircle(id);
			fig->shapes[j] = gShape{ 'C', (int)c.a, (int)c.b, (int)c.r, 0 };
		}
		else {
			Line l = myFactors[fig->figureId]->getLine(id);
			char type = 'L';
			switch (l.type)
			{
			case DOUBLE_INFINITE_LINE:
				type = 'L';
				break;
			case SINGLE_INFINITE_LINE:
				type = 'R';
				break;
			case LIMITED_LINE:
				type = 'S';
				break;
			default:
				break;
			}
			fig->shapes[j] = gShape{ type, (int)l.x1, (int)l.y1, (int)l.x2, (int)l.y2 };
		}
		++j;
	}

	
}

int getPointsCount(const gFigure * fig)
{
	return myFactors[fig->figureId]->getPointsCount();
}

int getShapesCount(const gFigure * fig)
{
	return myShapeIds[fig->figureId].size();
}
