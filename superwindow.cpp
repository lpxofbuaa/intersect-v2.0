#include "superwindow.h"
#include "ui_superwindow.h"

SuperWindow::SuperWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SuperWindow)
{
    ui->setupUi(this);
    plot = new MainWindow();
}

SuperWindow::~SuperWindow()
{
    delete ui;
}

void SuperWindow::on_pushButton_show_clicked()
{
    plot->show();
}
