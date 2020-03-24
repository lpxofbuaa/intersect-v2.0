#include "superwindow.h"
#include "ui_superwindow.h"
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

SuperWindow::SuperWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SuperWindow)
{
    ui->setupUi(this);
    core = new GeometryFactory();
    plot = new MainWindow(core);

    item_model = new QStandardItemModel(0, 1);
    ui->objectView->setModel(item_model);

    log_model = new QStandardItemModel(0, 1);
    ui->logView->setModel(log_model);
}

SuperWindow::~SuperWindow()
{
    delete ui;
}

void SuperWindow::on_pushButton_show_clicked()
{
    // rescale
    plot->reset_scale();
    // - by points
    int count = core->getPointsCount();
    double* point_x = new double[u_int(count)];
    double* point_y = new double[u_int(count)];
    core->getPoints(point_x, point_y, core->getPointsCount());
    this->plot->update_scale_by_intersects(point_x, point_y, core->getPointsCount());
    // - by lines and circles
    for(auto it = plot->id_graph.begin(); it != plot->id_graph.end(); it++){
        int id = (*it).first;
        if((*it).second >= 0){
            if(is_line(id)){
                Line l = core->getLine(id);
                plot->update_scale_by_line(l);
            }
            else if(is_circle(id)){
                Circle c = core->getCircle(id);
                plot->update_scale_by_circle(c);
            }
        }
    }
    plot->smooth_scale();

    // plot objects
    for(auto it = plot->id_graph.begin(); it != plot->id_graph.end(); it++){
        int id = (*it).first;
        if((*it).second >= 0){
            if(is_line(id)){
                Line l = core->getLine(id);
                plot->plot_one_line(l, id);
            }
            else if(is_circle(id)){
                Circle c = core->getCircle(id);
                plot->plot_one_circle(c, id);
            }
        }
    }

    // plot intersections
    plot->plot_intersects(point_x, point_y, count);

    delete[] point_x;
    delete[] point_y;

    // rescale
    // this->plot->customPlot->xAxis->setRange(plot->x_min, plot->x_max);
    // this->plot->customPlot->yAxis->setRange(plot->y_min, plot->y_max);
    plot->plot_transparent_box();
    plot->show();
}

void SuperWindow::on_pushBotton_AddCircle_clicked()
{
    QString x, y, r;
    x = ui->spin_circle_x->text();
    y = ui->spin_circle_y->text();
    r = ui->spin_circle_r->text();

    // cout << x.toStdString() << y.toStdString() << r.toStdString() << endl;
    // call core function to add circle and plot it.
     try {
        int x_int = x.toInt();
        int y_int = y.toInt();
        int r_int = r.toInt();
        int id = this->core->addCircle(x_int, y_int, r_int);
        // record
        this->plot->add_one_circle(id);
        Circle c = core->getCircle(id);
        add_to_item(id, int(c.a), int(c.b), int(c.r));
     } catch (exception &e) {
        string sentence = "[x] Add Circle " + x.toStdString() + " " + y.toStdString() +" " + r.toStdString() + "fail!";
        report(sentence);
        error_box(e.what());
     }
    ui->lineEdit_num_of_intersects->setText(tr(to_string(core->getPointsCount()).c_str()));
}

void SuperWindow::on_pushBotton_AddLine_clicked()
{
    QString type, x1, x2, y1, y2;
    type = ui->comboBox_line_type->currentText();
    x1 = ui->spin_line_x1->text();
    x2 = ui->spin_line_x2->text();
    y1 = ui->spin_line_y1->text();
    y2 = ui->spin_line_y2->text();

    int type_int, x1_int, x2_int, y1_int, y2_int;
    char line_type = '?';
    Line l;
    // call core function to add line and plot it.
    try {
        type_int = (type == "DoubleInfiniteLine") ? 1 :
                   (type == "SingleInfiniteLine") ? 2 :
                   (type == "FiniteLine") ? 3: 1;
        x1_int = x1.toInt();
        x2_int = x2.toInt();
        y1_int = y1.toInt();
        y2_int = y2.toInt();

        int id = this->core->addLine(type_int, x1_int, x2_int, y1_int, y2_int);

        // record
        this->plot->add_one_line(id);
        l = core->getLine(id);
        line_type = l.type == DOUBLE_INFINITE_LINE ? 'L' :
                    l.type == SINGLE_INFINITE_LINE ? 'R' :
                    l.type == LIMITED_LINE ? 'S' : '?';
        add_to_item(id, line_type, int(l.x1), int(l.x2), int(l.y1), int(l.y2));
    } catch (exception &e) {
        line_type = type_int == DOUBLE_INFINITE_LINE ? 'L' :
                    type_int == SINGLE_INFINITE_LINE ? 'R' :
                    type_int == LIMITED_LINE ? 'S' : '?';
        string message = "[x] Add Line " + to_string(line_type) + " " + to_string(x1_int) + " " + to_string(y1_int) +
                " " + to_string(x2_int) + " " + to_string(y2_int) + " fail!";
        report(message);
        error_box(e.what());
    }
    ui->lineEdit_num_of_intersects->setText(tr(to_string(core->getPointsCount()).c_str()));
}

void SuperWindow::on_pushBotton_DeleteObject_clicked()
{
    foreach (QStandardItem *item, item_model->findItems("*", Qt::MatchWildcard)) {
        if (item->checkState()) {
            // delete item;
            int id = item_id[item];
            try {
                this->core->remove(id);
                // get name
                string object = item->text().toStdString();
                // remove plot graph
                this->plot->remove_object(id);
                item_model->removeRow(item->index().row());

                string type = (object.at(0) == 'C') ? "Circle" : "Line";
                string message("[√] Remove " + type + " " + object + " successfully!");
                string ret = "";
                for (u_int i = 0; i < message.length(); ++i) {
                    if (message.at(i) == '\t') {
                        ret += " ";
                    } else {
                        char tmp[2] = {message.at(i), '\0'};
                        ret += string(tmp);
                    }
                }
                report(ret);

            } catch (exception e) {
                // string object = item->data().toString().toStdString();
                // string type = (object.at(0) == 'C') ? "Circle" : "Line";
                // string message = "[x] Remove " + type + " " + object + " fail!";
                // report(message);
                QErrorMessage error(this);
                error.showMessage(tr(e.what()));
            }
            ui->lineEdit_num_of_intersects->setText(tr(to_string(core->getPointsCount()).c_str()));
        }
    }
}

void SuperWindow::on_pushBotton_LoadFile_clicked()
{
    int count = 0;
    QString fileName = QFileDialog::getOpenFileName(this, "文件导入");
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Warning!", "Failed to open the file!");
    }
    else{
        try {
            ifstream reader;
            reader.open(fileName.toStdString().c_str(), ios::in);
            if (!reader.is_open()) {
                error_box("File Open Failed.");
            }
            string line;
            if (!getline(reader, line)) {
                error_box("The first line is empty. ");
            }
            stringstream s(line);
            if (!(s >> count)) {
                error_box("The first line is not a number. ");
            }
            while(count > 0){
                bool flag = false;
                try {
                    getline(reader, line);
                    count-=1;
                    int id = this->core->addObjectFromFile(line.c_str());
                    if(is_line(id)){
                        plot->add_one_line(id);
                        Line l = core->getLine(id);
                        char type = l.type == DOUBLE_INFINITE_LINE ? 'L' :
                                    l.type == SINGLE_INFINITE_LINE ? 'R' :
                                    l.type == LIMITED_LINE ? 'S' : '?';
                        add_to_item(id, type, int(l.x1), int(l.x2), int(l.y1), int(l.y2));
                    }
                    else if(is_circle(id)){
                        plot->add_one_circle(id);
                        Circle c = core->getCircle(id);
                        add_to_item(id, int(c.a), int(c.b), int(c.r));
                    }
                } catch (exception& e) {
                    flag = true;
                    string message = "[x] Add Object " + line +" fail!";
                    report(message);
                    string error_message = "[x] " + string(e.what());
                    report(error_message);
                    // error_box(e.what());
                }
                if(flag){
                    error_box("Error: Something wrong.");
                }
            }
        } catch (exception& e) {
            error_box(e.what());
        }
        ui->lineEdit_num_of_intersects->setText(tr(to_string(core->getPointsCount()).c_str()));
    }
}

void SuperWindow::error_box(const char *s){
    string message = "[x] " + string(s);
    report(message);
    QMessageBox::critical (this, tr("ERROR"), tr(s), QMessageBox::Ok);
}

/*
 * Given an id, ask core if it is a line.
*/
bool SuperWindow::is_line(int id){
    try {
        core->getLine(id);
        return true;
    } catch (exception &e) {
        return false;
    }
}

/*
 * Given an id, ask core if it is a circle.
*/
bool SuperWindow::is_circle(int id){
    try {
        core->getCircle(id);
        return true;
    } catch (exception &e) {
        return false;
    }
}

void SuperWindow::add_to_item(int id, char type, int x1, int x2, int y1, int y2)
{

    QStandardItem *item;

    item = new QStandardItem(QString("%0\t%1\t%2\t%3\t%4\t").arg(type).arg(x1).arg(y1).arg(x2).arg(y2));
    item->setEditable(false);
    item->setCheckable(true);

    item_model->appendRow(item);
    item_id[item] = id;

    // report
    char tmp[2] = {type, '\0'};
    string message("[√] Add Line " + string(tmp) + " " + to_string(x1) + " " +
                   to_string(y1) + " " + to_string(x2) + " " + to_string(y2) + " successfully!");
    report(message);
}

void SuperWindow::add_to_item(int id, int x, int y, int r)
{
    QStandardItem *item = new QStandardItem(QString("C\t%0\t%1\t%2").arg(x).arg(y).arg(r));
    item->setEditable(false);
    item->setCheckable(true);

    item_model->appendRow(item);
    item_id[item] = id;

    // report
    string message("[√] Add Circle C " + to_string(x) + " " +
                   to_string(y) + " " + to_string(r) + " successfully!");
    report(message);
}

void SuperWindow::report(string &message)
{
    QStandardItem *log;
    log = new QStandardItem(QString(message.c_str()));
    log->setEditable(false);
    log->setCheckable(false);
    log_model->appendRow(log);
}
