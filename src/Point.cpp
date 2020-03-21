#include "stdafx.h"
#include "Point.h"
#include "DoubleUtils.h"
#include <iostream>

using namespace std;



Point::Point() {}

Point::Point(double a, double b) {
	x = a;
	y = b;
}

bool Point::point_equals(const Point & b) const
{
	return equals(this->x, b.x) && equals(this->y, b.y);
}

string Point::toString()
{
	return string(to_string(this->x) + "," + to_string(this->y));
}

size_t point_hash::operator()(Point* const& a) const {
	size_t a_hash = hashcode(a->x);
	size_t b_hash = hashcode(a->y);
	return a_hash ^ (b_hash << 1u);
}

/*
 * �������漰�������⣬��Ҫѡ��epsilon��Χ��
 * todo��epsilon��С��ѡȡ����������Χ�����ݺܴ���С�����ľ���Ҫ����ߡ�����ͬ�Ĵ�����������1e-10�㼶��С��ֵ���ܲ�ͬ)��
*/
bool point_equal::operator()(Point* const& a, Point* const& b) const {
	return a->point_equals(*b);
}

