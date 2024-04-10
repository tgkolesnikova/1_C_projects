#include "depositwindow.h"
#include "ui_depositwindow.h"

depositwindow::depositwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::depositwindow)
{
    ui->setupUi(this);
}

depositwindow::~depositwindow()
{
    delete ui;
}

void depositwindow::on_pushButton_calculate_clicked()
{
    double payment = ui->lineEdit_credit->text().toDouble();
    double months = ui->spinBox_duration->text().toDouble();
    double percent = ui->spinBox_percent->text().toDouble() / 100.;
    double tax_rate = ui->spinBox_percent_3->text().toDouble() / 100.;

    int capitalize = ui->checkBox->isChecked();
    int period = ui->comboBox->currentIndex();
    int periodicity = get_periodicity(period);
    double periodicly_percent = get_periodicly_percent(period, months, percent);

    double fee_period = 1;
    double fee_payment = 0;
    if (ui->checkBox_2->isChecked()) {
        fee_period = ui->comboBox_2->currentIndex();
        fee_payment = ui->lineEdit_credit_2->text().toDouble();
    }
    int fee_periodicity = get_periodicity(fee_period);

    double drop_period = 1;
    double drop_amount = 0;
    if (ui->checkBox_3->isChecked()) {
        drop_period = ui->comboBox_3->currentIndex();
        drop_amount = ui->lineEdit_credit_3->text().toDouble();
    }
    int drop_periodicity = get_periodicity(drop_period);


    double amount = payment;
    double profit_for_period = 0;
    double profit = 0;

    if (period == 0) {
        int fee_periods_count = months / fee_periodicity;
        int drop_periods_count = months / drop_periodicity;
        amount = payment + fee_payment * fee_periods_count - drop_amount * drop_periods_count;
        profit = amount * periodicly_percent;
    } else {
        for (int i = 0; i < months; i++) {
            if ((i + 1) % periodicity == 0) {       // пора начислять проценты
                profit_for_period = amount * periodicly_percent;
                profit += profit_for_period;
                if (capitalize) {
                    amount += profit_for_period;
                };
            }
            if (ui->checkBox_2->isChecked() &&
                (i + 1) % fee_periodicity == 0) {   // пополнение
                amount += fee_payment;
            }
            if (ui->checkBox_3->isChecked() &&
                (i + 1) % drop_periodicity == 0) {  // частичное снятие
                amount -= drop_amount;
            }
        }
    }

    double CB_key_rate_2023 = 7.5 / 100.;
    double no_tax_amount = 1000000 * CB_key_rate_2023;

    double tax_amount = 0;
    if (profit > no_tax_amount) {
        tax_amount = (profit - no_tax_amount) * tax_rate;
    };

    ui->label_over->setNum(amount);
    ui->label_first->setNum(profit);
    ui->label_total->setNum(tax_amount);
}

void depositwindow::on_checkBox_2_clicked()
{
    ui->label_7->setEnabled(ui->checkBox_2->isChecked());
    ui->label_10->setEnabled(ui->checkBox_2->isChecked());
    ui->comboBox_2->setEnabled(ui->checkBox_2->isChecked());
    ui->lineEdit_credit_2->setEnabled(ui->checkBox_2->isChecked());
}

void depositwindow::on_checkBox_3_clicked()
{
    ui->label_11->setEnabled(ui->checkBox_3->isChecked());
    ui->label_12->setEnabled(ui->checkBox_3->isChecked());
    ui->comboBox_3->setEnabled(ui->checkBox_3->isChecked());
    ui->lineEdit_credit_3->setEnabled(ui->checkBox_3->isChecked());
}

int depositwindow::get_periodicity(int period) {
    int per[] = {1, 1, 3, 6, 12};
    return per[period];
}

double depositwindow::get_periodicly_percent(int period, int months, double percent) {
    double result = percent / 12. * months;  // "if (period == 0)"
    if (period == 1) result = percent / 12.;
    if (period == 2) result = percent / 12. * 3;
    if (period == 3) result = percent / 12. * 6;
    if (period == 4) result = percent;
    return result;
}
