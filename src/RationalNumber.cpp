#include "stdafx.h"
#include "RationalNumber.h"
#include <iostream>

using namespace std;

RationalNumber::RationalNumber(long long n, long long m) {
	int sign = ((n >= 0 && m >= 0)||(n <= 0 && m <= 0)) ? 1 : -1;
	n = abs(n);
	m = abs(m);
	long long before_n = n;
	long long before_m = m;
	bool isBig = n > m;
	if (n == 0) {
		molecule = 0;
		denominator = 1;
		return;
	}
	if (isBig) {
		long long tmp = n;
		n = m;
		m = tmp;
	}
	while (n != 0) {
		long long rem = m % n;
		m = n;
		n = rem;
	}
	this->molecule = before_n / m * sign;
	this->denominator = before_m / m;
	//cout << toString() << endl;
}

RationalNumber::RationalNumber() {}

string RationalNumber::toString() const {
	return to_string(molecule) + "/" + to_string(denominator);
}

double RationalNumber::toDouble() const {
	return (double) molecule / (double) denominator;
}

size_t RationalNumber::hashcode() const
{
	size_t h1 = hash<long long>{}(molecule);
	size_t h2 = hash<long long>{}(denominator);
	return h1 ^ (h2 << 1u);
}

bool RationalNumber::equals(const RationalNumber &b) const {
	return this->molecule == b.molecule && b.denominator == this->denominator;
}

bool RationalNumber::equals(long long b) const {
	return this->molecule == b * this->denominator;
}

bool RationalNumber::bigger(const RationalNumber & b) const
{
	return this->molecule * b.denominator > this->denominator * b.molecule;
}

bool RationalNumber::bigger(long long b) const
{
	return this->molecule > b * this->denominator;
}

bool RationalNumber::smaller(long long b) const
{
	return this->molecule < b * this->denominator;
}

RationalNumber RationalNumber::add(RationalNumber &b) const {
	return RationalNumber(this->molecule * b.denominator + b.molecule * this->denominator, this->denominator * b.denominator);
}

RationalNumber RationalNumber::sub(RationalNumber &b) const {
	return RationalNumber(this->molecule * b.denominator - b.molecule * this->denominator, this->denominator * b.denominator);
}

RationalNumber RationalNumber::mult(RationalNumber &b) const {
	return RationalNumber(this->molecule * b.molecule, this->denominator * b.denominator);
}

RationalNumber RationalNumber::div(RationalNumber &b) const {
	return RationalNumber(this->molecule * b.denominator, this->denominator * b.molecule);
}

RationalNumber RationalNumber::add(long long b) const {
	return RationalNumber(molecule + denominator * b, denominator);
}

RationalNumber RationalNumber::sub(long long b) const {
	return RationalNumber(molecule - denominator * b, denominator);
}

RationalNumber RationalNumber::mult(long long b) const {
	return RationalNumber(molecule * b, denominator);
}

RationalNumber RationalNumber::div(long long b) const {
	return RationalNumber(molecule, denominator * b);
}

RationalNumber RationalNumber::Sqrt() const {
	return RationalNumber((long long) sqrt(molecule), (long long) sqrt(denominator));
}


/*
 * 判断此份数是否可被整型开方。
 * HINT：负数不可以被开方。
 */
bool RationalNumber::canSqrt() const {
	if (molecule < 0)
		return false;
	long long sqrt_molecule = (long long)sqrt(molecule);
	long long sqrt_denominator = (long long)sqrt(denominator);
	return sqrt_molecule * sqrt_molecule == molecule && sqrt_denominator * sqrt_denominator == denominator;
}

bool RationalNumber::sign() const {
	return molecule >= 0;
}