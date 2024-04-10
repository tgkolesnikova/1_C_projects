#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMessageBox>
#include <QColorDialog>

#include <QDialog>
#include <QVector>
#include <QTimer>
#include <QtMath>

extern "C" {
#include "s21_smartcalc_v1.h"
}

namespace Ui {
class graphwindow;
}

class graphwindow : public QDialog
{
    Q_OBJECT

public:
    explicit graphwindow(QWidget *parent = nullptr);
    ~graphwindow();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::graphwindow *ui;
    QColor color = "red";
};

#endif // GRAPHWINDOW_H
