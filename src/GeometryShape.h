#pragma once
#include "Point.h"
#include "stdafx.h"

class LineKey {
public:
	double k, b;
	LineKey();
	LineKey(double k, double b);
};

class Line {
public:
	int x_min, x_max, y_min, y_max;
	int x1, y1, x2, y2;
	int type;
	LineKey k;
	Line();
	Line(int x1, int y1, int x2, int y2, int type);
	friend bool line_coincident(Line &l1, Line &l2);
};

class Circle {
public:
	int a, b, r;
	Circle();
	Circle(int aa, int bb, int cc);
};

/* 对于有相同的line_key，hash值相同。*/
struct line_key_hash {
	size_t operator()(LineKey const& a) const;
};

/* 判断line_key是否真的相同 */
struct line_key_equal {
	bool operator()(LineKey const& a, LineKey const& b) const;
};

/* 对于line_key和自身性质的对象，hash值相同。 
struct line_hash {
	size_t operator()(Line const& a) const;
};
*/

/* 判断对于line_key和自身性质是否都是相同的。
 * 这是做什么的？相同的k、b和类型，依然可以是不同的对象。
 * done: 没有使用。

struct line_equal {
	bool operator()(Line const& a, Line const& b) const;
};
*/

/* 对于相同参数的圆，hash值相同。 */
struct circle_hash {
	size_t operator()(Circle const& a) const;
};

/* 判断是否是真的一个圆 */
struct circle_equal {
	bool operator()(Circle const& a, Circle const& b) const;
};