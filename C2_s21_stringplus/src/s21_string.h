#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_
#define s21_size_t unsigned long
#define s21_NULL (void *)0
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct fl {
  char align;
  char sign;
  char zero;
  char hash;
} fl;
typedef struct pr {
  int width;
  int accuracy;
  char acc_flag;
} pr;
typedef struct tp {
  int length;
  char spec;
} tp;
typedef struct form {
  fl flag;
  pr prop;
  tp data;
} form;
int s21_sscanf(char *str, char *format, ...);
s21_size_t s21_strlen(const char *str);
int s21_isdigit(const char *ch);
int s21_memcmp(const void *str1, const void *str2, s21_size_t count);
void *s21_memchr(const void *str, int c, s21_size_t n);
char *s21_strchr(const char *str, int c);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strspn(const char *str1, const char *str2);
s21_size_t s21_strcspn(const char *str1, const char *str2);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strtok(char *str, const char *delim);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
void s21_uenum(int n, char s[]);
char *s21_strerror(int errnum);
void *s21_trim(const char *src, const char *trim_chars);
void trim_extra(const char *src, const char *trim_chars, char *p);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);
void s21_ftoa(long double n, form f, char *s);
void s21_itoa(long n, char f, int eq, char *s);
int s21_atoi(const char *str, int *n);
void s21_uitoa(s21_size_t n, unsigned int eq, char *s);
void s21_eftoa(long double n, int acc, char *s);
int strgen(form f, va_list l, char *s, const char *t);
int power(double x);
int powerL(long double x);
void strip(char *str);
void form_s(char *format, form f);
int s21_sprintf(char *str, char *format, ...);
int parser_print(char *format, va_list list, form *f);
void s21_reverse(char s[]);
#endif  // SRC_S21_STRING_H_
