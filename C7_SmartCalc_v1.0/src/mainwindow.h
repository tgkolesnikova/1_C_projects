#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphwindow.h"
#include "creditwindow.h"
#include "depositwindow.h"

extern "C" {
#include "s21_smartcalc_v1.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    graphwindow* grphWindow;
    creditwindow* crdWindow;
    depositwindow* dpstWindow;

private slots:
    void btn_digits();
    void btn_operators();
    void btn_mod();
    void btn_unaMinus();
    void btn_functions();
    void on_pushButton_CE_clicked();
    void on_pushButton_C_clicked();
    void on_pushButton_del_clicked();
    void on_pushButton_eq_clicked();
    void on_pushButton_credit_clicked();
    void on_pushButton_deposit_clicked();
    void on_pushButton_graph_clicked();

};
#endif // MAINWINDOW_H
