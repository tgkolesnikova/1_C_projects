#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QMessageBox>
#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QWidget>
#include <QtOpenGL>
// #include <iostream>
#include <QOpenGLFunctions>

extern "C" {
#include "../backend/3D_Viewer_v1_0.h"
}

enum { PROJ_PARALLEL, PROJ_CENTRAL };
enum { EDGES_SOLID, EDGES_DASHED };
enum { NODES_NON, NODES_SQUARE, NODES_CIRCLE };

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  explicit GLWidget(QWidget *parent = Q_NULLPTR);

  Obj_data *model;

  QString file_name;
  double bg_red = 0, bg_green = 0, bg_blue = 1;
  double edges_red = 1, edges_green = 1, edges_blue = 1;
  double nodes_red = 1, nodes_green = 1, nodes_blue = 1;
  int projection_type = PROJ_PARALLEL;  // 0 - Parallel, 1 - Central
  int edges_type = EDGES_SOLID;         // 0 - Solid, 1 - Dashed
  int nodes_type = NODES_CIRCLE;        // 0 - Non, 1 - Square, 2 - Circle
  GLfloat nodes_size = 2;
  GLfloat edges_size = 1;
  int angle_x = 0, angle_y = 0, angle_z = 0;
  double move_x = 0, move_y = 0, move_z = 0;
  int zoom = 100;

  void initializeGL() override;
  void paintGL() override;

  void build_points();
  void build_lines();
  int open_file();

 private:
  ~GLWidget() override;
};

#endif  // GLWIDGET_H
