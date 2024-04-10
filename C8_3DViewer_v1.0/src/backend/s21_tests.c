#include <check.h>

#include "3D_Viewer_v1_0.h"

START_TEST(parser0) {
  Obj_data model = {0, 0, NULL, NULL, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
  int err = read_obj_file(&model, "./backend/tests/test0.obj");
  ck_assert_int_eq(err, ERROR_FILE_OPEN);
  delete_data(&model);
}
END_TEST

START_TEST(parser1) {
  Obj_data model = {0, 0, NULL, NULL, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
  int err = read_obj_file(&model, "./backend/tests/test1.obj");
  ck_assert_int_eq(err, OK);
  int res_numV = 8, res_numF = 12;
  ck_assert_int_eq(model.num_V, res_numV);
  ck_assert_int_eq(model.num_F, res_numF);
  double res_Vmin[] = {0.0, 0.0, 0.0};
  double res_Vmax[] = {1.0, 1.0, 1.0};
  for (int i = 0; i < 3; ++i) {
    ck_assert(fabs(model.V_min[i] - res_Vmin[i]) < EPS);
    ck_assert(fabs(model.V_max[i] - res_Vmax[i]) < EPS);
  }
  double res_V[8 * 3] = {-1.0, -1.0, -1.0, -1.0, -1.0, 1.0,  -1.0, 1.0,
                         -1.0, -1.0, 1.0,  1.0,  1.0,  -1.0, -1.0, 1.0,
                         -1.0, 1.0,  1.0,  1.0,  -1.0, 1.0,  1.0,  1.0};
  for (int i = 0; i < res_numV * 3; ++i) {
    ck_assert(fabs(model.V[i] - res_V[i]) < EPS);
  }
  int res_F[12][3] = {{0, 6, 4}, {0, 2, 6}, {0, 3, 2}, {0, 1, 3},
                      {2, 7, 6}, {2, 3, 7}, {4, 6, 7}, {4, 7, 5},
                      {0, 4, 5}, {0, 5, 1}, {1, 5, 7}, {1, 7, 3}};
  for (int i = 0; i < res_numF; ++i) {
    for (int j = 0; j < model.F[i].num_vertices; ++j)
      ck_assert_int_eq(model.F[i].vertices_on_polygon[j], res_F[i][j]);
  }
  delete_data(&model);
}
END_TEST

START_TEST(parser2) {
  Obj_data model = {0, 0, NULL, NULL, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
  int err = read_obj_file(&model, "./backend/tests/test2.obj");
  ck_assert_int_eq(err, ERROR_FILE_STRUCT);
  delete_data(&model);
}
END_TEST

START_TEST(parser3) {
  Obj_data model = {0, 0, NULL, NULL, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
  int err = read_obj_file(&model, "./backend/tests/test3.obj");
  ck_assert_int_eq(err, ERROR_FILE_STRUCT);
  delete_data(&model);
}
END_TEST

START_TEST(parser4) {
  Obj_data model = {0, 0, NULL, NULL, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
  int err = read_obj_file(&model, "./backend/tests/test4.obj");
  ck_assert_int_eq(err, ERROR_FILE_STRUCT);
  delete_data(&model);
}
END_TEST

START_TEST(parser5) {
  Obj_data *model = NULL;
  int err = read_obj_file(model, "./backend/tests/test5.obj");
  ck_assert_int_eq(err, ERROR_MEMORY);
  delete_data(model);
}
END_TEST

START_TEST(parser6) {
  Obj_data model = {0, 0, NULL, NULL, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
  int err = read_obj_file(&model, "./backend/tests/test6.obj");
  ck_assert_int_eq(err, ERROR_FILE_STRUCT);
  delete_data(&model);
}
END_TEST

START_TEST(parser7) {
  Obj_data model = {0, 0, NULL, NULL, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
  int err = read_obj_file(&model, "./backend/tests/test7.obj");
  ck_assert_int_eq(err, ERROR_FILE_STRUCT);
  delete_data(&model);
}
END_TEST

START_TEST(parser8) {
  Obj_data model = {0, 0, NULL, NULL, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
  int err = read_obj_file(&model, "./backend/tests/test8.obj");
  ck_assert_int_eq(err, OK);
  int res_numV = 8, res_numF = 12;
  ck_assert_int_eq(model.num_V, res_numV);
  ck_assert_int_eq(model.num_F, res_numF);
  double res_Vmin[] = {0.0, 0.0, 0.0};
  double res_Vmax[] = {1.0, 1.0, 1.0};
  for (int i = 0; i < 3; ++i) {
    ck_assert(fabs(model.V_min[i] - res_Vmin[i]) < EPS);
    ck_assert(fabs(model.V_max[i] - res_Vmax[i]) < EPS);
  }
  double res_V[8 * 3] = {1.0,  1.0,  1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
                         1.0,  -1.0, 1.0, -1.0, -1.0, 1.0,  1.0,  1.0,
                         -1.0, -1.0, 1.0, -1.0, 1.0,  1.0,  1.0,  -1.0};
  for (int i = 0; i < res_numV * 3; ++i) {
    ck_assert(fabs(model.V[i] - res_V[i]) < EPS);
  }
  int res_F[12][3] = {{1, 7, 5}, {1, 3, 7}, {1, 4, 3}, {1, 2, 4},
                      {3, 0, 7}, {3, 4, 0}, {5, 7, 0}, {5, 0, 6},
                      {1, 5, 6}, {1, 6, 2}, {2, 6, 1}, {2, 0, 4}};
  for (int i = 0; i < res_numF; ++i) {
    for (int j = 0; j < model.F[i].num_vertices; ++j)
      ck_assert_int_eq(model.F[i].vertices_on_polygon[j], res_F[i][j]);
  }
  delete_data(&model);
}
END_TEST

START_TEST(transform_move_xyz) {
  Obj_data model = {0, 0, NULL, NULL, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
  int err = read_obj_file(&model, "./backend/tests/test9.obj");
  ck_assert_int_eq(err, OK);
  int res_numV = 8;
  ck_assert_int_eq(model.num_V, res_numV);

  double dX = 1.2;
  move_x(&model, dX);
  // double res_V[8 * 3] = {1.0,  1.0,  1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
  //                        1.0,  -1.0, 1.0, -1.0, -1.0, 1.0,  1.0,  1.0,
  //                        -1.0, -1.0, 1.0, -1.0, 1.0,  1.0,  1.0,  -1.0};
  // for (int i = 0; i < res_numV * 3; i += 3) {
  //   res_V[i] += dX;
  // }
  double res1_V[8 * 3] = {2.2, 1, 1, 0.2, -1, -1, 0.2, -1, 1, 0.2, 1, -1,
                          0.2, 1, 1, 2.2, -1, -1, 2.2, -1, 1, 2.2, 1, -1};
  for (int i = 0; i < res_numV * 3; ++i) {
    ck_assert(fabs(model.V[i] - res1_V[i]) < EPS);
  }

  dX = -5.7;
  move_x(&model, dX);
  double res2_V[8 * 3] = {-3.5, 1, 1, -5.5, -1, -1, -5.5, -1, 1, -5.5, 1, -1,
                          -5.5, 1, 1, -3.5, -1, -1, -3.5, -1, 1, -3.5, 1, -1};
  for (int i = 0; i < res_numV * 3; ++i) {
    ck_assert(fabs(model.V[i] - res2_V[i]) < EPS);
  }

  double dY = 1.2;
  move_y(&model, dY);
  double res3_V[8 * 3] = {-3.5, 2.2,  1,    -5.5, 0.2,  -1,   -5.5, 0.2,
                          1,    -5.5, 2.2,  -1,   -5.5, 2.2,  1,    -3.5,
                          0.2,  -1,   -3.5, 0.2,  1,    -3.5, 2.2,  -1};
  for (int i = 0; i < res_numV * 3; ++i) {
    ck_assert(fabs(model.V[i] - res3_V[i]) < EPS);
  }

  dY = -0.75;
  move_y(&model, dY);
  double res4_V[8 * 3] = {-3.5,  1.45, 1,    -5.5,  -0.55, -1,   -5.5, -0.55,
                          1,     -5.5, 1.45, -1,    -5.5,  1.45, 1,    -3.5,
                          -0.55, -1,   -3.5, -0.55, 1,     -3.5, 1.45, -1};
  for (int i = 0; i < res_numV * 3; ++i) {
    ck_assert(fabs(model.V[i] - res4_V[i]) < EPS);
  }

  double dZ = 11.4;
  move_z(&model, dZ);
  double res5_V[8 * 3] = {-3.5,  1.45, 12.4, -5.5,  -0.55, 10.4, -5.5, -0.55,
                          12.4,  -5.5, 1.45, 10.4,  -5.5,  1.45, 12.4, -3.5,
                          -0.55, 10.4, -3.5, -0.55, 12.4,  -3.5, 1.45, 10.4};
  for (int i = 0; i < res_numV * 3; ++i) {
    ck_assert(fabs(model.V[i] - res5_V[i]) < EPS);
  }

  dZ = -0.22;
  move_z(&model, dZ);
  double res6_V[8 * 3] = {-3.5, 1.45,  12.18, -5.5, -0.55, 10.18,
                          -5.5, -0.55, 12.18, -5.5, 1.45,  10.18,
                          -5.5, 1.45,  12.18, -3.5, -0.55, 10.18,
                          -3.5, -0.55, 12.18, -3.5, 1.45,  10.18};
  for (int i = 0; i < res_numV * 3; ++i) {
    ck_assert(fabs(model.V[i] - res6_V[i]) < EPS);
  }

  delete_data(&model);
}
END_TEST

START_TEST(transform_scale_up_down) {
  Obj_data model = {0, 0, NULL, NULL, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
  int err = read_obj_file(&model, "./backend/tests/test9.obj");
  ck_assert_int_eq(err, OK);
  int res_numV = 8;
  ck_assert_int_eq(model.num_V, res_numV);

  double coeff = 3.17;
  scale(&model, coeff);
  double res1_V[8 * 3] = {3.17,  3.17,  3.17, -3.17, -3.17, -3.17,
                          -3.17, -3.17, 3.17, -3.17, 3.17,  -3.17,
                          -3.17, 3.17,  3.17, 3.17,  -3.17, -3.17,
                          3.17,  -3.17, 3.17, 3.17,  3.17,  -3.17};
  for (int i = 0; i < res_numV * 3; ++i) {
    ck_assert(fabs(model.V[i] - res1_V[i]) < EPS);
  }

  coeff = 0.17;
  scale(&model, coeff);
  double res2_V[8 * 3] = {0.5389,  0.5389,  0.5389, -0.5389, -0.5389, -0.5389,
                          -0.5389, -0.5389, 0.5389, -0.5389, 0.5389,  -0.5389,
                          -0.5389, 0.5389,  0.5389, 0.5389,  -0.5389, -0.5389,
                          0.5389,  -0.5389, 0.5389, 0.5389,  0.5389,  -0.5389};
  for (int i = 0; i < res_numV * 3; ++i) {
    ck_assert(fabs(model.V[i] - res2_V[i]) < EPS);
  }

  delete_data(&model);
}
END_TEST

START_TEST(transform_rotate_xyz) {
  Obj_data model = {0, 0, NULL, NULL, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
  int err = read_obj_file(&model, "./backend/tests/test9.obj");
  ck_assert_int_eq(err, OK);
  int res_numV = 8;
  ck_assert_int_eq(model.num_V, res_numV);

  double alpha = 60;
  rotate_x(&model, alpha);
  double res1_V[8 * 3] = {1,  -0.366025, 1.366025,  -1, 0.366025, -1.366025,
                          -1, -1.366025, -0.366025, -1, 1.366025, 0.366025,
                          -1, -0.366025, 1.366025,  1,  0.366025, -1.366025,
                          1,  -1.366025, -0.366025, 1,  1.366025, 0.366025};
  for (int i = 0; i < res_numV * 3; ++i) {
    ck_assert(fabs(model.V[i] - res1_V[i]) < EPS);
  }

  alpha = 127;
  rotate_y(&model, alpha);
  double res2_V[8 * 3] = {0.489141,  -0.366025, -1.62073,  -0.489141, 0.366025,
                          1.62073,   0.309494,  -1.366025, 1.018915,  0.894136,
                          1.366025,  0.578356,  1.692771,  -0.366025, -0.023459,
                          -1.692771, 0.366025,  0.023459,  -0.894136, -1.366025,
                          -0.578356, -0.309494, 1.366025,  -1.018915};
  for (int i = 0; i < res_numV * 3; ++i) {
    ck_assert(fabs(model.V[i] - res2_V[i]) < EPS);
  }

  alpha = 13;
  rotate_z(&model, alpha);
  double res3_V[8 * 3] = {0.558943,  -0.246611, -1.62073,  -0.558943, 0.246611,
                          1.62073,   0.608851,  -1.261393, 1.018915,  0.56393,
                          1.532151,  0.578356,  1.731724,  0.024147,  -0.023459,
                          -1.731724, -0.024147, 0.023459,  -0.56393,  -1.532151,
                          -0.578356, -0.608851, 1.261393,  -1.018915};
  for (int i = 0; i < res_numV * 3; ++i) {
    ck_assert(fabs(model.V[i] - res3_V[i]) < EPS);
  }

  delete_data(&model);
}
END_TEST

START_TEST(no_transform) {
  Obj_data model = {0, 0, NULL, NULL, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
  int err = read_obj_file(&model, "./backend/tests/test10.obj");
  ck_assert_int_eq(err, ERROR_FILE_STRUCT);
  int res_numV = 8;
  ck_assert_int_eq(model.num_V, res_numV);
  // double *res1_V = NULL;
  // ck_assert_ptr_eq(model.V, res1_V);

  double alpha = 60;
  rotate_x(&model, alpha);
  double *res1_V = NULL;
  ck_assert_ptr_eq(model.V, res1_V);

  alpha = 127;
  rotate_y(&model, alpha);
  double *res2_V = NULL;
  ck_assert_ptr_eq(model.V, res2_V);

  alpha = 13;
  rotate_z(&model, alpha);
  double *res3_V = NULL;
  ck_assert_ptr_eq(model.V, res3_V);

  double coeff = 0.17;
  scale(&model, coeff);
  double *res4_V = NULL;
  ck_assert_ptr_eq(model.V, res4_V);

  double dZ = 11.4;
  move_z(&model, dZ);
  double *res5_V = NULL;
  ck_assert_ptr_eq(model.V, res5_V);

  double dY = -0.75;
  move_y(&model, dY);
  double *res6_V = NULL;
  ck_assert_ptr_eq(model.V, res6_V);

  double dX = 1.2;
  move_x(&model, dX);
  double *res7_V = NULL;
  ck_assert_ptr_eq(model.V, res7_V);

  delete_data(&model);
}
END_TEST

///////////////////////////////////////////////////
Suite *s21_3DViewer_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("3D_Viewer_v1_0");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, parser0);
  tcase_add_test(tc_core, parser1);
  tcase_add_test(tc_core, parser2);
  tcase_add_test(tc_core, parser3);
  tcase_add_test(tc_core, parser4);
  tcase_add_test(tc_core, parser5);
  tcase_add_test(tc_core, parser6);
  tcase_add_test(tc_core, parser7);
  tcase_add_test(tc_core, parser8);
  tcase_add_test(tc_core, transform_move_xyz);
  tcase_add_test(tc_core, transform_scale_up_down);
  tcase_add_test(tc_core, transform_rotate_xyz);
  tcase_add_test(tc_core, no_transform);
  suite_add_tcase(s, tc_core);
  return s;
}

int main() {
  int count_fail = 0;
  Suite *s;
  SRunner *sr;

  s = s21_3DViewer_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  count_fail = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (count_fail == 0) ? 0 : 1;
}
