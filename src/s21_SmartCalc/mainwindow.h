#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "qcustomplot.h"

extern "C" {
#include "../calc.h"
}

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
  QCustomPlot *customPlot;
  int flag_plot = 0;

 private slots:
  void digits_numbers();
  void on_pushButton_AC_clicked();
  void on_pushButton_Eq_clicked();
  void on_pushButton_Undo_clicked();
  void plot_func();
  void on_pushButton_cred_clicked();
  void on_pushButton_depos_clicked();
};
#endif  // MAINWINDOW_H
