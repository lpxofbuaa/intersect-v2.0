#include "stdafx.h"
#include "GeometryStatistic.h"
#include <iostream>

using namespace std;

GeometryFactory::GeometryFactory() {
	
}

int GeometryFactory::addLine(int type, long long x1, long long x2, long long y1, long long y2) {
		
	/* Exception Check */
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
	IdLineMap::iterator second_value;
	if (value != lines.end()) {
		for (second_value = value->second.begin(); second_value != value->second.end(); ++second_value) {
			if (line_coincident(l, second_value->second)) {
				LineCoincidenceException e("this line has been coincident!");
				e.coincidence = second_value->second;
				throw e;
			}
		}
	}
	
	/* Intersect Update */
	for (LineMap::iterator i = lines.begin(); i != lines.end(); ++i) {
		for (IdLineMap::iterator j = i->second.begin(); j != i->second.end(); ++j) {
			line_line_intersect(j->second, l);
		}
	}

	for (CircleSet::iterator i = circles.begin(); i != circles.end(); ++i) {
		Circle c2 = *i;
		line_circle_intersect(l, c2);
	}
	
	/* Insert the Circle */
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

int GeometryFactory::addCircle(long long x, long long y, long long r) {
	
	/* Exception Check */
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

	/* Intersect Update */
	for (LineMap::iterator i = lines.begin(); i != lines.end(); ++i) {
		for (IdLineMap::iterator j = i->second.begin(); j != i->second.end(); ++j) {
			line_circle_intersect(j->second, c);
		}
	}

	for (CircleSet::iterator i = circles.begin(); i != circles.end(); ++i) {
		Circle c2 = *i;
		circle_circle_intersect(c2, c);
	}

	/* Insert the Circle */
	circles.insert(c);
	circle_ids.insert({ circle_counter, c });
	circle_counter += 2;
	return circle_counter - 2;
}

Line GeometryFactory::getLine(int id)
{
	IdLineMap::iterator i = line_ids.find(id);
	if (i == line_ids.end()) {
		throw ObjectNotFoundException("line not found or invalid id!");
	}
	return i->second;
}

Circle GeometryFactory::getCircle(int id)
{
	IdCircleMap::iterator i = circle_ids.find(id);
	if (i == circle_ids.end()) {
		throw ObjectNotFoundException("circle not found or invalid id!");
	}
	return i->second;
}

void GeometryFactory::removeLine(Line &l) {

	/* Scan UnRational Points On the Line. */
	vector<Point*> to_delete_points;
	double_equal doubleequal;
	for (PointMap::iterator i = points.begin(); i != points.end(); ++i) {
		if (l.k.k == K_INFINITE && doubleequal((double)l.x1, i->first->x)) {
			// k not exists
			if (point_in_line_range(i->first, l)) {
				to_delete_points.push_back(i->first);
			}
		}
		else if (l.k.k != K_INFINITE) {
			// k exists

			double k = (double) (l.y1 - l.y2)/ (double) (l.x1 - l.x2);
			double b = (double) (l.x1*l.y2 - l.x2*l.y1)/ (double) (l.x1 - l.x2);
			// y = k * x + b
			if (doubleequal(k*i->first->x + b, i->first->y)) {
				if (point_in_line_range(i->first, l)) {
					to_delete_points.push_back(i->first);
				}
			}
		}
	}
	for (vector<Point*>::iterator i = to_delete_points.begin(); i != to_delete_points.end(); ++i) {
		decrease_point(*i);
	}
}

void GeometryFactory::removeCircle(Circle &c) {
	
	/* Scan UnRational Points on the Circle. */
	vector<Point*> to_delete_unrational_points;
	double_equal equals;
	for (PointMap::iterator i = points.begin(); i != points.end(); ++i) {
		// (x - x0)^2 + (y - y0)^2 == r^2
		if (equals((i->first->x - c.a) * (i->first->x - c.a) + (i->first->y - c.b) * (i->first->y - c.b), (double)c.r * c.r)) {
			to_delete_unrational_points.push_back(i->first);
		}
	}

	for (vector<Point*>::iterator i = to_delete_unrational_points.begin(); i != to_delete_unrational_points.end(); ++i) {
		decrease_point(*i);
	}
}

void GeometryFactory::remove(int id) {
	if (id % 2 != 0) {
		IdLineMap::iterator ptr = line_ids.find(id);
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
		IdCircleMap::iterator ptr = circle_ids.find(id);
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

	for (PointMap::iterator i = points.begin(); i != points.end(); ++i) {
		re.push_back(*i->first);
	}
	return re;
}

int GeometryFactory::getPointsCount()
{
	return (int) points.size();
}

void GeometryFactory::increase_point(Point* point) {
	PointMap::iterator value = points.find(point);
	if (value != points.end()) {
		value->second += 1;
	}
	else {
		points[point] = 1;
	}
}

void GeometryFactory::decrease_point(Point* p) {
	PointMap::iterator value = points.find(p);
	if (value != points.end()) {
		value->second -= 1;
		if (value->second == 0) {
			points.erase(value);
		}
	}
}

inline bool GeometryFactory::point_in_line_range(Point * p, Line & l)
{
	switch (l.type)
	{
	case DOUBLE_INFINITE_LINE:
		return true;
	case SINGLE_INFINITE_LINE:
		if (l.x1 != l.x2) {
			if (l.x2 > l.x1) {
				return Double::greater(p->x, (double)l.x1) || Double::equal(p->x, (double)l.x1);
			}
			else {
				return Double::less(p->x, (double)l.x1) || Double::equal(p->x, (double)l.x1);
			}
		}
		else {
			if (l.y2 > l.y1) {
				return Double::greater(p->y, (double)l.y1) || Double::equal(p->y, (double)l.y1);
			}
			else {
				return Double::less(p->y, (double)l.y1) || Double::equal(p->y, (double)l.y1);
			}
		}
	case LIMITED_LINE:
		if (l.x1 != l.x2) {
			return (Double::greater(p->x, (double)l.x_min) || Double::equal(p->x, (double)l.x_min))
				&& (Double::less(p->x, (double)l.x_max) || Double::equal(p->x, (double)l.x_max));
		}
		else {
			return (Double::greater(p->y, (double)l.y_min) || Double::equal(p->y, (double)l.y_min))
				&& (Double::less(p->y, (double)l.y_max) || Double::equal(p->y, (double)l.y_max));
		}
	default:
		break;
	}
	return false;
}

void GeometryFactory::line_line_intersect(Line &l1, Line &l2) {
	long long delta_k = l1.a * l2.b - l2.a * l1.b;
	if (delta_k != 0) {
		double x = (double)(l1.b * l2.c - l2.b * l1.c) / (double)delta_k;
		double y = (double)(l2.a * l1.c - l1.a * l2.c) / (double)delta_k;
		Point *p = new Point(x, y);
		if (point_in_line_range(p, l1) && point_in_line_range(p, l2)) {
			increase_point(p);
		}
	}
	else {
		// must not be coincident
		if (l1.x1 == l2.x1 && l1.y1 == l2.y1) {
			increase_point(new Point((double)l1.x1, (double)l1.y1));
		}
		else if (l1.x1 == l2.x2 && l1.y1 == l2.y2) {
			increase_point(new Point((double)l1.x1, (double)l1.y1));
		}
		else if (l1.x2 == l2.x1 && l1.y2 == l2.y1) {
			increase_point(new Point((double)l1.x2, (double)l1.y2));
		}
		else if (l1.x2 == l2.x2 && l1.y2 == l2.y2) {
			increase_point(new Point((double)l1.x2, (double)l1.y2));
		}
	}
}

// todo : check 
void GeometryFactory::line_circle_intersect(Line &l, Circle &c) {
	long long delta_y_2;
	if (l.b != 0) {
		// k exists
		double A = (double)(l.a * l.a + l.b * l.b) / (double)(l.b * l.b);
		double B = (double)(c.b * l.a * l.b - c.a * l.b * l.b + l.a * l.c) * 2.0 / (double)(l.b * l.b);
		double C = (double)(c.a * c.a + c.b * c.b + (double)(l.c * l.c) / (double)(l.b * l.b) - c.r * c.r + (double)(2.0 * l.c * c.b) / (double)(l.b));
		double delta = B * B - 4 * A * C;
		if (delta > 0) {
			double res1_x = (double)(-B + sqrt(delta)) / (double)(2 * A);
			double res2_x = (double)(-B - sqrt(delta)) / (double)(2 * A);
			double res1_y = (double)(-l.c - l.a * res1_x) / (double)l.b;
			double res2_y = (double)(-l.c - l.a * res2_x) / (double)l.b;
			Point *p1 = new Point(res1_x, res1_y);
			Point *p2 = new Point(res2_x, res2_y);
			if (point_in_line_range(p1, l)) {
				increase_point(p1);
			}
			if (point_in_line_range(p2, l)) {
				increase_point(p2);
			}
		}
		else if (delta == 0) {
			double res_x = (double)(-B) / (2 * A);
			double res_y = (double)(-l.c - l.a * res_x) / (double)l.b;
			Point *p = new Point(res_x, res_y);
			if (point_in_line_range(p, l)) {
				increase_point(p);
			}
		}
	}
	else {
		delta_y_2 = c.r * c.r - (l.x1 - c.a) * (l.x1 - c.a);
	} 
	
}

// todo: check
void GeometryFactory::circle_circle_intersect(Circle &c1, Circle &c2) {
	
}
