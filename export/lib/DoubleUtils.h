#pragma once
#include <algorithm>
#include "export/lib/Constant.h"
#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

struct double_hash {
	size_t operator()(double const& a) const;
};

struct double_equal {
	bool operator()(double const& a, double const& b) const;
};

	// Get size_t type hash value of a double value. 
inline size_t hashcode(double const &value)
{
	double_hash a;
	return a(value);
}

	// Compare equal of two double value.
inline bool equals(double const &a, double const &b)
{
	double delta = fabs(a - b);
	//return delta < 1e-7;
	//cout << "--------------------------------" << endl;
	//cout << setprecision(16) << delta << endl;
	//cout << setprecision(16) << max(min(fabs(a), fabs(b)) * DOUBLE_EPSILON, DOUBLE_MIN_EPSILON) << endl;
	return delta < max(min(fabs(a), fabs(b)) * DOUBLE_EPSILON, DOUBLE_MIN_EPSILON);
}

	// Compare Less of two double value.
inline bool lessthan(double const &a, double const &b)
{
	return b - a > max(min(fabs(a), fabs(b)) * DOUBLE_EPSILON, DOUBLE_MIN_EPSILON);
}


	// Compare Greater of two double value. 
inline bool greaterthan(double const &a, double const &b)
{
	return a - b > max(min(fabs(a), fabs(b)) * DOUBLE_EPSILON, DOUBLE_MIN_EPSILON);
}



