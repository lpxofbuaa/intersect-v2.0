#ifndef SUPERWINDOW_H
#define SUPERWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include <QSpinBox>
#include "export/lib/GeometryCore.h"
#pragma comment(lib,"export/lib/GeometryCore.lib")

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

    void on_pushBotton_AddCircle_clicked();

    void on_pushBotton_AddLine_clicked();

    void on_pushBotton_DeleteObject_clicked();

    void on_pushBotton_LoadFile_clicked();

private:
    Ui::SuperWindow *ui;
    MainWindow* plot;
    GeometryFactory* core;
    void init();

    void update_log(QString m);
    void update_logs(vector<QString> m);
};

#endif // SUPERWINDOW_H
