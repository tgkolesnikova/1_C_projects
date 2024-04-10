#include "3D_Viewer_v1_0.h"

void init_data(Obj_data *model) {
  if (model != NULL) {
    delete_data(model);
    model->num_V = 0;
    model->num_F = 0;
    model->V = NULL;
    model->F = NULL;
    for (int i = 0; i < 3; ++i) {
      model->V_min[i] = 0;
      model->V_max[i] = 0;
    }
  }
}

void delete_data(Obj_data *model) {
  if (model != NULL) {
    if (model->V) {
      free(model->V);
      model->V = NULL;
    }
    if (model->F) {
      for (int i = 0; i < model->num_F; ++i) {
        if (model->F[i].vertices_on_polygon)
          free(model->F[i].vertices_on_polygon);
      }
      free(model->F);
      model->F = NULL;
    }
  }
}

int read_obj_file(Obj_data *model, char *file_name) {
  int err = OK;

  if (model != NULL) {
    init_data(model);

    FILE *file;
    file = fopen(file_name, "r");
    if (file != NULL) {
      err = count_vf(model, file);
      if (err == OK) {
        model->V = (double *)calloc(model->num_V * 3, sizeof(double));
        model->F = (Polygon *)calloc(model->num_F, sizeof(Polygon));
        if (model->V && model->F) {
          err = add_points(model, file);
        }
      } else {
        err = ERROR_FILE_STRUCT;
      }
      fclose(file);
    } else {
      err = ERROR_FILE_OPEN;
    }
    if (err != OK) {
      delete_data(model);
    } else {
      normalize(model);
    }
  } else {
    err = ERROR_MEMORY;
  }
  return err;
}

int count_vf(Obj_data *model, FILE *file) {
  int err = OK;
  char symb0 = fgetc(file);
  while (!feof(file)) {
    char symb1 = fgetc(file);
    if (symb0 == 'v' && symb1 == ' ') model->num_V++;
    if (symb0 == 'f' && symb1 == ' ') model->num_F++;
    symb0 = symb1;
  }

  if ((model->num_V * model->num_F) == 0) {
    err = ERROR_FILE_STRUCT;
  }
  rewind(file);
  return err;
}

int add_points(Obj_data *model, FILE *file) {
  int err = OK;
  char line[BUFF_SIZE] = {0};
  int countV = 0;  // кол-во v-строк
  int countF = 0;  // кол-во f-строк

  char symb0 = fgetc(file), symb1 = 0;
  while (!feof(file) && err == OK) {
    symb1 = fgetc(file);

    if (symb0 == 'v' && symb1 == ' ') {
      if (fscanf(file, "%lf %lf %lf", &model->V[countV], &model->V[countV + 1],
                 &model->V[countV + 2]) != 3) {
        err = ERROR_FILE_STRUCT;
      }
      countV += 3;
    };
    if (symb0 == 'f' && symb1 == ' ') {
      fgets(line, sizeof(line), file);
      err = count_v_in_polygon(line, model, countF);
      if (err == OK) {
        err = add_polygon(line, model, countF);
      } else {
        err = ERROR_FILE_STRUCT;
      }
      countF++;
    }

    symb0 = symb1;
  }
  if (err == OK) {
    find_min_max(model);
  }
  rewind(file);
  return err;
}

int count_v_in_polygon(char *line, Obj_data *model, int countF) {
  int err = OK;
  int slahes = 0;
  model->F[countF].num_vertices = 0;
  int is_end = 0;

  while (line && err == OK && is_end != 1) {
    slahes = 0;
    if ('0' <= line[0] && line[0] <= '9') {
      model->F[countF].num_vertices++;
      do {
        if (line[0] == '/' &&
            (('0' <= line[1] && line[1] <= '9') || line[1] == '/')) {
          slahes++;
        } else if (line[0] == '/') {
          err = ERROR_FILE_STRUCT;
        }
        line++;
      } while (('0' <= line[0] && line[0] <= '9') ||
               (line[0] == '/' &&
                slahes < 2));  // 2 - кол-во '/' в f-строке obj-файла
    } else if (line[0] != ' ' && model->F[countF].num_vertices < MIN_VERTICES) {
      err = ERROR_FILE_STRUCT;
    }

    char *tmp = strchr(line, ' ');
    if (tmp && line - tmp == 0) {
      line = tmp;
    } else if (model->F[countF].num_vertices < MIN_VERTICES) {
      err = ERROR_FILE_STRUCT;
    } else {
      is_end = 1;
    }
    line++;
  }
  return err;
}

int add_polygon(char *line, Obj_data *model, int countF) {
  int err = OK;
  model->F[countF].vertices_on_polygon =
      (int *)calloc(model->F[countF].num_vertices, sizeof(int));

  int i = 0;
  while (line && err == OK && i < model->F[countF].num_vertices) {
    while (line[0] == ' ') line++;
    if ('0' <= line[0] && line[0] <= '9') {
      model->F[countF].vertices_on_polygon[i] = atoi(line) - 1;
      if (model->F[countF].vertices_on_polygon[i] >= model->num_V) {
        err = ERROR_FILE_STRUCT;
      }
    }
    i++;
    line = strchr(line, ' ');
  }
  return err;
}

void find_min_max(Obj_data *model) {
  for (int i = 0; i < 3; ++i) {
    model->V_min[i] = model->V[i];
    model->V_max[i] = model->V[i];
  }
  for (int i = 0; i < model->num_V; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (model->V[i * 3 + j] < model->V_min[j])
        model->V_min[j] = model->V[i * 3 + j];
      if (model->V[i * 3 + j] > model->V_max[j])
        model->V_max[j] = model->V[i * 3 + j];
    }
  }
}

void normalize(Obj_data *model) {
  centering(model);
  double d_max = model->V_max[0] - model->V_min[0],
         d_y = model->V_max[1] - model->V_min[1],
         d_z = model->V_max[2] - model->V_min[2];
  if (d_y > d_max) d_max = d_y;
  if (d_z > d_max) d_max = d_z;
  double scal = 2.0 / d_max;
  scale(model, scal);
}

void centering(Obj_data *model) {
  double center[3];
  for (int j = 0; j < 3; j++) {
    center[j] = (model->V_max[j] + model->V_min[j]) / 2;
  }
  for (int i = 0; i < model->num_V; i++)
    for (int j = 0; j < 3; j++) {
      model->V[i * 3 + j] -= center[j];
    }
}
