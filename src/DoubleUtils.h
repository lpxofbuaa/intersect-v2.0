#pragma once
#include "stdafx.h"
#include <algorithm>
#include "Constant.h"
#include <cmath>

using namespace std;

class Double {
public:
	// Get size_t type hash value of a double value. 
	static size_t hash(double const &value);

	// Compare equal of two double value.
	static bool equal(double const &a, double const &b);

	// Compare Less of two double value.
	static bool less(double const &a, double const &b);

	// Compare Greater of two double value. 
	static bool greater(double const &a, double const &b);
};

struct double_hash {
	size_t operator()(double const& a) const;
};

struct double_equal {
	bool operator()(double const& a, double const& b) const;
};
