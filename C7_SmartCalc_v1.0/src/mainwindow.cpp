#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "s21_smartcalc_v1.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(clicked(bool)), this, SLOT(btn_digits()));
    connect(ui->pushButton_1, SIGNAL(clicked(bool)), this, SLOT(btn_digits()));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(btn_digits()));
    connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(btn_digits()));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(btn_digits()));
    connect(ui->pushButton_5, SIGNAL(clicked(bool)), this, SLOT(btn_digits()));
    connect(ui->pushButton_6, SIGNAL(clicked(bool)), this, SLOT(btn_digits()));
    connect(ui->pushButton_7, SIGNAL(clicked(bool)), this, SLOT(btn_digits()));
    connect(ui->pushButton_8, SIGNAL(clicked(bool)), this, SLOT(btn_digits()));
    connect(ui->pushButton_9, SIGNAL(clicked(bool)), this, SLOT(btn_digits()));
    connect(ui->pushButton_x, SIGNAL(clicked(bool)), this, SLOT(btn_digits()));
    connect(ui->pushButton_brOpen, SIGNAL(clicked(bool)), this, SLOT(btn_digits()));
    connect(ui->pushButton_brClose, SIGNAL(clicked(bool)), this, SLOT(btn_digits()));

    connect(ui->pushButton_dot, SIGNAL(clicked(bool)), this, SLOT(btn_operators()));
    connect(ui->pushButton_pow, SIGNAL(clicked(bool)), this, SLOT(btn_operators()));
    connect(ui->pushButton_div, SIGNAL(clicked(bool)), this, SLOT(btn_operators()));
    connect(ui->pushButton_mult, SIGNAL(clicked(bool)), this, SLOT(btn_operators()));
    connect(ui->pushButton_minus, SIGNAL(clicked(bool)), this, SLOT(btn_operators()));
    connect(ui->pushButton_plus, SIGNAL(clicked(bool)), this, SLOT(btn_operators()));

    connect(ui->pushButton_mod, SIGNAL(clicked(bool)), this, SLOT(btn_mod()));
    connect(ui->pushButton_unaMinus, SIGNAL(clicked(bool)), this, SLOT(btn_unaMinus()));

    connect(ui->pushButton_sqrt, SIGNAL(clicked(bool)), this, SLOT(btn_functions()));
    connect(ui->pushButton_asin, SIGNAL(clicked(bool)), this, SLOT(btn_functions()));
    connect(ui->pushButton_sin, SIGNAL(clicked(bool)), this, SLOT(btn_functions()));
    connect(ui->pushButton_acos, SIGNAL(clicked(bool)), this, SLOT(btn_functions()));
    connect(ui->pushButton_cos, SIGNAL(clicked(bool)), this, SLOT(btn_functions()));
    connect(ui->pushButton_atan, SIGNAL(clicked(bool)), this, SLOT(btn_functions()));
    connect(ui->pushButton_tan, SIGNAL(clicked(bool)), this, SLOT(btn_functions()));
    connect(ui->pushButton_ln, SIGNAL(clicked(bool)), this, SLOT(btn_functions()));
    connect(ui->pushButton_log, SIGNAL(clicked(bool)), this, SLOT(btn_functions()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btn_digits()
{
    QPushButton* btn = (QPushButton*)sender();
    QString text;
    if (ui->label_1->text() == '0') {
        text = btn->text();
    } else {
        text = ui->label_1->text() + btn->text();
    }
    ui->label_1->setText(text);
}

void MainWindow::btn_operators()
{
    QPushButton* btn = (QPushButton*)sender();
    QString text = ui->label_1->text() + btn->text();
    ui->label_1->setText(text);
}

void MainWindow::btn_mod()
{
    QString text = ui->label_1->text() + " mod ";
    ui->label_1->setText(text);
}

void MainWindow::btn_unaMinus()
{
    QString text;
    if (ui->label_1->text() == '0') {
        text = "(-";
    } else {
        text = ui->label_1->text() + "(-";
    }
    ui->label_1->setText(text);
}

void MainWindow::btn_functions()
{
    QPushButton* btn = (QPushButton*)sender();
    QString text;
    if (ui->label_1->text() == '0') {
        text = btn->text() + "(";
    } else {
        text = ui->label_1->text() + btn->text() + "(";
    }
    ui->label_1->setText(text);
}

void MainWindow::on_pushButton_CE_clicked()
{
    ui->label_1->setText("0");  // Clear Entry (стереть введённое)
}

void MainWindow::on_pushButton_C_clicked()
{
    ui->label_1->setText("0"); // Clear [all]
    ui->label_2->setText("0");
}

void MainWindow::on_pushButton_del_clicked()
{
    QString text = ui->label_1->text();
    if (text != "0") {
        text.chop(1);
        if (text == "") {
            text = "0";
        }
        ui->label_1->setText(text);
    }
}

void MainWindow::on_pushButton_eq_clicked()
{
    QString text = ui->label_1->text();
    if (text != "0" && text != "") {
        QByteArray binary_text = text.toLocal8Bit();
        char* text_for_c = binary_text.data();
        double result = ui->lineEdit->text().toDouble();
        int err = smart_calc(text_for_c, &result);
        if (!err) {
            ui->label_2->setNum(result);
        } else {
            QString msg = "";
            if (err == 9) msg = "Wrong number of brackets";
            if (err == 8) msg = "Invalid expression";
            if (err == 7) msg = "Function entry error";
            if (err == 6) msg = "Empty brackets or argument";
            ui->label_2->setText(msg);
        }
    }
}

void MainWindow::on_pushButton_credit_clicked()
{
    crdWindow = new creditwindow(this);
    crdWindow->show();
}

void MainWindow::on_pushButton_deposit_clicked()
{
    dpstWindow = new depositwindow(this);
    dpstWindow->show();
}

void MainWindow::on_pushButton_graph_clicked()
{
    grphWindow = new graphwindow(this);
    grphWindow->show();
}



