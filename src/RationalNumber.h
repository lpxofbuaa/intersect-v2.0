#pragma once
#include "stdafx.h"
#include<unordered_set>
#include<string>

using namespace std;

class RationalNumber {
private:
	long long molecule;
	long long denominator;
public:
	RationalNumber();
	RationalNumber(long long n, long long m);
	string toString() const;
	double toDouble() const;
	size_t hashcode() const;
	bool equals(const RationalNumber &b) const;
	bool equals(long long b) const;
	bool bigger(const RationalNumber &b) const; // a > b?
	bool bigger(long long b) const; // a > b?
	bool smaller(long long b) const; // a < b?
	RationalNumber add(RationalNumber &b) const;
	RationalNumber sub(RationalNumber &b) const;
	RationalNumber mult(RationalNumber &b) const;
	RationalNumber div(RationalNumber &b) const;
	RationalNumber add(int b) const;
	RationalNumber sub(int b) const;
	RationalNumber mult(int b) const;
	RationalNumber div(int b) const;
	RationalNumber Sqrt() const;
	bool canSqrt() const;
	bool sign() const;
};
