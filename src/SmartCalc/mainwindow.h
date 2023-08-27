#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "qcustomplot.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "calculation/smart_calc.h"
#include "calculation/stack.h"

#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;

  QVector<double> x, y;

 private slots:
  void add_chars();
  void on_pushButton_clear_clicked();
  void on_pushButton_equal_clicked();
  void on_pushButton_clicked();
  void on_pushButton_delete_clicked();
  void drawPlot(char *input_str);
  void autoset_y_axis(struct node *rpn, double xBegin, double xEnd, double h);
};
#endif  // MAINWINDOW_H
