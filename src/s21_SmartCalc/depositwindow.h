#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QDate>
#include <QDialog>
#include <QTableWidget>

extern "C" {
#include "../calc.h"
}

namespace Ui {
class depositwindow;
}

class depositwindow : public QDialog {
  Q_OBJECT

 public:
  explicit depositwindow(QWidget* parent = nullptr);
  ~depositwindow();

 private slots:
  void on_Depos_pushButton_clicked();
  void on_comboBox_period_activated(int index, double* period);

 private:
  Ui::depositwindow* ui;
  void depos_table_func(Node_table* table);
  int topUp_func(Node_up_down** up_down, QDate dateToday);
  int withdrawal_func(Node_up_down** withdrawal, QDate dateToday);
  int pay_date_func(Node_date** pay_date, double period,
                    int payment_periodicity, int* table_row);
};

#endif  // DEPOSITWINDOW_H
