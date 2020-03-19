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

inline bool GeometryFactory::point_on_line(Point *p, Line &l) {
	// ax + by + c = 0
	return Double::equal((double)(l.a * p->x + l.b * p->y + l.c), 0.0);
}

inline bool GeometryFactory::point_on_circle(Point *p, Circle &c) {
	// (x - x0)^2 + (y - y0)^2 == r^2
	return Double::equal((p->x - c.a) * (p->x - c.a) + (p->y - c.b) * (p->y - c.b), (double)c.r * c.r);
}

void GeometryFactory::removeLine(Line &l) {

	/* Scan UnRational Points On the Line. */
	vector<Point*> to_delete_points;
	for (PointMap::iterator i = points.begin(); i != points.end(); ++i) {
		if (point_on_line(i->first, l)) {
			to_delete_points.push_back(i->first);
		}
	}
	for (vector<Point*>::iterator i = to_delete_points.begin(); i != to_delete_points.end(); ++i) {
		decrease_point(*i);
	}
}

void GeometryFactory::removeCircle(Circle &c) {
	
	/* Scan UnRational Points on the Circle. */
	vector<Point*> to_delete_unrational_points;
	for (PointMap::iterator i = points.begin(); i != points.end(); ++i) {
		
		if (point_on_circle(i->first, c)) {
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
		double A = (double)((double)l.a * l.a + (double)l.b * l.b) / (double)((double)l.b * l.b);
		double B = (double)((double)c.b * l.a * l.b - (double)c.a * l.b * l.b + (double)l.a * l.c) * 2.0 / (double)((double)l.b * l.b);
		double C = (double)((double)c.a * c.a + (double)c.b * c.b + (double)((double)l.c * l.c) / (double)((double)l.b * l.b) - (double)c.r * c.r + (double)(2.0 * l.c * c.b) / (double)(l.b));
		double delta = B * B - 4 * A * C;
		if (Double::greater(delta, 0)) {
			double res1_x = (double)(-B + sqrt(delta)) / (double)(2.0 * A);
			double res2_x = (double)(-B - sqrt(delta)) / (double)(2.0 * A);
			double res1_y = (double)(-l.c - l.a * res1_x) / (double)l.b;
			double res2_y = (double)(-l.c - l.a * res2_x) / (double)l.b;
			Point *p1 = new Point(res1_x, res1_y);
			Point *p2 = new Point(res2_x, res2_y);
			//cout << l.type << endl;
			//cout << p1->toString() << endl;
			//cout << p2->toString() << endl;
			if (point_in_line_range(p1, l)) {
				increase_point(p1);
			}
			if (point_in_line_range(p2, l)) {
				increase_point(p2);
			}
		}
		else if (Double::equal(delta, 0)) {
			double res_x = (double)(-B) / (2 * A);
			double res_y = (double)(-l.c - l.a * res_x) / (double)l.b;
			Point *p = new Point(res_x, res_y);
			//cout << l.type << endl;
			//cout << p->toString() << endl;
			if (point_in_line_range(p, l)) {
				increase_point(p);
			}
		}
	}
	else {
		delta_y_2 = c.r * c.r - (l.x1 - c.a) * (l.x1 - c.a);
		if (delta_y_2 > 0) {
			double res_y1 = sqrt(delta_y_2) + c.b;
			double res_y2 = -sqrt(delta_y_2) + c.b;
			Point *p1 = new Point((double)l.x1, res_y1);
			Point *p2 = new Point((double)l.x1, res_y2);
			//cout << l.type << endl;
			//cout << p1->toString() << endl;
			//cout << p2->toString() << endl;
			if (point_in_line_range(p1, l)) {
				increase_point(p1);
			}
			if (point_in_line_range(p2, l)) {
				increase_point(p2);
			}
		}
		else if (delta_y_2 == 0) {
			Point *p = new Point((double)l.x1, (double)c.b);
			//cout << l.type << endl;
			//cout << p->toString() << endl;
			if (point_in_line_range(p, l)) {
				increase_point(p);
			}
		}
	} 
	
}

// todo: check
void GeometryFactory::circle_circle_intersect(Circle &c1, Circle &c2) {
	// get common line
	long long a = 2 * (c2.a - c1.a);
	long long b = 2 * (c2.b - c1.b);
	long long c = c1.a * c1.a - c2.a * c2.a + c1.b * c1.b - c2.b * c2.b + c2.r * c2.r - c1.r * c1.r;

	// copy by line_intersect_circle
	if (b != 0) {
		// k exists
		double A = (double)((double)a * a + (double)b * b) / (double)((double)b * b);
		double B = (double)((double)c1.b * a * b - (double)c1.a * b * b + (double)a * c) * 2.0 / (double)((double)b * b);
		double C = (double)((double)c1.a * c1.a + (double)c1.b * c1.b + (double)((double)c * c) / (double)((double)b * b) - (double)c1.r * c1.r + (double)(2.0 * c * c1.b) / (double)(b));
		double delta = B * B - 4 * A * C;
		if (Double::greater(delta, 0)) {
			double res1_x = (double)(-B + sqrt(delta)) / (double)(2.0 * A);
			double res2_x = (double)(-B - sqrt(delta)) / (double)(2.0 * A);
			double res1_y = (double)(-c - a * res1_x) / (double)b;
			double res2_y = (double)(-c - a * res2_x) / (double)b;
			Point *p1 = new Point(res1_x, res1_y);
			Point *p2 = new Point(res2_x, res2_y);
			
			increase_point(p1);
			increase_point(p2);
		}
		else if (Double::equal(delta, 0)) {
			double res_x = (double)(-B) / (2 * A);
			double res_y = (double)(-c - a * res_x) / (double)b;
			Point *p = new Point(res_x, res_y);
			
			increase_point(p);
		}
	}
	else {
		double x1 = (double)((double)c1.r * c1.r - (double)c2.r * c2.r + (double)c2.b * c2.b - (double)c1.b * c1.b + (double)c2.a * c2.a - (double)c1.a * c1.a) / (double)(2.0 * ((double)c2.a - c1.a));
		double delta_y_2 = (double)c1.r * c1.r - ((double)x1 - (double)c1.a) * ((double)x1 - (double)c1.a);
		if (Double::greater(delta_y_2, 0)) {
			double res_y1 = sqrt(delta_y_2) + c1.b;
			double res_y2 = -sqrt(delta_y_2) + c1.b;
			Point *p1 = new Point((double)x1, res_y1);
			Point *p2 = new Point((double)x1, res_y2);
			
			increase_point(p1);
			increase_point(p2);
		}
		else if (Double::equal(delta_y_2, 0)) {
			Point *p = new Point((double)x1, (double)c1.b);

			increase_point(p);
		}
	}
	
}
