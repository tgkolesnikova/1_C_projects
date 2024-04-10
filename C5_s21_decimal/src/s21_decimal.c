#include "s21_decimal.h"


int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  int B_round = 1;

  s21_long_decimal res = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  s21_long_decimal long_1;
  s21_long_decimal long_2;


  unsigned int b1 = value_1.bits[3];
  unsigned int b2 = value_2.bits[3];
  unsigned int sign_1 = get_int_sign(b1);
  unsigned int sign_2 = get_int_sign(b2);

  int sign = 0;

  int general_scale = to_equal_scale(value_1, value_2, &long_1, &long_2);


  if (sign_1 == 1 && sign_2 == 0) {
    res = s21_add_long(long_1, long_2);
    sign = 1;
  }
  if (sign_1 == 0 && sign_2 == 1) {
    res = s21_add_long(long_1, long_2);
    sign = 0;
  }

  if (sign_1 == 0 && sign_2 == 0) {
    int compare = s21_is_greater_or_equal(value_1, value_2);
    if (compare == 1) {
      res = s21_sub_long(long_1, long_2);
      sign = 0;
    } else {
      res = s21_sub_long(long_2, long_1);
      sign = 1;
    }
  }

  if (sign_1 == 1 && sign_2 == 1) {
    int compare = s21_is_greater_or_equal(value_1, value_2);

    if (compare == 1) {
      res = s21_sub_long(long_2, long_1);
      sign = 0;
    } else {
      res = s21_sub_long(long_1, long_2);
      sign = 1;
    }
  }
  flag = build_dec_from_long(res, general_scale, sign, result, B_round);
  return flag;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  int B_round = 1;

  s21_long_decimal res = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal long_1;
  s21_long_decimal long_2;


  unsigned int b1 = value_1.bits[3];
  unsigned int b2 = value_2.bits[3];
  unsigned int sign_1 = get_int_sign(b1);
  unsigned int sign_2 = get_int_sign(b2);

  int sign = 0;

  int general_scale = to_equal_scale(value_1, value_2, &long_1, &long_2);

  if (sign_1 == 0 && sign_2 == 0) {
    res = s21_add_long(long_1, long_2);
    sign = 0;
  }
  if (sign_1 == 1 && sign_2 == 1) {
    res = s21_add_long(long_1, long_2);
    sign = 1;
  }

  if (sign_1 == 0 && sign_2 == 1) {
    value_2.bits[3] = value_2.bits[3] & 0x7FFFFFFF;
    int compare = s21_is_greater_or_equal(value_1, value_2);
    if (compare == 1) {
      res = s21_sub_long(long_1, long_2);
      sign = 0;
    } else {
      res = s21_sub_long(long_2, long_1);
      sign = 1;
    }
  }

  if (sign_1 == 1 && sign_2 == 0) {
    value_1.bits[3] = value_1.bits[3] & 0x7FFFFFFF;

    int compare = s21_is_greater_or_equal(value_1, value_2);
    if (compare == 1) {
      res = s21_sub_long(long_1, long_2);
      sign = 1;
    } else if (compare == 0) {
      res = s21_sub_long(long_2, long_1);
      sign = 0;
    }
  }
  flag = build_dec_from_long(res, general_scale, sign, result, B_round);
  return flag;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  int B_round = 1;

  s21_long_decimal res = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal long_1;
  s21_long_decimal long_2;

  unsigned int b1 = value_1.bits[3];
  unsigned int b2 = value_2.bits[3];
  unsigned int sign_1 = get_int_sign(b1);
  unsigned int sign_2 = get_int_sign(b2);
  unsigned int scale_1 = b1 << 8 >> 24;
  unsigned int scale_2 = b2 << 8 >> 24;

  int sign = 0;

  int general_scale = scale_1 + scale_2;

  long_decimal(value_1, &long_1);
  long_decimal(value_2, &long_2);

  if ((sign_1 == 0 && sign_2 == 0) || (sign_1 == 1 && sign_2 == 1)) {
    res = s21_mul_long(long_1, long_2);
    sign = 0;
  } else if ((sign_1 == 1 && sign_2 == 0) || (sign_1 == 0 && sign_2 == 1)) {
    res = s21_mul_long(long_1, long_2);
    sign = 1;
  }
  flag = build_dec_from_long(res, general_scale, sign, result, B_round);
  return flag;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  if (check_if_dec_is_zero(value_2)) {
    flag = 3;
  } else {
    int B_round = 1;
    int scale = 0;

    s21_long_decimal res = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    s21_long_decimal long_1;
    s21_long_decimal long_2;
    long_decimal(value_1, &long_1);
    long_decimal(value_2, &long_2);
    unsigned int b1 = value_1.bits[3];
    unsigned int b2 = value_2.bits[3];
    unsigned int sign_1 = get_int_sign(b1);
    unsigned int sign_2 = get_int_sign(b2);
    unsigned int scale_1 = b1 << 8 >> 24;
    unsigned int scale_2 = b2 << 8 >> 24;

    int sign = 0;

    if ((sign_1 == 0 && sign_2 == 0) || (sign_1 == 1 && sign_2 == 1)) {
      res = s21_div_long_drobnoe(long_1, long_2, &scale);
      sign = 0;
    } else if ((sign_1 == 1 && sign_2 == 0) || (sign_1 == 0 && sign_2 == 1)) {
      res = s21_div_long_drobnoe(long_1, long_2, &scale);
      sign = 1;
    }

    int general_scale = scale_1 - scale_2 + scale;
    flag = build_dec_from_long(res, general_scale, sign, result, B_round);
  }
  return flag;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  if (check_if_dec_is_zero(value_2)) {
    flag = 3;
  } else {
    int B_round = 0;
    s21_long_decimal res;

    s21_long_decimal long_1;
    s21_long_decimal long_2;

    unsigned int b1 = value_1.bits[3];
    unsigned int sign_1 = get_int_sign(b1);

    int sign = 0;

    int general_scale = to_equal_scale(value_1, value_2, &long_1, &long_2);

    if (sign_1 == 0) {
      s21_div_long_end(long_1, long_2, &res);
      sign = 0;
    } else if (sign_1 == 1) {
      s21_div_long_end(long_1, long_2, &res);
      sign = 1;
    }

    flag = build_dec_from_long(res, general_scale, sign, result, B_round);
  }
  return flag;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  init_decimal(dst);
  dst->bits[3] = src & SIGN_MASK;
  if (get_int_sign(src) == 1) {
    dst->bits[0] = change_int_sign(src);
  } else {
    dst->bits[0] = src;
  }
  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int sign = get_int_sign(src.bits[3]);
  int flag = 0;
  unsigned int scale = src.bits[3] << 8 >> 24;
  for (unsigned int n = 1; n <= scale; n++) {
    src = div_10(src);
  }
  dst[0] = 0;

  if ((sign == 1) && (src.bits[2] == 0) && (src.bits[1] == 0) &&
      (get_quantity_bit_pos_for_int(src.bits[0]) <= 31)) {
    src.bits[0] = change_int_sign(src.bits[0]);
    *dst = src.bits[0];
  } else if ((sign == 0) && (src.bits[2] == 0) && (src.bits[1] == 0) &&
             (get_quantity_bit_pos_for_int(src.bits[0]) <= 31)) {
    *dst = src.bits[0];
  } else {
    flag = 1;
  }
  return flag;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  unsigned int fbits = *(unsigned int *)&src;
  int res = 0;
  int Exp = (fbits << 1 >> 24) - 127;
    if (!isnan(src) || !isinf(src)) {
    if (src > 7.9e28) {
      res = 1;
      init_decimal(dst);
    } else if (src < -7.9e28) {
      res = 1;
      init_decimal(dst);
    } else if (fabs(src) < 1e-28) {
      init_decimal(dst);
      res = 1;
    } else {
      init_decimal(dst);
      int scale = 0;

      unsigned int fsign = get_int_sign(fbits);
      unsigned int mantissa = fbits << 9 >> 9;
      unsigned int temp_float =
          mantissa | (0x800000);
      int reduce_exp = 23 - Exp;

      s21_decimal d_temp;
      init_decimal(&d_temp);
      d_temp.bits[0] = temp_float;

      s21_long_decimal float_long;
      long_decimal(d_temp, &float_long);

      s21_long_decimal two_long = {{2, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
      s21_long_decimal five_long = {{5, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
      s21_long_decimal reminder = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

      if (reduce_exp > 0) {
        for (int i = 0; i < reduce_exp; i++) {
          unsigned int end_number = float_long.bits[0] << 31 >> 31;
          if (end_number == 0) {
            float_long = s21_div_long_end(float_long, two_long, &reminder);
          } else {
            scale++;
            float_long = s21_mul_long(float_long, five_long);
          }
        }
      } else if (reduce_exp < 0) {
        for (int j = reduce_exp; j < 0; j++) {
          float_long = s21_mul_long(float_long, two_long);
        }
      }
      int flag = build_dec_from_float(float_long, scale, fsign, dst);
      if (flag != 0) res = 1;
    }
  } else {
    res = 1;
    init_decimal(dst);
  }
  return res;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int flag = 0;
  int *w = (int *)dst;

  s21_long_decimal long_1;
  unsigned int Exp = 0;
  s21_long_decimal five_long = {{5, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal two_long = {{2, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal one_long = {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  int sign = get_int_sign(src.bits[3]);
  unsigned int b3 = src.bits[3];
  int scale = b3 << 8 >> 24;
  if (check_if_dec_is_zero(src)) {
    b3 = 0;
  } else {
    long_decimal(src, &long_1);
    for (int i = 0; i < (S21_LONG - 3) * 32; i++) {
      long_1 = s21_mul_long(long_1, two_long);
    }

    s21_long_decimal reminder = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    for (int i = 0; i < scale; i++) {
      long_1 = s21_div_long_end(long_1, five_long, &reminder);
    }

    int k, pos, x = 0;
    for (k = S21_LONG - 1; k >= 0; k--) {
      x = get_bit_pos(long_1.bits[k], &pos);
      if (x) break;
    }
    if (!x) k = 0;

    s21_long_decimal reminder_1 = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    for (int j = 0; j < (k * 32 + pos - 25); j++) {
      long_1 = s21_div_long_end(long_1, two_long, &reminder_1);
    }

    b3 = long_1.bits[0];
    b3 = b3 << 31 >> 31;

    if (b3 == 1) {
      long_1 = s21_div_long_end(long_1, two_long, &reminder);
      long_1 = s21_add_long(long_1, one_long);
    } else {
      long_1 = s21_div_long_end(long_1, two_long, &reminder);
    }
    Exp = 127 - scale - (S21_LONG - 3) * 32 + k * 32 + pos - 24 + 24 - 1;
    b3 = long_1.bits[0] ^ 0x800000;
  }

  unsigned int res = (sign << 31) | (Exp << 23);
  res = res | b3;
  *w = res;
  return flag;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int flag = 0;
  init_decimal(result);
  unsigned int b3 = value.bits[3];
  if (get_int_sign(value.bits[3]) == 1) {
    result->bits[3] = b3 & ~SIGN_MASK;
    result->bits[2] = value.bits[2];
    result->bits[1] = value.bits[1];
    result->bits[0] = value.bits[0];
  } else {
    result->bits[3] = b3 | SIGN_MASK;
    result->bits[2] = value.bits[2];
    result->bits[1] = value.bits[1];
    result->bits[0] = value.bits[0];
  }
  return flag;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int flag = 0;
  init_decimal(result);
  unsigned int scale = value.bits[3] << 8 >> 24;
  for (unsigned int n = 1; n <= scale; n++) {
    value = div_10(value);
  }
  result->bits[3] = value.bits[3];
  result->bits[2] = value.bits[2];
  result->bits[1] = value.bits[1];
  result->bits[0] = value.bits[0];
  return flag;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int flag = 0;
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal temp;
  temp.bits[0] = value.bits[0];
  temp.bits[1] = value.bits[1];
  temp.bits[2] = value.bits[2];
  temp.bits[3] = value.bits[3];
  init_decimal(result);
  int sign = get_int_sign(value.bits[3]);
  unsigned int scale = value.bits[3] << 8 >> 24;
  for (unsigned int n = 1; n <= scale; n++) {
    temp = div_10(temp);
  }
  if (sign == 1) {
    int y = s21_is_not_equal(temp, value);
    if (y == 1) {
      s21_sub(
          temp, one,
          result);
    } else {
      result->bits[3] = temp.bits[3];
      result->bits[2] = temp.bits[2];
      result->bits[1] = temp.bits[1];
      result->bits[0] = temp.bits[0];
    }
  } else {
    result->bits[3] = temp.bits[3];
    result->bits[2] = temp.bits[2];
    result->bits[1] = temp.bits[1];
    result->bits[0] = temp.bits[0];
  }
  return flag;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int flag = 0;
  s21_decimal half = {{5, 0, 0, 0x10000}};
  s21_decimal half_minus = {{5, 0, 0, 0x80010000}};
  s21_decimal one = {{1, 0, 0, 0}};
  init_decimal(result);
  s21_decimal temp;
  temp.bits[0] = value.bits[0];
  temp.bits[1] = value.bits[1];
  temp.bits[2] = value.bits[2];
  temp.bits[3] = value.bits[3];
  int sign = get_int_sign(value.bits[3]);
  unsigned int scale = value.bits[3] << 8 >> 24;

  for (unsigned int n = 1; n <= scale; n++) {
    temp = div_10(temp);
  }
  if (sign == 0) {
    s21_decimal temp_0;
    s21_sub(value, temp, &temp_0);
    if (s21_is_greater_or_equal(temp_0, half) == 1) {
      s21_add(temp, one, result);
    } else {
      result->bits[3] = temp.bits[3];
      result->bits[2] = temp.bits[2];
      result->bits[1] = temp.bits[1];
      result->bits[0] = temp.bits[0];
    }
  } else if (sign == 1) {
    s21_decimal temp_1;
    s21_sub(value, temp, &temp_1);
    if (s21_is_less_or_equal(temp_1, half_minus) == 1) {
      s21_sub(
          temp, one,
          result);
    } else {
      result->bits[3] = temp.bits[3];
      result->bits[2] = temp.bits[2];
      result->bits[1] = temp.bits[1];
      result->bits[0] = temp.bits[0];
    }
  }
  return flag;
}

int s21_is_equal(s21_decimal dec1, s21_decimal dec2) {
  int res = 0;
  int signDec1 = get_int_sign(dec1.bits[3]);
  int signDec2 = get_int_sign(dec2.bits[3]);

  if (isZero(dec1) && isZero(dec2)) {
    res = 1;
  } else {
    if (signDec1 == signDec2) {
      unsigned int scaleDec1 = dec1.bits[3] << 8 >> 24;
      unsigned int scaleDec2 = dec2.bits[3] << 8 >> 24;
      if (scaleDec1 != scaleDec2) {
        s21_long_decimal long_dec1;
        s21_long_decimal long_dec2;
        to_equal_scale(dec1, dec2, &long_dec1, &long_dec2);
        res = 1;
        for (int i = 0; i < S21_LONG; i++) {
          unsigned int long_bits1 = long_dec1.bits[i],
                       long_bits2 = long_dec2.bits[i];
          if (long_bits1 != long_bits2) {
            res = 0;
            break;
          }
        }
      } else {
        res = 1;
        for (int i = 0; i <= 2; i++) {
          unsigned int dec_bits1 = dec1.bits[i], dec_bits2 = dec2.bits[i];
          if (dec_bits1 != dec_bits2) {
            res = 0;
            break;
          }
        }
      }
    }
  }
  return res;
}

int s21_is_not_equal(s21_decimal dec1, s21_decimal dec2) {
  return !s21_is_equal(dec1, dec2);
}

int s21_is_greater_or_equal(s21_decimal dec1, s21_decimal dec2) {
  int res = 0;
  int zeroDec1 = isZero(dec1), zeroDec2 = isZero(dec2);
  unsigned int b3_1 = dec1.bits[3], b3_2 = dec2.bits[3];
  unsigned int signDec1 = get_int_sign(b3_1), signDec2 = get_int_sign(b3_2);

  if (zeroDec1 || zeroDec2) {
    if (zeroDec1 == zeroDec2) {
      res = 1;
    } else {
      if ((zeroDec1 && signDec2) || (zeroDec2 && !signDec1)) res = 1;
    }
  } else {
    s21_long_decimal long_dec1;
    s21_long_decimal long_dec2;
    to_equal_scale(dec1, dec2, &long_dec1, &long_dec2);
    int equal_long = greater_or_equil_long(long_dec1, long_dec2);
    if (signDec1 == signDec2) {
      if (!signDec1 && equal_long) {
        res = 1;
      } else if (signDec1 && !equal_long) {
        res = 1;
      }
    } else {
      if (!signDec1) res = 1;
    }
  }
  return res;
}

int s21_is_less(s21_decimal dec1, s21_decimal dec2) {
  return !s21_is_greater_or_equal(dec1, dec2);
}
int s21_is_greater(s21_decimal dec1, s21_decimal dec2) {
  return (s21_is_greater_or_equal(dec1, dec2) && s21_is_not_equal(dec1, dec2));
}

int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2) {
  return (s21_is_less(dec1, dec2) || s21_is_equal(dec1, dec2));
}

void init_decimal(s21_decimal *src) {
  for (int i = 0; i < 4; i++) {
    src->bits[i] = 0;
  }
}

int get_int_sign(int num) {
  int res = 0;
  if (num & SIGN_MASK) res = 1;

  return res;
}

int change_int_sign(int x) {
  unsigned int signmask = 0x80000000;
  unsigned int tmpvalue = (~x & ~signmask) + 1;

  int y = tmpvalue ^ (~x & signmask);

  y = ((~x & ~signmask) + 1) ^ (~x & signmask);
  return y;
}

int get_bit_pos(unsigned int x, int *pos) {
  int res = 0;
  unsigned int fbit = *(unsigned int *)&x;
  for (int i = 0; i <= 31; i++) {
    unsigned int a31 = 0;
    a31 = fbit << i >> 31;
    if (a31 == 1) {
      *pos = 31 - i + 1;
      res = 1;
      break;
    } else {
      continue;
    }
  }
  return res;
}

int get_quantity_bit_pos_for_int(int x) {
  int pos = -1;
  unsigned int fbit = *(unsigned int *)&x;
  for (int i = 0; i <= 31; i++) {
    unsigned int a31 = 0;
    a31 = fbit << i >> 31;
    if (a31 == 1) {
      pos = 31 - i;
      break;
    } else {
      continue;
    }
  }
  return pos + 1;
}

s21_decimal div_10(s21_decimal src) {
  s21_long_decimal dst_long;
  s21_long_decimal reminder;
  s21_long_decimal ten_long = {{10, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  long_decimal(src, &dst_long);
  unsigned int b3 = src.bits[3];
  unsigned int scale = b3 << 8 >> 24;
  if (scale > 0) {
    scale = scale - 1;
  }
  int sign = get_int_sign(src.bits[3]);
  if (sign == 1) {
    src.bits[3] = (scale << 16) | SIGN_MASK;

  } else {
    src.bits[3] = scale << 16;
  }

  dst_long = s21_div_long_end(dst_long, ten_long, &reminder);
  src.bits[0] = dst_long.bits[0];
  src.bits[1] = dst_long.bits[1];
  src.bits[2] = dst_long.bits[2];
  return src;
}

void long_decimal(s21_decimal src, s21_long_decimal *dst) {
  for (int i = 0; i < 3; i++) {
    dst->bits[i] = src.bits[i];
  }
  for (int i = 3; i < S21_LONG; i++) {
    dst->bits[i] = 0;
  }
}

s21_long_decimal s21_sub_long(s21_long_decimal value_1,
                              s21_long_decimal value_2) {
  s21_long_decimal res = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  int z = 0;
  for (int j = 0; j < S21_LONG; j++) {
    for (int i = 0; i < 32; i++) {
      unsigned int temp_res = 0;
      unsigned int temp_0 = value_1.bits[j];
      unsigned int temp_1 = value_2.bits[j];
      temp_0 = temp_0 >> i << 31 >> 31;
      temp_1 = temp_1 >> i << 31 >> 31;
      if (temp_0 == 0 && temp_1 == 0 && z == 0) {
        temp_res = 0;
        z = 0;
        res.bits[j] = temp_res << i | res.bits[j];
      } else if (temp_0 == 1 && temp_1 == 0 && z == 0) {
        temp_res = 1;
        z = 0;
        res.bits[j] = temp_res << i | res.bits[j];
      } else if (temp_0 == 1 && temp_1 == 1 && z == 0) {
        temp_res = 0;
        z = 0;
        res.bits[j] = temp_res << i | res.bits[j];
      } else if (temp_0 == 0 && temp_1 == 1 && z == 0) {
        temp_res = 1;
        z = 1;
        res.bits[j] = temp_res << i | res.bits[j];
      } else if (temp_0 == 0 && temp_1 == 0 && z == 1) {
        temp_res = 1;
        z = 1;
        res.bits[j] = temp_res << i | res.bits[j];
      } else if (temp_0 == 1 && temp_1 == 0 && z == 1) {
        temp_res = 0;
        z = 0;
        res.bits[j] = temp_res << i | res.bits[j];
      } else if (temp_0 == 1 && temp_1 == 1 && z == 1) {
        temp_res = 1;
        z = 1;
        res.bits[j] = temp_res << i | res.bits[j];
      } else if (temp_0 == 0 && temp_1 == 1 && z == 1) {
        temp_res = 0;
        z = 1;
        res.bits[j] = temp_res << i | res.bits[j];
      }
    }
  }
  return res;
}

int check_if_long_dec_too_big(s21_long_decimal x) {
  int res = 0;
  for (int i = 3; i < S21_LONG; i++) {
    res = res | (x.bits[i] & 0xffffffff);
  }
  return res;
}

int check_if_dec_is_zero(s21_decimal x) {
  int res = 0;
  for (int i = 0; i < 3; i++) {
    res = res | (x.bits[i] & 0xffffffff);
  }
  return !res;
}

int build_dec_from_long(s21_long_decimal res, int scale, int sign,
                        s21_decimal *result, int B_round) {
  init_decimal(result);
  s21_long_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal one_long = {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  int flag = 0;
  s21_long_decimal reminder;
  int scale_second = scale;
  if (scale_second < 0) {
    for (int i = scale; i < 0; i++) {
      res = s21_mul_long(res, ten);
      scale_second++;
    }
  }
  scale = scale_second;
  for (int i = 3; i < S21_LONG; i++) {
    int step = 0;
    if (check_if_long_dec_too_big(res) == 0 && scale_second <= 28) {
      result->bits[3] = (scale << 16) | (sign << 31);
      result->bits[2] = res.bits[2];
      result->bits[1] = res.bits[1];
      result->bits[0] = res.bits[0];
    } else if (check_if_long_dec_too_big(res) != 0 && scale == 0 && sign == 1) {
      flag = 2;
    } else if (check_if_long_dec_too_big(res) != 0 && scale == 0 && sign == 0) {
      flag = 1;
    } else if ((check_if_long_dec_too_big(res) != 0 && scale > 0) ||
               (!check_if_long_dec_too_big(res) && scale >= 29)) {
      for (int j = 0; j < scale; j++) {
        if (scale_second == 1 && B_round && check_if_long_dec_too_big(res)) {
          s21_long_decimal res_bank;
          res_bank = s21_div_long_end(res, ten, &reminder);
          if (check_if_long_dec_too_big(res_bank) == 0) {
            s21_bank_round(res, scale_second, &res);
            scale_second--;
            step = 1;
            break;
          }
        }
        res = s21_div_long_end(res, ten, &reminder);
        scale_second--;
        if (check_if_long_dec_too_big(res) == 0 && scale_second <= 28) {
          break;
        }
      }
      if (reminder.bits[0] >= 5 && !step) {
        res = s21_add_long(res, one_long);
      }
      scale = scale_second;
    }

    if (check_if_long_dec_too_big(res) == 0) {
      result->bits[3] = (scale << 16) | (sign << 31);
      result->bits[2] = res.bits[2];
      result->bits[1] = res.bits[1];
      result->bits[0] = res.bits[0];
    } else {
      if (sign == 1) flag = 2;
      if (sign == 0) flag = 1;
    }
  }
  return flag;
}

int build_dec_from_float(s21_long_decimal res, int scale, int sign,
                         s21_decimal *result) {
    init_decimal(result);
    s21_long_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    s21_long_decimal one_long = {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    int flag = 0;
    s21_long_decimal reminder;
    int scale_second = scale;
    if (scale_second < 0) {
        for (int i = scale; i < 0; i++) {
          res = s21_mul_long(res, ten);
          scale_second++;
        }
    }
    scale = scale_second;
    if (check_if_long_dec_too_big(res) != 0 && scale == 0 && sign == 1) {
        flag = 1;
    } else if (check_if_long_dec_too_big(res) != 0 && scale == 0 && sign == 0) {
        flag = 1;
    } else if ((check_if_long_dec_too_big(res) != 0 && scale > 0) ||
                 (!check_if_long_dec_too_big(res) && scale >= 29)) {
        for (int j = 0; j < scale; j++) {
            res = s21_div_long_end(res, ten, &reminder);
            scale_second--;
            if (check_if_long_dec_too_big(res) == 0 && scale_second <= 28) {
                break;
            }
        }
    }
    if (!flag) {
        while (quantity_numbers(res) > 7) {
          res = s21_div_long_end(res, ten, &reminder);
          scale_second--;
        }

        if (reminder.bits[0] >= 5) {
          res = s21_add_long(res, one_long);
        }
        while (scale_second < 0) {
          res = s21_mul_long(res, ten);
          scale_second++;
        }

        while (scale_second > 0) {
          s21_long_decimal temp_res = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
          temp_res = creat_equal_long(temp_res, res);
          temp_res = s21_div_long_end(temp_res, ten, &reminder);
          if (reminder.bits[0] == 0) {
            scale_second--;
            res = creat_equal_long(res, temp_res);
          } else {
            break;
          }
        }
        scale = scale_second;

        if (check_if_long_dec_too_big(res) == 0) {
            result->bits[3] = (scale << 16) | (sign << 31);
            result->bits[2] = res.bits[2];
            result->bits[1] = res.bits[1];
            result->bits[0] = res.bits[0];
        } else {
            flag = 1;
        }
    }
    return flag;
}

int to_equal_scale(s21_decimal value_1, s21_decimal value_2,
                   s21_long_decimal *long_1, s21_long_decimal *long_2) {
  long_decimal(value_1, long_1);
  long_decimal(value_2, long_2);
  unsigned int b1 = value_1.bits[3];
  unsigned int b2 = value_2.bits[3];

  int scale_1 = b1 << 8 >> 24;
  int scale_2 = b2 << 8 >> 24;
  s21_long_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  int k = 0;
  if (scale_1 > scale_2) {
    int y = scale_1 - scale_2;
    for (int i = 0; i < y; i++) {
      *long_2 = s21_mul_long(*long_2, ten);
      scale_2++;
    }
  } else if (scale_2 > scale_1) {
    int y = scale_2 - scale_1;
    for (int i = 0; i < y; i++) {
      *long_1 = s21_mul_long(*long_1, ten);
      scale_1++;
    }
  }
  k = scale_1;
  return k;
}

s21_long_decimal s21_mul_long_help(s21_long_decimal value_1,
                                   s21_long_decimal value_2) {
  s21_long_decimal zero = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal one_long = {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal temp = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  temp = creat_equal_long(temp, value_1);
  if (check_if_long_dec_is_zero(value_1) ||
      check_if_long_dec_is_zero(value_2)) {
    value_1 = creat_equal_long(value_1, zero);
  } else {
    while (!check_if_long_dec_is_one(value_2)) {
      value_1 = s21_add_long(value_1, temp);
      value_2 = s21_sub_long(value_2, one_long);
    }
  }
  return value_1;
}

s21_long_decimal s21_mul_long(s21_long_decimal value_1,
                              s21_long_decimal value_2) {
  s21_long_decimal zero = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal res = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal temp = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal two_long = {{2, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  if (check_if_long_dec_is_zero(value_1) ||
      check_if_long_dec_is_zero(value_2)) {
    res = creat_equal_long(res, zero);
  } else {
    int k = 0;
    for (int j = 0; j < S21_LONG; j++) {
      for (int i = 0; i < 32; i++) {
        unsigned int temp_2 = value_2.bits[j];
        temp_2 = temp_2 >> i << 31 >> 31;
        if (temp_2 == 0) {
          k++;
        } else if (temp_2 == 1 && k == 0) {
          k++;
          res = s21_add_long(res, value_1);
        } else if (temp_2 == 1 && k != 0) {
          k++;
          temp = creat_equal_long(temp, value_1);
          for (int m = 1; m < k; m++) {
            temp = s21_mul_long_help(temp, two_long);
          }
          res = s21_add_long(temp, res);
        }
      }
    }
  }
  return res;
}

s21_long_decimal s21_div_long_end(s21_long_decimal value_1,
                                  s21_long_decimal divisor,
                                  s21_long_decimal *reminder) {
  s21_long_decimal res = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal two_long = {{2, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal dividend = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  for (int i = S21_LONG - 1; i >= 0; i--) {
    for (int j = 0; j < 32; j++) {
      unsigned int temp = value_1.bits[i];
      temp = temp << j >> 31;
      dividend = s21_mul_long(dividend, two_long);
      dividend.bits[0] = dividend.bits[0] | temp;
      if (!greater_or_equil_long(dividend, divisor)) {
        res = s21_mul_long(res, two_long);
      } else {
        dividend = s21_sub_long(dividend, divisor);
        res = s21_mul_long(res, two_long);
        res.bits[0] = res.bits[0] | 0x1;
      }
    }
  }
  *reminder = creat_equal_long(*reminder, dividend);
  return res;
}

s21_long_decimal s21_div_long_drobnoe(s21_long_decimal value_1,
                                      s21_long_decimal divisor, int *scale) {
  s21_long_decimal res = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal two_long = {{2, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal ten_long = {{10, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal dividend = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal reminder = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  int k = 0;
  for (int i = S21_LONG - 1; i >= 0; i--) {
    for (int j = 0; j < 32; j++) {
      unsigned int temp = value_1.bits[i];
      temp = temp << j >> 31;
      dividend = s21_mul_long(dividend, two_long);
      dividend.bits[0] = dividend.bits[0] | temp;
      if (!greater_or_equil_long(dividend, divisor)) {
        res = s21_mul_long(res, two_long);
      } else {
        dividend = s21_sub_long(dividend, divisor);
        res = s21_mul_long(res, two_long);
        res.bits[0] = res.bits[0] | 0x1;
      }
    }
  }
  reminder = creat_equal_long(reminder, dividend);

  while (!check_if_long_dec_is_zero(dividend) && k < 28) {
    s21_long_decimal temp_dec = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    dividend = s21_mul_long(dividend, ten_long);
    k++;
    if (greater_or_equil_long(dividend, divisor)) {
      temp_dec = s21_div_long_end(dividend, divisor, &reminder);
      dividend = creat_equal_long(dividend, reminder);
      res = s21_mul_long(res, ten_long);
      res = s21_add_long(res, temp_dec);
    } else {
      res = s21_mul_long(res, ten_long);
    }
  }
  *scale = k;
  return res;
}

s21_long_decimal s21_add_long(s21_long_decimal value_1,
                              s21_long_decimal value_2) {
  s21_long_decimal res = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  int z = 0;
  for (int j = 0; j < S21_LONG; j++) {
    for (int i = 0; i < 32; i++) {
      unsigned int temp_res = 0;
      unsigned int temp_0 = value_1.bits[j];
      unsigned int temp_1 = value_2.bits[j];
      temp_0 = temp_0 >> i << 31 >> 31;
      temp_1 = temp_1 >> i << 31 >> 31;
      if (temp_0 == 0 && temp_1 == 0 && z == 0) {
        temp_res = 0;
        z = 0;
        res.bits[j] = temp_res << i | res.bits[j];
      } else if (temp_0 == 0 && temp_1 == 1 && z == 0) {
        temp_res = 1;
        z = 0;
        res.bits[j] = temp_res << i | res.bits[j];
      } else if (temp_0 == 1 && temp_1 == 0 && z == 0) {
        temp_res = 1;
        z = 0;
        res.bits[j] = temp_res << i | res.bits[j];
      } else if (temp_0 == 1 && temp_1 == 1 && z == 0) {
        temp_res = 0;
        z = 1;
        res.bits[j] = temp_res << i | res.bits[j];
      } else if (temp_0 == 0 && temp_1 == 0 && z == 1) {
        temp_res = 1;
        z = 0;
        res.bits[j] = temp_res << i | res.bits[j];
      } else if (temp_0 == 0 && temp_1 == 1 && z == 1) {
        temp_res = 0;
        z = 1;
        res.bits[j] = temp_res << i | res.bits[j];
      } else if (temp_0 == 1 && temp_1 == 0 && z == 1) {
        temp_res = 0;
        z = 1;
        res.bits[j] = temp_res << i | res.bits[j];
      } else if (temp_0 == 1 && temp_1 == 1 && z == 1) {
        temp_res = 1;
        z = 1;
        res.bits[j] = temp_res << i | res.bits[j];
      }
    }
  }
  return res;
}

s21_long_decimal creat_equal_long(s21_long_decimal value_1,
                                  s21_long_decimal value_2) {
  for (int i = 0; i < S21_LONG; i++) {
    value_1.bits[i] = value_2.bits[i];
  }
  return value_1;
}

int greater_or_equil_long(s21_long_decimal value_1, s21_long_decimal value_2) {
  for (int i = S21_LONG - 1; i >= 0; i--) {
    if ((unsigned int)value_1.bits[i] > (unsigned int)value_2.bits[i]) {
      return 1;
    } else if ((unsigned int)value_1.bits[i] < (unsigned int)value_2.bits[i]) {
      return 0;
    }
  }
  return 1;
}

int check_if_long_dec_is_one(s21_long_decimal x) {
  int temp = 0;
  int res = 0;
  for (int i = 1; i < S21_LONG; i++) {
    temp = temp | (x.bits[i] & 0xffffffff);
  }
  if (x.bits[0] == 1 && temp == 0) {
    res = 1;
  }
  return res;
}

int check_if_long_dec_is_zero(s21_long_decimal x) {
  int res = 0;
  for (int i = 0; i < S21_LONG; i++) {
    res = res | (x.bits[i] & 0xffffffff);
  }
  return !res;
}

int isZero(s21_decimal dec) {
  int res = 1;
  for (int i = 0; i <= 2; i++) {
    unsigned int b = dec.bits[i];
    if (b != 0) {
      res = 0;
      break;
    }
  }
  return res;
}

int s21_bank_round(s21_long_decimal value, int scale,
                   s21_long_decimal *result) {
  int flag = 0;
  s21_long_decimal half = {{5, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal ten_long = {{10, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal two_long = {{2, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal one_long = {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal temp = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal reminder;
  s21_long_decimal x;

  temp = creat_equal_long(temp, value);
  for (int n = 0; n < scale; n++) {
    temp = s21_div_long_end(temp, ten_long, &reminder);
  }
  s21_div_long_end(
      temp, two_long,
      &reminder);
  s21_long_decimal temp_0;
  temp = s21_mul_long(temp, ten_long);
  temp_0 =
      s21_sub_long(value, temp);
  if (greater_or_equil_long(temp_0, half) &&
      !check_if_long_dec_is_zero(s21_sub_long(temp_0, half))) {
    temp = s21_div_long_end(temp, ten_long, &x);
    *result = s21_add_long(temp, one_long);
    *result = s21_mul_long(*result, ten_long);
  } else if (!greater_or_equil_long(temp_0, half)) {
    *result = creat_equal_long(*result, temp);
  } else if (greater_or_equil_long(temp_0, half) &&
             check_if_long_dec_is_zero(s21_sub_long(temp_0, half)) &&
             check_if_long_dec_is_zero(reminder)) {
    *result = creat_equal_long(*result, temp);
  } else if (greater_or_equil_long(temp_0, half) &&
             check_if_long_dec_is_zero(s21_sub_long(temp_0, half)) &&
             !check_if_long_dec_is_zero(reminder)) {
    *result = s21_add_long(temp, ten_long);
  }
  *result = s21_div_long_end(*result, ten_long, &x);
  return flag;
}

int quantity_numbers(s21_long_decimal long_1) {
  int res = 0;
  s21_long_decimal ten_long = {{10, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal reminder;
  while (!check_if_long_dec_is_zero(long_1)) {
    long_1 = s21_div_long_end(long_1, ten_long, &reminder);
    res++;
  }
  return res;
}
