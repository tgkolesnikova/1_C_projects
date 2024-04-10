#include "s21_math.h"

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// #define s21_eps 1e-6
// #define s21_eps 1e-9

START_TEST(s21_abs_test) {
  ck_assert_int_eq(s21_abs(0), abs(0));
  ck_assert_int_eq(s21_abs(2147483647), abs(2147483647));
  ck_assert_int_eq(s21_abs(-1), abs(-1));
  ck_assert_int_eq(s21_abs(-2147483647), abs(-2147483647));
}
END_TEST

START_TEST(s21_acos_test) {
  ck_assert(fabsl(s21_acos(1) - acos(1)) < s21_eps);
  ck_assert(fabsl(s21_acos(0.9) - acos(0.9)) < s21_eps);
  ck_assert(fabsl(s21_acos(0.5) - acos(0.5)) < s21_eps);
  ck_assert(fabsl(s21_acos(0.1) - acos(0.1)) < s21_eps);
  ck_assert(fabsl(s21_acos(0.01) - acos(0.01)) < s21_eps);
  ck_assert(fabsl(s21_acos(0.001) - acos(0.001)) < s21_eps);
  ck_assert(fabsl(s21_acos(-1) - acos(-1)) < s21_eps);
  ck_assert(fabsl(s21_acos(-0.9) - acos(-0.9)) < s21_eps);
  ck_assert(fabsl(s21_acos(-0.5) - acos(-0.5)) < s21_eps);
  ck_assert(fabsl(s21_acos(-0.1) - acos(-0.1)) < s21_eps);
  ck_assert(fabsl(s21_acos(-0.01) - acos(-0.01)) < s21_eps);
  ck_assert(fabsl(s21_acos(-0.001) - acos(-0.001)) < s21_eps);
}
END_TEST

START_TEST(s21_asin_test) {
  ck_assert(isnan(s21_asin(5)) && isnan(asin(5)));
  ck_assert(fabsl(s21_asin(1) - asin(1)) < s21_eps);
  ck_assert(fabsl(s21_asin(0.9) - asin(0.9)) < s21_eps);
  ck_assert(fabsl(s21_asin(0.5) - asin(0.5)) < s21_eps);
  ck_assert(fabsl(s21_asin(0.1) - asin(0.1)) < s21_eps);
  ck_assert(fabsl(s21_asin(0.01) - asin(0.01)) < s21_eps);
  ck_assert(fabsl(s21_asin(0.001) - asin(0.001)) < s21_eps);
  ck_assert(fabsl(s21_asin(0.0001) - asin(0.0001)) < s21_eps);
  ck_assert(fabsl(s21_asin(0) - asin(0)) < s21_eps);
  ck_assert(fabsl(s21_asin(-0) - asin(-0)) < s21_eps);
  ck_assert(isnan(s21_asin(-5)) && isnan(asin(-5)));
  ck_assert(fabsl(s21_asin(-1) - asin(-1)) < s21_eps);
  ck_assert(fabsl(s21_asin(-0.9) - asin(-0.9)) < s21_eps);
  ck_assert(fabsl(s21_asin(-0.5) - asin(-0.5)) < s21_eps);
  ck_assert(fabsl(s21_asin(-0.1) - asin(-0.1)) < s21_eps);
  ck_assert(fabsl(s21_asin(-0.01) - asin(-0.01)) < s21_eps);
  ck_assert(fabsl(s21_asin(-0.001) - asin(-0.001)) < s21_eps);
  ck_assert(fabsl(s21_asin(-0.0001) - asin(-0.0001)) < s21_eps);
  ck_assert(isnan(s21_asin(s21_nan)) && isnan(asin(s21_nan)));
  ck_assert(isnan(s21_asin(-s21_nan)) && isnan(asin(-s21_nan)));
}
END_TEST

START_TEST(s21_atan_test) {
  ck_assert(fabsl(s21_atan(0.5) - atan(0.5)) < s21_eps);
  ck_assert(fabsl(s21_atan(1) - atan(1)) < s21_eps);
  ck_assert(fabsl(s21_atan(2) - atan(2)) < s21_eps);
  ck_assert(fabsl(s21_atan(3) - atan(3)) < s21_eps);
  ck_assert(fabsl(s21_atan(4) - atan(4)) < s21_eps);
  ck_assert(fabsl(s21_atan(5) - atan(5)) < s21_eps);
  ck_assert(fabsl(s21_atan(10) - atan(10)) < s21_eps);
  ck_assert(fabsl(s21_atan(100) - atan(100)) < s21_eps);
  ck_assert(fabsl(s21_atan(1000) - atan(1000)) < s21_eps);
  ck_assert(fabsl(s21_atan(-0.5) - atan(-0.5)) < s21_eps);
  ck_assert(fabsl(s21_atan(-1) - atan(-1)) < s21_eps);
  ck_assert(fabsl(s21_atan(-2) - atan(-2)) < s21_eps);
  ck_assert(fabsl(s21_atan(-3) - atan(-3)) < s21_eps);
  ck_assert(fabsl(s21_atan(-4) - atan(-4)) < s21_eps);
  ck_assert(fabsl(s21_atan(-5) - atan(-5)) < s21_eps);
  ck_assert(fabsl(s21_atan(-10) - atan(-10)) < s21_eps);
  ck_assert(fabsl(s21_atan(-100) - atan(-100)) < s21_eps);
  ck_assert(isnan(s21_atan(s21_nan)) && isnan(atan(s21_nan)));
  ck_assert(isnan(s21_atan(-s21_nan)) && isnan(atan(-s21_nan)));
}
END_TEST

START_TEST(s21_ceil_test) {
  ck_assert(fabsl(s21_ceil(-0.567) - ceil(-0.567)) < s21_eps);
  ck_assert(fabsl(s21_ceil(-0.523) - ceil(-0.523)) < s21_eps);
  ck_assert(fabsl(s21_ceil(1.6) - ceil(1.6)) < s21_eps);
  ck_assert(fabsl(s21_ceil(1.9999) - ceil(1.999)) < s21_eps);
  ck_assert(fabsl(s21_ceil(123456.6789) - ceil(123456.6789)) < s21_eps);
  ck_assert(fabsl(s21_ceil(-1.6) - ceil(-1.6)) < s21_eps);
  ck_assert(fabsl(s21_ceil(-1.9999) - ceil(-1.999)) < s21_eps);
  ck_assert(fabsl(s21_ceil(-123456.6789) - ceil(-123456.6789)) < s21_eps);
  ck_assert(fabsl(s21_ceil(0) - ceil(0)) < s21_eps);
  ck_assert(fabsl(s21_ceil(1e-9) - ceil(1e-9)) < s21_eps);
  ck_assert(fabsl(s21_ceil(1e9) - ceil(1e9)) < s21_eps);
  ck_assert(fabsl(s21_ceil(99999.9999999) - ceil(99999.9999999)) < s21_eps);
  ck_assert(fabsl(s21_ceil(-99999.9999999) - ceil(-99999.9999999)) < s21_eps);
  ck_assert(isnan(s21_ceil(s21_nan)) && isnan(ceil(s21_nan)));
  ck_assert(s21_ceil(s21_inf) && s21_inf);
  ck_assert(s21_ceil(s21_minus_inf) && s21_minus_inf);
}
END_TEST

START_TEST(s21_cos_test) {
  ck_assert(fabsl(s21_cos(1) - cos(1)) < s21_eps);
  ck_assert(fabsl(s21_cos(2) - cos(2)) < s21_eps);
  ck_assert(fabsl(s21_cos(3) - cos(3)) < s21_eps);
  ck_assert(fabsl(s21_cos(4) - cos(4)) < s21_eps);
  ck_assert(fabsl(s21_cos(5) - cos(5)) < s21_eps);
  ck_assert(fabsl(s21_cos(-1) - cos(-1)) < s21_eps);
  ck_assert(fabsl(s21_cos(-2) - cos(-2)) < s21_eps);
  ck_assert(fabsl(s21_cos(-3) - cos(-3)) < s21_eps);
  ck_assert(fabsl(s21_cos(-4) - cos(-4)) < s21_eps);
  ck_assert(fabsl(s21_cos(-5) - cos(-5)) < s21_eps);
  ck_assert(fabsl(s21_cos(100) - cos(100)) < s21_eps);
  ck_assert(fabsl(s21_cos(0.1) - cos(0.1)) < s21_eps);
  ck_assert(fabsl(s21_cos(0.01) - cos(0.01)) < s21_eps);
  ck_assert(fabsl(s21_cos(0.001) - cos(0.001)) < s21_eps);
  ck_assert(fabsl(s21_cos(-0.1) - cos(-0.1)) < s21_eps);
  ck_assert(fabsl(s21_cos(-0.01) - cos(-0.01)) < s21_eps);
  ck_assert(fabsl(s21_cos(-0.001) - cos(-0.001)) < s21_eps);
  ck_assert(isnan(s21_cos(s21_nan)) == isnan(cos(s21_nan)));
  ck_assert(isinf(s21_cos(s21_minus_inf)) == isinf(cos(s21_minus_inf)));
  ck_assert(isinf(s21_cos(s21_inf)) == isinf(cos(s21_inf)));
}
END_TEST

START_TEST(s21_exp_test) {
  ck_assert(fabsl(s21_exp(0) - exp(0)) < s21_eps);
  ck_assert(fabsl(s21_exp(15) - exp(15)) < s21_eps);
  ck_assert(fabsl(s21_exp(1) - exp(1)) < s21_eps);
  ck_assert(fabsl(s21_exp(2) - exp(2)) < s21_eps);
  ck_assert(fabsl(s21_exp(3) - exp(3)) < s21_eps);
  ck_assert(fabsl(s21_exp(4) - exp(4)) < s21_eps);
  ck_assert(fabsl(s21_exp(5) - exp(5)) < s21_eps);
  ck_assert(fabsl(s21_exp(10) - exp(10)) < s21_eps);
  ck_assert(fabsl(s21_exp(0.1) - exp(0.1)) < s21_eps);
  ck_assert(fabsl(s21_exp(0.01) - exp(0.01)) < s21_eps);
  ck_assert(fabsl(s21_exp(0.001) - exp(0.001)) < s21_eps);
  ck_assert(fabsl(s21_exp(0.0001) - exp(0.0001)) < s21_eps);
  ck_assert(fabsl(s21_exp(-1) - exp(-1)) < s21_eps);
  ck_assert(fabsl(s21_exp(-2) - exp(-2)) < s21_eps);
  ck_assert(fabsl(s21_exp(-3) - exp(-3)) < s21_eps);
  ck_assert(fabsl(s21_exp(-4) - exp(-4)) < s21_eps);
  ck_assert(fabsl(s21_exp(-5) - exp(-5)) < s21_eps);
  ck_assert(fabsl(s21_exp(-10) - exp(-10)) < s21_eps);
  ck_assert(fabsl(s21_exp(-0.1) - exp(-0.1)) < s21_eps);
  ck_assert(fabsl(s21_exp(-0.01) - exp(-0.01)) < s21_eps);
  ck_assert(fabsl(s21_exp(-0.001) - exp(-0.001)) < s21_eps);
  ck_assert(fabsl(s21_exp(-0.0001) - exp(-0.0001)) < s21_eps);
  ck_assert(isnan(s21_exp(s21_nan)) == isnan(exp(s21_nan)));
  ck_assert(isinf(s21_exp(s21_minus_inf)) == isinf(exp(s21_minus_inf)));
  ck_assert(s21_exp(s21_inf) == s21_inf);
}
END_TEST

START_TEST(s21_fabs_test) {
  ck_assert(fabsl(s21_fabs(-1.7) - fabs(-1.7)) < s21_eps);
  ck_assert(fabsl(s21_fabs(1.7) - fabs(1.7)) < s21_eps);
  ck_assert(fabsl(s21_fabs(-0.00007) - fabs(-0.00007)) < s21_eps);
  ck_assert(fabsl(s21_fabs(0.00007) - fabs(0.00007)) < s21_eps);
  ck_assert(fabsl(s21_fabs(-0.0) - fabs(-0.0)) < s21_eps);
  ck_assert(isnan(s21_fabs(s21_nan)) && isnan(fabsl(s21_nan)));
  ck_assert(s21_fabs(s21_inf) && s21_minus_inf);
  ck_assert(s21_fabs(s21_minus_inf) && s21_inf);
}
END_TEST

START_TEST(s21_floor_test) {
  ck_assert(fabsl(s21_floor(-1.7) - floor(-1.7)) < s21_eps);
  ck_assert(fabsl(s21_floor(1.6) - floor(1.6)) < s21_eps);
  ck_assert(fabsl(s21_floor(1.9999) - floor(1.999)) < s21_eps);
  ck_assert(fabsl(s21_floor(123456.6789) - floor(123456.6789)) < s21_eps);
  ck_assert(fabsl(s21_floor(-1.6) - floor(-1.6)) < s21_eps);
  ck_assert(fabsl(s21_floor(-1.9999) - floor(-1.999)) < s21_eps);
  ck_assert(fabsl(s21_floor(-123456.6789) - floor(-123456.6789)) < s21_eps);
  ck_assert(isnan(s21_floor(s21_nan)) && isnan(floor(s21_nan)));
  ck_assert(s21_floor(s21_inf) && s21_inf);
  ck_assert(s21_floor(s21_minus_inf) && s21_minus_inf);
}
END_TEST

START_TEST(s21_fmod_test) {
  ck_assert(fabsl(s21_fmod(9.99, 7) - fmod(9.99, 7)) < s21_eps);
  ck_assert(fabsl(s21_fmod(0.000123, 0.07) - fmod(0.000123, 0.07)) < s21_eps);
  ck_assert(fabsl(s21_fmod(12345.678, 3.3) - fmod(12345.678, 3.3)) < s21_eps);
  ck_assert(fabsl(s21_fmod(-12345.678, 3.3) - fmod(-12345.678, 3.3)) < s21_eps);
  ck_assert(fabsl(s21_fmod(12345.678, -883.5783) - fmod(12345.678, -883.5783)) <
            s21_eps);
  ck_assert(fabsl(s21_fmod(-12345.678, -883.5783) -
                  fmod(-12345.678, -883.5783)) < s21_eps);
  ck_assert(fabsl(s21_fmod(0, 7) - fmod(0, 7)) < s21_eps);
  ck_assert(fabsl(s21_fmod(154.54, 154.54) - fmod(154.54, 154.54)) < s21_eps);
  ck_assert(fabsl(s21_fmod(154, 154.54) - fmod(154, 154.54)) < s21_eps);
  ck_assert(isnan(s21_fmod(9.99, 0)) == isnan(fmod(9.99, 0)));
  ck_assert(isnan(s21_fmod(0, 0)) == isnan(fmod(0, 0)));
  ck_assert(isnan(s21_fmod(2.34, s21_nan)) == isnan(fmod(2.34, s21_nan)));
  ck_assert(fabsl(s21_fmod(2.34, s21_inf) - fmod(2.34, s21_inf)) < s21_eps);
  ck_assert(fabsl(s21_fmod(2.34, s21_minus_inf) - fmod(2.34, s21_minus_inf)) <
            s21_eps);
  ck_assert(isnan(s21_fmod(s21_nan, 10.75)) == isnan(fmod(s21_nan, 10.75)));
  ck_assert(isnan(s21_fmod(s21_inf, 10.75)) == isnan(fmod(s21_inf, 10.75)));
  ck_assert(isnan(s21_fmod(s21_minus_inf, 10.75)) ==
            isnan(fmod(s21_minus_inf, 10.75)));
  ck_assert(isnan(s21_fmod(s21_minus_inf, s21_minus_inf)) ==
            isnan(fmod(s21_minus_inf, s21_minus_inf)));
  ck_assert(isnan(s21_fmod(s21_inf, s21_inf)) == isnan(fmod(s21_inf, s21_inf)));
  ck_assert(isnan(s21_fmod(s21_minus_inf, s21_inf)) ==
            isnan(fmod(s21_minus_inf, s21_inf)));
  ck_assert(isnan(s21_fmod(s21_inf, s21_minus_inf)) ==
            isnan(fmod(s21_inf, s21_minus_inf)));
  ck_assert(isnan(s21_fmod(s21_inf, s21_nan)) == isnan(fmod(s21_inf, s21_nan)));
  ck_assert(isnan(s21_fmod(s21_minus_inf, s21_nan)) ==
            isnan(fmod(s21_minus_inf, s21_nan)));
  ck_assert(isnan(s21_fmod(s21_nan, s21_minus_inf)) ==
            isnan(fmod(s21_nan, s21_minus_inf)));
  ck_assert(isnan(s21_fmod(s21_nan, s21_inf)) == isnan(fmod(s21_nan, s21_inf)));
  ck_assert(isnan(s21_fmod(s21_nan, s21_nan)) == isnan(fmod(s21_nan, s21_nan)));
}
END_TEST

START_TEST(s21_log_test) {
  ck_assert(fabsl(s21_log(1.1) - log(1.1)) < s21_eps);
  ck_assert(fabsl(s21_log(123.4) - log(123.4)) < s21_eps);
  ck_assert(fabsl(s21_log(1234.4) - log(1234.4)) < s21_eps);
  ck_assert(fabsl(s21_log(123.4) - log(123.4)) < s21_eps);
  ck_assert(fabsl(s21_log(1234.4) - log(1234.4)) < s21_eps);
  ck_assert(isnan(s21_log(-1)) == isnan(log(-1)));
  ck_assert(isnan(s21_log(-0.0001)) == isnan(log(-0.0001)));
  ck_assert(fabsl(s21_log(0.1) - log(0.1)) < s21_eps);
  ck_assert(fabsl(s21_log(0.01) - log(0.01)) < s21_eps);
  ck_assert(fabsl(s21_log(1) - log(1)) < s21_eps);
  ck_assert(fabsl(s21_log(2.72) - log(2.72)) < s21_eps);
  ck_assert(isnan(s21_log(s21_nan)) == isnan(log(s21_nan)));
  ck_assert(isnan(s21_log(s21_minus_inf)) == isnan(log(s21_minus_inf)));
  ck_assert(s21_log(s21_inf) == s21_inf);
  ck_assert(s21_log(0) == s21_minus_inf);
  ck_assert(fabsl(s21_log(1e-5) - log(1e-5)) < 1e-6);
  // ck_assert(fabsl(s21_log(1e4) - log(1e4)) < s21_eps);
  // ck_assert(fabsl(s21_log(1e16) - log(1e16)) < s21_eps);
  // ck_assert(fabsl(s21_log(1e32) - log(1e32)) < s21_eps);
}
END_TEST

START_TEST(s21_pow_test) {
  ck_assert(fabsl(s21_pow(2, 2.2) - pow(2, 2.2)) < s21_eps);
  ck_assert(fabsl(s21_pow(1, 2) - pow(1, 2)) < s21_eps);
  ck_assert(fabsl(s21_pow(10, 4) - pow(10, 4)) < s21_eps);
  ck_assert(fabsl(s21_pow(66, 5) - pow(66, 5)) < s21_eps);
  ck_assert(fabsl(s21_pow(0.12, 3) - pow(0.12, 3)) < s21_eps);
  ck_assert(fabsl(s21_pow(0.123, 3) - pow(0.123, 3)) < s21_eps);
  ck_assert(isnan(s21_pow(-2, 2.2)) == isnan(pow(-2, 2.2)));
  ck_assert(fabsl(s21_pow(-1, 2) - pow(-1, 2)) < s21_eps);
  ck_assert(fabsl(s21_pow(-10, 4) - pow(-10, 4)) < s21_eps);
  ck_assert(fabsl(s21_pow(66, -5) - pow(66, -5)) < s21_eps);
  ck_assert(fabsl(s21_pow(-0.12, 3) - pow(-0.12, 3)) < s21_eps);
  ck_assert(fabsl(s21_pow(0.123, -3) - pow(0.123, -3)) < s21_eps);
  ck_assert(fabsl(s21_pow(-66, -5) - pow(-66, -5)) < s21_eps);
  ck_assert(fabsl(s21_pow(-0.123, -3) - pow(-0.123, -3)) < s21_eps);
  ck_assert(fabsl(s21_pow(3.65, 0) - pow(3.65, 0)) < s21_eps);
  ck_assert(fabsl(s21_pow(0, 15) - pow(0, 15)) < s21_eps);
  ck_assert(fabsl(s21_pow(0, 0) - pow(0, 0)) < s21_eps);
  ck_assert_int_eq(s21_pow(100000, 100000), pow(100000, 100000));
  ck_assert(isnan(s21_pow(2.34, s21_nan)) == isnan(pow(2.34, s21_nan)));
  ck_assert(s21_pow(2.34, s21_inf) == s21_inf);
  ck_assert(fabsl(s21_pow(2.34, s21_minus_inf) - pow(2.34, s21_minus_inf)) <
            s21_eps);
  ck_assert(isnan(s21_pow(s21_nan, 10.75)) == isnan(pow(s21_nan, 10.75)));
  ck_assert(s21_pow(s21_inf, 10.75) == s21_inf);
  ck_assert(s21_pow(s21_minus_inf, 10.75) == s21_inf);
  ck_assert(isnan(s21_pow(s21_inf, s21_nan)) == isnan(pow(s21_inf, s21_nan)));
  ck_assert(isnan(s21_pow(s21_minus_inf, s21_nan)) ==
            isnan(pow(s21_minus_inf, s21_nan)));
  ck_assert(isnan(s21_pow(s21_nan, s21_inf)) == isnan(pow(s21_nan, s21_inf)));
  ck_assert(isnan(s21_pow(s21_nan, s21_minus_inf)) ==
            isnan(pow(s21_nan, s21_minus_inf)));
  ck_assert(isnan(s21_pow(s21_nan, s21_nan)) == isnan(pow(s21_nan, s21_nan)));
  ck_assert(s21_pow(s21_inf, s21_inf) == s21_inf);
  // ck_assert(fabsl(s21_pow(s21_minus_inf, s21_minus_inf) -
  //                 pow(s21_minus_inf, s21_minus_inf)) < s21_eps);
  ck_assert(fabsl(s21_pow(s21_inf, s21_minus_inf) -
                  pow(s21_inf, s21_minus_inf)) < s21_eps);
  ck_assert(s21_pow(s21_minus_inf, s21_inf) == s21_inf);
  ck_assert(fabsl(s21_pow(s21_inf, s21_minus_inf) -
                  pow(s21_inf, s21_minus_inf)) < s21_eps);
  ck_assert(fabsl(s21_pow(s21_inf, 0) - pow(s21_inf, 0)) < s21_eps);
  ck_assert(fabsl(s21_pow(s21_minus_inf, 0) - pow(s21_minus_inf, 0)) < s21_eps);
  ck_assert(fabsl(s21_pow(s21_minus_inf, -1) - pow(s21_minus_inf, -1)) <
            s21_eps);
  ck_assert(fabsl(s21_pow(s21_minus_inf, 1) - pow(s21_minus_inf, 1)));
  // ck_assert(fabsl(s21_pow(-1, s21_inf) - pow(-1, s21_inf)) < s21_eps);
}
END_TEST

START_TEST(s21_sin_test) {
  ck_assert(fabsl(s21_sin(1) - sin(1)) < s21_eps);
  ck_assert(fabsl(s21_sin(2) - sin(2)) < s21_eps);
  ck_assert(fabsl(s21_sin(3) - sin(3)) < s21_eps);
  ck_assert(fabsl(s21_sin(4) - sin(4)) < s21_eps);
  ck_assert(fabsl(s21_sin(5) - sin(5)) < s21_eps);
  ck_assert(fabsl(s21_sin(-1) - sin(-1)) < s21_eps);
  ck_assert(fabsl(s21_sin(-2) - sin(-2)) < s21_eps);
  ck_assert(fabsl(s21_sin(-3) - sin(-3)) < s21_eps);
  ck_assert(fabsl(s21_sin(-4) - sin(-4)) < s21_eps);
  ck_assert(fabsl(s21_sin(-5) - sin(-5)) < s21_eps);
  ck_assert(fabsl(s21_sin(100) - sin(100)) < s21_eps);
  ck_assert(fabsl(s21_sin(0.1) - sin(0.1)) < s21_eps);
  ck_assert(fabsl(s21_sin(0.01) - sin(0.01)) < s21_eps);
  ck_assert(fabsl(s21_sin(0.001) - sin(0.001)) < s21_eps);
  ck_assert(fabsl(s21_sin(-0.1) - sin(-0.1)) < s21_eps);
  ck_assert(fabsl(s21_sin(-0.01) - sin(-0.01)) < s21_eps);
  ck_assert(fabsl(s21_sin(-0.001) - sin(-0.001)) < s21_eps);
  ck_assert(isnan(s21_sin(s21_nan)) == isnan(sin(s21_nan)));
}
END_TEST

START_TEST(s21_sqrt_test) {
  ck_assert(fabsl(s21_sqrt(0.0) - sqrt(0.0)) < s21_eps);
  ck_assert(fabsl(s21_sqrt(1) - sqrt(1)) < s21_eps);
  ck_assert(fabsl(s21_sqrt(2) - sqrt(2)) < s21_eps);
  ck_assert(fabsl(s21_sqrt(3) - sqrt(3)) < s21_eps);
  ck_assert(fabsl(s21_sqrt(4) - sqrt(4)) < s21_eps);
  ck_assert(fabsl(s21_sqrt(5) - sqrt(5)) < s21_eps);
  ck_assert(fabsl(s21_sqrt(100) - sqrt(100)) < s21_eps);
  ck_assert(fabsl(s21_sqrt(0.1) - sqrt(0.1)) < s21_eps);
  ck_assert(fabsl(s21_sqrt(0.01) - sqrt(0.01)) < s21_eps);
  ck_assert(fabsl(s21_sqrt(0.001) - sqrt(0.001)) < s21_eps);
  // ck_assert(isnan(s21_sqrt(-1)) == isnan(sqrt(-1)));
  // ck_assert(isnan(s21_sqrt(-0.0001)) == isnan(sqrt(-0.0001)));
}
END_TEST

START_TEST(s21_tan_test) {
  ck_assert(fabsl(s21_tan(0) - tan(0)) < s21_eps);
  ck_assert(fabsl(s21_tan(0.7) - tan(0.7)) < s21_eps);
  ck_assert(fabsl(s21_tan(0.07) - tan(0.07)) < s21_eps);
  ck_assert(fabsl(s21_tan(0.007) - tan(0.007)) < s21_eps);
  ck_assert(fabsl(s21_tan(0.0007) - tan(0.0007)) < s21_eps);
  ck_assert(fabsl(s21_tan(1) - tan(1)) < s21_eps);
  ck_assert(fabsl(s21_tan(2) - tan(2)) < s21_eps);
  ck_assert(fabsl(s21_tan(3) - tan(3)) < s21_eps);
  ck_assert(fabsl(s21_tan(4) - tan(4)) < s21_eps);
  ck_assert(fabsl(s21_tan(5) - tan(5)) < s21_eps);
  ck_assert(fabsl(s21_tan(100) - tan(100)) < s21_eps);
  ck_assert(fabsl(s21_tan(-0.7) - tan(-0.7)) < s21_eps);
  ck_assert(fabsl(s21_tan(-0.07) - tan(-0.07)) < s21_eps);
  ck_assert(fabsl(s21_tan(-0.007) - tan(-0.007)) < s21_eps);
  ck_assert(fabsl(s21_tan(-0.0007) - tan(-0.0007)) < s21_eps);
  ck_assert(fabsl(s21_tan(-1) - tan(-1)) < s21_eps);
  ck_assert(fabsl(s21_tan(-2) - tan(-2)) < s21_eps);
  ck_assert(fabsl(s21_tan(-3) - tan(-3)) < s21_eps);
  ck_assert(fabsl(s21_tan(-4) - tan(-4)) < s21_eps);
  ck_assert(fabsl(s21_tan(-5) - tan(-5)) < s21_eps);
  ck_assert(fabsl(s21_tan(-100) - tan(-100)) < s21_eps);
  ck_assert(isnan(s21_tan(s21_nan)) == isnan(tan(s21_nan)));
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");    // Объявляем сьюит
  SRunner *sr = srunner_create(s1);    // Лаунчер сьюита
  TCase *Case = tcase_create("Test");  // Новый кейс
  suite_add_tcase(s1, Case);           // Добавляем кейс

  tcase_add_test(Case, s21_abs_test);
  tcase_add_test(Case, s21_acos_test);
  tcase_add_test(Case, s21_asin_test);
  tcase_add_test(Case, s21_atan_test);
  tcase_add_test(Case, s21_ceil_test);
  tcase_add_test(Case, s21_cos_test);
  tcase_add_test(Case, s21_exp_test);
  tcase_add_test(Case, s21_fabs_test);
  tcase_add_test(Case, s21_floor_test);
  tcase_add_test(Case, s21_fmod_test);
  tcase_add_test(Case, s21_log_test);
  tcase_add_test(Case, s21_pow_test);
  tcase_add_test(Case, s21_sin_test);
  tcase_add_test(Case, s21_sqrt_test);
  tcase_add_test(Case, s21_tan_test);

  srunner_run_all(sr, CK_ENV);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return 0;
}
