 #include "mainwindow.h"
 #include "ui_mainwindow.h"
 #include <math.h>

// === BEGIN ===

/*
 * Some initial operation for software projects when constructing.
*/
void MainWindow::software_init(){
    // initial graph_count
    this->graph_count = 1;
    // initial
    setWindowTitle("Intersect");
    statusBar()->clearMessage();
    ui->customPlot->replot();

    // set scale automatical change
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    this->x_min = -15;
    this->y_min = -15;
    this->x_max = 15;
    this->y_max = 15;
}

void MainWindow::reset_scale()
{
    x_min = -15;
    x_max = 15;
    y_min = -15;
    y_max = 15;
}

/*
 * FUNC: Given all the intersects, update it in the graph(0)
*/
int MainWindow::plot_intersects(double* x, double* y, int count){
    cout << "Plot Intersects " << count << endl;
    ui->customPlot->graph(0)->setPen(QColor(255, 0, 0));
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));

    QVector<double> vx, vy;
    for(int i = 0; i < count; i++){
        if(in_scale(x[i], y[i])){
            vx.push_back(x[i]);
            vy.push_back(y[i]);
        }
    }
    ui->customPlot->graph(0)->setData(vx, vy);

    // ui->customPlot->graph(0)->rescaleAxes(true);
    ui->customPlot->replot();

    return 0;
}

/*
 * Plot transparent box to fit entire box.
*/
int MainWindow::plot_transparent_box()
{
    cout << x_max << " " << y_max << " " << x_min << " " << y_min << endl;
    ui->customPlot->graph(1)->setPen(QColor(0, 0, 0, 0));
    ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    QVector<double> vx, vy;
    vx.push_back(x_max);vy.push_back(y_max);
    vx.push_back(x_min);vy.push_back(y_min);
    ui->customPlot->graph(1)->setData(vx, vy);

    ui->customPlot->graph(1)->rescaleAxes();
    ui->customPlot->replot();

    return 0;
}

int MainWindow::add_one_line(int id){
    this->id_graph[id] = this->graph_count + 1;
    this->graph_count += 2;

    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    return 0;
}

/*
 * FUNC: Give a line and its core id, allocate a new graph for it and paint it on the graph.
*/
int MainWindow::plot_one_line(Line l, int id){
    double min_bound, max_bound;
    double first_cor, second_cor;
    // check if k exist. 
    if(l.x1 == l.x2){
        first_cor = l.y1;
        second_cor = l.y2;
        min_bound = this->y_min;
        max_bound = this->y_max;
    }
    else{
        first_cor = l.x1;
        second_cor = l.x2;
        min_bound = this->x_min;
        max_bound = this->x_max;
    }
    
    // finite line
    if(l.type == LIMITED_LINE){
        min_bound = (first_cor > second_cor) ? second_cor : first_cor;
        max_bound = (first_cor > second_cor) ? first_cor : second_cor;
    }
    // single infinite line
    else if(l.type == SINGLE_INFINITE_LINE){
        min_bound = (first_cor > second_cor) ? min_bound : first_cor;
        max_bound = (first_cor > second_cor) ? first_cor : max_bound;
    }
    // double infinite line
    else if(l.type == DOUBLE_INFINITE_LINE){
        // the bigget range, so ignore.
    }

    QVector<double> x, y;
    if(l.x1 == l.x2){
        y.push_back(min_bound); x.push_back(l.x1);
        y.push_back(max_bound); x.push_back(l.x2);
    }
    else{
        // to make sure line in the scale, must choose the small one.
        x.push_back(min_bound);
        y.push_back(min_bound * l.k.k + l.k.b);
//        if(in_scale(min_bound, min_bound * l.k.k + l.k.b)){

//        }
//        else{
//            x.push_back((y_min - l.k.b)/l.k.k);
//            y.push_back(y_min);
//        }
        x.push_back(max_bound);
        y.push_back(max_bound * l.k.k + l.k.b);
//        if(in_scale(max_bound, max_bound * l.k.k + l.k.b)){

//        }
//        else{
//            x.push_back((y_max - l.k.b) / l.k.k);
//            y.push_back(y_max);
//        }
    }

    ui->customPlot->graph(id_graph[id])->setData(x, y);
    // ui->customPlot->graph(id_graph[id])->rescaleAxes(true);
    // ui->customPlot->graph(id_graph[id] + 1)->rescaleAxes(true);

    ui->customPlot->replot();

    return 0;
}

int MainWindow::add_one_circle(int id){
    this->id_graph[id] = this->graph_count + 1;
    this->graph_count += 2;
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();

    return 0;
}

/*
 * FUNC: Given a circle, allocate a new graph and paint it on the graph. 
*/
int MainWindow::plot_one_circle(Circle c, int id){
    QVector<double> x_up, y_up;
    for(int angle = 0; angle <= 180; angle++){
        double rel_x = c.r * cos((angle * 1.0) / 180 * 3.14159265);
        double rel_y = c.r * sin((angle * 1.0) / 180 * 3.14159265);
        if(in_scale(rel_x + c.a, rel_y + c.b)){
            x_up.push_back(double(c.a) + rel_x);
            y_up.push_back(double(c.b) + rel_y);
        }
    }
    ui->customPlot->graph(id_graph[id])->setData(x_up, y_up);

    QVector<double> x_down, y_down;
    for(int angle = 180; angle <= 360; angle++){
        double rel_x = c.r * cos((angle * 1.0) / 180 * 3.14159265);
        double rel_y = c.r * sin((angle * 1.0) / 180 * 3.14159265);
        if(in_scale(rel_x + c.a, rel_y + c.b)){
            x_down.push_back(double(c.a) + rel_x);
            y_down.push_back(double(c.b) + rel_y);
        }
    }
    ui->customPlot->graph(id_graph[id] + 1)->setData(x_down, y_down);

    // ui->customPlot->graph(id_graph[id])->rescaleAxes(true);
    // ui->customPlot->graph(id_graph[id] + 1)->rescaleAxes(true);

    ui->customPlot->replot();

    return 0;
}

/*
 * Remove a geometry object by id. 
*/
int MainWindow::remove_object(int id){
    int graph_id = id_graph[id];
    QVector<double> a(0), b(0);
    ui->customPlot->graph(graph_id)->setData(a, b);
    ui->customPlot->graph(graph_id + 1)->setData(a, b);
    id_graph[id] = -1;
    return 0;
}

// private
/*
 * FUNC: Given intersects, update plot axis scale automatically. 
*/
void MainWindow::update_scale_by_intersects(double* x, double* y, int count){
    for(int i = 0; i < count; i++){
        double _x = x[i];
        double _y = y[i];
        this->x_max = (this->x_max < _x) ? _x : this->x_max;
        this->x_min = (this->x_min > _x) ? _x : this->x_min;
        this->y_max = (this->y_max < _y) ? _y : this->y_max;
        this->y_min = (this->y_min > _y) ? _y : this->y_min;
    }
    double real_max = std::max(this->x_max, this->y_max);
    real_max = std::max(real_max, std::max(-this->x_min, -this->y_min));
    this->x_max = real_max;
    this->x_min = -real_max;
    this->y_max = real_max;
    this->y_min = -real_max;
}

void MainWindow::update_scale_by_line(Line l)
{
    x_max = std::max(x_max, double(std::max(l.x1, l.x2)));
    x_min = std::min(x_min, double(std::min(l.x1, l.x2)));
    y_max = std::max(y_max, double(std::max(l.y1, l.y2)));
    y_min = std::min(y_min, double(std::min(l.y1, l.y2)));

    double real_max = std::max(x_max, y_max);
    real_max = std::max(real_max, std::max(-x_min, -y_min));
    x_max = real_max;
    x_min = -real_max;
    y_max = real_max;
    y_min = -real_max;
}

void MainWindow::update_scale_by_circle(Circle c)
{
    x_max = std::max(x_max, double(c.a + c.r));
    x_min = std::min(x_min, double(c.a - c.r));
    y_max = std::max(y_max, double(c.b + c.r));
    y_min = std::min(y_min, double(c.b - c.r));

    double real_max = std::max(x_max, y_max);
    real_max = std::max(real_max, std::max(-x_min, -y_min));
    x_max = real_max;
    x_min = -real_max;
    y_max = real_max;
    y_min = -real_max;
}

void MainWindow::smooth_scale()
{
    x_max *= 1.5;
    y_max *= 1.5;
    x_min *= 1.5;
    y_min *= 1.5;
}

bool MainWindow::in_scale(double x, double y)
{
    return (x_min <= x+0.1 && x-0.1 <= x_max && y_min+0.1 <= y && y-0.1 <= y_max);
}
