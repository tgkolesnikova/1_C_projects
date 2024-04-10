#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setlocale(LC_NUMERIC, "C");
  set_validators();
  settings = new QSettings("21school", "3DViewer1", this);
  read_settings();
  timer = new QTimer(0);
  connect(timer, SIGNAL(timeout()), this, SLOT(make_gif()));
  enable_pult(false);
}

MainWindow::~MainWindow() {
  write_settings();
  delete settings;
  delete validator_move;
  delete validator_rotate;
  delete validator_zoom;
  delete timer;
  delete gif_frame;
  delete ui;
}

void MainWindow::enable_pult(bool sw) {
  ui->zoom_slider->setEnabled(sw);
  ui->rotate_scroll_bar_x->setEnabled(sw);
  ui->rotate_scroll_bar_y->setEnabled(sw);
  ui->rotate_scroll_bar_z->setEnabled(sw);
  ui->move_scroll_bar_x->setEnabled(sw);
  ui->move_scroll_bar_y->setEnabled(sw);
  ui->move_scroll_bar_z->setEnabled(sw);

  ui->input_zoom_value->setEnabled(sw);
  ui->input_rotate_value_x->setEnabled(sw);
  ui->input_rotate_value_y->setEnabled(sw);
  ui->input_rotate_value_z->setEnabled(sw);
  ui->input_move_value_x->setEnabled(sw);
  ui->input_move_value_y->setEnabled(sw);
  ui->input_move_value_z->setEnabled(sw);

  ui->pushButton_reset->setEnabled(sw);
  ui->pushButton_screenshot->setEnabled(sw);
  ui->pushButton_screencast->setEnabled(sw);
}

void MainWindow::set_validators() {
  validator_zoom = new QRegularExpressionValidator(
      QRegularExpression("^([1-9]\\d?|1\\d{2}|200)$"), 0);
  validator_rotate = new QRegularExpressionValidator(
      QRegularExpression("^[+-]?([1-9]\\d?|1[0-7]\\d{1}|180|0)$"), 0);
  validator_move = new QRegularExpressionValidator(
      QRegularExpression("^[+-]?([01]\\.\\d{2}|2\\.00)$"), 0);

  ui->input_zoom_value->setValidator(validator_zoom);

  ui->input_rotate_value_x->setValidator(validator_rotate);
  ui->input_rotate_value_y->setValidator(validator_rotate);
  ui->input_rotate_value_z->setValidator(validator_rotate);

  ui->input_move_value_x->setValidator(validator_move);
  ui->input_move_value_y->setValidator(validator_move);
  ui->input_move_value_z->setValidator(validator_move);
}

void MainWindow::read_settings() {
  int projection_type = settings->value("projection_type", 0).toInt();
  if (projection_type)
    ui->radioButton_central_projection->setChecked(true);
  else
    ui->radioButton_parallel_projection->setChecked(true);

  int edges_type = settings->value("edges_type", 0).toInt();
  if (edges_type)
    ui->edges_dashed_radioButton->setChecked(true);
  else
    ui->edges_solid_radioButton->setChecked(true);
  ui->gl_widget->edges_red = settings->value("edges_red", 1).toDouble();
  ui->gl_widget->edges_green = settings->value("edges_green", 1).toDouble();
  ui->gl_widget->edges_blue = settings->value("edges_blue", 1).toDouble();
  ui->edges_width_spinBox->setValue(settings->value("edges_size", 1).toInt());

  int nodes_type = settings->value("nodes_type", 1).toInt();
  if (!nodes_type) {
    ui->sizeNodes_radioButton_none->setChecked(true);
  } else if (nodes_type == NODES_SQUARE) {
    ui->sizeNodes_radioButton_square->setChecked(true);
  } else {
    ui->sizeNodes_radioButton_circle->setChecked(true);
  }
  ui->gl_widget->nodes_red = settings->value("nodes_red", 1).toDouble();
  ui->gl_widget->nodes_green = settings->value("nodes_green", 1).toDouble();
  ui->gl_widget->nodes_blue = settings->value("nodes_blue", 1).toDouble();
  ui->nodes_size_spinbox->setValue(settings->value("nodes_size", 1).toInt());

  ui->gl_widget->bg_red = settings->value("bg_red", 0).toDouble();
  ui->gl_widget->bg_green = settings->value("bg_green", 0).toDouble();
  ui->gl_widget->bg_blue = settings->value("bg_blue", 1).toDouble();
}

void MainWindow::write_settings() {
  settings->setValue("projection_type", ui->gl_widget->projection_type);

  settings->setValue("edges_red", ui->gl_widget->edges_red);
  settings->setValue("edges_green", ui->gl_widget->edges_green);
  settings->setValue("edges_blue", ui->gl_widget->edges_blue);
  settings->setValue("edges_size", ui->gl_widget->edges_size);
  settings->setValue("edges_type", ui->gl_widget->edges_type);

  settings->setValue("nodes_red", ui->gl_widget->nodes_red);
  settings->setValue("nodes_green", ui->gl_widget->nodes_green);
  settings->setValue("nodes_blue", ui->gl_widget->nodes_blue);
  settings->setValue("nodes_size", ui->gl_widget->nodes_size);
  settings->setValue("nodes_type", ui->gl_widget->nodes_type);

  settings->setValue("bg_red", ui->gl_widget->bg_red);
  settings->setValue("bg_green", ui->gl_widget->bg_green);
  settings->setValue("bg_blue", ui->gl_widget->bg_blue);
}

void MainWindow::reset_options() {
  ui->rotate_scroll_bar_x->setValue(0);
  ui->rotate_scroll_bar_y->setValue(0);
  ui->rotate_scroll_bar_z->setValue(0);
  ui->zoom_slider->setValue(100);

  ui->move_scroll_bar_x->setValue(0);
  ui->move_scroll_bar_y->setValue(0);
  ui->move_scroll_bar_z->setValue(0);
}

void MainWindow::on_pushButton_openFile_clicked() {
  QString file_name = QFileDialog::getOpenFileName(
      this, tr("Open obj files"), "~", tr("Obj Files (*.obj)"));
  if (file_name != "") {
    reset_options();
    ui->gl_widget->file_name = file_name;
    int err = ui->gl_widget->open_file();
    enable_pult(err == 0);
    QString file_name_short = file_name.section("/", -1, -1);
    ui->build_status_pic_label->setText(file_name_short);
    print_status(err);
  }
}

void MainWindow::print_status(int err) {
  if (!err) {
    QString nodes_txt =
        QString::asprintf("Nodes: %d", ui->gl_widget->model->num_V);
    ui->nodes_value_label->setText(nodes_txt);
    int edges_value = 0;
    for (int i = 0; i < ui->gl_widget->model->num_F; i++) {
      edges_value += ui->gl_widget->model->F[i].num_vertices + 1;
    }
    QString edges_txt = QString::asprintf("Edges: %d", edges_value);
    ui->edges_value_label->setText(edges_txt);
    ui->build_status_label->setText("Status: OK");
  } else {
    ui->nodes_value_label->setText("Nodes:");
    ui->edges_value_label->setText("Edges");
    ui->build_status_label->setText(QString::asprintf("Status: Error %d", err));
  }
}

void MainWindow::on_rotate_scroll_bar_x_valueChanged(int value) {
  if (f_print) ui->input_rotate_value_x->setText(QString::number(value));
  f_print = true;
  int angle = value - ui->gl_widget->angle_x;
  ui->gl_widget->angle_x = value;
  rotate_x(ui->gl_widget->model, angle);
  ui->gl_widget->update();
}

void MainWindow::on_input_rotate_value_x_textEdited(const QString &arg1) {
  f_print = false;
  ui->rotate_scroll_bar_x->setValue(arg1.toInt());
}

void MainWindow::on_rotate_scroll_bar_y_valueChanged(int value) {
  if (f_print) ui->input_rotate_value_y->setText(QString::number(value));
  f_print = true;
  int angle = value - ui->gl_widget->angle_y;
  ui->gl_widget->angle_y = value;
  rotate_y(ui->gl_widget->model, angle);
  ui->gl_widget->update();
}

void MainWindow::on_input_rotate_value_y_textEdited(const QString &arg1) {
  f_print = false;
  ui->rotate_scroll_bar_y->setValue(arg1.toInt());
}

void MainWindow::on_rotate_scroll_bar_z_valueChanged(int value) {
  if (f_print) ui->input_rotate_value_z->setText(QString::number(value));
  f_print = true;
  int angle = value - ui->gl_widget->angle_z;
  ui->gl_widget->angle_z = value;
  rotate_z(ui->gl_widget->model, angle);
  ui->gl_widget->update();
}

void MainWindow::on_input_rotate_value_z_textEdited(const QString &arg1) {
  f_print = false;
  ui->rotate_scroll_bar_z->setValue(arg1.toInt());
}

void MainWindow::on_zoom_slider_valueChanged(int value) {
  if (f_print) ui->input_zoom_value->setText(QString::number(value));
  f_print = true;
  double scal = (1 / (ui->gl_widget->zoom / 100.0)) * (value / 100.0);
  if (f_print) ui->gl_widget->zoom = value;
  f_print = true;
  scale(ui->gl_widget->model, scal);
  ui->gl_widget->update();
}

void MainWindow::on_input_zoom_value_textEdited(const QString &arg1) {
  f_print = false;
  ui->zoom_slider->setValue(arg1.toInt());
}

void MainWindow::on_radioButton_central_projection_toggled(bool checked) {
  ui->gl_widget->projection_type = checked;
  ui->gl_widget->update();
}

void MainWindow::on_radioButton_parallel_projection_toggled(bool checked) {
  ui->gl_widget->projection_type = !checked;
  ui->gl_widget->update();
}

void MainWindow::on_pushButton_set_bg_color_clicked() {
  QColor color =
      QColor::fromRgbF(ui->gl_widget->bg_red, ui->gl_widget->bg_green,
                       ui->gl_widget->bg_blue, 1);
  color = QColorDialog::getColor(color, nullptr, "Select background color");
  if (color.isValid()) {
    ui->gl_widget->bg_blue = color.blueF();
    ui->gl_widget->bg_red = color.redF();
    ui->gl_widget->bg_green = color.greenF();
    ui->gl_widget->update();
  }
}

void MainWindow::on_pushButton_set_edges_color_clicked() {
  QColor color =
      QColor::fromRgbF(ui->gl_widget->edges_red, ui->gl_widget->edges_green,
                       ui->gl_widget->edges_blue, 1);
  color = QColorDialog::getColor(color, nullptr, "Select background color");
  if (color.isValid()) {
    ui->gl_widget->edges_blue = color.blueF();
    ui->gl_widget->edges_red = color.redF();
    ui->gl_widget->edges_green = color.greenF();
    ui->gl_widget->update();
  }
}

void MainWindow::on_pushButton_set_nodes_color_clicked() {
  QColor color =
      QColor::fromRgbF(ui->gl_widget->nodes_red, ui->gl_widget->nodes_green,
                       ui->gl_widget->nodes_blue, 1);
  color = QColorDialog::getColor(color, nullptr, "Select background color");
  if (color.isValid()) {
    ui->gl_widget->nodes_blue = color.blueF();
    ui->gl_widget->nodes_red = color.redF();
    ui->gl_widget->nodes_green = color.greenF();
    ui->gl_widget->update();
  }
}

void MainWindow::on_nodes_size_spinbox_valueChanged(int arg1) {
  ui->gl_widget->nodes_size = arg1;
  ui->gl_widget->update();
}

void MainWindow::on_edges_width_spinBox_valueChanged(int arg1) {
  ui->gl_widget->edges_size = arg1;
  ui->gl_widget->update();
}

void MainWindow::on_edges_solid_radioButton_toggled(bool checked) {
  ui->gl_widget->edges_type = !checked;
  ui->gl_widget->update();
}

void MainWindow::on_edges_dashed_radioButton_toggled(bool checked) {
  ui->gl_widget->edges_type = checked;
  ui->gl_widget->update();
}

void MainWindow::on_sizeNodes_radioButton_none_toggled(bool checked) {
  if (checked) {
    ui->gl_widget->nodes_type = NODES_NON;
    ui->gl_widget->update();
  }
}

void MainWindow::on_sizeNodes_radioButton_square_toggled(bool checked) {
  if (checked) {
    ui->gl_widget->nodes_type = NODES_SQUARE;
    ui->gl_widget->update();
  }
}

void MainWindow::on_sizeNodes_radioButton_circle_toggled(bool checked) {
  if (checked) {
    ui->gl_widget->nodes_type = NODES_CIRCLE;
    ui->gl_widget->update();
  }
}

void MainWindow::on_move_scroll_bar_x_valueChanged(int value) {
  double val = value / 100.0, move = val - ui->gl_widget->move_x;
  QString txt = QString::asprintf("%.2f", val);
  if (f_print) ui->input_move_value_x->setText(txt);
  f_print = true;
  ui->gl_widget->move_x = val;
  move_x(ui->gl_widget->model, move);
  ui->gl_widget->update();
}

void MainWindow::on_input_move_value_x_textEdited(const QString &arg1) {
  f_print = false;
  ui->move_scroll_bar_x->setValue(arg1.toDouble() * 100);
}

void MainWindow::on_move_scroll_bar_y_valueChanged(int value) {
  double val = value / 100.0, move = val - ui->gl_widget->move_y;
  QString txt = QString::asprintf("%.2f", val);
  if (f_print) ui->input_move_value_y->setText(txt);
  f_print = true;
  ui->gl_widget->move_y = val;
  move_y(ui->gl_widget->model, move);
  ui->gl_widget->update();
}

void MainWindow::on_input_move_value_y_textEdited(const QString &arg1) {
  f_print = false;
  ui->move_scroll_bar_y->setValue(arg1.toDouble() * 100);
}

void MainWindow::on_move_scroll_bar_z_valueChanged(int value) {
  double val = value / 100.0, move = val - ui->gl_widget->move_z;
  QString txt = QString::asprintf("%.2f", val);
  if (f_print) ui->input_move_value_z->setText(txt);
  f_print = true;
  ui->gl_widget->move_z = val;
  move_z(ui->gl_widget->model, move);
  ui->gl_widget->update();
}

void MainWindow::on_input_move_value_z_textEdited(const QString &arg1) {
  f_print = false;
  ui->move_scroll_bar_z->setValue(arg1.toDouble() * 100);
}

void MainWindow::on_pushButton_screenshot_clicked() {
  if (ui->gl_widget->model->V) {
    QFileDialog dialog_image(this);
    QDateTime date = QDateTime::currentDateTime();
    QString time = date.toString("ddMMyy_hh:mm:ss");
    QString file_name = "screenshot_" + time + ".jpeg";
    file_name = dialog_image.getSaveFileName(
        this, tr("Save a screenshot"), file_name, tr("image (*.jpeg *.bmp)"));
    if (file_name != "") {
      QImage img = ui->gl_widget->grabFramebuffer();
      img.save(file_name, nullptr, 100);
      QMessageBox message_image;
      message_image.information(0, "", "Screenshot saved successfully");
    }
  } else {
    QMessageBox warning = QMessageBox();
    warning.setWindowTitle("Error");
    warning.setText("Please open .obj file to take a screenshot");
    warning.setIcon(QMessageBox::Warning);
    warning.exec();
  }
}

void MainWindow::make_gif() {
  ui->pushButton_screencast->setText(QString::number(frames_counter / 10) +
                                     "s");
  QImage image = ui->gl_widget->grabFramebuffer();
  QSize image_size(640, 480);
  QImage scaled_image = image.scaled(image_size);
  gif_frame->addFrame(scaled_image);
  if (frames_counter == 50) {
    timer->stop();
    gif_frame->save(gif_name);
    QMessageBox messageBoxGif;
    messageBoxGif.information(0, "", "Gif animation saved successfully");
    delete gif_frame;
    gif_frame = nullptr;
    ui->pushButton_screencast->setText("Screencast");
    ui->pushButton_screencast->setEnabled(true);
  }
  frames_counter++;
}

void MainWindow::on_pushButton_screencast_clicked() {
  if (ui->gl_widget->model->V) {
    QDateTime current_date = QDateTime::currentDateTime();
    QString formattedTime = current_date.toString("yyyy-MM-dd hh.mm.ss");
    QString name_pattern = "Screen Cast " + formattedTime + ".gif";
    gif_name = QFileDialog::getSaveFileName(this, tr("Save a gif animation"),
                                            name_pattern, tr("gif (*.gif)"));
    if (gif_name != "") {
      ui->pushButton_screencast->setDisabled(true);
      gif_frame = new QGifImage;
      gif_frame->setDefaultDelay(10);
      timer->setInterval(100);
      frames_counter = 0;
      timer->start();
    }
  } else {
    QMessageBox warning = QMessageBox();
    warning.setWindowTitle("Error");
    warning.setText("Please open .obj file to take a screencast");
    warning.setIcon(QMessageBox::Warning);
    warning.exec();
  }
}

void MainWindow::on_pushButton_reset_clicked() {
  reset_options();
  int err = ui->gl_widget->open_file();
  print_status(err);
}
