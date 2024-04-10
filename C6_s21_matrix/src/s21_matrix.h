#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-6

#define SUCCESS 1
#define FAILURE 0

#define OK 0
#define MATRIX_ERROR 1
#define CALC_ERROR 2

/* Все операции (кроме сравнения матриц) должны возвращать результирующий код:
    0 - OK
    1 - Ошибка, некорректная матрица (MATRIX_ERROR)
    2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
   нельзя провести вычисления и т.д.) (CALC_ERROR)

   Сравнение матриц возвращает код:
   0 - не равны (FAILURE)
   1 - равны (SUCCESS)
*/

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns,
                      matrix_t *result);      // Создание матрицы
void s21_remove_matrix(matrix_t *A);          // Очистка матрицы
int s21_eq_matrix(matrix_t *A, matrix_t *B);  // Сравнение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B,
                   matrix_t *result);  // Сложение матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B,
                   matrix_t *result);  // Вычитание матриц
int s21_mult_number(matrix_t *A, double number,
                    matrix_t *result);  // Умножение матрицы на число
int s21_mult_matrix(matrix_t *A, matrix_t *B,
                    matrix_t *result);  // Перемножение двух матриц
int s21_transpose(matrix_t *A, matrix_t *result);  // Транспонирование матрицы
int s21_calc_complements(
    matrix_t *A, matrix_t *result);  // Минор матрицы и матрица алг.дополнений
int s21_determinant(matrix_t *A, double *result);  // Определитель матрицы
int s21_inverse_matrix(matrix_t *A, matrix_t *result);  // Обратная матрица

void del_row_col(matrix_t *A, int i, int j,
                 matrix_t *temp);  // вычеркивание i-той строки, j-того столбца
double det(matrix_t *A);  // собственно формула определителя (разложением по 0-й
                          // строчке)

#endif  // SRC_S21_MATRIX_H_
