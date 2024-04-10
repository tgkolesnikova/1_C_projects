#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  result->matrix = NULL;
  result->rows = 0;
  result->columns = 0;
  int res = OK;

  if (rows > 0 && columns > 0) {
    result->matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)malloc(columns * sizeof(double));
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = 0;
      }
    }
    result->rows = rows;
    result->columns = columns;
  } else {
    res = MATRIX_ERROR;
  }
  return res;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
  A->rows = 0;
  A->columns = 0;
  A->matrix = NULL;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (A->rows == B->rows && A->columns == B->columns && A->matrix &&
      B->matrix) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= EPS) {
          res = FAILURE;
        }
      }
    }
  } else {
    res = FAILURE;
  }
  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0 &&
      A->matrix && B->matrix) {
    if (A->rows == B->rows && A->columns == B->columns) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      res = CALC_ERROR;
    }
  } else {
    res = MATRIX_ERROR;
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0 &&
      A->matrix && B->matrix) {
    if (A->rows == B->rows && A->columns == B->columns) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      res = CALC_ERROR;
    }
  } else {
    res = MATRIX_ERROR;
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (A->rows > 0 && A->columns > 0 && A->matrix) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  } else {
    res = MATRIX_ERROR;
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (A->rows > 0 && A->columns > 0 && A->matrix && B->matrix) {
    int err = s21_create_matrix(A->rows, B->columns, result);
    if (A->columns == B->rows && err == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          double S = 0;
          for (int k = 0; k < A->columns; k++) {
            S += A->matrix[i][k] * B->matrix[k][j];
          }
          result->matrix[i][j] = S;
        }
      }
    } else {
      res = CALC_ERROR;
    }
  } else {
    res = MATRIX_ERROR;
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (A->rows > 0 && A->columns > 0 && A->matrix) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->columns; i++) {
      for (int j = 0; j < A->rows; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  } else {
    res = MATRIX_ERROR;
  }
  return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (A->rows > 0 && A->columns > 0 && A->matrix) {
    int err = s21_create_matrix(A->rows, A->columns, result);
    if (A->rows == A->columns && err == 0) {
      if (A->rows == 1) {
        result->matrix[0][0] = 1;
      } else {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->rows; j++) {
            matrix_t temp;
            s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
            del_row_col(A, i, j, &temp);
            result->matrix[i][j] = det(&temp) * pow(-1.0, i + j);
            s21_remove_matrix(&temp);
          }
        }
      }
    } else {
      res = CALC_ERROR;
    }
  } else {
    res = MATRIX_ERROR;
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = OK;
  *result = NAN;
  if (A->rows > 0 && A->columns > 0 && A->matrix) {
    if (A->rows == A->columns) {
      *result = det(A);
    } else {
      res = CALC_ERROR;
    }
  } else {
    res = MATRIX_ERROR;
  }
  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (A->rows > 0 && A->columns > 0 && A->matrix) {
    double detA = 0.0;
    int err = s21_determinant(A, &detA);
    if (A->rows == A->columns && fabs(detA) > EPS && err == 0) {
      s21_create_matrix(A->rows, A->columns, result);

      matrix_t temp1;  // матрица алг.дополнений
      s21_calc_complements(A, &temp1);

      matrix_t temp2;  // союзная матрица (трансп алг доп)
      s21_transpose(&temp1, &temp2);

      for (int i = 0; i < temp2.rows; i++) {
        for (int j = 0; j < temp2.columns; j++) {
          result->matrix[i][j] = temp2.matrix[i][j] / detA;
        }
      }

      s21_remove_matrix(&temp1);
      s21_remove_matrix(&temp2);
    } else {
      res = CALC_ERROR;
    }
  } else {
    res = MATRIX_ERROR;
  }
  return res;
}

void del_row_col(matrix_t *A, int I, int J, matrix_t *temp) {
  int i_temp = 0;
  for (int i = 0; i < A->rows; i++) {
    int j_temp = 0;
    if (i != I) {
      for (int j = 0; j < A->columns; j++) {
        if (j != J) {
          temp->matrix[i_temp][j_temp] = A->matrix[i][j];
          j_temp++;
        }
      }
      i_temp++;
    }
  }
}

double det(matrix_t *A) {
  double res = 0;
  if (A->rows == 1) {
    res = A->matrix[0][0];
  } else if (A->rows == 2) {
    res = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    double sign = 1.;
    for (int j = 0; j < A->columns; j++) {
      matrix_t temp;
      s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
      del_row_col(A, 0, j, &temp);
      res += sign * A->matrix[0][j] * det(&temp);
      sign *= -1;
      s21_remove_matrix(&temp);
    }
  }
  return res;
}
