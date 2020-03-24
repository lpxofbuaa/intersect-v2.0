#include "stdafx.h"
#include "CppUnitTest.h"
#include <unordered_set>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
#include "../src/GeometryCore.h"
#define CHECK Assert::AreEqual 

namespace CoreTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(LineKeyTest)
		{
			struct line_key_equal equals;
			LineKey k(((double)4444444444 - 4444444442) / ((double)5555555555 - 5555555552), ((double)2222222222 - 2222222220) / ((double)5555555555 - 5555555550));
			CHECK((double) 2 / 3, k.k);
			CHECK((double) 2 / 5, 0.4);
			CHECK(true, equals(k, LineKey(0.6666666666666666, 0.4)));
		}

		TEST_METHOD(LineTest1)
		{
			Line l1(344, 56, 3245, 3334, DOUBLE_INFINITE_LINE);
			CHECK((int)l1.x_max, MAX_RANGE);
			CHECK((int)l1.x_min, MIN_RANGE);
			CHECK((int)l1.y_max, MAX_RANGE);
			CHECK((int)l1.y_min, MIN_RANGE);
			Line l2(-342, 422, 90, 0, SINGLE_INFINITE_LINE);
			CHECK((int)l2.x_max, MAX_RANGE);
			CHECK((int)l2.x_min, -342);
			Line l3(0, 344, 0, -325, SINGLE_INFINITE_LINE);
			CHECK((int)l3.y_max, 344);
			CHECK((int)l3.y_min, MIN_RANGE);
			Line l4(44532, 332, 564, 999, LIMITED_LINE);
			CHECK((int)l4.x_min, 564);
			CHECK((int)l4.x_max, 44532);
			Line l5(-432, -3423, -432, 8893, LIMITED_LINE);
			CHECK((int)l5.y_max, 8893);
			CHECK((int)l5.y_min, -3423);
		}

		TEST_METHOD(LineTest2)
		{
			Line l1(-3452, -27600, 0, 16, LIMITED_LINE);
			Line l2(-100, -784, 40, 336, LIMITED_LINE);
			CHECK(line_coincident(l1, l2), true);
			Line l3(0, 16, 40, 336, LIMITED_LINE);
			CHECK(line_coincident(l1, l3), false);
			CHECK(line_coincident(l2, l3), true);
			Line l4(-100, -784, -10, -64, LIMITED_LINE);
			CHECK(line_coincident(l4, l2), true);
			Line l5(-100, -784, -3452, -27600, SINGLE_INFINITE_LINE);
			CHECK(line_coincident(l5, l2), false);
			Line l6(-100, -784, 0, 16, SINGLE_INFINITE_LINE);
			Line l7(0, 16, 1, 24, SINGLE_INFINITE_LINE);
			CHECK(line_coincident(l6, l2), true);
			CHECK(line_coincident(l7, l2), true);
			Line l8(40, 336, 10, 96, SINGLE_INFINITE_LINE);
			CHECK(line_coincident(l8, l1), true);
			Line l9(0, 16, 10, 96, DOUBLE_INFINITE_LINE);
			CHECK(line_coincident(l9, l1), true);
			CHECK(line_coincident(l9, l2), true);
			CHECK(line_coincident(l9, l3), true);
			CHECK(line_coincident(l9, l4), true);
			CHECK(line_coincident(l9, l5), true);
			CHECK(line_coincident(l9, l6), true);
			CHECK(line_coincident(l9, l7), true);
			CHECK(line_coincident(l9, l8), true);
		}

		TEST_METHOD(DoubleTest)
		{
			CHECK(equals(0.20000000000000001, 0.19999999999999991), true);
			CHECK(hashcode(0.20000000000000001), hashcode(0.19999999999999991));
			CHECK(equals(0.00000000000000001234, 0.0), true);
			CHECK(hashcode(0.00000000000000001234), hashcode(0.0));
			CHECK(equals(12345678901234.55677889, 12345678901234.557789), true);
		}


		TEST_METHOD(GeometryFactory_point_in_line_range)
		{
			GeometryFactory *test = new GeometryFactory();
			Point *p = new Point(3.0, 4.0);
			Line l1(3, 4, 5, 8, LIMITED_LINE);
			Line l2(3, 4, -10, -33, SINGLE_INFINITE_LINE);
			Line l3(-3, -4, -6, -8, SINGLE_INFINITE_LINE);
			Line l4(0, 0, 1, 1, DOUBLE_INFINITE_LINE);
			CHECK(test->point_in_line_range(3.0, 4.0, l1), true);
			CHECK(test->point_in_line_range(3.0, 4.0, l2), true);
			CHECK(test->point_in_line_range(3.0, 4.0, l3), false);
			CHECK(test->point_in_line_range(3.0, 4.0, l4), true);
			delete(test);
			delete(p);
		}

		TEST_METHOD(GeometryFactory_point_on_line) 
		{
			GeometryFactory *test = new GeometryFactory();
			Point *p1 = new Point(2.999999999999999001, 3.0);
			Point *p2 = new Point(3.000000000123, 3.0);
			Point *p3 = new Point(4.0, -4.0);
			Line l1(3, 3, 4, 4, DOUBLE_INFINITE_LINE);
			CHECK(test->point_on_line(p1, l1), true);
			CHECK(test->point_on_line(p2, l1), false);
			CHECK(test->point_on_line(p3, l1), false);
			delete p1;
			delete p2;
			delete p3;
			delete test;
		}

		TEST_METHOD(GeometryFactory_point_on_circle)
		{
			GeometryFactory *test = new GeometryFactory();
			Point *p1 = new Point(1.00000000000000003, 0.0);
			Point *p2 = new Point(1.0000000000223, 1.0);
			Point *p3 = new Point(1.0000000000223, 0.0);
			Circle c(0, 0, 1);
			CHECK(test->point_on_circle(p1, c), true);
			CHECK(test->point_on_circle(p2, c), false);
			delete test;
			delete p1;
			delete p2;
			delete p3;
		}

		TEST_METHOD(line_line_intersect_1)
		{
			GeometryFactory *test = new GeometryFactory();
			Line l1(1, 2, 3, 4, DOUBLE_INFINITE_LINE);
			Line l2(1, 2, -1, 0, SINGLE_INFINITE_LINE);
			Line l3(1, 2, 5, 8, LIMITED_LINE);
			Point p1(1.0, 2.0);
			test->line_line_intersect(l1, l2);
			double *px = new double[test->getPointsCount()];
			double *py = new double[test->getPointsCount()];
			test->getPoints(px, py, test->getPointsCount());
			CHECK(test->getPointsCount(), 1);
			CHECK(Point(px[0], py[0]).point_equals(p1), true);
			test->line_line_intersect(l1, l3);
			test->getPoints(px, py, test->getPointsCount());
			CHECK(test->getPointsCount(), 1);
			CHECK(Point(px[0], py[0]).point_equals(p1), true);
			test->line_line_intersect(l2, l3);
			test->getPoints(px, py, test->getPointsCount());
			CHECK(test->getPointsCount(), 1);
			CHECK(Point(px[0], py[0]).point_equals(p1), true);
			delete test;
		}

		TEST_METHOD(line_line_intersect_2)
		{
			GeometryFactory test;
			CHECK(1, test.addLine(LIMITED_LINE, 0, 2, 0, 2));
			CHECK(3, test.addLine(LIMITED_LINE, 0, 2, 0, 4));
			CHECK(5, test.addLine(LIMITED_LINE, 2, 54, 2, 322));
			CHECK(7, test.addLine(LIMITED_LINE, 3222, 0, -35, 0));
			CHECK(9, test.addLine(LIMITED_LINE, 99932, 2, 22, 2));
		}

		TEST_METHOD(add_line_test_1)
		{
			GeometryFactory test;
			CHECK(1,test.addLine(DOUBLE_INFINITE_LINE, 0, 1, 0, 1));
			CHECK(3, test.addLine(DOUBLE_INFINITE_LINE, 0, 2, 0, 4));
			bool catch_flag = false;
			try {
				test.addLine(SINGLE_INFINITE_LINE, 0, -1, 0, -1);
			}
			catch (LineCoincidenceException &e) {
				catch_flag = true;
				CHECK("Error: this line has been coincident!", e.what());
			}
			CHECK(true, catch_flag);
		}

		TEST_METHOD(add_line_test_2)
		{
			GeometryFactory test;
			CHECK(1, test.addLine(LIMITED_LINE, 0, 2, 0, 2));
			CHECK(3, test.addLine(SINGLE_INFINITE_LINE, 0, -1, 0, -1));
			
			bool catch_flag = false;
			try {
				test.addLine(SINGLE_INFINITE_LINE, 1, 4, 1, 4);
			}
			catch (LineCoincidenceException &e) {
				catch_flag = true;
				CHECK("Error: this line has been coincident!", e.what());
			}
			CHECK(true, catch_flag);
			catch_flag = false;
			try {
				test.addLine(LIMITED_LINE, 1, -1, 1, -1);
			}
			catch (LineCoincidenceException &e) {
				catch_flag = true;
				CHECK("Error: this line has been coincident!", e.what());
			}
			CHECK(true, catch_flag);
			catch_flag = false;
		}

		TEST_METHOD(add_line_test_3)
		{
			GeometryFactory test;
			CHECK(1, test.addLine(DOUBLE_INFINITE_LINE, 0, 1, 0, 1));
			bool flag = false;
			try {
				test.addLine(DOUBLE_INFINITE_LINE, 0, 0, 1, 1);
			}
			catch (CoordinateCoincidenceException &e) {
				CHECK("Error: coordinate coincident!", e.what());
				flag = true;
			}
			CHECK(true, flag);

			flag = false;
			try {
				test.addLine(DOUBLE_INFINITE_LINE, 100000, 0, 0, 0);
			}
			catch (CoordinateRangeException &e) {
				CHECK("Error: coordinate is out of range!", e.what());
				flag = true;
			}
			CHECK(true, flag);

			flag = false;
			try {
				test.addLine(DOUBLE_INFINITE_LINE, -100000, 0, 0, 0);
			}
			catch (CoordinateRangeException &e) {
				CHECK("Error: coordinate is out of range!", e.what());
				flag = true;
			}
			CHECK(true, flag);

			flag = false;
			try {
				test.addLine(5, 1000, 0, 0, 0);
			}
			catch (UndefinedLineException &e) {
				CHECK("Error: undefined line type!", e.what());
				flag = true;
			}
			CHECK(true, flag);
		}

		TEST_METHOD(add_circle_test1) 
		{
			GeometryFactory test;
			CHECK(0, test.addCircle(0, 0, 3));
			CHECK(2, test.addCircle(0, 0, 8));
			bool flag = false;

			try {
				test.addCircle(0, 0, -4);
			}
			catch (NegativeRadiusException &e) {
				flag = true;
				CHECK("Error: radius of circle is illegal!", e.what());
			}
			CHECK(true, flag);

			flag = false;
			try {
				test.addCircle(0, 0, 100000);
			}
			catch (CoordinateRangeException &e) {
				flag = true;
				CHECK("Error: coordinate is out of range!", e.what());
			}
			CHECK(true, flag);

			flag = false;
			try {
				test.addCircle(0, -100000, 10000);
			}
			catch (CoordinateRangeException &e) {
				flag = true;
				CHECK("Error: coordinate is out of range!", e.what());
			}
			CHECK(true, flag);

			flag = false;
			try {
				test.addCircle(0, 0, 3);
			}
			catch (CircleCoincidenceException &e) {
				flag = true;
				CHECK("Error: this circle has been added!", e.what());
			}
			CHECK(true, flag);
		}

		TEST_METHOD(add_line_add_circle) 
		{
			GeometryFactory test;
			CHECK(1, test.addLine(DOUBLE_INFINITE_LINE, 0, 324, 0, 332));
			CHECK(3, test.addLine(DOUBLE_INFINITE_LINE, 0, -3, 0, 322));
			CHECK(0, test.addCircle(0, 0, 8));
			CHECK(2, test.addCircle(0, 0, 7));
			CHECK(5, test.addLine(DOUBLE_INFINITE_LINE, -32, -33, 32, 22));
		}

		TEST_METHOD(line_circle_intersect_1)
		{
			Circle c1(0, 0, 1);
			Line l1(1, 0, 1, 43, DOUBLE_INFINITE_LINE);
			GeometryFactory test;
			test.line_circle_intersect(l1, c1);
			CHECK(test.getPointsCount(), 1);
			Line l2(2, 0, 2, 932, DOUBLE_INFINITE_LINE);
			test.line_circle_intersect(l2, c1);
			CHECK(test.getPointsCount(), 1);
			Line l3(0, 0, 0, 32, DOUBLE_INFINITE_LINE);
			test.line_circle_intersect(l3, c1);
			CHECK(test.getPointsCount(), 3);
			Line l4(-1, 1, 4, 1, DOUBLE_INFINITE_LINE);
			test.line_circle_intersect(l4, c1);
			CHECK(test.getPointsCount(), 3);
		}

		TEST_METHOD(circle_circle_intersect_1)
		{
			Circle c1(3, 8, 9);
			Circle c2(8, -4, 4);
			GeometryFactory test;
			test.circle_circle_intersect(c1, c2);
			CHECK(1, test.getPointsCount());
		}

		TEST_METHOD(circle_circle_intersect_2)
		{
			Circle c1(0, 0, 2);
			Circle c2(3, 0, 1);
			GeometryFactory test;
			test.circle_circle_intersect(c1, c2);
			CHECK(1, test.getPointsCount());
			Circle c3(-1, 0, 2);
			test.circle_circle_intersect(c1, c3);
			CHECK(3, test.getPointsCount());
		}

		TEST_METHOD(circle_circle_intersect_3)
		{
			Circle c1(0, 0, 42);
			Circle c2(25, 25, 10);
			GeometryFactory test;
			test.circle_circle_intersect(c1, c2);
			CHECK(2, test.getPointsCount());
		}

		TEST_METHOD(get_line_remove_line)
		{
			GeometryFactory test;
			CHECK(1, test.addLine(DOUBLE_INFINITE_LINE, 0, 3, 0, 3));
			CHECK(3, test.addLine(DOUBLE_INFINITE_LINE, 0, 43, 0, 23));
			Line l = test.getLine(1);
			CHECK((int)l.x1, 0);
			CHECK((int)l.x2, 3);
			CHECK((int)l.y1, 0);
			CHECK((int)l.y2, 3);
			CHECK((size_t)2, test.line_ids.size());
			test.remove(1);
			CHECK((size_t)1, test.line_ids.size());
			bool flag = false;
			try {
				test.remove(33);
			}
			catch (ObjectNotFoundException &e) {
				CHECK("Error: line not found or invalid id!", e.what());
				flag = true;
			}
			CHECK(true, flag);
		}

		TEST_METHOD(get_circle)
		{
			GeometryFactory test;
			CHECK(0, test.addCircle(0, 0, 3));
			CHECK(2, test.addCircle(1, 1, 3));
			Circle c = test.getCircle(0);
			CHECK((int)c.a, 0);
			CHECK((int)c.b, 0);
			CHECK((int)c.r, 3);
			CHECK((size_t)2, test.circle_ids.size());
			test.remove(0);
			CHECK((size_t)1, test.circle_ids.size());
			bool flag = false;
			try {
				test.remove(22);
			}
			catch (ObjectNotFoundException &e) {
				CHECK("Error: circle not found or invalid id!", e.what());
				flag = true;
			}
			CHECK(true, flag);
		}

		TEST_METHOD(add_Object_from_file)
		{
			GeometryFactory test;
			test.addObjectFromFile("L 0 0 1 1");
			test.addObjectFromFile("S 0 0 -1 1");
			test.addObjectFromFile("R 0 0 1 -1");
			Line l = test.getLine(1);
			CHECK((int)l.x1, 0);
			CHECK((int)l.y1, 0);
			CHECK((int)l.x2, 1);
			CHECK((int)l.y2, 1);
			test.addObjectFromFile("C 0 0 3");
			Circle c = test.getCircle(0);
			CHECK((int)c.a, 0);
			CHECK((int)c.b, 0);
			CHECK((int)c.r, 3);
			bool flag = false;
			try {
				test.addObjectFromFile("L 0 0 0 0 0");
			}
			catch (WrongFormatException &e) {
				flag = true;
				CHECK("Error: we got the wrong format input!", e.what());
			}
			CHECK(true, flag);
		}

		TEST_METHOD(exception_test)
		{
			try {
				throw CoordinateCoincidenceException();
			}
			catch (CoordinateCoincidenceException &e) {}
			try {
				throw CoordinateRangeException();
			}
			catch (CoordinateRangeException &e) {}
			try {
				throw NegativeRadiusException();
			}
			catch (NegativeRadiusException &e) {}
			try {
				throw LineCoincidenceException();
			}
			catch (LineCoincidenceException &e) {}
			try {
				throw UndefinedLineException();
			}
			catch (UndefinedLineException &e) {}
			try {
				throw ObjectNotFoundException();
			}
			catch (ObjectNotFoundException &e) {}
			try {
				throw WrongFormatException();
			}
			catch (WrongFormatException &e) {}
		}

		TEST_METHOD(point_test)
		{
			Point p;
			p.x = 1;
			p.y = 32;
			struct double_equal e;
			CHECK(e(1, p.x), true);
			CHECK(e(32, p.y), true);
			Point pp = Point(23.33, 32.22);
			CHECK(e(23.33, pp.x), true);
			CHECK(e(32.22, pp.y), true);
		}


	};
}