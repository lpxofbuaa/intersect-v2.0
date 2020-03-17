#include "stdafx.h"
#include "GeometryShape.h"

Line::Line(int x1, int y1, int x2, int y2, int type) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->type = type;
}

Line::Line() {}

Circle::Circle() {}

Circle::Circle(int aa, int bb, int cc) {
	a = aa;
	b = bb;
	r = cc;
}