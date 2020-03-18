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

/* ��������ͬ��line_key��hashֵ��ͬ��*/
struct line_key_hash {
	size_t operator()(LineKey const& a) const;
};

/* �ж�line_key�Ƿ������ͬ */
struct line_key_equal {
	bool operator()(LineKey const& a, LineKey const& b) const;
};

/* ����line_key���������ʵĶ���hashֵ��ͬ�� 
struct line_hash {
	size_t operator()(Line const& a) const;
};
*/

/* �ж϶���line_key�����������Ƿ�����ͬ�ġ�
 * ������ʲô�ģ���ͬ��k��b�����ͣ���Ȼ�����ǲ�ͬ�Ķ���
 * done: û��ʹ�á�

struct line_equal {
	bool operator()(Line const& a, Line const& b) const;
};
*/

/* ������ͬ������Բ��hashֵ��ͬ�� */
struct circle_hash {
	size_t operator()(Circle const& a) const;
};

/* �ж��Ƿ������һ��Բ */
struct circle_equal {
	bool operator()(Circle const& a, Circle const& b) const;
};