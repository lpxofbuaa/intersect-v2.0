#include "stdafx.h"
#include "DoubleUtils.h"

using namespace std;



size_t double_hash::operator()(double const& a) const {
	return hash<long long>{}((long long)round(a * DOUBLE_HASH_EPS));
}

bool double_equal::operator()(double const& a, double const& b) const {
	return equals(a, b);
}


