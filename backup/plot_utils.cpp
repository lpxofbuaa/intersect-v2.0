#include "plot_utils.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

// Get max value of points
pair<double, double> get_max(vector<Point> a){
    double max_x = -1e12, max_y = -1e12;
    for(auto it = a.begin(); it != a.end(); it++){
        max_x = max(max_x, (*it).x);
        max_y = max(max_y, (*it).y);
    }
    return pair<double, double>(max_x, max_y);
}

// Get min value of points
pair<double, double> get_min(vector<Point> a){
        double min_x = 1e12, min_y = 1e12;
    for(auto it = a.begin(); it != a.end(); it++){
        min_x = min(min_x, (*it).x);
        min_y = min(min_y, (*it).y);
    }
    return pair<double, double>(min_x, min_y);
}

// Generate line points
// todo : consider special occasion - k = inf.
pair<QVector<double>, QVector<double>> generate_line_points(Line l, pair<double, double> axis_max, pair<double, double> axis_min){
    int type = l.type;
    double max_x = axis_max.first * 1.5 + 10;
    double max_y = axis_max.second * 1.5 + 10;
    double min_x = axis_min.first * 1.5 - 10;
    double min_y = axis_max.second * 1.5 - 10;
    
    double x_scale_min;
    double x_scale_max;

    QVector<double> xs;
    QVector<double> ys;

    if(type == 1){
        x_scale_min = min_x;
        x_scale_max = max_x;
    }
    else if(type == 2){
        x_scale_max = (l.x1 < l.x2) ? max_x : l.x1;
        x_scale_min = (l.x1 < l.x2) ? l.x1 : min_x;
    }
    else{
        x_scale_max = max(l.x1, l.x2);
        x_scale_min = min(l.x1, l.x2);
    }

    double i = x_scale_min;
    do{
        xs.push_back(i);
        ys.push_back(l.key.k * i + l.key.b);
        i = i + (x_scale_max - x_scale_min) / 250;
    }while(i < x_scale_max);

    return pair<QVector<double>, QVector<double>>(xs, ys);
}
