#include "superwindow.h"
#include "ui_superwindow.h"
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <string>

SuperWindow::SuperWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SuperWindow)
{
    ui->setupUi(this);
    core = new GeometryFactory();
    plot = new MainWindow(core);

    init();
}

SuperWindow::~SuperWindow()
{
    delete ui;
}

void SuperWindow::on_pushButton_open_clicked()
{
    return;
}

void SuperWindow::on_pushButton_show_clicked()
{

    plot->show();
}

void SuperWindow::on_pushBotton_AddCircle_clicked()
{
    QString x, y, r;
    x = ui->spin_circle_x->text();
    y = ui->spin_circle_y->text();
    r = ui->spin_circle_r->text();

    // call core function to add circle and plot it.
    try {
        int x_int = x.toInt();
        int y_int = y.toInt();
        int r_int = r.toInt();
        int id = this->core->addCircle(x_int, y_int, r_int);
        // plot
        Circle c = this->core->getCircle(id);
        this->plot->update_scale_by_intersects(this->core->getPoints());
        this->plot->add_one_circle(c, id);
    } catch (exception e) {
        // todo
    }
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
    // call core function to add line and plot it.
    try {
        type_int = (type == "DoubleInfiniteLine") ? 1 :
                   (type == "SignleInfiniteLine") ? 2 :
                   (type == "FiniteLine") ? 3: 1;
        x1_int = x1.toInt();
        x2_int = x2.toInt();
        y1_int = y1.toInt();
        y2_int = y2.toInt();

        int id = this->core->addLine(type_int, x1_int, y1_int, x2_int, y2_int);

        // plot
        this->plot->update_scale_by_intersects(this->core->getPoints());
        Line l = this->core->getLine(id);
        this->plot->add_one_line(l, id);
    } catch (exception e) {
        QErrorMessage error(this);
        error.showMessage(tr(e.what()));
    }
}

void SuperWindow::on_pushBotton_DeleteObject_clicked()
{
    QString id_str;
    id_str = ui->spin_delete_id->text();
    int id = id_str.toInt();

    try {
        this->core->remove(id);
        // remove plot graph
        this->plot->remove_object(id);
    } catch (exception e) {
        QErrorMessage error(this);
        error.showMessage(tr(e.what()));
    }
}

void SuperWindow::on_pushBotton_LoadFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "文件导入");
    char line[1024];
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Warning!", "Failed to open the video!");
    }
    else{
        auto reader = new ifstream(fileName.toStdString().c_str());
        while(reader->getline(line,sizeof(line))){
            string line_str(line);
            try {
                this->core->addObjectFromFile(line_str);
            } catch (exception e) {
                // todo
            }
        }
    }
}
