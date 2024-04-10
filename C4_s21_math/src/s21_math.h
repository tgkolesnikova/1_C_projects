#ifndef _USERS_BLANCURG_C4_S21_MATH_0_DEVELOP_SRC_S21_MATH_H_
#define _USERS_BLANCURG_C4_S21_MATH_0_DEVELOP_SRC_S21_MATH_H_

#include <stdio.h>
#define s21_inf  1.0 / 0.0
#define s21_minus_inf  -1.0 / 0.0
#define s21_nan  0.0 / 0.0
#define s21_eps  1e-9
#define s21_pi 3.14159265358979323846264338327950288
#define MAX_COUNT_ITER 600

int s21_abs(int x);             // абсолютное значение целого числа
long double s21_fabs(double x);  //  абсолютное значение числа с плавающей точкой

long double s21_cos(double x);  // косинус
long double s21_sin(double x);  // синус
long double s21_tan(double x_);  // тангенс

long double s21_acos(double x);  //  арккосинус
long double s21_asin(double x);  // арксинус
long double s21_atan(double x);  // арктангенс

long double s21_ceil(double x);     // ближайшее целое число, не меньшее (>=) заданного значения
long double s21_floor(double x);    // ближайшее целое число, не превышающее (<=) заданное значение

long double s21_exp(double x);  // значение e, возведенное в заданную степень
long double s21_log(double x);  // натуральный логарифм
long double log_natural(double d);  //  натуральный логарифм для 0 < x < 1
long double log_natural1(double d);  //  натуральный логарифм для 1 < x < +inf

long double s21_fmod(double x, double y);  //  остаток операции деления с плавающей точкой

long double s21_sqrt(double x);  //  квадратный корень
long double s21_pow(double base, double exp);  //  возводит число в заданную степень
long double pow_for_int_exp(double base, long long int exp);  // число в заданную ЦЕЛУЮ степень
long double pow_for_double_exp(double base, double exp);  // число в заданную DOUBLE степень

#endif  //  _USERS_BLANCURG_C4_S21_MATH_0_DEVELOP_SRC_S21_MATH_H_
