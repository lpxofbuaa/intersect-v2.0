#ifndef PLOT_UTILS_H
#define PLOT_UTILS_H

#include<iostream>
#include "intersectexample.h"
#include <QDebug>
#include <QMetaEnum>

using namespace std;

// Get max value of points
pair<double, double> get_max(vector<Point> a);

// Get min value of points
pair<double, double> get_min(vector<Point> b);

// Generate line points
pair<QVector<double>, QVector<double>> generate_line_points(Line l, pair<double, double>, pair<double, double>);

#endif // PLOT_UTILS_H
