#include "3D_Viewer_v1_0.h"

void move_x(Obj_data *model, double dX) {
  if (model && model->V) {
    for (int i = 0; i < model->num_V * 3; i += 3) {
      model->V[i] += dX;
    }
  }
}

void move_y(Obj_data *model, double dY) {
  if (model && model->V) {
    for (int i = 0; i < model->num_V * 3; i += 3) {
      model->V[i + 1] += dY;
    }
  }
}

void move_z(Obj_data *model, double dZ) {
  if (model && model->V) {
    for (int i = 0; i < model->num_V * 3; i += 3) {
      model->V[i + 2] += dZ;
    }
  }
}

void rotate_x(Obj_data *model, double angle_deg) {
  if (model && model->V) {
    double angel_rad = angle_deg * (M_PI / 180);
    double y, z;
    for (int i = 0; i < model->num_V * 3; i += 3) {
      y = model->V[i + 1];
      z = model->V[i + 2];
      model->V[i + 1] = cos(angel_rad) * y - sin(angel_rad) * z;
      model->V[i + 2] = sin(angel_rad) * y + cos(angel_rad) * z;
    }
  }
}

void rotate_y(Obj_data *model, double angle_deg) {
  if (model && model->V) {
    double angel_rad = angle_deg * (M_PI / 180);
    double x, z;
    for (int i = 0; i < model->num_V * 3; i += 3) {
      x = model->V[i];
      z = model->V[i + 2];
      model->V[i] = cos(angel_rad) * x + sin(angel_rad) * z;
      model->V[i + 2] = -sin(angel_rad) * x + cos(angel_rad) * z;
    }
  }
}

void rotate_z(Obj_data *model, double angle_deg) {
  if (model && model->V) {
    double angel_rad = angle_deg * (M_PI / 180);
    double x, y;
    for (int i = 0; i < model->num_V * 3; i += 3) {
      x = model->V[i];
      y = model->V[i + 1];
      model->V[i] = cos(angel_rad) * x - sin(angel_rad) * y;
      model->V[i + 1] = sin(angel_rad) * x + cos(angel_rad) * y;
    }
  }
}

void scale(Obj_data *model, double coeff) {
  if (model && model->V) {
    for (int i = 0; i < model->num_V * 3; ++i) {
      model->V[i] *= coeff;
    }
  }
}
