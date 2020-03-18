#include "stdafx.h"
#include "GeometryStatistic.h"
#include <iostream>

using namespace std;

GeometryFactory::GeometryFactory() {
	
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
	else if ((x1 <= MIN_RANGE) || (x2 <= MIN_RANGE) || (y1 <= MIN_RANGE) || (y2 <= MIN_RANGE)) {
		throw CoordinateRangeException("coordinate is out of range!");
	}
	if ((x1 == x2) && (y1 == y2)) {
		throw CoordinateCoincidenceException("coordinate coincident!");
	}
	
	Line l(x1, y1, x2, y2, type);
	LineMap::iterator value = lines.find(l.k);
	LineIdMap::iterator second_value;
	if (value != lines.end()) {
		for (second_value = value->second.begin(); second_value != value->second.end(); ++second_value) {
			if (line_coincident(l, second_value->second)) {
				LineCoincidenceException e("this line has been coincident!");
				e.coincidence = second_value->second;
				throw e;
			}
		}
	}
	

	//-------------------------------------------------------------------------
	for (LineMap::iterator i = lines.begin(); i != lines.end(); ++i) {
		for (LineIdMap::iterator j = i->second.begin(); j != i->second.end(); ++j) {
			line_line_intersect(j->second, l);
		}
	}
	for (CircleSet::iterator i = circles.begin(); i != circles.end(); ++i) {
		Circle c2 = *i;
		line_circle_intersect(l, c2);
	}
	if (value != lines.end()) {
		value->second.insert({ line_counter, l });
	}
	else {
		lines[l.k].insert({ line_counter, l });
	}
	line_ids.insert({ line_counter, l });
	line_counter += 2;
	return line_counter - 2;
}

int GeometryFactory::addCircle(int x, int y, int r) {
	if (r <= 0) {
		throw NegativeRadiusException("radius of circle is illegal!");
	}
	if ((x >= MAX_RANGE) || (y >= MAX_RANGE) || (r >= MAX_RANGE)) {
		throw CoordinateRangeException("coordinate is out of range!");
	}
	else if ((x <= MIN_RANGE) || (y <= MIN_RANGE) || (r <= MIN_RANGE)) {
		throw CoordinateRangeException("coordinate is out of range!");
	}
	Circle c(x, y, r);
	CircleSet::iterator value;
	if ((value = circles.find(c)) != circles.end()) {
		CircleCoincidenceException e("this circle has been added!");
		e.coincidence = *value;
		throw e;
	}

	//---------------------------------------------------------------------------
	for (LineMap::iterator i = lines.begin(); i != lines.end(); ++i) {
		for (LineIdMap::iterator j = i->second.begin(); j != i->second.end(); ++j) {
			line_circle_intersect(j->second, c);
		}
	}
	for (CircleSet::iterator i = circles.begin(); i != circles.end(); ++i) {
		Circle c2 = *i;
		circle_circle_intersect(c2, c);
	}

	circles.insert(c);
	circle_ids.insert({ circle_counter, c });
	circle_counter += 2;
	return circle_counter - 2;
}

Line GeometryFactory::getLine(int id)
{
	LineIdMap::iterator i = line_ids.find(id);
	if (i == line_ids.end()) {
		throw ObjectNotFoundException("line not found or invalid id!");
	}
	return i->second;
}

Circle GeometryFactory::getCircle(int id)
{
	CircleIdMap::iterator i = circle_ids.find(id);
	if (i == circle_ids.end()) {
		throw ObjectNotFoundException("circle not found or invalid id!");
	}
	return i->second;
}

void GeometryFactory::removeLine(Line &l) {
	vector<RationalPoint*> to_delete_rational_points;
	for (RationalPointMap::iterator i = rational_points.begin(); i != rational_points.end(); ++i) {
		if (l.k.k == INT32_MAX && i->first->x.equals(RationalNumber(l.x1, 1))) {
			// k not exists
			to_delete_rational_points.push_back(i->first);
		}
		else if (l.k.k != INT32_MAX) {
			// k exists
			RationalNumber tmp_x = i->first->x;
			RationalNumber tmp_y = i->first->y;

			RationalNumber k(l.y1 - l.y2, l.x1 - l.x2);
			RationalNumber b(RationalNumber(l.x1*l.y2 - l.x2*l.y1, l.x1 - l.x2));
			// tmp_y = k * tmp_x + b
			if (tmp_x.mult(k).add(b).equals(tmp_y)) {
				to_delete_rational_points.push_back(i->first);
			}
		}
	}
	for (vector<RationalPoint*>::iterator i = to_delete_rational_points.begin(); i != to_delete_rational_points.end(); ++i) {
		decrease_rational_point(*i);
	}
	//--------------------------------------------------------------------------------
	vector<UnRationalPoint*> to_delete_unrational_points;
	double_equal doubleequal;
	for (UnRationalPointMap::iterator i = unrational_points.begin(); i != unrational_points.end(); ++i) {
		if (l.k.k == INT32_MAX && doubleequal((double)l.x1, i->first->x)) {
			// k not exists
			to_delete_unrational_points.push_back(i->first);
		}
		else if (l.k.k != INT32_MAX) {
			// k exists

			double k = (l.y1 - l.y2)/(l.x1 - l.x2);
			double b = (l.x1*l.y2 - l.x2*l.y1)/ (l.x1 - l.x2);
			// y = k * x + b
			if (doubleequal(k*i->first->x + b, i->first->y)) {
				to_delete_unrational_points.push_back(i->first);
			}
		}
	}
	for (vector<UnRationalPoint*>::iterator i = to_delete_unrational_points.begin(); i != to_delete_unrational_points.end(); ++i) {
		decrease_unrational_point(*i);
	}
}

void GeometryFactory::removeCircle(Circle &c) {
	vector<RationalPoint*> to_delete_rational_points;
	for (RationalPointMap::iterator i = rational_points.begin(); i != rational_points.end(); ++i) {
		RationalNumber delta_x = i->first->x.sub(c.a);
		RationalNumber delta_y = i->first->y.sub(c.b);
		delta_x = delta_x.mult(delta_x);
		delta_y = delta_y.mult(delta_y);
		RationalNumber delta = delta_x.add(delta_y);
		if (delta.canSqrt() && delta.equals(c.r * c.r)) {
			to_delete_rational_points.push_back(i->first);
		}
	}
	for (vector<RationalPoint*>::iterator i = to_delete_rational_points.begin(); i != to_delete_rational_points.end(); ++i) {
		decrease_rational_point(*i);
	}
	//--------------------------------------------------------------------------------
	vector<UnRationalPoint*> to_delete_unrational_points;
	double_equal equals;
	for (UnRationalPointMap::iterator i = unrational_points.begin(); i != unrational_points.end(); ++i) {
		if (equals.operator()((i->first->x - c.a)*(i->first->x - c.a) + (i->first->y - c.b)*(i->first->y - c.b), c.r*c.r)) {
			to_delete_unrational_points.push_back(i->first);
		}
	}
	for (vector<UnRationalPoint*>::iterator i = to_delete_unrational_points.begin(); i != to_delete_unrational_points.end(); ++i) {
		decrease_unrational_point(*i);
	}
}

void GeometryFactory::remove(int id) {
	if (id % 2 != 0) {
		LineIdMap::iterator ptr = line_ids.find(id);
		if (ptr == line_ids.end()) {
			throw ObjectNotFoundException("line not found or invalid id!");
		}
		removeLine(ptr->second);
		LineMap::iterator root_ptr = lines.find(ptr->second.k);
		if (root_ptr != lines.end()) {
			root_ptr->second.erase(id);
			if (root_ptr->second.empty()) {
				lines.erase(root_ptr);
			}
		}
		line_ids.erase(ptr);
	}
	else {
		CircleIdMap::iterator ptr = circle_ids.find(id);
		if (ptr == circle_ids.end()) {
			throw ObjectNotFoundException("circle not found or invalid id!");
		}
		removeCircle(ptr->second);
		circles.erase(ptr->second);
		circle_ids.erase(ptr);
	}
}

vector<Point> GeometryFactory::getPoints()
{
	vector<Point> re;
	for (RationalPointMap::iterator i = rational_points.begin(); i != rational_points.end(); ++i) {
		Point p(i->first->x.toDouble(), i->first->y.toDouble());
		re.push_back(p);
	}

	for (UnRationalPointMap::iterator i = unrational_points.begin(); i != unrational_points.end(); ++i) {
		Point p(i->first->x, i->first->y);
		re.push_back(p);
	}
	return re;
}

int GeometryFactory::getPointsCount()
{
	return (int)(rational_points.size() + unrational_points.size());
}

void GeometryFactory::increase_rational_point(RationalPoint* point) {
	RationalPointMap::iterator value = rational_points.find(point);
	if (value != rational_points.end()) {
		value->second += 1;
	}
	else {
		rational_points[point] = 1;
	}
}

void GeometryFactory::increase_unrational_point(UnRationalPoint* point) {
	UnRationalPointMap::iterator value = unrational_points.find(point);
	if (value != unrational_points.end()) {
		value->second += 1;
	}
	else {
		unrational_points[point] = 1;
	}
}

void GeometryFactory::decrease_rational_point(RationalPoint* p) {
	RationalPointMap::iterator value = rational_points.find(p);
	if (value != rational_points.end()) {
		value->second -= 1;
		if (value->second == 0) {
			rational_points.erase(value);
		}
	}
}

void GeometryFactory::decrease_unrational_point(UnRationalPoint* p) {
	UnRationalPointMap::iterator value = unrational_points.find(p);
	if (value != unrational_points.end()) {
		value->second -= 1;
		if (value->second == 0) {
			unrational_points.erase(value);
		}
	}
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

		increase_rational_point(new RationalPoint(new_x, new_y));
		
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
			increase_rational_point(new RationalPoint(x, y1));
			increase_rational_point(new RationalPoint(x, y2));
		}
		else {
			double x = sqrt(tmp);
			double y1 = sqrt(tmp) + c.b;
			double y2 = -sqrt(tmp) + c.b;
			increase_unrational_point(new UnRationalPoint(x, y1));
			increase_unrational_point(new UnRationalPoint(x, y2));
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
		increase_rational_point(new RationalPoint(x1, y1));
		increase_rational_point(new RationalPoint(x2, y2));
	}
	else {
		double t1 = tmp_1.toDouble();
		double t2 = k2_1.toDouble();
		double d = sqrt(delta.toDouble());

		double x1 = (-2 * t1 + d) / (2 * t2);
		double y1 = k.toDouble() * x1 + b.toDouble();

		double x2 = (-2 * t1 - d) / (2 * t2);
		double y2 = k.toDouble() * x2 + b.toDouble();

		increase_unrational_point(new UnRationalPoint(x1, y1));
		increase_unrational_point(new UnRationalPoint(x2, y2));
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
		increase_rational_point(new RationalPoint(x1, y1));
		increase_rational_point(new RationalPoint(x2, y2));
	}
	else {
		double t1 = tmp_1.toDouble();
		double t2 = k2_1.toDouble();
		double d = sqrt(delta.toDouble());

		double x1 = (-2 * t1 + d) / (2 * t2);
		double y1 = k.toDouble() * x1 + b.toDouble();

		double x2 = (-2 * t1 - d) / (2 * t2);
		double y2 = k.toDouble() * x2 + b.toDouble();

		increase_unrational_point(new UnRationalPoint(x1, y1));
		increase_unrational_point(new UnRationalPoint(x2, y2));
	}
}
