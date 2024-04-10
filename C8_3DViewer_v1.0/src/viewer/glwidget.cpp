#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget{parent} {}

GLWidget::~GLWidget() {
  delete_data(model);
  free(model);
}

int GLWidget::open_file() {
  QByteArray ba = file_name.toLatin1();
  char *char_file_name = ba.data();
  angle_x = 0;
  int err = read_obj_file(model, char_file_name);
  if (!err) {
    update();
  }
  return err;
}

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();
  model = (Obj_data *)calloc(1, sizeof(Obj_data));
}

void GLWidget::paintGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(bg_red, bg_green, bg_blue, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  if (model->V) {
    glMatrixMode(GL_PROJECTION);
    glVertexPointer(3, GL_DOUBLE, 0, model->V);

    if (this->projection_type == PROJ_PARALLEL) {  // Parallel
      glRotatef(30, .2, -.2, 0);
      glOrtho(-1, 1, -1, 1, -4, 4);
      //      glMatrixMode(GL_MODELVIEW);
      //      glTranslatef(0, 0, -2.0);
    } else {
      glFrustum(-1.0, 1.0, -1.0, 1.0, 1, 200);  // Central
      glMatrixMode(GL_MODELVIEW);
      glTranslatef(0, 0, -2.8);
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    if (nodes_type) build_points();
    build_lines();
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
  }
}

void GLWidget::build_points() {
  if (nodes_type == NODES_CIRCLE) glEnable(GL_POINT_SMOOTH);
  glPointSize(nodes_size);
  glColor3f(nodes_red, nodes_green, nodes_blue);
  glDrawArrays(GL_POINTS, 0, model->num_V);
  glDisable(GL_POINT_SMOOTH);
}

void GLWidget::build_lines() {
  if (model->F) {
    if (this->edges_type == EDGES_DASHED) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, 0x00FF);
    } else {
      glDisable(GL_LINE_STIPPLE);
    }
    glLineWidth(edges_size);
    glColor3f(edges_red, edges_green, edges_blue);

    for (int i = 0; i < model->num_F; i++) {
      glBegin(GL_LINE_LOOP);
      for (int u = 0; u < model->F[i].num_vertices; u++) {
        int index_V = (model->F[i].vertices_on_polygon[u]) * 3;
        glVertex3d(model->V[index_V], model->V[index_V + 1],
                   model->V[index_V + 2]);
      }
      glEnd();
    }
  }
}
