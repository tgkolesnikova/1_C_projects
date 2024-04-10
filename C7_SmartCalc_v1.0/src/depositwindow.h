#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QMainWindow>

namespace Ui {
class depositwindow;
}

class depositwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit depositwindow(QWidget *parent = nullptr);
    ~depositwindow();
    int get_periodicity(int period);
    double get_periodicly_percent(int period, int months, double percent);

private slots:
    void on_pushButton_calculate_clicked();
    void on_checkBox_2_clicked();
    void on_checkBox_3_clicked();

private:
    Ui::depositwindow *ui;
};

#endif // DEPOSITWINDOW_H
