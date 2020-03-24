/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011-2018 Emanuel Eichhammer                            **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.qcustomplot.com/                          **
**             Date: 25.06.18                                             **
**          Version: 2.0.1                                                **
****************************************************************************/

/************************************************************************************************************
**                                                                                                         **
**  This is the example code for QCustomPlot.                                                              **
**                                                                                                         **
**  It demonstrates basic and some advanced capabilities of the widget. The interesting code is inside     **
**  the "setup(...)Demo" functions of MainWindow.                                                          **
**                                                                                                         **
**  In order to see a demo in action, call the respective "setup(...)Demo" function inside the             **
**  MainWindow constructor. Alternatively you may call setupDemo(i) where i is the index of the demo       **
**  you want (for those, see MainWindow constructor comments). All other functions here are merely a       **
**  way to easily create screenshots of all demos for the website. I.e. a timer is set to successively     **
**  setup all the demos and make a screenshot of the window area and save it in the ./screenshots          **
**  directory.                                                                                             **
**                                                                                                         **
*************************************************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GeometryCore.h"
#include <QMainWindow>
#include <QTimer>
#include <map>
#include <vector>
#include "qcustomplot.h" // the header file of QCustomPlot. Don't forget to add it to your project, if you use an IDE, so it gets compiled.
// #pragma comment(lib,"export/lib/GeometryCore.lib")

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  /*
   * Added for BUAA software pair project.
   * By. YZN, LPX
   */
  // === BEGIN ===
  QCustomPlot* customPlot;

  GeometryFactory* intersect;
  map<int, int> id_graph;
  int graph_count;  // to count graphs, each graph contains a_line/a_circle/all_intersects.
  double x_max, x_min, y_max, y_min;

  int add_one_line(int id);
  int add_one_circle(int id);
  int plot_one_line(Line l, int id);
  int plot_one_circle(Circle c, int id);
  int plot_intersects(double* x, double* y, int count);
  int plot_transparent_box();
  int remove_object(int id);

  // private
  void software_init();
  void reset_scale();
  void update_scale_by_intersects(double* x, double* y, int count);
  void update_scale_by_line(Line l);
  void update_scale_by_circle(Circle c);
  void smooth_scale();
  bool in_scale(double x, double y);

  // ===  END  ===

  explicit MainWindow(GeometryFactory* intersect, QWidget *parent = 0);
  ~MainWindow();

  void softwarePlot(QCustomPlot *customPlot);

  void setupDemo(int demoIndex);
  void setupQuadraticDemo(QCustomPlot *customPlot);
  void setupSimpleDemo(QCustomPlot *customPlot);
  void setupSincScatterDemo(QCustomPlot *customPlot);
  void setupScatterStyleDemo(QCustomPlot *customPlot);
  void setupLineStyleDemo(QCustomPlot *customPlot);
  void setupScatterPixmapDemo(QCustomPlot *customPlot);

  void setupPlayground(QCustomPlot *customPlot);

private slots:
  void realtimeDataSlot();
  void bracketDataSlot();
  void screenShot();
  void allScreenShots();

private:
  Ui::MainWindow *ui;
  QString demoName;
  QTimer dataTimer;
  QCPItemTracer *itemDemoPhaseTracer;
  int currentDemoIndex;
};

#endif // MAINWINDOW_H
