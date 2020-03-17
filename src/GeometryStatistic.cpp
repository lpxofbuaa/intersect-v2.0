#include "stdafx.h"
#include "GeometryStatistic.h"
#include <iostream>

using namespace std;

GeometryFactory::GeometryFactory() {
	rational_points = new unordered_set<RationalPoint*, rational_point_hash, rational_point_equal>();
	unrational_points = new unordered_set<UnRationalPoint*, unrational_point_hash, unrational_point_equal>();
}

int GeometryFactory::addLine(int type, int x1, int x2, int y1, int y2) {
	switch (type)
	{
	case DOUBLE_INFINITE_LINE:
	case LIMITED_LINE:
	case SINGLE_INFINITE_LINE:
		break;
	default:
		throw UndefinedLineException("undefined line type!");
	}
	if ((x1 >= MAX_RANGE) || (x2 >= MAX_RANGE) || (y1 >= MAX_RANGE) || (y2 >= MAX_RANGE)) {
		throw CoordinateRangeException("coordinate is out of range!");
	}
	if ((x1 == x2) && (y1 == y2)) {
		throw CoordinateCoincidenceException("coordinate coincident!");
	}
	double k = (double) INT32_MAX;
	if (x1 != x2) {
		k = (y1 - y2) / (x1 - x2);
	}
	if (slopes.find(k) != slopes.end()) {
		throw LineCoincidenceException("this line has been added!");
	}

	//-------------------------------------------------------------------------
	slopes.insert(k);
	lines.insert({ line_counter, Line(x1, y1, x2, y2, type) });
}

void GeometryFactory::feed(Line &l) {
	for (vector<Line>::iterator i = lines.begin(); i != lines.end(); ++i) {
		line_line_intersect(*i, l);
	}
	for (vector<Circle>::iterator i = circles.begin(); i != circles.end(); ++i) {
		line_circle_intersect(l, *i);
	}
	lines.push_back(l);
}

void GeometryFactory::feed(Circle &c) {
	for (vector<Line>::iterator i = lines.begin(); i != lines.end(); ++i) {
		line_circle_intersect(*i, c);
	}
	for (vector<Circle>::iterator i = circles.begin(); i != circles.end(); ++i) {
		circle_circle_intersect(c, *i);
	}
	circles.push_back(c);
}

void GeometryFactory::line_line_intersect(Line &l1, Line &l2) {
	RationalNumber new_x;
	RationalNumber new_y;
	long long b = (l2.x1 * l2.y2 - l2.y1 * l2.x2) * (l1.x1 - l1.x2)
		- (l1.x1 * l1.y2 - l1.y1 * l1.x2) * (l2.x1 - l2.x2);
	long long a = (l1.y1 - l1.y2) * (l2.x1 - l2.x2) - (l1.x1 - l1.x2) * (l2.y1 - l2.y2);
	if (a != 0) {
		new_x = RationalNumber(b, a);
		//cout << b << "/" << a << endl;
		if (l1.x1 - l1.x2 != 0) {
			new_y = RationalNumber((l1.y1 - l1.y2) * b + (l1.x1 * l1.y2 - l1.y1 * l1.x2) * a
				, a * (l1.x1 - l1.x2));
		}
		else {
			new_y = RationalNumber((l2.y1 - l2.y2) * b + (l2.x1 * l2.y2 - l2.y1 * l2.x2) * a
				, a * (l2.x1 - l2.x2));
		}
		//cout << (l1.a_y - l1.b_y) * b + (l1.a_x * l1.b_y - l1.a_y * l1.b_x) * a << "/" << a * (l1.a_x - l1.b_x) << endl;
		rational_points->insert(new RationalPoint(new_x, new_y));
	}
}

void GeometryFactory::line_circle_intersect(Line &l, Circle &c) {
	if (l.x2 - l.x1 == 0) {
		double tmp = c.r*c.r - (l.x1 - c.a)*(l.x1 - c.a);
		if (tmp < 0) {
			return;
		}
		long long q = (long long) sqrt(tmp);
		if (q*q == tmp) {
			RationalNumber x(q, 1);
			RationalNumber y1(q + c.b, 1);
			RationalNumber y2(-q + c.b, 1);
			rational_points->insert(new RationalPoint(x, y1));
			rational_points->insert(new RationalPoint(x, y2));
		}
		else {
			double x = sqrt(tmp);
			double y1 = sqrt(tmp) + c.b;
			double y2 = -sqrt(tmp) + c.b;
			unrational_points->insert(new UnRationalPoint(x, y1));
			unrational_points->insert(new UnRationalPoint(x, y2));
		}
		return;
	}
	RationalNumber k(l.y2 - l.y1, l.x2 - l.x1);
	RationalNumber b(l.x1*l.y2 - l.x2*l.y1, l.x1 - l.x2);
	RationalNumber tmp = b.sub(c.b);
	RationalNumber tmp_1 = k.mult(tmp).sub(c.a);
	RationalNumber delta = tmp_1.mult(tmp_1);

	RationalNumber k2_1 = k.mult(k).add(1);
	RationalNumber b_n = b.sub(c.b);
	b_n = b_n.mult(b_n);
	RationalNumber tmp2 = b_n.add(c.a * c.a - c.r * c.r);
	tmp2 = tmp2.mult(k2_1);
	delta = delta.sub(tmp2).mult(4);

	if (not delta.sign()) {
		return;
	}

	if (delta.canSqrt()) {
		delta = delta.Sqrt();
		RationalNumber aa = tmp_1.mult(-2).add(delta);
		RationalNumber bb = k2_1.mult(2);
		RationalNumber x1 = aa.div(bb);
		RationalNumber y1 = k.mult(x1).add(b);

		aa = tmp_1.mult(-2).sub(delta);
		RationalNumber x2 = aa.div(bb);
		RationalNumber y2 = k.mult(x2).add(b);
		rational_points->insert(new RationalPoint(x1, y1));
		rational_points->insert(new RationalPoint(x2, y2));
	}
	else {
		double t1 = tmp_1.toDouble();
		double t2 = k2_1.toDouble();
		double d = sqrt(delta.toDouble());

		double x1 = (-2 * t1 + d) / (2 * t2);
		double y1 = k.toDouble() * x1 + b.toDouble();

		double x2 = (-2 * t1 - d) / (2 * t2);
		double y2 = k.toDouble() * x2 + b.toDouble();

		unrational_points->insert(new UnRationalPoint(x1, y1));
		unrational_points->insert(new UnRationalPoint(x2, y2));
	}


}

void GeometryFactory::circle_circle_intersect(Circle &c1, Circle &c2) {
	RationalNumber k((c1.a - c2.a) , (c2.b - c1.b));
	RationalNumber b(((c1.r*c1.r - c2.r*c2.r) + (c2.a*c2.a - c1.a*c1.a) + (c2.b*c2.b - c1.b*c1.b)) , 2*(c2.b - c1.b));

	RationalNumber tmp = b.sub(c1.b);
	RationalNumber tmp_1 = k.mult(tmp).sub(c1.a);
	RationalNumber delta = tmp_1.mult(tmp_1);

	RationalNumber k2_1 = k.mult(k).add(1);
	RationalNumber b_n = b.sub(c1.b);
	b_n = b_n.mult(b_n);
	RationalNumber tmp2 = b_n.add(c1.a * c1.a - c1.r * c1.r);
	tmp2 = tmp2.mult(k2_1);
	delta = delta.sub(tmp2).mult(4);

	if (not delta.sign()) {
		return;
	}

	if (delta.canSqrt()) {
		delta = delta.Sqrt();
		RationalNumber aa = tmp_1.mult(-2).add(delta);
		RationalNumber bb = k2_1.mult(2);
		RationalNumber x1 = aa.div(bb);
		RationalNumber y1 = k.mult(x1).add(b);

		aa = tmp_1.mult(-2).sub(delta);
		RationalNumber x2 = aa.div(bb);
		RationalNumber y2 = k.mult(x2).add(b);
		rational_points->insert(new RationalPoint(x1, y1));
		rational_points->insert(new RationalPoint(x2, y2));
	}
	else {
		double t1 = tmp_1.toDouble();
		double t2 = k2_1.toDouble();
		double d = sqrt(delta.toDouble());

		double x1 = (-2 * t1 + d) / (2 * t2);
		double y1 = k.toDouble() * x1 + b.toDouble();

		double x2 = (-2 * t1 - d) / (2 * t2);
		double y2 = k.toDouble() * x2 + b.toDouble();

		unrational_points->insert(new UnRationalPoint(x1, y1));
		unrational_points->insert(new UnRationalPoint(x2, y2));
	}
}

int GeometryFactory::getPointCount() {
	return rational_points->size() + unrational_points->size();
}

bool GeometryFactory::containsPoint(RationalPoint *a) {
	return rational_points->find(a) != rational_points->end();
}