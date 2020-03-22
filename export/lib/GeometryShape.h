#pragma once
#include "export/lib/Point.h"
#include <cmath>
#include "export/lib/DoubleUtils.h"
#include "export/lib/Constant.h"

class LineKey {
public:
	double k, b;
	LineKey();
	LineKey(double k, double b);
};

class Line {
private:
	void get_coincident_check_bounding();
public:
	long long x_min, x_max, y_min, y_max;
	long long x1, y1, x2, y2;
	long long a, b, c;
	int type;
	LineKey k;
	Line();
	Line(long long x1, long long y1, long long x2, long long y2, int type);
	friend bool line_coincident(Line &l1, Line &l2);
};

class Circle {
public:
	long long a, b, r;
	Circle();
	Circle(long long aa, long long bb, long long cc);
};

/* ��������ͬ��line_key��hashֵ��ͬ��*/
struct line_key_hash {
	size_t operator()(LineKey const& a) const;
};

/* �ж�line_key�Ƿ������ͬ */
struct line_key_equal {
	bool operator()(LineKey const& a, LineKey const& b) const;
};


/* ������ͬ������Բ��hashֵ��ͬ�� */
struct circle_hash {
	size_t operator()(Circle const& a) const;
};

/* �ж��Ƿ������һ��Բ */
struct circle_equal {
	bool operator()(Circle const& a, Circle const& b) const;
};
