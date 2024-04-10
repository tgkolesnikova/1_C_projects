#include "s21_math.h"

int s21_abs(int x) {
  if (x < 0) x = -x;
  return x;
}

long double s21_fabs(double x) {
  if (x < 0) x = -x;
  return x;
}

long double s21_fmod(double x, double y) {
  long double result = 0;
  if (x != x || x == s21_inf || x == s21_minus_inf || y != y || y == 0) {
    // (x != x) mean x == nan
    result = s21_nan;
  } else if (s21_fabs(y) <= 1e-6) {
    result = 0;
  } else if (y == s21_inf || y == s21_minus_inf) {
    result = x;
  } else {
    long long int z = x / y;
    result = x - z * y;
  }
  return result;
}

long double s21_sin(double x_) {
  long double result = 0;
  if (x_ != x_ || x_ == s21_inf || x_ == s21_minus_inf) {
    // (x != x) mean x == nan
    result = s21_nan;
  } else {
    double x = s21_fmod(x_, 2 * s21_pi);
    int n = 1;
    double a = x;
    long double s = a;
    while (s21_fabs(a) >= s21_eps) {
      a = a * (-x * x / (2 * n * (2 * n + 1)));
      s += a;
      n++;
    }
    result = s;
  }
  return result;
}

long double s21_cos(double x_) {
  long double result = 0;
  if (x_ != x_ || x_ == s21_inf || x_ == s21_minus_inf) {
    // (x != x) mean x == nan
    result = s21_nan;
  } else {
    double x = s21_fmod(x_, 2 * s21_pi);
    int n = 1;
    double a = 1;
    long double s = a;
    while (s21_fabs(a) >= s21_eps) {
      a = a * (-x * x / ((2 * n - 1) * 2 * n));
      s += a;
      n++;
    }
    result = s;
  }
  return result;
}

long double s21_tan(double x_) {
  long double result = 0;
  if (x_ != x_ || x_ == s21_inf || x_ == s21_minus_inf) {
    // (x != x) mean x == nan
    result = s21_nan;
  } else if (x_ == 0) {
    result = 0;
  } else {
    double x = s21_fmod(x_, s21_pi);
    if (x == s21_pi / 2) {
      return 16331239353195370L;
    } else if (x == -s21_pi / 2) {
      return -16331239353195370L;
    }
    result = (s21_sin(x) / s21_cos(x));
  }
  return result;
}

long double s21_exp(double x) {
  long double result = 0;
  if (x != x) {
    // (x != x) mean x == nan
    result = s21_nan;
  } else if (x == s21_inf) {
    result = s21_inf;
  } else if (x == s21_minus_inf) {
    result = 0.;
  } else {
    int n = 1;
    double a = 1;
    long double s = a;
    while (s21_fabs(a) >= s21_eps && n < MAX_COUNT_ITER) {
      a = a * x / n;
      s += a;
      n++;
    }
    if (n == MAX_COUNT_ITER && x < 0) {
      result = 0;
    } else if (n == MAX_COUNT_ITER && x > 0) {
      result = s21_inf;
    } else {
      result = s;
    }
  }
  return result;
}

long double s21_ceil(
    double x) {  // ближайшее целое, не меньшее (>=) заданного значения
  long double result = 0;
  if (x != x || x == s21_inf || x == s21_minus_inf) {
    result = x;
  } else {
    long double int_x = (long long int)x;
    if (int_x != x && x > 0) {
      result = int_x + 1;
    } else if (int_x != x && x < 0) {
      result = int_x;
    } else {
      result = int_x;
    }
  }
  return result;
}

long double s21_floor(
    double x) {  // ближайшее целое число, не превышающее (<=) заданное значение
  long double result = 0;
  if (x == s21_inf || x == s21_minus_inf) {
    result = x;
  } else if (x != x) {
    result = s21_nan;
  } else {
    long double floor_x = (long long int)x;
    if (s21_fabs(x - floor_x) > 0. && s21_fabs(x) > 0.) {
      if (x < 0.) {
        floor_x -= 1;
      }
    }
    result = floor_x;
  }
  return result;
}

long double s21_pow(double base, double exp) {
  long double result = 0;
  if (exp == 0) {
    result = 1;
  } else if (exp != exp) {
    result = s21_nan;
  } else if (exp == (int)exp) {
    result = pow_for_int_exp(base, (long long int)exp);
  } else {
    result = pow_for_double_exp(base, exp);
  }
  return result;
}

long double pow_for_int_exp(double base, long long int exp) {
  long double result = 1;
  for (int i = 0; i < s21_abs(exp); i++) {
    result *= base;
  }
  if (exp < 0) {
    result = 1. / result;
  }
  return result;
}

long double pow_for_double_exp(double base, double exp) {
  long double result = 0;
  if (base == s21_minus_inf) {
    if (exp == s21_minus_inf) {
      result = 0.;
    } else {
      result = s21_inf;
    }
  } else if (base < 0.) {
    if (exp == s21_inf) {
      if (base > -1.)
        result = 0.;
      else if (base == -1.)
        result = 1.;
      else
        result = s21_inf;
    } else if (exp == s21_minus_inf) {
      if (base < -1.)
        result = 0.;
      else if (base == -1.)
        result = 1.;
      else
        result = s21_inf;
    } else {
      result = s21_nan;
    }
  } else if (base == 0 && exp < 0) {
    result = s21_inf;
  } else {
    result = s21_exp(exp * s21_log(base));
  }
  return result;
}

long double s21_log(double x) {
  long double result = 0;
  if (x > 1.0) {
    result = log_natural1(x);
  } else if (0 < x && x < 1) {
    result = log_natural(x);
  } else if (x == 0) {
    result = s21_minus_inf;
  }
  if (x == s21_inf) {
    result = s21_inf;
  } else if (x < 0 || x == s21_minus_inf || x != x) {
    result = s21_nan;
  }
  return result;
}

long double log_natural1(double d) {
  long double result = 0.0, term = (d - 1) / d;
  long long denominator = 2;
  long double temp = term;
  while (temp > 1E-15) {
    result += temp;
    term *= (d - 1) / d;
    temp = term * (1.0 / denominator);
    denominator += 1;
  }
  return result;
}

long double log_natural(double d) {
  long double result = 0.0, term = d - 1;
  int power_of_one = -1;
  long long denominator = 2;
  long double temp = term;
  while (temp > 1E-15 || -temp > 1E-15) {
    if (temp > 1E-15) {
      result -= temp;
    } else {
      result += temp;
    }
    term = term * (d - 1);
    temp = term * power_of_one;
    temp /= denominator;
    denominator += 1;
  }
  result += term;
  return result;
}

long double s21_sqrt(double x) {
  long double result = 0;
  if (x != x || x == s21_minus_inf) {
    result = s21_nan;
  } else if (x == s21_inf) {
    result = s21_inf;
  } else if (x < 0) {
    result = s21_nan;
  } else {
    result = s21_pow(x, 0.5);
  }
  return result;
}

long double s21_atan(double x) {
  long double result = 0;
  if (x == s21_inf) {
    result = s21_pi / 2.;
  } else if (x == s21_minus_inf) {
    result = -s21_pi / 2.;
  } else if (s21_fabs(x) < 1.) {
    int n = 0;
    double a = x;
    long double s = a;
    while (s21_fabs(a) >= s21_eps) {
      a = a * (-x * x * (2 * n + 1) / (2 * n + 3));
      s += a;
      n++;
    }
    result = s;
  } else if (s21_fabs(x) > 1) {
    int n = 0;
    double a = 1. / x;
    long double s = a;
    while (s21_fabs(a) >= s21_eps) {
      a = a * (-(2 * n + 1) / (x * x * (2 * n + 3)));
      s += a;
      n++;
    }
    result = s21_pi * s21_sqrt(x * x) / (2. * x) - s;
  } else if (x == 1. || x == -1.) {
    result = x * s21_pi / 4.;
  } else if (x != x) {
    result = s21_nan;
  }
  return result;
}

long double s21_asin(double x) {
  long double result = 0;
  if (s21_fabs(x) < 1.) {
    result = s21_atan(x / s21_sqrt(1. - x * x));
  } else if (x == 1. || x == -1.) {
    result = x * s21_pi / 2.;
  } else if (s21_fabs(x) > 1. || x != x || x == s21_inf || x == s21_minus_inf) {
    result = s21_nan;
  }
  return result;
}

long double s21_acos(double x) {
  long double result = 0;
  if (0. < x && x < 1.) {
    result = s21_atan(s21_sqrt(1. - x * x) / x);
  } else if (-1. < x && x < 0.) {
    result = s21_atan(s21_sqrt(1. - x * x) / x) + s21_pi;
  } else if (x == 1.) {
    result = 0.0;
  } else if (x == -1.) {
    result = s21_pi;
  } else if (x == 0.) {
    result = s21_pi / 2.;
  } else if (s21_fabs(x) > 1. || x != x || x == s21_inf || x == s21_minus_inf) {
    result = s21_nan;
  }
  return result;
}
