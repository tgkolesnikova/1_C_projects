#include "test.h"

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

int sign(int x) {
  if (x > 0) x = 1;
  if (x < 0) x = -1;
  return x;
}

//===================== sscanf test =============================
START_TEST(s21_sscanf_d_test) {
  ck_assert(s21_sscanf(str_sscanf_d[_i], format[0], &intsscanf) ==
            sscanf(str_sscanf_d[_i], format[0], &intsscanf));
}
END_TEST

START_TEST(s21_sscanf_i_test) {
  int i1 = 0, i2 = 0;
  s21_sscanf(str_sscanf_i[_i], format[1], &intsscanf);
  sscanf(str_sscanf_i[_i], format[1], &intsscanf);
  ck_assert_int_eq(i1, i2);
}
END_TEST

START_TEST(s21_sscanf_e_test) {
  ck_assert(s21_sscanf(str_sscanf_eEfgG[_i], format[2], &intsscanf) ==
            sscanf(str_sscanf_eEfgG[_i], format[2], &intsscanf));
}
END_TEST

START_TEST(s21_sscanf_E_test) {
  ck_assert(s21_sscanf(str_sscanf_eEfgG[_i], format[3], &intsscanf) ==
            sscanf(str_sscanf_eEfgG[_i], format[3], &intsscanf));
}
END_TEST

START_TEST(s21_sscanf_f_test) {
  ck_assert(s21_sscanf(str_sscanf_eEfgG[_i], format[4], &intsscanf) ==
            sscanf(str_sscanf_eEfgG[_i], format[4], &intsscanf));
}
END_TEST

START_TEST(s21_sscanf_g_test) {
  ck_assert(s21_sscanf(str_sscanf_eEfgG[_i], format[5], &intsscanf) ==
            sscanf(str_sscanf_eEfgG[_i], format[5], &intsscanf));
}
END_TEST

START_TEST(s21_sscanf_G_test) {
  ck_assert(s21_sscanf(str_sscanf_eEfgG[_i], format[6], &intsscanf) ==
            sscanf(str_sscanf_eEfgG[_i], format[6], &intsscanf));
}
END_TEST

START_TEST(s21_sscanf_o_test) {
  ck_assert(s21_sscanf(str_sscanf_o[_i], format[7], &intsscanf) ==
            sscanf(str_sscanf_o[_i], format[7], &intsscanf));
}
END_TEST

START_TEST(s21_sscanf_u_test) {
  ck_assert(s21_sscanf(str_sscanf_u[_i], format[8], &intsscanf) ==
            sscanf(str_sscanf_u[_i], format[8], &intsscanf));
}
END_TEST

START_TEST(s21_sscanf_x_test) {
  ck_assert(s21_sscanf(str_sscanf_x[_i], format[9], &intsscanf) ==
            sscanf(str_sscanf_x[_i], format[9], &intsscanf));
}
END_TEST

START_TEST(s21_sscanf_X_test) {
  ck_assert(s21_sscanf(str_sscanf_X[_i], format[10], &intsscanf) ==
            sscanf(str_sscanf_X[_i], format[10], &intsscanf));
}
END_TEST

START_TEST(s21_sscanf_p_test) {
  ck_assert(s21_sscanf(str_sscanf_p[_i], format[11], &intsscanf) ==
            sscanf(str_sscanf_p[_i], format[11], &intsscanf));
}
END_TEST

START_TEST(s21_sscanf_c_test) {
  char c1 = 0, c2 = 0;
  s21_sscanf(str_sscanf_c[_i], format2[0], &c1);
  sscanf(str_sscanf_c[_i], format2[0], &c2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(s21_sscanf_s_test) {
  ck_assert(s21_sscanf(str_sscanf_s[_i], format2[1], &charsscanf) ==
            sscanf(str_sscanf_s[_i], format2[1], &charsscanf));
}
END_TEST
// //================== end sscanf test =============================

START_TEST(s21_strlen_test) {
  ck_assert(s21_strlen(string1[_i]) == strlen(string1[_i]));
}
END_TEST

START_TEST(s21_memcmp_test) {
  ck_assert(s21_memcmp(string1[_i], string1[_i], _i) ==
            memcmp(string1[_i], string1[_i], _i));
}
END_TEST

START_TEST(s21_memchr_test) {
  ck_assert(s21_memchr(string1[_i], c[_i], 5) == memchr(string1[_i], c[_i], 5));
}
END_TEST

START_TEST(s21_strchr_test) {
  ck_assert(s21_strchr(string1[_i], c[_i]) == strchr(string1[_i], c[_i]));
}
END_TEST

START_TEST(s21_strpbrk_test) {
  ck_assert(s21_strpbrk(string1[_i], st) == strpbrk(string1[_i], st));
}
END_TEST

START_TEST(s21_strrchr_test) {
  ck_assert(s21_strrchr(string1[_i], c[_i]) == strrchr(string1[_i], c[_i]));
}
END_TEST

START_TEST(s21_strstr_test) {
  ck_assert(s21_strstr(string1[_i], string2[_i]) ==
            strstr(string1[_i], string2[_i]));
}
END_TEST

START_TEST(s21_memcpy_test) {
  ck_assert(s21_memcpy(s, (unsigned char *)string2[_i], 2) ==
            memcpy(s, (unsigned char *)string2[_i], 2));
}
END_TEST

START_TEST(s21_memmove_test) {
  ck_assert(s21_memmove(s, (unsigned char *)string2[_i], 2) ==
            memmove(s, (unsigned char *)string2[_i], 2));
}
END_TEST

START_TEST(s21_memset_test) {
  ck_assert(s21_memset(s, _i, 2) == memset(s, _i, 2));
}
END_TEST

START_TEST(s21_strcpy_test) {
  ck_assert(s21_strcpy((char *)s, string1[_i]) ==
            strcpy((char *)s, string1[_i]));
}
END_TEST

START_TEST(s21_strncpy_test) {
  ck_assert(s21_strncpy((char *)s, string1[_i], 4) ==
            strncpy((char *)s, string1[_i], 4));
}
END_TEST

START_TEST(s21_strspn_test) {
  ck_assert(s21_strspn(string1[_i], string2[_i]) ==
            strspn(string1[_i], string2[_i]));
}
END_TEST

START_TEST(s21_strcspn_test) {
  ck_assert(s21_strcspn(string1[_i], string2[_i]) ==
            strcspn(string1[_i], string2[_i]));
}
END_TEST

START_TEST(s21_strcmp_test) {
  ck_assert(sign(s21_strcmp(string1[_i], string2[_i])) ==
            sign(strcmp(string1[_i], string2[_i])));
}
END_TEST

START_TEST(s21_strncmp_test) {
  ck_assert(sign(s21_strncmp(string1[_i], string2[_i], 2)) ==
            sign(strncmp(string1[_i], string2[_i], 2)));
}
END_TEST

START_TEST(s21_strtok_test) {
  ck_assert(s21_strtok(string1[_i], c) == strtok(string1[_i], c));
}
END_TEST

START_TEST(s21_strerror_test) {
  char *s_tmp = s21_strerror(_i);
  char *tmp2 = strerror(_i);
  ck_assert_str_eq(s_tmp, tmp2);
  // free(s_tmp);
}
END_TEST

START_TEST(s21_strcat_test) {
  ck_assert(s21_strcat(string1[_i], string2[_i]) ==
            strcat(string1[_i], string2[_i]));
}
END_TEST

START_TEST(s21_strncat_test) {
  ck_assert(s21_strncat(string1[_i], string2[_i], 2) ==
            strncat(string1[_i], string2[_i], 2));
}
END_TEST

START_TEST(s21_to_upper_test) {
  char *s_tmp = s21_to_upper(string1[_i]);
  ck_assert_str_eq(s_tmp, array_test_to_upper[_i]);
  free(s_tmp);
}
END_TEST

START_TEST(s21_to_lower_test) {
  char *s_tmp = s21_to_lower(string1[_i]);
  ck_assert_str_eq(s_tmp, array_test_to_lower[_i]);
  free(s_tmp);
}
END_TEST

START_TEST(s21_insert_test) {
  char *s_tmp = s21_insert(string1_test_insert[_i], string2_test_insert[_i], 2);
  ck_assert_str_eq(s_tmp, array_test_insert[_i]);
  free(s_tmp);
}
END_TEST

START_TEST(s21_trim_test) {
  char *s_tmp = s21_trim(string1[_i], string2[_i]);
  ck_assert_str_eq(s_tmp, array_test_trim[_i]);
  if (s_tmp) free(s_tmp);
}
END_TEST

START_TEST(s21_sprintf_test) {
  char str[256], str2[256];
  char f[1024] =
      "%0-+ 9.9d%0-+ 9.9hd%0-+# 9.9ld % 0 - + 9.9u % 0 - + 9.9hu % 0 - + 9.9u "
      "| \"";
  s21_sprintf(str, f, 1, 1, 1, 1, 1, 1);
  sprintf(str2, f, 1, 1, 1, 1, 1, 1);
  ck_assert_str_eq(str, str2);
}
END_TEST

START_TEST(s21_sprintf_test2) {
  char str[256], str2[256];
  double a = 1.;
  long double b = 2.;
  unsigned int ci = 1;
  char f[1024] = "%9.9f%9.9Lf%9.9e%9.9Le%%%o%lo%ho%p%x%lx%hx%s%c%#u";
  s21_sprintf(str, f, a, b, a, b, 1, 1, 1, 3, 4, 5, 6, "123", 'H', ci, ci);
  sprintf(str2, f, a, b, a, b, 1, 1, 1, 3, 4, 5, 6, "123", 'H', ci, ci);
  ck_assert_str_eq(str, str2);
}
END_TEST
START_TEST(s21_sprintf_test3) {
  char str[256], str2[256];
  double a = 1., ci = 100000.;
  long double b = 2., d = 100000;

  char f[1024] = "%#10.10g%#10.10LG%3.3g%Lg%1.1g%1.1Lg";
  s21_sprintf(str, f, a, b, a, b, ci, d);
  sprintf(str2, f, a, b, a, b, ci, d);
  ck_assert_str_eq(str, str2);
}
END_TEST

START_TEST(s21_sscanf_test_full) {
  char str[1024] =
      "4214 512 215551 -12521. -421. -216666. 9919. 12412.1241. 123 321";
  int d = 0, d2 = 0;
  long int ld = 0, ld2 = 0;
  short int hd = 0, hd2 = 0;
  double lf = 0, lf2 = 0;
  long double Lf = 0, Lf2 = 0;
  float f = 0, f2 = 0;
  unsigned short int hud = 0, hud2 = 0;
  unsigned long int lud = 0, lud2 = 0;
  char ff[1024] = "%3d %3hd %5ld %7f %7lf %Lf %lu %hu";
  sscanf(str, ff, &d2, &hd2, &ld2, &f2, &lf2, &Lf2, &lud2, &hud2);
  s21_sscanf(str, ff, &d, &hd, &ld, &f, &lf, &Lf, &lud, &hud);
  ck_assert_int_eq(d, d2);
  ck_assert_int_eq(ld, ld2);
  ck_assert_int_eq(hd, hd2);
  ck_assert_uint_eq(f, f2);
  ck_assert_uint_eq(Lf, Lf2);
}
END_TEST

Suite *example_suite_create(void) {
  Suite *suite = suite_create("s21_string");
  TCase *tcase_core = tcase_create("Core");
  tcase_add_loop_test(tcase_core, s21_sscanf_d_test, 0, 10);
  tcase_add_loop_test(tcase_core, s21_sscanf_i_test, 0, 14);
  tcase_add_loop_test(tcase_core, s21_sscanf_e_test, 0, 10);
  tcase_add_loop_test(tcase_core, s21_sscanf_E_test, 0, 10);
  tcase_add_loop_test(tcase_core, s21_sscanf_f_test, 0, 10);
  tcase_add_loop_test(tcase_core, s21_sscanf_g_test, 0, 10);
  tcase_add_loop_test(tcase_core, s21_sscanf_G_test, 0, 10);
  tcase_add_loop_test(tcase_core, s21_sscanf_o_test, 0, 10);
  tcase_add_loop_test(tcase_core, s21_sscanf_u_test, 0, 10);
  tcase_add_loop_test(tcase_core, s21_sscanf_x_test, 0, 11);
  tcase_add_loop_test(tcase_core, s21_sscanf_X_test, 0, 11);
  tcase_add_loop_test(tcase_core, s21_sscanf_p_test, 0, 11);
  tcase_add_loop_test(tcase_core, s21_sscanf_c_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_sscanf_test_full, 0, 5);
  tcase_add_loop_test(tcase_core, s21_sscanf_c_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_sscanf_s_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_sprintf_test3, 0, 5);
  tcase_add_loop_test(tcase_core, s21_sprintf_test2, 0, 5);
  tcase_add_loop_test(tcase_core, s21_sprintf_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_to_upper_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_to_lower_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_insert_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_trim_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_strlen_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_memcmp_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_memchr_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_strchr_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_strpbrk_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_strrchr_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_strstr_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_memcpy_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_memmove_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_memset_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_strcpy_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_strncpy_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_strspn_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_strcspn_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_strcmp_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_strncmp_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_strtok_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_strcat_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_strncat_test, 0, 5);
  tcase_add_loop_test(tcase_core, s21_strerror_test, 0, 140);
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main(void) {
  Suite *suite = example_suite_create();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);

  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  if (failed_count != 0) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
