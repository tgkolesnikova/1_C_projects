#include "graphwindow.h"
#include "ui_graphwindow.h"

graphwindow::graphwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graphwindow)
{
    ui->setupUi(this);
}

graphwindow::~graphwindow()
{
    delete ui;
}

void graphwindow::on_pushButton_2_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Interval error");
    msgBox.setIcon(QMessageBox::Critical);

    int flag = 1;

    double x_start = ui->doubleSpinBox_xStart->value();
    double x_end = ui->doubleSpinBox_xEnd->value();
    if (x_end < x_start) {
        msgBox.setText("X: Left border greater than right");
        msgBox.exec();
        flag = 0;
    }

    double y_start = ui->doubleSpinBox_yStart->value();
    double y_end = ui->doubleSpinBox_yEnd->value();
    if (y_end < y_start) {
        msgBox.setText("Y: Left border greater than right");
        msgBox.exec();
        flag = 0;
    }

    if (flag) {
        int count = 100000;
        QVector<double> x, y;

        double step = (x_end - x_start) / count;

        ui->widget->clearGraphs();
        x.clear();
        y.clear();

        ui->widget->setInteraction(QCP::iRangeZoom, true);
        ui->widget->setInteraction(QCP::iRangeDrag, true);
        ui->widget->xAxis->setRange(x_start, x_end);
        ui->widget->yAxis->setRange(y_start, y_end);
        ui->widget->xAxis->setLabel("x");
        ui->widget->yAxis->setLabel("F(x)");

        QString text = ui->lineEdit_2->text();
        QByteArray binary_text = text.toLocal8Bit();
        char* text_for_c = binary_text.data();

        double X = x_start, Y;
        for (int i = 0; i < count; ++i)
        {
            Y = X;
            smart_calc(text_for_c, &Y);
            x.push_back(X);
            if (!isnan(Y) && y_start <= Y && Y <= y_end) {
                y.push_back(Y);
            } else {
                y.push_back(qQNaN());
            }
            X += step;
        }
        QPen pen;
        pen.setColor(this->color);
        pen.setWidth(2);

        ui->widget->addGraph();
        ui->widget->graph(0)->setData(x, y);
        ui->widget->graph(0)->setPen(pen);

        ui->widget->replot();
    }
}

void graphwindow::on_pushButton_clicked()
{
    QColor clr = QColorDialog::getColor(Qt::red, this);
    if (clr.isValid())
    {
        this->color = clr;
    }
}

