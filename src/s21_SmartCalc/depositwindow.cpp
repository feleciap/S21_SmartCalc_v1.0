#include "depositwindow.h"

#include "ui_depositwindow.h"

depositwindow::depositwindow(QWidget* parent)
    : QDialog(parent), ui(new Ui::depositwindow) {
  ui->setupUi(this);
}

depositwindow::~depositwindow() { delete ui; }

void depositwindow::on_Depos_pushButton_clicked() {
  QDate dateToday = QDate::currentDate();
  ui->tableWidget->clear();
  double deposit_amount = ui->line_deposit_amount->text().toDouble();
  double percent = ui->line_percent->text().toDouble();
  double period = ui->line_period->text().toDouble();
  double tax_rate = ui->line_tax_rate->text().toDouble();
  int capitalization = 0;
  int payment_periodicity = ui->payment_periodicity->currentIndex();
  ;  // 0-день, 1-неделя, 2-месяц, 3-квартал, 4-год, 5-в конце
  double accured_interest = 0;
  double tax_amount = 0;
  char temp_str[1000] = {0};
  Node_table* table = NULL;
  Node_up_down* up_down = NULL;
  Node_up_down* withdrawal = NULL;
  Node_date* N_payment_date = NULL;
  int index = ui->comboBox_period->currentIndex();
  int table_row = 0;
  //    changeIndex(ui->comboBox_period->currentIndexChanged());
  on_comboBox_period_activated(index, &period);
  if (period > 18263) {
    period = 18263;
    ui->line_period->setText("50");
    ui->comboBox_period->setCurrentIndex(2);
  }
  pay_date_func(&N_payment_date, period, payment_periodicity, &table_row);
  QStringList headers;
  headers << "дата"
          << "начисленные %"
          << "изменение баланса"
          << "выплата"
          << "остаток";
  ui->tableWidget->setRowCount(table_row);
  ui->tableWidget->setColumnCount(5);
  ui->tableWidget->setHorizontalHeaderLabels(headers);
  if (ui->capitalization->isChecked()) capitalization = 1;
  topUp_func(&up_down, dateToday);
  withdrawal_func(&withdrawal, dateToday);
  deposit_calc(&deposit_amount, percent, period, tax_rate, capitalization,
               &up_down, &withdrawal, &accured_interest, &tax_amount, &table,
               &N_payment_date);
  sprintf(temp_str, "%.2lf", accured_interest);
  ui->accured_interest->setText(temp_str);
  sprintf(temp_str, "%.2lf", deposit_amount);
  ui->deposit_amount_end->setText(temp_str);
  sprintf(temp_str, "%.2lf", tax_amount);
  ui->tax_amount->setText(temp_str);
  depos_table_func(table);
}

int depositwindow::pay_date_func(Node_date** pay_date, double period,
                                 int payment_periodicity, int* table_row) {
  int date = 0;
  QDate dateToday = QDate::currentDate();
  if (payment_periodicity == 0) {
    while (date <= period) {
      date++;
      push_date(pay_date, date);
      *table_row = *table_row + 1;
    }
  } else if (payment_periodicity == 1) {
    date = date + 7;
    while (date <= period) {
      push_date(pay_date, date);
      date = date + 7;
      *table_row = *table_row + 1;
    }
    int lost = (int)period % 7;
    if (lost) {
      push_date(pay_date, period);
      *table_row = *table_row + 1;
    }
  } else if (payment_periodicity == 2) {
    QDate topDate = dateToday.addMonths(1);
    date = date + dateToday.daysTo(topDate);
    int lost = (int)period;
    while (date <= period) {
      push_date(pay_date, date);
      QDate tempDate = topDate.addMonths(1);
      date = date + topDate.daysTo(tempDate);
      lost = lost - topDate.daysTo(tempDate);
      topDate = tempDate;
      *table_row = *table_row + 1;
    }
    if (lost) {
      push_date(pay_date, period);
      *table_row = *table_row + 1;
    }
  } else if (payment_periodicity == 3) {
    QDate topDate = dateToday.addMonths(3);
    int lost = (int)period;
    date = date + dateToday.daysTo(topDate);
    while (date <= period) {
      push_date(pay_date, date);
      QDate tempDate = topDate.addMonths(3);
      date = date + topDate.daysTo(tempDate);
      lost = lost - topDate.daysTo(tempDate);
      topDate = tempDate;
      *table_row = *table_row + 1;
    }
    if (lost) {
      push_date(pay_date, period);
      *table_row = *table_row + 1;
    }
  } else if (payment_periodicity == 4) {
    QDate topDate = dateToday.addYears(1);
    int lost = (int)period;
    date = date + dateToday.daysTo(topDate);
    while (date <= period) {
      push_date(pay_date, date);
      QDate tempDate = topDate.addYears(1);
      date = date + topDate.daysTo(tempDate);
      lost = lost - topDate.daysTo(tempDate);
      topDate = tempDate;
      *table_row = *table_row + 1;
    }
    if (lost) {
      push_date(pay_date, period);
      *table_row = *table_row + 1;
    }
  } else if (payment_periodicity == 5) {
    push_date(pay_date, period);
    *table_row = *table_row + 1;
  }
  return 0;
}

int depositwindow::withdrawal_func(Node_up_down** withdrawal, QDate dateToday) {
  QDate topControl;
  if (ui->down_checkBox_1->isChecked()) {
    QDate topDate = ui->down_dateEdit_1->date();
    if (topDate > dateToday) {
      topControl = topDate;
      double topUp = ui->down_1->text().toDouble();
      int d = dateToday.daysTo(topDate);
      push_up_down(withdrawal, topUp, d, 0);
    }
  }
  if (ui->down_checkBox_2->isChecked()) {
    QDate topDate = ui->down_dateEdit_2->date();
    if (topDate > topControl) {
      topControl = topDate;
      double topUp = ui->down_2->text().toDouble();
      int d = dateToday.daysTo(topDate);
      push_up_down(withdrawal, topUp, d, 0);
    }
  }
  if (ui->down_checkBox_3->isChecked()) {
    QDate topDate = ui->down_dateEdit_3->date();
    if (topDate > topControl) {
      topControl = topDate;
      double topUp = ui->down_3->text().toDouble();
      int d = dateToday.daysTo(topDate);
      push_up_down(withdrawal, topUp, d, 0);
    }
  }
  if (ui->down_checkBox_4->isChecked()) {
    QDate topDate = ui->down_dateEdit_4->date();
    if (topDate > topControl) {
      topControl = topDate;
      double topUp = ui->down_4->text().toDouble();
      int d = dateToday.daysTo(topDate);
      push_up_down(withdrawal, topUp, d, 0);
    }
  }
  if (ui->down_checkBox_5->isChecked()) {
    QDate topDate = ui->down_dateEdit_5->date();
    if (topDate > topControl) {
      topControl = topDate;
      double topUp = ui->down_5->text().toDouble();
      int d = dateToday.daysTo(topDate);
      push_up_down(withdrawal, topUp, d, 0);
    }
  }
  return 0;
}

int depositwindow::topUp_func(Node_up_down** up_down, QDate dateToday) {
  QDate topControl;
  if (ui->top_checkBox_1->isChecked()) {
    QDate topDate = ui->top_dateEdit_1->date();
    if (topDate > dateToday) {
      topControl = topDate;
      double topUp = ui->top_1->text().toDouble();
      int d = dateToday.daysTo(topDate);
      push_up_down(up_down, topUp, d, 1);
    }
  }
  if (ui->top_checkBox_2->isChecked()) {
    QDate topDate = ui->top_dateEdit_2->date();
    if (topDate > topControl) {
      topControl = topDate;
      double topUp = ui->top_2->text().toDouble();
      int d = dateToday.daysTo(topDate);
      push_up_down(up_down, topUp, d, 1);
    }
  }
  if (ui->top_checkBox_3->isChecked()) {
    QDate topDate = ui->top_dateEdit_3->date();
    if (topDate > topControl) {
      topControl = topDate;
      double topUp = ui->top_3->text().toDouble();
      int d = dateToday.daysTo(topDate);
      push_up_down(up_down, topUp, d, 1);
    }
  }
  if (ui->top_checkBox_4->isChecked()) {
    QDate topDate = ui->top_dateEdit_4->date();
    if (topDate > topControl) {
      topControl = topDate;
      double topUp = ui->top_4->text().toDouble();
      int d = dateToday.daysTo(topDate);
      push_up_down(up_down, topUp, d, 1);
    }
  }
  if (ui->top_checkBox_5->isChecked()) {
    QDate topDate = ui->top_dateEdit_5->date();
    if (topDate > topControl) {
      topControl = topDate;
      double topUp = ui->top_5->text().toDouble();
      int d = dateToday.daysTo(topDate);
      push_up_down(up_down, topUp, d, 1);
    }
  }
  return 0;
}

void depositwindow::depos_table_func(Node_table* table) {
  double temp_amount = 0, add_percent = 0, balance_change = 0, payment = 0;
  int date = 0;
  int rows = 0;
  QDate dateToday = QDate::currentDate();
  char temp_str[1000] = {0};
  while (table != NULL) {
    print_table(&table, &date, &add_percent, &balance_change, &payment,
                &temp_amount);
    QDate date_table = dateToday.addDays(date);
    QString str_date = date_table.toString("dd/MM/yyyy");
    QTableWidgetItem* item1 = new QTableWidgetItem(str_date);
    ui->tableWidget->setItem(rows, 0, item1);
    sprintf(temp_str, "%.2lf", (add_percent));
    QTableWidgetItem* item2 = new QTableWidgetItem(QString(temp_str));
    ui->tableWidget->setItem(rows, 1, item2);
    sprintf(temp_str, "%.2lf", balance_change);
    QTableWidgetItem* item3 = new QTableWidgetItem(QString(temp_str));
    ui->tableWidget->setItem(rows, 2, item3);
    sprintf(temp_str, "%.2lf", payment);
    QTableWidgetItem* item4 = new QTableWidgetItem(QString(temp_str));
    ui->tableWidget->setItem(rows, 3, item4);
    sprintf(temp_str, "%.2lf", temp_amount);
    QTableWidgetItem* item5 = new QTableWidgetItem(QString(temp_str));
    ui->tableWidget->setItem(rows, 4, item5);
    rows++;
  }
}

void depositwindow::on_comboBox_period_activated(int index, double* period) {
  QDate dateToday = QDate::currentDate();
  if (index == 0) {
    QDate tempDate = dateToday.addDays(*period);
    *period = dateToday.daysTo(tempDate);
  } else if (index == 1) {
    QDate tempDate = dateToday.addMonths(*period);
    *period = dateToday.daysTo(tempDate);
  } else if (index == 2) {
    QDate tempDate = dateToday.addYears(*period);
    *period = dateToday.daysTo(tempDate);
  }
}
