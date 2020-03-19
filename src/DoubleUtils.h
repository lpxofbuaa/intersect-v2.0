#pragma once
#include "stdafx.h"
#include <unordered_set>
#include <string>
#include <map>

using namespace std;

class Double{
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