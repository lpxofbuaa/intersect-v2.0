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
#include "../Intersect/RationalNumber.h"
#include "../Intersect/GeometryCalculator.h"
#define CHECK Assert::AreEqual 

namespace CoreTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: 在此输入测试代码
			unordered_set<RationalPoint*, rational_point_hash, rational_point_equal> *test = new unordered_set<RationalPoint*, rational_point_hash, rational_point_equal>();

			for (int i = 0; i < 1000; ++i) {
				RationalNumber *a = new RationalNumber(3, 4);
				RationalNumber *b = new RationalNumber(6, 800);
				test->insert(new RationalPoint(*a, *b));
			}
			CHECK((int)test->size(), 1);
		}

		TEST_METHOD(RationalNumberTest)
		{
			// TODO: 在此输入测试代码
			RationalNumber a(-324, 23);
			RationalNumber b(1, 23);
			CHECK(true, b.bigger(a));
			CHECK(false, a.bigger(b));
			RationalNumber c(-3444, 4);
			CHECK(true, a.bigger(c));
			CHECK(false, c.bigger(a));
			RationalNumber dd(100000, 100000);
			CHECK(dd.toString(), string("1/1"));
			RationalNumber f((long long)324345 * (long long)324345, (long long)9998888 * (long long)9998888);
			//CHECK(f.toString(), string("33"));
			CHECK(true, f.canSqrt());
			RationalNumber e((long long)44444444 * (long long)44444444, (long long)888888888 * (long long)888888887);
			CHECK(false, e.canSqrt());
			long long g = 34;
			RationalNumber gg(345, 2);
			CHECK(true, a.smaller(g));
			CHECK(true, b.smaller(g));
			CHECK(true, gg.bigger(g));
		}

		TEST_METHOD(LineKeyTest)
		{
			struct line_key_equal equals;
			LineKey k((double) (4444444444 - 4444444442) / (5555555555 - 5555555552), (double) (2222222222 - 2222222220) / (5555555555 - 5555555550));
			CHECK((double) 2 / 3, k.k);
			CHECK((double) 2 / 5, 0.4);
			CHECK(true, equals(k, LineKey(0.6666666666666666, 0.4)));
		}

		TEST_METHOD(LineTest1)
		{
			Line l1(344, 56, 3245, 3334, DOUBLE_INFINITE_LINE);
			CHECK(l1.x_max, MAX_RANGE);
			CHECK(l1.x_min, MIN_RANGE);
			CHECK(l1.y_max, MAX_RANGE);
			CHECK(l1.y_min, MIN_RANGE);
			Line l2(-342, 422, 90, 0, SINGLE_INFINITE_LINE);
			CHECK(l2.x_max, MAX_RANGE);
			CHECK(l2.x_min, -342);
			Line l3(0, 344, 0, -325, SINGLE_INFINITE_LINE);
			CHECK(l3.y_max, 344);
			CHECK(l3.y_min, MIN_RANGE);
			Line l4(44532, 332, 564, 999, LIMITED_LINE);
			CHECK(l4.x_min, 564);
			CHECK(l4.x_max, 44532);
			Line l5(-432, -3423, -432, 8893, LIMITED_LINE);
			CHECK(l5.y_max, 8893);
			CHECK(l5.y_min, -3423);
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

		TEST_METHOD(HashTest) 
		{
			struct line_key_hash LineKeyHash;
			struct circle_hash CircleHash;
			struct rational_point_hash RationalPointHash;
			// struct unrational_point_hash UnRationalPointHash;
			LineKey l1((double)2 / 3, (double)6 / 7);
			LineKey l2((double)12 / 18, (double)606 / 707);
			CHECK(LineKeyHash(l1), LineKeyHash(l2));
			LineKey l3((double)9999 / 88888888, (double)9999 / 88887777);
			LineKey l4((double)9999 / 88888999, (double)9999 / 88887777);
			CHECK(LineKeyHash(l3) == LineKeyHash(l4), false);
			Circle a(3, 4, 5);
			Circle b(3, 4, 5);
			CHECK(CircleHash(a), CircleHash(b));
			RationalNumber n1(4, 5);
			RationalNumber n2(16, 20);
			RationalPoint *p1 = new RationalPoint(n1, n2);
			RationalPoint *p2 = new RationalPoint(n2, n1);
			CHECK(RationalPointHash(p1), RationalPointHash(p2));

		}

	};
}