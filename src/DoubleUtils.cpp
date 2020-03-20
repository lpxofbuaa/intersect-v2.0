#include "stdafx.h"
#include "DoubleUtils.h"

using namespace std;

size_t Double::hash(double const & value)
{
	double_hash a;
	return a(value);
}

bool Double::equal(double const & a, double const & b)
{
	double delta = fabs(a - b);
	//return delta < 1e-7;
	//cout << "--------------------------------" << endl;
	//cout << setprecision(16) << delta << endl;
	//cout << setprecision(16) << max(min(fabs(a), fabs(b)) * DOUBLE_EPSILON, DOUBLE_MIN_EPSILON) << endl;
	return delta < max(min(fabs(a), fabs(b)) * DOUBLE_EPSILON, DOUBLE_MIN_EPSILON);
}

bool Double::greater(double const & a, double const & b)
{
	return a - b > max(min(fabs(a), fabs(b)) * DOUBLE_EPSILON, DOUBLE_MIN_EPSILON);
}

bool Double::less(double const & a, double const & b)
{
	return b - a > max(min(fabs(a), fabs(b)) * DOUBLE_EPSILON, DOUBLE_MIN_EPSILON);
}

size_t double_hash::operator()(double const& a) const {
	return hash<long long>{}((long long)round(a * DOUBLE_HASH_EPS));
}

bool double_equal::operator()(double const& a, double const& b) const {
	return Double::equal(a, b);
}


