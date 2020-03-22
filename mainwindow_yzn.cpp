 #include "mainwindow.h"
 #include <math.h>

// === BEGIN ===

/*
 * Some initial operation for software projects when constructing.
*/
void MainWindow::software_init(){
    // initial graph_count
    this->graph_count = 0;
    // set axis scale automatically change. 
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
}

/*
 * FUNC: Given all the intersects in vector, update it in the graph(0)
*/
int MainWindow::refresh_intersects(std::vector<Point> intersects){
    customPlot->graph(0)->setPen(QColor(0, 0, 255, 20));
    customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

    QVector<double> x, y; 
    for(auto it = intersects.begin(); it != intersects.end(); it++){
        x.push_back((*it).x);
        y.push_back((*it).y);
    }

    customPlot->graph(0)->setData(x, y);
    return 1;
}

/*
 * FUNC: Give a line and its core id, allocate a new graph for it and paint it on the graph.
*/
int MainWindow::add_one_line(Line l, int id){
    this->graph_count += 1;
    this->id_graph[id] = this->graph_count;

    customPlot->addGraph();

    long long min_bound, max_bound;
    long first_cor, second_cor;
    // check if k exist. 
    if(l.x1 == l.x2){
        first_cor = l.y1;
        second_cor = l.y2;
        min_bound = this->y_min;
        max_bound = this->y_max;
    }
    else{
        first_cor = l.x1;
        first_cor = l.x2;
        min_bound = this->x_min;
        max_bound = this->x_max;
    }
    
    // finite line
    if(l.type == 3){
        min_bound = (first_cor > second_cor) ? second_cor : first_cor;
        max_bound = (first_cor > second_cor) ? first_cor : second_cor;
    }
    // single infinite line
    else if(l.type == 2){
        min_bound = (first_cor > second_cor) ? min_bound : first_cor;
        max_bound = (first_cor > second_cor) ? first_cor : max_bound;
    }
    // double infinite line
    else if(l.type == 1){
        // the bigget range, so ignore.
    }

    QVector<double> x, y;
    if(l.x1 == l.x2){
        y.push_back(min_bound); x.push_back(l.x1);
        y.push_back(max_bound); x.push_back(l.x2);
    }
    else{
        x.push_back(min_bound); y.push_back(min_bound * l.key.k + l.key.b);
        x.push_back(max_bound); y.push_back(max_bound * l.key.k + l.key.b);
    }

    this->customPlot->graph(this->graph_count)->setData(x, y);
    customPlot->graph(this->graph_count)->rescaleAxes();

    return 1;
}

/*
 * FUNC: Given a circle, allocate a new graph and paint it on the graph. 
*/
int MainWindow::add_one_circle(Circle c, int id){
    this->graph_count += 1;
    this->id_graph[id] = this->graph_count;

    this->customPlot->addGraph();

    QVector<double> x, y;
    for(int angle = 0; angle <= 360; angle++){
        double rel_x = cos(angle * 1.0 / 360 * std::_Pi);
        double rel_y = sin(angle * 1.0 / 360 * std::_Pi);
        x.push_back(double(c.a) + rel_x);
        y.push_back(double(c.b) + rel_y);
    }

    this->customPlot->graph(this->graph_count)->setData(x, y);

    return 1;
}

/*
 * Remove a geometry object by id. 
*/
int MainWindow::remove_object(int id){
    int graph_id = id_graph[id];
    QVector<double> a(0), b(0);
    this->customPlot->graph(0)->setData(a, b);
}

// private
/*
 * FUNC: Given intersects, update plot axis scale automatically. 
*/
void MainWindow::update_scale_by_intersects(vector<Point> intersect){
    for(auto it = intersect.begin(); it != intersect.end(); it++){
        this->x_max = (this->x_max < (*it).x) ? (*it).x : this->x_max;
        this->x_min = (this->x_min > (*it).x) ? (*it).x : this->x_min;
        this->y_max = (this->y_max < (*it).y) ? (*it).y : this->y_max;
        this->y_min = (this->y_min > (*it).y) ? (*it).y : this->y_min;
    }
}