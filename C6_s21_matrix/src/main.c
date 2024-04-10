#include "s21_matrix.h"

int main() {
  /*   create_matrix    */
  {
    matrix_t A;
    int err = -1;
    err = s21_create_matrix(1, 1, &A);
    s21_remove_matrix(&A);
    printf("creat_matrix 1:  %d %d\n", err, OK);

    err = s21_create_matrix(4, 2, &A);
    s21_remove_matrix(&A);
    printf("creat_matrix 2:  %d %d\n", err, OK);

    err = s21_create_matrix(-4, 2, &A);
    s21_remove_matrix(&A);
    printf("creat_matrix 3:  %d %d\n", err, MATRIX_ERROR);

    err = s21_create_matrix(4, -2, &A);
    s21_remove_matrix(&A);
    printf("creat_matrix 4:  %d %d\n", err, MATRIX_ERROR);

    err = s21_create_matrix(0, 2, &A);
    s21_remove_matrix(&A);
    printf("creat_matrix 5:  %d %d\n", err, MATRIX_ERROR);

    err = s21_create_matrix(2, 0, &A);
    s21_remove_matrix(&A);
    printf("creat_matrix 6:  %d %d\n", err, MATRIX_ERROR);
  }

  /*   eq_matrix   */
  {
    matrix_t A, B;
    int err = -1;

    s21_create_matrix(1, 3, &A);
    s21_create_matrix(1, 3, &B);
    err = s21_eq_matrix(&A, &B);
    printf("eq_matrix 1:  %d %d\n", err, SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);

    s21_create_matrix(3, 1, &A);
    s21_create_matrix(1, 3, &B);
    err = s21_eq_matrix(&A, &B);
    printf("eq_matrix 2:  %d %d\n", err, FAILURE);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);

    s21_create_matrix(0, 1, &A);
    s21_create_matrix(0, 1, &B);
    err = s21_eq_matrix(&A, &B);
    printf("eq_matrix 3:  %d %d\n", err, FAILURE);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);

    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);
    A.matrix[0][0] = 0.1;
    A.matrix[0][1] = 0.12345678;
    A.matrix[0][2] = 1.1;
    A.matrix[1][0] = 0.3;
    A.matrix[1][1] = 0.1;
    A.matrix[1][2] = 0.1;
    A.matrix[2][0] = 0.1;
    A.matrix[2][1] = 0.1;
    A.matrix[2][2] = 0.1;
    B.matrix[0][0] = 0.1;
    B.matrix[0][1] = 0.12345689;
    B.matrix[0][2] = 1.1;
    B.matrix[1][0] = 0.3;
    B.matrix[1][1] = 0.1;
    B.matrix[1][2] = 0.1;
    B.matrix[2][0] = 0.1;
    B.matrix[2][1] = 0.1;
    B.matrix[2][2] = 0.1;
    err = s21_eq_matrix(&A, &B);
    printf("eq_matrix 4:  %d %d\n", err, SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);

    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);
    A.matrix[0][0] = 0.1;
    A.matrix[0][1] = 0.12345678;
    A.matrix[0][2] = 1.1;
    A.matrix[1][0] = 0.3;
    A.matrix[1][1] = 66666666660.10101;
    A.matrix[1][2] = 0.1;
    A.matrix[2][0] = 0.1;
    A.matrix[2][1] = 53453454357.1;
    A.matrix[2][2] = 0.1;
    B.matrix[0][0] = 0.1;
    B.matrix[0][1] = 0.1234567;
    B.matrix[0][2] = 1.1;
    B.matrix[1][0] = 0.3;
    B.matrix[1][1] = 66666666660.10101;
    B.matrix[1][2] = 0.1;
    B.matrix[2][0] = 0.1;
    B.matrix[2][1] = 53453454357.1;
    B.matrix[2][2] = 0.1;
    err = s21_eq_matrix(&A, &B);
    printf("eq_matrix 5:  %d %d\n", err, SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);

    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    A.matrix[0][0] = -0.13232;
    A.matrix[0][1] = 0.1234567854354;
    A.matrix[1][0] = 0.3;
    A.matrix[1][1] = -23;
    B.matrix[0][0] = -0.13232;
    B.matrix[0][1] = 0.12345678123;
    B.matrix[1][0] = 0.3;
    B.matrix[1][1] = -23;
    err = s21_eq_matrix(&A, &B);
    printf("eq_matrix 6:  %d %d\n", err, SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
  }

  /*  sum_matrix   */
  {
    matrix_t A;
    matrix_t B;
    matrix_t C;
    int err = -1;

    s21_create_matrix(2, 1, &A);
    s21_create_matrix(2, 1, &B);
    double test[] = {5.0, -1.003};
    A.matrix[0][0] = 1.0;
    A.matrix[1][0] = 2.23;
    B.matrix[0][0] = 4.0;
    B.matrix[1][0] = -3.233;
    err = s21_sum_matrix(&A, &B, &C);
    for (int i = 0, k = 0; i < C.rows; i++)
      for (int j = 0; j < C.columns; j++) {
        printf(" %d ", fabs(C.matrix[i][j] - test[k]) < EPS);
        k++;
      }
    printf("\nsum_matrix 1: %d %d\n", err, OK);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);

    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    double test2[] = {5.0, 0.0, -1.003, 0.0};
    A.matrix[0][0] = 1.0;
    A.matrix[1][0] = 2.23;
    B.matrix[0][0] = 4.0;
    B.matrix[1][0] = -3.233;
    err = s21_sum_matrix(&A, &B, &C);
    for (int i = 0, k = 0; i < C.rows; i++)
      for (int j = 0; j < C.columns; j++) {
        printf(" %d ", fabs(C.matrix[i][j] - test2[k]) < EPS);
        k++;
      }
    printf("\nsum_matrix 2: %d %d\n", err, OK);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);

    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 3, &B);
    err = s21_sum_matrix(&A, &B, &C);
    printf("\nsum_matrix 3: %d %d\n", err, CALC_ERROR);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);

    s21_create_matrix(2, 2, &A);
    s21_create_matrix(0, 0, &B);
    err = s21_sum_matrix(&A, &B, &C);
    printf("\nsum_matrix 4: %d %d\n", err, MATRIX_ERROR);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
  }

  /*   sub_matrix  */
  {
    matrix_t A;
    matrix_t B;
    matrix_t C;
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    double test[] = {1.0, 0.0, 0.0, 1.0};
    A.matrix[0][0] = 1.0;
    A.matrix[0][1] = 1.0;
    A.matrix[1][0] = 2.0;
    A.matrix[1][1] = 65.234;
    B.matrix[0][0] = 0.0;
    B.matrix[0][1] = 1.0;
    B.matrix[1][0] = 2.0;
    B.matrix[1][1] = 64.234;
    int err = s21_sub_matrix(&A, &B, &C);
    for (int i = 0, k = 0; i < C.rows; i++)
      for (int j = 0; j < C.columns; j++) {
        printf(" %d ", fabs(C.matrix[i][j] - test[k]) < 1e-6);
        k++;
      }
    printf("\nsub_matrix 1: %d %d\n", err, OK);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);

    s21_create_matrix(2, 3, &A);
    s21_create_matrix(2, 2, &B);
    A.matrix[0][0] = 1.0;
    A.matrix[0][1] = 3.0;
    A.matrix[0][2] = 5.0;
    A.matrix[1][0] = 29.0;
    A.matrix[1][1] = 2143.0;
    A.matrix[1][2] = 2.0;
    B.matrix[0][0] = 0.0;
    B.matrix[0][1] = -3.0;
    B.matrix[1][0] = -5.0;
    B.matrix[1][1] = -1.0;
    err = s21_sub_matrix(&A, &B, &C);
    printf("\nsub_matrix 2: %d %d\n", err, CALC_ERROR);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);

    s21_create_matrix(2, 3, &A);
    s21_create_matrix(0, 0, &B);
    A.matrix[0][0] = 0.0;
    A.matrix[0][1] = -3.0;
    A.matrix[0][2] = -3.0;
    A.matrix[1][0] = -5.0;
    A.matrix[1][1] = -1.0;
    A.matrix[1][2] = -1.0;
    err = s21_sub_matrix(&A, &B, &C);
    printf("\nsub_matrix 3: %d %d\n", err, MATRIX_ERROR);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
  }

  /*  multy_number  */
  {
    matrix_t C;
    matrix_t A;
    int err = -1;
    s21_create_matrix(0, 0, &A);
    err = s21_mult_number(&A, 3, &C);
    printf("mult_number 1: %d %d\n", err, MATRIX_ERROR);
    s21_remove_matrix(&A);

    s21_create_matrix(2, 2, &A);
    double test[] = {12.12, 38.9052, -60.6, 25.6944};
    A.matrix[0][0] = 1.0;
    A.matrix[0][1] = 3.21;
    A.matrix[1][0] = -5.0;
    A.matrix[1][1] = 2.12;
    err = s21_mult_number(&A, 12.12, &C);
    for (int i = 0, k = 0; i < C.rows; i++)
      for (int j = 0; j < C.columns; j++) {
        printf(" %d ", fabs(C.matrix[i][j] - test[k]) < 1e-6);
        k++;
      }
    printf("\nmult_number 2: %d %d\n", err, OK);
    s21_remove_matrix(&A);
    s21_remove_matrix(&C);

    s21_create_matrix(2, 2, &A);
    A.matrix[0][0] = 1.0;
    A.matrix[0][1] = 3.21;
    A.matrix[1][0] = -5.0;
    A.matrix[1][1] = 2.12;
    err = s21_mult_number(&A, 1, &C);
    printf("\nmult_number 3: %d %d\n", err, OK);
    err = s21_eq_matrix(&A, &C);
    printf("equal A & C: %d %d\n", err, SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&C);
  }

  /*   mult_matrix  */
  {
    matrix_t A;
    matrix_t B;
    matrix_t C;
    int err = -1;
    s21_create_matrix(2, 3, &A);
    s21_create_matrix(2, 2, &B);
    A.matrix[0][1] = 23;
    A.matrix[1][2] = 1;
    B.matrix[0][1] = 12;
    B.matrix[1][1] = 23;
    err = s21_mult_matrix(&A, &B, &C);
    printf("\nmult_matrix 1: %d %d\n", err, CALC_ERROR);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);

    s21_create_matrix(2, 3, &A);
    s21_create_matrix(3, 2, &B);
    A.matrix[0][1] = 23;
    A.matrix[1][2] = 1;
    B.matrix[1][1] = 23;
    B.matrix[0][1] = 12;
    err = s21_mult_matrix(&A, &B, &C);
    double test[] = {0, 529, 0, 0};
    for (int i = 0, k = 0; i < C.rows; i++)
      for (int j = 0; j < C.columns; j++) {
        printf(" %d ", fabs(C.matrix[i][j] - test[k]) < 1e-6);
        k++;
      }
    printf("\nmult_matrix 2: %d %d\n", err, OK);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);

    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);
    A.matrix[0][1] = 23;
    A.matrix[1][1] = 32;
    B.matrix[0][1] = 1;
    B.matrix[1][1] = 1;
    err = s21_mult_matrix(&A, &B, &C);
    printf("\nmult_matrix 3: %d %d\n", err, OK);
    err = s21_eq_matrix(&A, &C);
    printf("equal matrix A & C: %d %d\n", err, SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);

    s21_create_matrix(3, 2, &A);
    s21_create_matrix(0, 0, &B);
    err = s21_mult_matrix(&A, &B, &C);
    printf("\nmult_matrix 4: %d %d\n", err, MATRIX_ERROR);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
  }

  /*  transpose  */
  {
    matrix_t A;
    matrix_t B;
    matrix_t C;
    int err = -1, err1 = -1;

    s21_create_matrix(0, 0, &A);
    err = s21_transpose(&A, &C);
    printf("\ntranspose 1: %d %d\n", err, MATRIX_ERROR);
    s21_remove_matrix(&A);

    s21_create_matrix(3, 2, &A);
    s21_create_matrix(2, 3, &B);
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 4;
    A.matrix[1][0] = 2;
    A.matrix[1][1] = 5;
    A.matrix[2][0] = 3;
    A.matrix[2][1] = 6;
    B.matrix[0][0] = 1;
    B.matrix[0][1] = 2;
    B.matrix[0][2] = 3;
    B.matrix[1][0] = 4;
    B.matrix[1][1] = 5;
    B.matrix[1][2] = 6;
    err = s21_transpose(&A, &C);
    err1 = s21_eq_matrix(&C, &B);
    printf("\ntranspose 2: %d %d\n", err, OK);
    printf("equal matrix: %d %d\n", err1, SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);
  }

  /*  complements  */
  {
    matrix_t A;
    matrix_t C;
    int err = -1;
    s21_create_matrix(2, 3, &A);
    A.matrix[0][0] = 1.24;
    A.matrix[0][1] = 23;
    A.matrix[0][2] = 3;
    A.matrix[1][0] = 111;
    A.matrix[1][1] = 0;
    A.matrix[1][2] = 2;
    err = s21_calc_complements(&A, &C);
    printf("\ncomplements 1: %d %d\n", err, CALC_ERROR);
    s21_remove_matrix(&A);
    s21_remove_matrix(&C);

    s21_create_matrix(1, 1, &A);
    A.matrix[0][0] = 1;
    err = s21_calc_complements(&A, &C);
    printf("\ncomplements 2: %d %d\n", err, OK);
    s21_remove_matrix(&A);
    s21_remove_matrix(&C);

    s21_create_matrix(3, 3, &A);
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 3;
    A.matrix[1][0] = 0;
    A.matrix[1][1] = 4;
    A.matrix[1][2] = 2;
    A.matrix[2][0] = 5;
    A.matrix[2][1] = 2;
    A.matrix[2][2] = 1;
    err = s21_calc_complements(&A, &C);
    double test[] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
    for (int i = 0, k = 0; i < C.rows; i++)
      for (int j = 0; j < C.columns; j++) {
        printf(" %d ", fabs(C.matrix[i][j] - test[k]) < 1e-6);
        k++;
      }
    printf("\ncomplements 3: %d %d\n", err, OK);
    s21_remove_matrix(&A);
    s21_remove_matrix(&C);

    matrix_t B;
    B.columns = 0;
    B.rows = 0;
    B.matrix = NULL;
    err = s21_calc_complements(&B, &C);
    printf("\ncomplements 4: %d %d \n\n", err, MATRIX_ERROR);
    s21_remove_matrix(&B);

    s21_create_matrix(4, 4, &A);
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 3;
    A.matrix[0][3] = 4;

    A.matrix[1][0] = 0;
    A.matrix[1][1] = 4;
    A.matrix[1][2] = 2;
    A.matrix[1][3] = 3;

    A.matrix[2][0] = 5;
    A.matrix[2][1] = 2;
    A.matrix[2][2] = 1;
    A.matrix[2][3] = 3;

    A.matrix[3][0] = -1;
    A.matrix[3][1] = 2;
    A.matrix[3][2] = -3;
    A.matrix[3][3] = 4;

    err = s21_calc_complements(&A, &C);
    double test3[] = {24,  88,  -56, -80, 12, -112, -4, 56,
                      -60, -16, 20,  8,   12, 8,    44, -40};
    for (int i = 0, k = 0; i < C.rows; i++) {
      for (int j = 0; j < C.columns; j++) {
        printf(" %6.1f", C.matrix[i][j]);
        printf(" %d ", fabs(C.matrix[i][j] - test3[k]) < 1e-6);
        k++;
      }
      printf("\n");
    }
    printf("complements 5: %d %d\n", err, OK);
    s21_remove_matrix(&A);
    s21_remove_matrix(&C);
  }

  /*  determinant  */
  {
    matrix_t A;
    double det = 0;
    s21_create_matrix(1, 1, &A);
    A.matrix[0][0] = 12.3451;
    int check = s21_determinant(&A, &det);
    double test = 12.3451;
    printf("determinant 1: %d %d %d\n", fabs(det - test) < 1e-6, check, OK);
    s21_remove_matrix(&A);

    det = 0;
    matrix_t B;
    B.columns = 0;
    B.rows = 0;
    B.matrix = NULL;
    check = s21_determinant(&B, &det);
    printf("determinant 2: _ %d %d\n", check, MATRIX_ERROR);
    s21_remove_matrix(&B);

    det = 0;
    s21_create_matrix(2, 3, &A);
    A.matrix[0][0] = 1.24;
    A.matrix[0][1] = 23;
    A.matrix[0][2] = 3;
    A.matrix[1][0] = 111;
    A.matrix[1][1] = 0;
    A.matrix[1][2] = 2;
    check = s21_determinant(&A, &det);
    printf("determinant 3: _ %d %d\n", check, CALC_ERROR);
    s21_remove_matrix(&A);

    det = 0;
    s21_create_matrix(3, 3, &A);
    A.matrix[0][0] = 1.24;
    A.matrix[0][1] = 23;
    A.matrix[0][2] = 3;
    A.matrix[1][0] = 111;
    A.matrix[1][1] = 0;
    A.matrix[1][2] = 2;
    A.matrix[2][0] = 111;
    A.matrix[2][1] = 0;
    A.matrix[2][2] = 2;
    check = s21_determinant(&A, &det);
    printf("determinant 4: %f %d %d\n", det, check, OK);
    s21_remove_matrix(&A);
  }

  /* inverse */
  {
    matrix_t A;
    matrix_t B;
    matrix_t C;

    s21_create_matrix(0, 0, &B);
    int check = s21_inverse_matrix(&B, &C);
    printf("inverse 1: %d %d\n", check, MATRIX_ERROR);
    s21_remove_matrix(&B);

    s21_create_matrix(1, 1, &A);
    check = s21_inverse_matrix(&A, &C);
    printf("inverse 2: %d %d\n\n", check, CALC_ERROR);
    s21_remove_matrix(&A);

    s21_create_matrix(2, 2, &A);
    A.matrix[0][0] = 7.589;
    A.matrix[0][1] = 59.1;
    A.matrix[1][0] = 26.35;
    A.matrix[1][1] = 75.17;
    check = s21_inverse_matrix(&A, &C);
    double test4[] = {-0.076173, 0.059889, 0.026701, -0.00769};
    for (int i = 0, k = 0; i < C.rows; i++)
      for (int j = 0; j < C.columns; j++) {
        printf(" %d ", fabs(C.matrix[i][j] - test4[k]) < 1e-6);
        k++;
      }
    printf("\ninverse 3: %d %d\n", check, OK);
    s21_remove_matrix(&A);
    s21_remove_matrix(&C);
  }

  return 0;
}
