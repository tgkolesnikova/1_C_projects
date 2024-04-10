#include <check.h>

#include "s21_matrix.h"

START_TEST(create_matrix) {
  matrix_t A;
  int check = s21_create_matrix(1, 1, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(check, OK);

  check = s21_create_matrix(4, 2, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(check, OK);

  check = s21_create_matrix(-4, 2, &A);
  ck_assert_int_eq(check, MATRIX_ERROR);

  check = s21_create_matrix(4, -2, &A);
  ck_assert_int_eq(check, MATRIX_ERROR);

  check = s21_create_matrix(4, 0, &A);
  ck_assert_int_eq(check, MATRIX_ERROR);

  check = s21_create_matrix(0, 4, &A);
  ck_assert_int_eq(check, MATRIX_ERROR);
}
END_TEST

START_TEST(eq_matrix) {
  matrix_t A;
  matrix_t B;

  s21_create_matrix(1, 3, &A);
  s21_create_matrix(1, 3, &B);
  int check = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(check, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  s21_create_matrix(3, 1, &A);
  s21_create_matrix(1, 3, &B);
  check = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(check, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  s21_create_matrix(0, 1, &A);
  s21_create_matrix(0, 1, &B);
  check = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(check, FAILURE);
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
  B.matrix[0][1] = 0.1234567;
  B.matrix[0][2] = 1.1;
  B.matrix[1][0] = 0.3;
  B.matrix[1][1] = 0.1;
  B.matrix[1][2] = 0.1;
  B.matrix[2][0] = 0.1;
  B.matrix[2][1] = 0.1;
  B.matrix[2][2] = 0.1;
  check = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(check, SUCCESS);
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
  check = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(check, SUCCESS);
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
  check = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(check, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(2, 1, &A);
  s21_create_matrix(2, 1, &B);
  double test[] = {5.0, -1.003};
  A.matrix[0][0] = 1.0;
  A.matrix[1][0] = 2.23;
  B.matrix[0][0] = 4.0;
  B.matrix[1][0] = -3.233;
  int check = s21_sum_matrix(&A, &B, &C);
  for (int i = 0, k = 0; i < C.rows; i++)
    for (int j = 0; j < C.columns; j++) {
      ck_assert_int_eq(fabs(C.matrix[i][j] - test[k]) < 1e-6, 1);
      k++;
    }
  ck_assert_int_eq(check, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(sum_matrix_3) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  double test[] = {0.0, 0.0, 0.0, 0.0};
  int check = s21_sum_matrix(&A, &B, &C);
  for (int i = 0, k = 0; i < C.rows; i++)
    for (int j = 0; j < C.columns; j++) {
      ck_assert_int_eq(fabs(C.matrix[i][j] - test[k]) < 1e-6, 1);
      k++;
    }
  ck_assert_int_eq(check, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(sum_matrix_4) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 3, &B);
  int check = s21_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(check, CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_5) {
  matrix_t A;
  matrix_t C;
  matrix_t null;
  null.columns = 0;
  null.rows = 0;
  null.matrix = NULL;
  s21_create_matrix(2, 2, &A);
  int check = s21_sum_matrix(&A, &null, &C);
  ck_assert_int_eq(check, MATRIX_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&null);
}
END_TEST

START_TEST(sub_matrix_1) {
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
  int check = s21_sub_matrix(&A, &B, &C);
  for (int i = 0, k = 0; i < C.rows; i++)
    for (int j = 0; j < C.columns; j++) {
      ck_assert_int_eq(fabs(C.matrix[i][j] - test[k]) < 1e-6, 1);
      k++;
    }
  ck_assert_int_eq(check, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(sub_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
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
  int check = s21_sub_matrix(&A, &B, &C);
  ck_assert_int_eq(check, CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_3) {
  matrix_t A;
  matrix_t C;
  matrix_t null;
  null.columns = 0;
  null.rows = 0;
  null.matrix = NULL;
  s21_create_matrix(2, 3, &A);
  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = -3.0;
  A.matrix[0][2] = -3.0;
  A.matrix[1][0] = -5.0;
  A.matrix[1][1] = -1.0;
  A.matrix[1][2] = -1.0;
  int check = s21_sub_matrix(&A, &null, &C);
  ck_assert_int_eq(check, MATRIX_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&null);
}
END_TEST

START_TEST(mul_number_1) {
  matrix_t C;
  matrix_t null;
  null.columns = 0;
  null.rows = 0;
  null.matrix = NULL;
  int check = s21_mult_number(&null, 3, &C);
  ck_assert_int_eq(check, MATRIX_ERROR);
  s21_remove_matrix(&null);
}
END_TEST

START_TEST(mul_number_2) {
  matrix_t A;
  matrix_t C;
  s21_create_matrix(2, 2, &A);
  double test[] = {12.12, 38.9052, -60.6, 25.6944};
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 3.21;
  A.matrix[1][0] = -5.0;
  A.matrix[1][1] = 2.12;
  int check = s21_mult_number(&A, 12.12, &C);
  for (int i = 0, k = 0; i < C.rows; i++)
    for (int j = 0; j < C.columns; j++) {
      ck_assert_int_eq(fabs(C.matrix[i][j] - test[k]) < 1e-6, 1);
      k++;
    }
  ck_assert_int_eq(check, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(mul_number_3) {
  matrix_t A;
  matrix_t C;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 3.21;
  A.matrix[1][0] = -5.0;
  A.matrix[1][1] = 2.12;
  int check = s21_mult_number(&A, 1, &C);
  int check1 = s21_eq_matrix(&A, &C);
  ck_assert_int_eq(check, OK);
  ck_assert_int_eq(check1, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(mul_matrix_1) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][1] = 23;
  A.matrix[1][2] = 1;
  B.matrix[0][1] = 12;
  B.matrix[1][1] = 23;
  int check = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(check, CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(mul_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  A.matrix[0][1] = 23;
  A.matrix[1][2] = 1;
  B.matrix[1][1] = 23;
  B.matrix[0][1] = 12;
  int check = s21_mult_matrix(&A, &B, &C);
  double test[] = {0, 529, 0, 0};
  for (int i = 0, k = 0; i < C.rows; i++)
    for (int j = 0; j < C.columns; j++) {
      ck_assert_int_eq(fabs(C.matrix[i][j] - test[k]) < 1e-6, 1);
      k++;
    }
  ck_assert_int_eq(check, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(mul_matrix_3) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  A.matrix[0][1] = 23;
  A.matrix[1][1] = 32;
  B.matrix[0][1] = 1;
  B.matrix[1][1] = 1;
  int check = s21_mult_matrix(&A, &B, &C);
  int check1 = s21_eq_matrix(&A, &C);
  ck_assert_int_eq(check, OK);
  ck_assert_int_eq(check1, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(mul_matrix_4) {
  matrix_t A;
  matrix_t C;
  matrix_t null;
  null.columns = 0;
  null.rows = 0;
  null.matrix = NULL;
  s21_create_matrix(3, 2, &A);
  int check = s21_mult_matrix(&A, &null, &C);
  ck_assert_int_eq(check, MATRIX_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&null);
}
END_TEST

START_TEST(transpose_1) {
  matrix_t null;
  null.columns = 0;
  null.rows = 0;
  null.matrix = NULL;
  matrix_t C;
  int check = s21_transpose(&null, &C);
  ck_assert_int_eq(check, MATRIX_ERROR);
  s21_remove_matrix(&null);
}
END_TEST

START_TEST(transpose_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
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
  int check = s21_transpose(&A, &C);
  int check1 = s21_eq_matrix(&C, &B);
  ck_assert_int_eq(check1, SUCCESS);
  ck_assert_int_eq(check, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(complements_1) {
  matrix_t A;
  matrix_t C;
  s21_create_matrix(2, 3, &A);
  A.matrix[0][0] = 1.24;
  A.matrix[0][1] = 23;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 111;
  A.matrix[1][1] = 0;
  A.matrix[1][2] = 2;
  int check = s21_calc_complements(&A, &C);
  ck_assert_int_eq(check, CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(complements_2) {
  matrix_t A;
  matrix_t C;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 1.0;
  int check = s21_calc_complements(&A, &C);
  double test = 1.0;
  ck_assert_int_eq(check, OK);
  ck_assert_int_eq(fabs(C.matrix[0][0] - test) < 1e-6, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(complements_3) {
  matrix_t A;
  matrix_t C;
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
  int check = s21_calc_complements(&A, &C);
  double test[] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
  for (int i = 0, k = 0; i < C.rows; i++)
    for (int j = 0; j < C.columns; j++) {
      ck_assert_int_eq(fabs(C.matrix[i][j] - test[k]) < 1e-6, 1);
      k++;
    }
  ck_assert_int_eq(check, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(complements_4) {
  matrix_t C;
  matrix_t null;
  null.columns = 0;
  null.rows = 0;
  null.matrix = NULL;
  int check = s21_calc_complements(&null, &C);
  ck_assert_int_eq(check, MATRIX_ERROR);
  s21_remove_matrix(&null);
}
END_TEST

START_TEST(complements_5) {
  matrix_t A;
  matrix_t C;
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
  int check = s21_calc_complements(&A, &C);
  double test[] = {24,  88,  -56, -80, 12, -112, -4, 56,
                   -60, -16, 20,  8,   12, 8,    44, -40};
  for (int i = 0, k = 0; i < C.rows; i++)
    for (int j = 0; j < C.columns; j++) {
      ck_assert_int_eq(fabs(C.matrix[i][j] - test[k]) < 1e-6, 1);
      k++;
    }
  ck_assert_int_eq(check, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(determinant_1) {
  matrix_t A;
  double det;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 12.3451;
  int check = s21_determinant(&A, &det);
  double test = 12.3451;
  ck_assert_int_eq(fabs(det - test) < 1e-6, 1);
  ck_assert_int_eq(check, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_2) {
  double det;
  matrix_t null;
  null.columns = 0;
  null.rows = 0;
  null.matrix = NULL;
  int check = s21_determinant(&null, &det);
  ck_assert_int_eq(check, MATRIX_ERROR);
  s21_remove_matrix(&null);
}
END_TEST

START_TEST(determinant_3) {
  matrix_t A;
  double det;
  s21_create_matrix(2, 3, &A);
  A.matrix[0][0] = 1.24;
  A.matrix[0][1] = 23;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 111;
  A.matrix[1][1] = 0;
  A.matrix[1][2] = 2;
  int check = s21_determinant(&A, &det);
  ck_assert_int_eq(check, CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_4) {
  matrix_t A;
  double det;
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
  int check = s21_determinant(&A, &det);
  ck_assert_int_eq(check, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_1) {
  matrix_t null;
  null.columns = 0;
  null.rows = 0;
  null.matrix = NULL;
  matrix_t C;
  int check = s21_inverse_matrix(&null, &C);
  ck_assert_int_eq(check, MATRIX_ERROR);
  s21_remove_matrix(&null);
}
END_TEST

START_TEST(inverse_2) {
  matrix_t A;
  matrix_t C;
  s21_create_matrix(1, 1, &A);
  int check = s21_inverse_matrix(&A, &C);
  ck_assert_int_eq(check, CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_3) {
  matrix_t A;
  matrix_t C;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 7.589;
  A.matrix[0][1] = 59.1;
  A.matrix[1][0] = 26.35;
  A.matrix[1][1] = 75.17;
  int check = s21_inverse_matrix(&A, &C);
  double test[] = {-0.076173, 0.059889, 0.026701, -0.00769};
  for (int i = 0, k = 0; i < C.rows; i++)
    for (int j = 0; j < C.columns; j++) {
      ck_assert_int_eq(fabs(C.matrix[i][j] - test[k]) < 1e-6, 1);
      k++;
    }
  ck_assert_int_eq(check, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("tests");
  SRunner *sr = srunner_create(s1);
  int nf;

  TCase *tc1_1 = tcase_create("tests");
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, create_matrix);
  tcase_add_test(tc1_1, eq_matrix);
  tcase_add_test(tc1_1, sum_matrix_2);
  tcase_add_test(tc1_1, sum_matrix_3);
  tcase_add_test(tc1_1, sum_matrix_4);
  tcase_add_test(tc1_1, sum_matrix_5);

  tcase_add_test(tc1_1, sub_matrix_1);
  tcase_add_test(tc1_1, sub_matrix_2);
  tcase_add_test(tc1_1, sub_matrix_3);

  tcase_add_test(tc1_1, mul_number_1);
  tcase_add_test(tc1_1, mul_number_2);
  tcase_add_test(tc1_1, mul_number_3);
  tcase_add_test(tc1_1, mul_matrix_1);
  tcase_add_test(tc1_1, mul_matrix_2);
  tcase_add_test(tc1_1, mul_matrix_3);
  tcase_add_test(tc1_1, mul_matrix_4);

  tcase_add_test(tc1_1, transpose_1);
  tcase_add_test(tc1_1, transpose_2);

  tcase_add_test(tc1_1, complements_1);
  tcase_add_test(tc1_1, complements_2);
  tcase_add_test(tc1_1, complements_3);
  tcase_add_test(tc1_1, complements_4);
  tcase_add_test(tc1_1, complements_5);

  tcase_add_test(tc1_1, determinant_1);
  tcase_add_test(tc1_1, determinant_2);
  tcase_add_test(tc1_1, determinant_3);
  tcase_add_test(tc1_1, determinant_4);

  tcase_add_test(tc1_1, inverse_1);
  tcase_add_test(tc1_1, inverse_2);
  tcase_add_test(tc1_1, inverse_3);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
