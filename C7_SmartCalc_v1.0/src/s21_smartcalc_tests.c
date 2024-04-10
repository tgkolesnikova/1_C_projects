#include <check.h>

#include "s21_smartcalc_v1.h"

START_TEST(VALIDATION) {
  char str[20] = "(((5 / 4)))";
  int err = validate_str(str);
  ck_assert_int_eq(err, 0);
  char str2[10] = "(5 / -4)";
  err = validate_str(str2);
  ck_assert_int_eq(err, 8);
  char str3[10] = "(5 / 4-)";
  err = validate_str(str3);
  ck_assert_int_eq(err, 8);
  char str4[10] = "(-5 / 4)";
  err = validate_str(str4);
  ck_assert_int_eq(err, 0);
  char str5[50] = "tg(5) + 4";
  err = validate_str(str5);
  ck_assert_int_eq(err, 7);
  char str6[50] = "(-(5 / 4))";
  err = validate_str(str6);
  ck_assert_int_eq(err, 0);
  char str7[50] = "(-(5 / 4)";
  err = validate_str(str7);
  ck_assert_int_eq(err, 9);
  char str8[50] = "(-(5 / 4)) - (-5 * 4)";
  err = validate_str(str8);
  ck_assert_int_eq(err, 0);
  char str9[50] = "(-(8/4))-(-5*4)";
  err = validate_str(str9);
  ck_assert_int_eq(err, 0);
  char str10[50] = "(3mod4)-(-5 mod 2) / ( 3 mod 3 )";
  err = validate_str(str10);
  ck_assert_int_eq(err, 0);
  char str11[100] = "4 * sin(5) / (cos(-3 ))/tan(5*asin(acos(432 - 23)))";
  err = validate_str(str11);
  ck_assert_int_eq(err, 0);
  char str12[50] = "atan(-4 * ln(42.3)/log(-3)^sqrt(+5))";
  err = validate_str(str12);
  ck_assert_int_eq(err, 0);
  char str13[50] = "(2 + 3 + mod 4";
  err = validate_str(str13);
  ck_assert_int_eq(err, 8);
  char str14[50] = "6,432 + 5,666 + 10,1";
  err = validate_str(str14);
  ck_assert_int_eq(err, 0);
  char str15[50] = "6,432 + 5,666 - () + 10,1";
  err = validate_str(str15);
  ck_assert_int_eq(err, 8);
  char str16[50] = "() - 6,432 + 5,666 + 10,1";
  err = validate_str(str16);
  ck_assert_int_eq(err, 6);
  char str17[50] = "sin() - 6,432 + 5,666 + 10,1";
  err = validate_str(str17);
  ck_assert_int_eq(err, 6);
  char str18[50] = "6,432 + 5,666 + sin() - 10,1";
  err = validate_str(str18);
  ck_assert_int_eq(err, 6);
}
END_TEST

START_TEST(UNARY_PLUS) {
  char str[50] = "(+6.432) + (5.666 + (+10.1)) + ((+5.34) + 4.54)";
  double result;
  int error = smart_calc(str, &result);
  ck_assert_int_eq(error, 0);
  double second = 32.078;
  ck_assert(fabsl(result - second) < 1e-9);

  char str2[50] = "(+(+6.432+5.666))+10.1+(+(5.34+4.54))";
  second = 32.078;
  error = smart_calc(str2, &result);
  ck_assert_int_eq(error, 0);
  ck_assert(fabsl(result - second) < 1e-9);
}
END_TEST

START_TEST(UNARY_MINUS) {
  char str[60] = "(-6.432) - (5.666 - (-10.1)) - (-(-5.34 - (-4.54)))";
  double result;
  int error = smart_calc(str, &result);
  ck_assert_int_eq(error, 0);
  double second = -22.998;
  ck_assert(fabsl(result - second) < 1e-9);

  char str2[50] = "(-(-6.432-5.666))-10.1* (-(5.34-4.54))";
  second = 20.178;
  error = smart_calc(str2, &result);
  ck_assert_int_eq(error, 0);
  ck_assert(fabsl(result - second) < 1e-9);
}
END_TEST

START_TEST(ADD) {
  char str[50] = "6.432 + 5.666 + 10.1 * 5.34 + 4.54";
  double result;
  int error = smart_calc(str, &result);
  ck_assert_int_eq(error, 0);
  double second = 70.572;
  ck_assert(fabsl(result - second) < 1e-9);

  char str2[50] = "(6.432+5.666)+10.1*(5.34+4.54)";
  second = 111.886;
  error = smart_calc(str2, &result);
  ck_assert_int_eq(error, 0);
  ck_assert(fabsl(result - second) < 1e-9);
}
END_TEST

START_TEST(SUB) {
  char str[50] = "6.432 - 5.666 - 10.1 * 5.34 - 4.54";
  double result;
  int error = smart_calc(str, &result);
  ck_assert_int_eq(error, 0);
  double second = -57.708;
  ck_assert(fabsl(result - second) < 1e-9);

  char str2[50] = "(6.432-5.666)-10.1*(5.34-4.54)";
  second = -7.314;
  error = smart_calc(str2, &result);
  ck_assert_int_eq(error, 0);
  ck_assert(fabsl(result - second) < 1e-9);
}
END_TEST

START_TEST(MULT) {
  char str[60] = "6.432 * (5.666 * 10.1) * (5.34 * 4.54)";
  double result;
  int error = smart_calc(str, &result);
  ck_assert_int_eq(error, 0);
  double second = 8923.62044005632;
  ck_assert(fabsl(result - second) < 1e-9);

  char str2[50] = "(-(6.432*5.666))*10.1* (-(5.34*4.54))";
  second = 8923.62044005632;
  error = smart_calc(str2, &result);
  ck_assert_int_eq(error, 0);
  ck_assert(fabsl(result - second) < 1e-9);

  char str3[50] = "(-(6.432*(-5.666)))*10.1* (-(-(5.34*4.54)))";
  second = 8923.62044005632;
  error = smart_calc(str3, &result);
  ck_assert_int_eq(error, 0);
  ck_assert(fabsl(result - second) < 1e-9);
}
END_TEST

START_TEST(DIV) {
  char str[60] = "6.432 / (5.666 / 10.1) / (5.34 / 4.54)";
  double result;
  int error = smart_calc(str, &result);
  ck_assert_int_eq(error, 0);
  double second = 9.7477736310021933;
  ck_assert(fabsl(result - second) < 1e-9);

  char str2[50] = "(-(6.432/5.666))/10.1/ (-(5.34/4.54))";
  second = 0.0955570398098441;
  error = smart_calc(str2, &result);
  ck_assert_int_eq(error, 0);
  ck_assert(fabsl(result - second) < 1e-9);

  char str3[50] = "(-(6.432/(-5.666)))/10.1/ (-(-(5.34/4.54)))";
  second = 0.0955570398098441;
  error = smart_calc(str3, &result);
  ck_assert_int_eq(error, 0);
  ck_assert(fabsl(result - second) < 1e-9);
}
END_TEST

START_TEST(MOD) {
  char str[60] = "123 mod 12 mod 5";
  double result;
  int error = smart_calc(str, &result);
  ck_assert_int_eq(error, 0);
  double second = fmod(fmod(123, 12), 5);
  ck_assert(fabsl(result - second) < 1e-9);

  char str2[50] = "6.432 mod (5.666 mod 10.1) mod (5.34 mod 4.54)";
  error = smart_calc(str2, &result);
  ck_assert_int_eq(error, 0);
  second = fmod(fmod(6.432, fmod(5.666, 10.1)), fmod(5.34, 4.54));
  ck_assert(fabsl(result - second) < 1e-9);
}
END_TEST

START_TEST(POW) {
  char str[60] = "2 ^(8^((-2) + 2)) ^ 2";
  double result;
  int error = smart_calc(str, &result);
  ck_assert_int_eq(error, 0);
  double second = 4;
  ck_assert(fabsl(result - second) < 1e-9);

  char str2[50] = "2 ^ 2 ^ 3";
  second = 64;
  error = smart_calc(str2, &result);
  ck_assert_int_eq(error, 0);
  ck_assert(fabsl(result - second) < 1e-9);
}
END_TEST

START_TEST(SIN) {
  char str[60] = "sin(sin(5 - 2) * sin(sin(5)))";
  double result;
  int error = smart_calc(str, &result);
  ck_assert_int_eq(error, 0);
  double second = sin(sin(5 - 2) * sin(sin(5)));
  ck_assert(fabsl(result - second) < 1e-9);
}
END_TEST

START_TEST(COS) {
  char str[60] = "cos(cos(5 - 2) * cos(cos(5)))";
  double result;
  int error = smart_calc(str, &result);
  ck_assert_int_eq(error, 0);
  double second = cos(cos(5 - 2) * cos(cos(5)));
  ck_assert(fabsl(result - second) < 1e-9);
}
END_TEST

START_TEST(TAN) {
  char str[60] = "tan(tan(5 - 2) * tan(tan(5)))";
  double result;
  int error = smart_calc(str, &result);
  ck_assert_int_eq(error, 0);
  double second = tan(tan(5 - 2) * tan(tan(5)));
  ck_assert(fabsl(result - second) < 1e-9);
}
END_TEST

START_TEST(ASIN) {
  char str[60] = "asin(0.2)";
  double result;
  int error = smart_calc(str, &result);
  ck_assert_int_eq(error, 0);
  double second = asin(0.2);
  ck_assert(fabsl(result - second) < 1e-9);
}
END_TEST

START_TEST(ACOS) {
  char str[60] = "acos(0.003)";
  double result;
  int error = smart_calc(str, &result);
  ck_assert_int_eq(error, 0);
  double second = acos(0.003);
  ck_assert(fabsl(result - second) < 1e-9);
}
END_TEST

START_TEST(ATAN) {
  char str[60] = "atan(atan(5 - 2) * atan(atan(5)))";
  double result;
  int error = smart_calc(str, &result);
  ck_assert_int_eq(error, 0);
  double second = atan(atan(5 - 2) * atan(atan(5)));
  ck_assert(fabsl(result - second) < 1e-9);
}
END_TEST

START_TEST(LN) {
  char str[60] = "ln(0.003)";
  double result;
  int error = smart_calc(str, &result);
  ck_assert_int_eq(error, 0);
  double second = log(0.003);
  ck_assert(fabsl(result - second) < 1e-9);
}
END_TEST

START_TEST(LOG) {
  char str[60] = "log(0.003)";
  double result;
  int error = smart_calc(str, &result);
  ck_assert_int_eq(error, 0);
  double second = log10(0.003);
  ck_assert(fabsl(result - second) < 1e-9);
}
END_TEST

START_TEST(SQRT) {
  char str[60] = "sqrt(9)";
  double result;
  int error = smart_calc(str, &result);
  ck_assert_int_eq(error, 0);
  double second = sqrt(9);
  ck_assert(fabsl(result - second) < 1e-9);

  char str2[60] = "sqrt(2)";
  error = smart_calc(str2, &result);
  ck_assert_int_eq(error, 0);
  second = sqrt(2);
  ck_assert(fabsl(result - second) < 1e-9);
}
END_TEST

START_TEST(X) {
  char str[60] = "2 + 3 * x";
  double x = 6;
  double result = x;
  int error = smart_calc(str, &result);
  ck_assert_int_eq(error, 0);
  double second = 2 + 3 * x;
  ck_assert(fabsl(result - second) < 1e-9);

  char str2[60] = "sin(x) * sin(x) - (cos(x)) ^ 2";
  x = 1;
  result = x;
  error = smart_calc(str2, &result);
  ck_assert_int_eq(error, 0);
  second = sin(x) * sin(x) - pow(cos(x), 2);
  ck_assert(fabsl(result - second) < 1e-9);
}
END_TEST

Suite *s21_calc_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_smart_calc");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, VALIDATION);
  tcase_add_test(tc_core, UNARY_PLUS);
  tcase_add_test(tc_core, UNARY_MINUS);
  tcase_add_test(tc_core, ADD);
  tcase_add_test(tc_core, SUB);
  tcase_add_test(tc_core, MULT);
  tcase_add_test(tc_core, DIV);
  tcase_add_test(tc_core, MOD);
  tcase_add_test(tc_core, POW);
  tcase_add_test(tc_core, SIN);
  tcase_add_test(tc_core, COS);
  tcase_add_test(tc_core, TAN);
  tcase_add_test(tc_core, ASIN);
  tcase_add_test(tc_core, ACOS);
  tcase_add_test(tc_core, ATAN);
  tcase_add_test(tc_core, LN);
  tcase_add_test(tc_core, LOG);
  tcase_add_test(tc_core, SQRT);
  tcase_add_test(tc_core, X);

  suite_add_tcase(s, tc_core);
  return s;
}

int main() {
  int count_fail = 0;
  Suite *s;
  SRunner *sr;

  s = s21_calc_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  count_fail = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (count_fail == 0) ? 0 : 1;
}