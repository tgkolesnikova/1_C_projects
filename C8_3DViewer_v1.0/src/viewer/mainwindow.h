#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGifImage/gifimage/qgifimage.h>
#include <glwidget.h>

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QRegularExpressionValidator>
#include <QSettings>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_openFile_clicked();
  void on_rotate_scroll_bar_x_valueChanged(int value);
  void on_rotate_scroll_bar_y_valueChanged(int value);
  void on_rotate_scroll_bar_z_valueChanged(int value);
  void on_zoom_slider_valueChanged(int value);
  void on_radioButton_central_projection_toggled(bool checked);
  void on_radioButton_parallel_projection_toggled(bool checked);
  void on_pushButton_set_bg_color_clicked();
  void on_pushButton_set_edges_color_clicked();
  void on_pushButton_set_nodes_color_clicked();
  void on_nodes_size_spinbox_valueChanged(int arg1);
  void on_edges_width_spinBox_valueChanged(int arg1);
  void on_edges_solid_radioButton_toggled(bool checked);
  void on_edges_dashed_radioButton_toggled(bool checked);
  void on_sizeNodes_radioButton_none_toggled(bool checked);
  void on_sizeNodes_radioButton_square_toggled(bool checked);
  void on_sizeNodes_radioButton_circle_toggled(bool checked);
  void on_move_scroll_bar_x_valueChanged(int value);
  void on_move_scroll_bar_y_valueChanged(int value);
  void on_move_scroll_bar_z_valueChanged(int value);
  void on_pushButton_screenshot_clicked();
  void on_pushButton_screencast_clicked();
  void make_gif();
  void on_input_zoom_value_textEdited(const QString &arg1);
  void on_input_rotate_value_x_textEdited(const QString &arg1);
  void on_input_rotate_value_y_textEdited(const QString &arg1);
  void on_input_rotate_value_z_textEdited(const QString &arg1);
  void on_pushButton_reset_clicked();
  void on_input_move_value_x_textEdited(const QString &arg1);
  void on_input_move_value_y_textEdited(const QString &arg1);
  void on_input_move_value_z_textEdited(const QString &arg1);

 private:
  Ui::MainWindow *ui;
  QRegularExpressionValidator *validator_zoom;
  QRegularExpressionValidator *validator_rotate;
  QRegularExpressionValidator *validator_move;
  QSettings *settings;
  QTimer *timer;
  QGifImage *gif_frame = nullptr;
  QString gif_name;
  int frames_counter = 0;
  void set_validators();
  void reset_options();
  void read_settings();
  void write_settings();
  void print_status(int err);
  void enable_pult(bool sw);
  bool f_print = true;
};
#endif  // MAINWINDOW_H
