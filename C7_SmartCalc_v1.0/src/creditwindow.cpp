#include "creditwindow.h"
#include "ui_creditwindow.h"

creditwindow::creditwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creditwindow)
{
    ui->setupUi(this);
}

creditwindow::~creditwindow()
{
    delete ui;
}

void creditwindow::on_pushButton_calculate_clicked()
{
    double amount = ui->lineEdit_credit->text().toDouble();
    double percent = ui->spinBox_percent->text().toDouble();
    double months = ui->spinBox_duration->text().toDouble();
    double rate = percent / (100 * 12);

    double payment = 0;
    double total = 0;
    double overpay = amount;
    if (!ui->comboBox->currentIndex()) {  // аннуитентный
        double tmp = pow((1 + rate), months);
        payment = amount * (rate * tmp) / (tmp - 1);
        total = payment * months;
        overpay = fabs(overpay - total);
        ui->label_first->setNum(payment);
        ui->label_last->setNum(payment);
        ui->label_over->setNum(overpay);
        ui->label_total->setNum(total);
    } else {  // дифференцированный платеж
        ui->tableWidget->setColumnCount(4);
        ui->tableWidget->setRowCount(months);

        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Payment" << "Main Credit" << "Percent" << "Balance");
        for (int i = 0; i < 4; i++) {
            ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        }

        QTableWidgetItem *item;

        double part = amount / months;
        for (int i = 0; i < (int)months; i++) {
            double coeff = amount * rate;
            payment = part + coeff;
            amount -= part;
            total += payment;
            item = new QTableWidgetItem(QString::number(payment, 'l', 2));
            ui->tableWidget->setItem(i, 0, item);
            item = new QTableWidgetItem(QString::number(part, 'l', 2));
            ui->tableWidget->setItem(i, 1, item);
            item = new QTableWidgetItem(QString::number(coeff, 'l', 2));
            ui->tableWidget->setItem(i, 2, item);
            item = new QTableWidgetItem(QString::number(amount, 'l', 2));
            ui->tableWidget->setItem(i, 3, item);
        }

        ui->label_first->setNum(overpay * rate + part);
        ui->label_last->setNum(part * (rate + 1));
        ui->label_total->setNum(total);
        overpay = fabs(overpay - total);
        ui->label_over->setNum(overpay);
    }
}

