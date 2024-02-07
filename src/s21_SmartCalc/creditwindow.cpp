#include "creditwindow.h"

#include "ui_creditwindow.h"

Creditwindow::Creditwindow(QWidget* parent)
    : QDialog(parent), ui(new Ui::Creditwindow) {
  ui->setupUi(this);
}

Creditwindow::~Creditwindow() { delete ui; }

void Creditwindow::on_result_Button_clicked() {
  ui->tableWidget->clear();
  double cr_percent = ui->credit_percent->text().toDouble();
  double cr_period = ui->credit_period->text().toDouble();
  if (cr_period > 300) {
    cr_period = 300;
    ui->credit_period->setText("300");
  }
  double cr_sum = ui->credit_sum->text().toDouble();
  double mount_p, overp, total_p;
  double mount_p_min = 0, mount_p_max = 0;
  char temp_str[1000] = {0};
  Node_Dif* dif_m_p = NULL;
  QStringList headers;
  headers << "месяц"
          << "сумма платежа"
          << "осн. долг"
          << "проценты"
          << "остаток";
  ui->tableWidget->setRowCount(cr_period);
  ui->tableWidget->setColumnCount(5);
  ui->tableWidget->setHorizontalHeaderLabels(headers);
  if (ui->annuitent->isChecked()) {
    annuitant_credit_calc(&dif_m_p, cr_sum, cr_percent, cr_period, &mount_p,
                          &overp, &total_p);
    sprintf(temp_str, "%.2lf", mount_p);
    ui->mounth_payment->setText(temp_str);
    sprintf(temp_str, "%.2lf", overp);
    ui->overpayment->setText(temp_str);
    sprintf(temp_str, "%.2lf", total_p);
    ui->total_payment->setText(temp_str);
    table_func(dif_m_p, &mount_p_max, &mount_p_min);
  }
  if (ui->different->isChecked()) {
    differential_credit_calc(cr_sum, cr_percent, cr_period, &dif_m_p, &overp,
                             &total_p);
    sprintf(temp_str, "%.2lf", overp);
    ui->overpayment->setText(temp_str);
    sprintf(temp_str, "%.2lf", total_p);
    ui->total_payment->setText(temp_str);
    table_func(dif_m_p, &mount_p_max, &mount_p_min);
    sprintf(temp_str, "от %.2lf до %.2lf ", mount_p_min, mount_p_max);
    ui->mounth_payment->setText(temp_str);
  }
}

void Creditwindow::table_func(Node_Dif* dif_m_p, double* mount_p_max,
                              double* mount_p_min) {
  double temp_amount = 0, base_m_p = 0, temp_over = 0;
  int month = 0;
  char temp_str[1000] = {0};
  while (dif_m_p != NULL) {
    dmp(&dif_m_p, &temp_over, &base_m_p, &temp_amount, &month);
    if (month == 1) *mount_p_max = base_m_p + temp_over;
    QTableWidgetItem* item1 = new QTableWidgetItem(QString::number(month));
    ui->tableWidget->setItem(month - 1, 0, item1);
    sprintf(temp_str, "%.2lf", (base_m_p + temp_over));
    QTableWidgetItem* item2 = new QTableWidgetItem(QString(temp_str));
    ui->tableWidget->setItem(month - 1, 1, item2);
    sprintf(temp_str, "%.2lf", base_m_p);
    QTableWidgetItem* item3 = new QTableWidgetItem(QString(temp_str));
    ui->tableWidget->setItem(month - 1, 2, item3);
    sprintf(temp_str, "%.2lf", temp_over);
    QTableWidgetItem* item4 = new QTableWidgetItem(QString(temp_str));
    ui->tableWidget->setItem(month - 1, 3, item4);
    sprintf(temp_str, "%.2lf", temp_amount);
    QTableWidgetItem* item5 = new QTableWidgetItem(QString(temp_str));
    ui->tableWidget->setItem(month - 1, 4, item5);
    *mount_p_min = base_m_p + temp_over;
  }
}
