#ifndef SUPERWINDOW_H
#define SUPERWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"

namespace Ui {
class SuperWindow;
}

class SuperWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SuperWindow(QWidget *parent = nullptr);
    ~SuperWindow();

private slots:
    void on_pushButton_open_clicked();

    void on_pushButton_show_clicked();

private:
    Ui::SuperWindow *ui;
    MainWindow* plot;
};

#endif // SUPERWINDOW_H
