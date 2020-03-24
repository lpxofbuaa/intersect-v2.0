#ifndef SUPERWINDOW_H
#define SUPERWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include <QSpinBox>
#include "GeometryCore.h"
// #pragma comment(lib,"export/lib/GeometryCore.lib")

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
    void on_pushButton_show_clicked();

    void on_pushBotton_AddCircle_clicked();

    void on_pushBotton_AddLine_clicked();

    void on_pushBotton_DeleteObject_clicked();

    void on_pushBotton_LoadFile_clicked();

private:
    Ui::SuperWindow *ui;
    MainWindow* plot;
    GeometryFactory* core;

    void update_log(QString m);
    void update_logs(vector<QString> m);
    bool is_line(int id);
    bool is_circle(int id);

    /*
     * View list with check box
    */
    map<QStandardItem*, int> item_id;
    QStandardItemModel* item_model;
    void add_to_item(int id, char type, int x1, int x2, int y1, int y2);
    void add_to_item(int id, int x, int y, int r);

    QStandardItemModel* log_model;
    void report(string & message);

    void error_box(const char* s);
};

#endif // SUPERWINDOW_H
