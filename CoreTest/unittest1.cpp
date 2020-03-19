#include "stdafx.h"
#include "CppUnitTest.h"
#include <unordered_set>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
#include "../Intersect/Exception.h"
#include "../Intersect/Constant.h"
#include "../Intersect/GeometryShape.h"
#include "../Intersect/GeometryStatistic.h"
#include "../Intersect/Point.h"
#include "../Intersect/GeometryCalculator.h"
#include "../Intersect/DoubleUtils.h"
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
			CHECK(Double::equal(0.20000000000000001, 0.19999999999999991), true);
			CHECK(Double::hash(0.20000000000000001), Double::hash(0.19999999999999991));
			CHECK(Double::equal(0.00000000000000001234, 0.0), true);
			CHECK(Double::hash(0.00000000000000001234), Double::hash(0.0));
			CHECK(Double::equal(12345678901234.55677889, 12345678901234.557789), true);
		}


		TEST_METHOD(GeometryFactory_point_in_line_range)
		{
			GeometryFactory *test = new GeometryFactory();
			Point *p = new Point(3.0, 4.0);
			Line l1(3, 4, 5, 8, LIMITED_LINE);
			Line l2(3, 4, -10, -33, SINGLE_INFINITE_LINE);
			Line l3(-3, -4, -6, -8, SINGLE_INFINITE_LINE);
			Line l4(0, 0, 1, 1, DOUBLE_INFINITE_LINE);
			CHECK(test->point_in_line_range(p, l1), true);
			CHECK(test->point_in_line_range(p, l2), true);
			CHECK(test->point_in_line_range(p, l3), false);
			CHECK(test->point_in_line_range(p, l4), true);
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

		TEST_METHOD(line_line_intersect)
		{
			GeometryFactory *test = new GeometryFactory();
			vector<Point> p;
			Line l1(1, 2, 3, 4, DOUBLE_INFINITE_LINE);
			Line l2(1, 2, -1, 0, SINGLE_INFINITE_LINE);
			Line l3(1, 2, 5, 8, LIMITED_LINE);
			Point p1(1.0, 2.0);
			test->line_line_intersect(l1, l2);
			p = test->getPoints();
			CHECK((int)p.size(), 1);
			CHECK(p[0].equals(p1), true);
			test->line_line_intersect(l1, l3);
			CHECK((int)p.size(), 1);
			CHECK(p[0].equals(p1), true);
			test->line_line_intersect(l2, l3);
			CHECK((int)p.size(), 1);
			CHECK(p[0].equals(p1), true);
			delete test;
		}

	};
}