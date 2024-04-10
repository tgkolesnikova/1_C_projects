#include "s21_string.h"

#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

char bufer[100];

s21_size_t s21_strlen(const char *str) {
  const char *sc;
  for (sc = str; *sc != '\0';) ++sc;
  return sc - str;
}
int s21_memcmp(const void *str1, const void *str2, s21_size_t count) {
  const unsigned char *stru1, *stru2;
  int res = 0;
  for (stru1 = str1, stru2 = str2; 0 < count; ++stru1, ++stru2, count--)
    if ((res = *stru1 - *stru2) != 0) break;
  return res;
}
void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *p = str;
  void *ans = s21_NULL;
  while (n--) {
    if ((unsigned char)c == *p++) {
      ans = (void *)(p - 1);
      break;
    }
  }
  return ans;
}
char *s21_strchr(const char *s, int c) {
  char *ans = s21_NULL;
  do {
    if (*s == c) {
      ans = (char *)s;
      break;
    }
  } while (*s++);
  return ans;
}
char *s21_strpbrk(const char *str1, const char *str2) {
  const char *sc1, *sc2;
  void *ans = s21_NULL;
  for (sc1 = str1; ((*sc1) && (!ans)); ++sc1) {
    for (sc2 = str2; ((*sc2) && (!ans)); ++sc2) {
      if (*sc1 == *sc2) ans = (char *)sc1;
    }
  }
  return ans;
}
char *s21_strrchr(const char *str, int c) {
  const char *last = s21_NULL;
  do {
    if (*str == (char)c) last = str;
  } while (*str++);
  return (char *)last;
}
char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t l1 = s21_strlen(haystack), l2 = s21_strlen(needle);
  char *ans = s21_NULL;
  if (!l2) ans = (char *)haystack;
  while ((l1 >= l2) && (!ans)) {
    l1--;
    if (!s21_memcmp(haystack, needle, l2)) ans = (char *)haystack;
    haystack++;
  }
  return ans;
}
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *tmp = dest;
  const char *s = src;
  while (n--) *tmp++ = *s++;
  return dest;
}
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *tmp;
  const char *s;
  if (dest <= src) {
    tmp = dest;
    s = src;
    while (n--) *tmp++ = *s++;
  } else {
    tmp = dest;
    tmp += n;
    s = src;
    s += n;
    while (n--) *--tmp = *--s;
  }
  return dest;
}
void *s21_memset(void *str, int c, s21_size_t n) {
  char *xs = str;
  while (n--) *xs++ = c;
  return str;
}
char *s21_strcpy(char *dest, const char *src) {
  char *tmp = dest;
  while ((*dest++ = *src++) != '\0') {
  }
  return tmp;
}
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *tmp = dest;
  while (n) {
    if ((*tmp = *src) != 0) src++;
    tmp++;
    n--;
  }
  return dest;
}
s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t item = 0;
  const char *stru1, *stru2;
  for (stru1 = str1; *stru1 != '\0'; ++stru1) {
    for (stru2 = str2; *stru2 != '\0'; ++stru2) {
      if (*stru1 == *stru2) break;
    }
    if (*stru2 == '\0') break;
    ++item;
  }
  return item;
}
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *p, *r;
  s21_size_t count = 0;
  for (p = str1; *p != '\0'; ++p) {
    for (r = str2; *r != '\0'; ++r) {
      if (*p == *r) break;
    }
    if (*p == *r) break;
    ++count;
  }
  return count;
}
int s21_strcmp(const char *str1, const char *str2) {
  int item = 0;
  while (1) {
    unsigned char stru1 = *str1++, stru2 = *str2++;
    if (stru1 != stru2) {
      stru1 < stru2 ? item-- : item++;
      break;
    }
    if (!stru1) break;
  }
  return item;
}
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int item = 0;
  while (n) {
    unsigned char stru1 = *str1++, stru2 = *str2++;
    if (stru1 != stru2) {
      stru1 < stru2 ? item-- : item++;
      break;
    }
    if (!stru1) break;
    n--;
  }
  return item;
}
char *s21_strtok(char *str, const char *delim) {
  static unsigned char *last;
  unsigned char *str2, map[32];
  char *tmp;
  const unsigned char *ctrl = (const unsigned char *)delim;
  int count;

  for (count = 0; count < 32; count++) {
    map[count] = 0;
  }
  do {
    map[*ctrl >> 3] |= (1 << (*ctrl & 7));
  } while (*ctrl++);
  if (str) {
    str2 = (unsigned char *)str;
  } else {
    str2 = last;
  }
  while ((map[*str2 >> 3] & (1 << (*str2 & 7))) && *str2) {
    str2++;
  }
  str = (char *)str2;
  for (; *str2; str2++) {
    if (map[*str2 >> 3] & (1 << (*str2 & 7))) {
      *str2++ = '\0';
      break;
    }
  }
  last = str2;
  if (str == (char *)str2) {
    tmp = s21_NULL;
  } else {
    tmp = str;
  }
  return tmp;
}
char *s21_strcat(char *dest, const char *src) {
  char *tmp = dest;
  while (*dest) dest++;
  while ((*dest++ = *src++) != '\0') {
  }
  return tmp;
}
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *tmp = dest;
  if (n) {
    while (*dest) dest++;
    while ((*dest++ = *src++) != 0) {
      if (--n == 0) {
        *dest = '\0';
        break;
      }
    }
  }
  return tmp;
}
void s21_uenum(int n, char s[]) {
  int j, i = 0;
#if defined(__APPLE__) || (__My_APPLE__)
  s21_strcpy(s, "Unknown error: ");
  int lenstr = 15;
#elif defined(__linux__) || (__My_linux__)
  s21_strcpy(s, "Unknown error ");
  int lenstr = 14;
#endif
  for (int z = 0; z < lenstr; z++) s++;
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);
  s[i] = '\0';
  for (i = 0, j = s21_strlen(s) - 1; i < j; i++, j--) {
    char c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}
void *s21_to_upper(const char *str) {
  char *res = s21_NULL;
  int len = s21_strlen(str);
  if (str) {
    res = (char *)malloc(sizeof(char) * (len + 1));
    if (res) {
      for (char *tmp = res; *str != '\0'; str++, tmp++) {
        if (*str >= 'a' && *str <= 'z')
          *tmp = *str - 32;
        else
          *tmp = *str;
      }
      res[len] = 0;
    }
  }
  return (void *)res;
}
void *s21_to_lower(const char *str) {
  char *res = s21_NULL;
  int len = s21_strlen(str);
  if (str) {
    res = (char *)malloc(sizeof(char) * (len + 1));
    if (res) {
      char *tmp = res;
      for (; *str != '\0'; str++, tmp++) {
        if (*str >= 'A' && *str <= 'Z')
          *tmp = *str + 32;
        else
          *tmp = *str;
      }
      res[len] = 0;
    }
  }
  return (void *)res;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = s21_NULL;
  s21_size_t len1 = s21_strlen(src) + 1;
  s21_size_t len2 = s21_strlen(str);
  if (start_index < (len1 + len2) && start_index) {
    res = (char *)calloc((len1 + len2), sizeof(char));
    if (res) {
      if (start_index < len1) {
        for (s21_size_t n = 0; n < start_index; n++) {
          res[n] = src[n];
        }
        for (s21_size_t n = 0; n < len2; n++) {
          res[n + start_index] = str[n];
        }
        for (s21_size_t n = start_index; n < len1; n++) {
          res[n + len2] = src[n];
        }
        res[len2 + len1 - 1] = '\0';
      }
    }
  }
  return (void *)res;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = s21_NULL;
  if (src) {
    s21_size_t len = s21_strlen(src);
    if (!trim_chars) {
      trim_chars = "";
    }
    s21_size_t n1 = s21_strspn(src, trim_chars);
    s21_size_t n2 = 0;
    char *tmp = (char *)src + n1;
    char *end = tmp + s21_strlen(tmp) - 1;
    while ((end != tmp) && s21_strlen(tmp)) {
      if (s21_strchr(trim_chars, *(end--)))
        n2++;
      else
        break;
    }
    res = (char *)calloc((len + 1 - n1 - n2), sizeof(char));
    if (res) {
      s21_strncpy(res, src + n1, len - n1 - n2);
    }
  }
  return (void *)res;
}

char *s21_strerror(int errnum) {
#if defined(__APPLE__) || (__My_APPLE__)
  int num = 107;
#elif defined(__linux__) || (__My_linux__)
  int num = 134;
#endif
  if (errnum < num) {
#if defined(__APPLE__) || (__My_APPLE__)
    char err[107][99] = {"Undefined error: 0",
                         "Operation not permitted",
                         "No such file or directory",
                         "No such process",
                         "Interrupted system call",
                         "Input/output error",
                         "Device not configured",
                         "Argument list too long",
                         "Exec format error",
                         "Bad file descriptor",
                         "No child processes",
                         "Resource deadlock avoided",
                         "Cannot allocate memory",
                         "Permission denied",
                         "Bad address",
                         "Block device required",
                         "Resource busy",
                         "File exists",
                         "Cross-device link",
                         "Operation not supported by device",
                         "Not a directory",
                         "Is a directory",
                         "Invalid argument",
                         "Too many open files in system",
                         "Too many open files",
                         "Inappropriate ioctl for device",
                         "Text file busy",
                         "File too large",
                         "No space left on device",
                         "Illegal seek",
                         "Read-only file system",
                         "Too many links",
                         "Broken pipe",
                         "Numerical argument out of domain",
                         "Result too large",
                         "Resource temporarily unavailable",
                         "Operation now in progress",
                         "Operation already in progress",
                         "Socket operation on non-socket",
                         "Destination address required",
                         "Message too long",
                         "Protocol wrong type for socket",
                         "Protocol not available",
                         "Protocol not supported",
                         "Socket type not supported",
                         "Operation not supported",
                         "Protocol family not supported",
                         "Address family not supported by protocol family",
                         "Address already in use",
                         "Can't assign requested address",
                         "Network is down",
                         "Network is unreachable",
                         "Network dropped connection on reset",
                         "Software caused connection abort",
                         "Connection reset by peer",
                         "No buffer space available",
                         "Socket is already connected",
                         "Socket is not connected",
                         "Can't send after socket shutdown",
                         "Too many references: can't splice",
                         "Operation timed out",
                         "Connection refused",
                         "Too many levels of symbolic links",
                         "File name too long",
                         "Host is down",
                         "No route to host",
                         "Directory not empty",
                         "Too many processes",
                         "Too many users",
                         "Disc quota exceeded",
                         "Stale NFS file handle",
                         "Too many levels of remote in path",
                         "RPC struct is bad",
                         "RPC version wrong",
                         "RPC prog. not avail",
                         "Program version wrong",
                         "Bad procedure for program",
                         "No locks available",
                         "Function not implemented",
                         "Inappropriate file type or format",
                         "Authentication error",
                         "Need authenticator",
                         "Device power is off",
                         "Device error",
                         "Value too large to be stored in data type",
                         "Bad executable (or shared library)",
                         "Bad CPU type in executable",
                         "Shared library version mismatch",
                         "Malformed Mach-o file",
                         "Operation canceled",
                         "Identifier removed",
                         "No message of desired type",
                         "Illegal byte sequence",
                         "Attribute not found",
                         "Bad message",
                         "EMULTIHOP (Reserved)",
                         "No message available on STREAM",
                         "ENOLINK (Reserved)",
                         "No STREAM resources",
                         "Not a STREAM",
                         "Protocol error",
                         "STREAM ioctl timeout",
                         "Operation not supported on socket",
                         "Policy not found",
                         "State not recoverable",
                         "Previous owner died",
                         "Interface output queue is full"};
#elif defined(__linux__) || (__My_linux__)
    char err[134][99] = {
        "Success",
        "Operation not permitted",
        "No such file or directory",
        "No such process",
        "Interrupted system call",
        "Input/output error",
        "No such device or address",
        "Argument list too long",
        "Exec format error",
        "Bad file descriptor",
        "No child processes",
        "Resource temporarily unavailable",
        "Cannot allocate memory",
        "Permission denied",
        "Bad address",
        "Block device required",
        "Device or resource busy",
        "File exists",
        "Invalid cross-device link",
        "No such device",
        "Not a directory",
        "Is a directory",
        "Invalid argument",
        "Too many open files in system",
        "Too many open files",
        "Inappropriate ioctl for device",
        "Text file busy",
        "File too large",
        "No space left on device",
        "Illegal seek",
        "Read-only file system",
        "Too many links",
        "Broken pipe",
        "Numerical argument out of domain",
        "Numerical result out of range",
        "Resource deadlock avoided",
        "File name too long",
        "No locks available",
        "Function not implemented",
        "Directory not empty",
        "Too many levels of symbolic links",
        "Unknown error 41",
        "No message of desired type",
        "Identifier removed",
        "Channel number out of range",
        "Level 2 not synchronized",
        "Level 3 halted",
        "Level 3 reset",
        "Link number out of range",
        "Protocol driver not attached",
        "No CSI structure available",
        "Level 2 halted",
        "Invalid exchange",
        "Invalid request descriptor",
        "Exchange full",
        "No anode",
        "Invalid request code",
        "Invalid slot",
        "Unknown error 58",
        "Bad font file format",
        "Device not a stream",
        "No data available",
        "Timer expired",
        "Out of streams resources",
        "Machine is not on the network",
        "Package not installed",
        "Object is remote",
        "Link has been severed",
        "Advertise error",
        "Srmount error",
        "Communication error on send",
        "Protocol error",
        "Multihop attempted",
        "RFS specific error",
        "Bad message",
        "Value too large for defined data type",
        "Name not unique on network",
        "File descriptor in bad state",
        "Remote address changed",
        "Can not access a needed shared library",
        "Accessing a corrupted shared library",
        ".lib section in a.out corrupted",
        "Attempting to link in too many shared libraries",
        "Cannot exec a shared library directly",
        "Invalid or incomplete multibyte or wide character",
        "Interrupted system call should be restarted",
        "Streams pipe error",
        "Too many users",
        "Socket operation on non-socket",
        "Destination address required",
        "Message too long",
        "Protocol wrong type for socket",
        "Protocol not available",
        "Protocol not supported",
        "Socket type not supported",
        "Operation not supported",
        "Protocol family not supported",
        "Address family not supported by protocol",
        "Address already in use",
        "Cannot assign requested address",
        "Network is down",
        "Network is unreachable",
        "Network dropped connection on reset",
        "Software caused connection abort",
        "Connection reset by peer",
        "No buffer space available",
        "Transport endpoint is already connected",
        "Transport endpoint is not connected",
        "Cannot send after transport endpoint shutdown",
        "Too many references: cannot splice",
        "Connection timed out",
        "Connection refused",
        "Host is down",
        "No route to host",
        "Operation already in progress",
        "Operation now in progress",
        "Stale file handle",
        "Structure needs cleaning",
        "Not a XENIX named type file",
        "No XENIX semaphores available",
        "Is a named type file",
        "Remote I/O error",
        "Disk quota exceeded",
        "No medium found",
        "Wrong medium type",
        "Operation canceled",
        "Required key not available",
        "Key has expired",
        "Key has been revoked",
        "Key was rejected by service",
        "Owner died",
        "State not recoverable",
        "Operation not possible due to RF-kill",
        "Memory page has hardware error",
    };
#endif
    s21_memcpy(bufer, err[errnum], 100);
  } else {
    s21_uenum(errnum, bufer);
  }
  return bufer;
}

int s21_atoi2(const char *str, int *n) {
  int ans = 0;
  while ((str[ans] >= '0') && (str[ans] < ':')) {
    *n = *n * 10 + str[ans++] - '0';
  }
  return ans;
}

void pars_hex(char *str, char *strhex, int num) {
  size_t i = 0, j = 0;
  if ((str[0] == '0') & ((str[1] & 0xDF) == 'X')) {
    i = 2;
    j = 1;
  }

  if (num > 0) {
    num -= 2;
    for (; num--; i++) {
      if ((('0' <= str[i]) & (str[i] <= '9')) ||
          (((str[i] & 0xDF) >= 'A') & ((str[i] & 0xDF) <= 'F'))) {
        if (j == 1) {
          strhex[i - 2] = str[i];
        } else {
          strhex[i] = str[i];
        }
      } else {
        break;
      }
    }
  } else {
    for (; i < s21_strlen(str); i++) {
      if ((('0' <= str[i]) & (str[i] <= '9')) ||
          (((str[i] & 0xDF) >= 'A') & ((str[i] & 0xDF) <= 'F'))) {
        if (j == 1) {
          strhex[i - 2] = str[i];
        } else {
          strhex[i] = str[i];
        }
      } else {
        break;
      }
    }
  }
}

double long hex_to_int(char *str) {
  char *p = str;
  long num = 0;
  while (*p != 0) {
    num <<= 4;
    num += (*p < 'A') ? *p & 0xF : (*p & 0x7) + 9;
    p++;
  }
  return num;
}
int s21_atox(const char *str, void *n, char c, int num) {
  int ans = 0;
  if (num <= 0) {
    if (c == 'd') {
      while ((str[ans] >= '0') && (str[ans] < ':')) {
        *(int *)n = *(int *)n * 10 + str[ans++] - '0';
      }
      if (*--str == '-') {
        *(int *)n = -(*(int *)n);
      }
    } else if (c == 'l') {
      while ((str[ans] >= '0') && (str[ans] < ':')) {
        *(long int *)n = *(long int *)n * 10 + str[ans++] - '0';
      }
      if (*--str == '-') {
        *(long int *)n = -(*(long int *)n);
      }
    } else if (c == 'h') {
      while ((str[ans] >= '0') && (str[ans] < ':')) {
        *(short int *)n = *(short int *)n * 10 + str[ans++] - '0';
      }
      if (*--str == '-') {
        *(short int *)n = -(*(short int *)n);
      }
    } else if (c == 'o') {
      while ((str[ans] >= '0') && (str[ans] < '8')) {
        *(int *)n = *(int *)n * 10 + str[ans++] - '0';
      }
    }
  } else {
    if (c == 'd') {
      while (((str[ans] >= '0') && (str[ans] < ':')) && num--) {
        *(int *)n = *(int *)n * 10 + str[ans++] - '0';
      }
      if (*--str == '-') {
        *(int *)n = -(*(int *)n);
        *(int *)n /= 10;
      }
    } else if (c == 'l') {
      while (((str[ans] >= '0') && (str[ans] < ':')) && num--) {
        *(long int *)n = *(long int *)n * 10 + str[ans++] - '0';
      }
      if (*--str == '-') {
        *(long int *)n = -(*(long int *)n);
        *(long int *)n /= 10;
      }
    } else if (c == 'h') {
      while (((str[ans] >= '0') && (str[ans] < ':')) && num--) {
        *(short int *)n = *(short int *)n * 10 + str[ans++] - '0';
      }
      if (*--str == '-') {
        *(short int *)n = -(*(short int *)n);
        *(short int *)n /= 10;
      }
    } else if (c == 'o') {
      while (((str[ans] >= '0') && (str[ans] < ':')) && num--) {
        *(long int *)n = *(long int *)n * 10 + str[ans++] - '0';
      }
    }
  }
  return ans;
}
int strleni(char *str) {
  int x = 0;
  for (; (*str != 32) && (*str != 0); x++, str++) {
  }
  return x;
}
int s21_atof(const char *str, long double *n) {
  int ans = 0;
  while ((str[ans] >= '0') && (str[ans] < ':')) {
    *n = *n * 10 + str[ans++] - '0';
  }
  return ans;
}
long double search_float(char *str, form f, int *len) {
  long double n = 0, n1 = 0;
  int num1 = 0, num2 = 0;
  num1 += s21_atof(str, &n);
  if (*--str == '-') {
    n = -n;
  }
  str++;
  str += num1;
  if (*str == '.') {
    str++;
    num2 += s21_atof(str, &n1);
  }
  if (n < 0) {
    n1 = -n1;
    num1++;
  }
  int flag = (num1 - f.prop.width) + num2 + 1;
  if ((f.prop.width > 0) && (flag > -1)) {
    for (; flag; n1 /= 10, flag--) {
    }
    n1 = (int)n1;
  }
  for (; n1 >= 1 || n1 <= -1; n1 /= 10) {
  }
  long double res = n + n1;
  int flag2 = num1 - f.prop.width;
  if ((f.prop.width > 0) && (flag2 > -1)) {
    for (; flag2; flag2--) {
      res /= 10;
    }
    if (num1 >= f.prop.width - 1) {
      res = (int)res;
    }
  }
  *len = num1 + num2 + 1;
  return res;
}

int parser(char *format, form *f) {
  char *tmp = format;
  // read flags. Magic of binary operations
  while (s21_strchr("0 -+#", *format)) {
    f->flag.zero |= (*format == '0');
    if (f->flag.sign != '+')
      f->flag.sign |= (*format == ' ') * ' ' + (*format == '+') * '+';
    f->flag.align |= (*format == '-');
    f->flag.hash |= (*format == '#');
    format += 1;
  }
  // width reading
  if ((*format > '0') & (*format < ':')) {
    format += s21_atoi2(format, &(*f).prop.width);
  } else if (*format == '*') {
    f->prop.acc_flag = 1;
    format++;
  }
  // length read
  if (s21_strchr("hlL", *format)) f->data.length = *format++;
  if (s21_strchr("%cdieEfgGosuxXpn", *format)) f->data.spec = *format++;
  return (format - tmp);
}
// Конвертер 8-ой системы в 10-ую
int converter(char *s, int *tmpr, int num) {
  long int res = 0;
  int n = 0;
  if (num) {
    n = s21_atox(s, &res, 'o', num--);
  } else {
    n = s21_atox(s, &res, 'o', num);
  }
  int tmp = n - 1;
  res = 0;
  for (int i = 0; i < n; i++) {
    if ((s[i] != '9') && (s[i] != '8')) {
      res += (s[i] - '0') * pow(8, tmp--);
    }
  }
  *tmpr += n;
  if (*--s == '-') res = -res;
  return res;
}
int filling(form f, va_list list, char *str, int *tmp_n, int *num) {
  int tmp = 0, x = 0;
  if ((f.data.spec == 'c') && (!f.prop.acc_flag)) {
    char *p = va_arg(list, char *);
    *p = *str;
    tmp++;
    x++;
  } else if ((f.data.spec == 's') && (!f.prop.acc_flag)) {
    for (;; tmp++, str++) {
      if (*str != 32) {
        char *p = va_arg(list, char *);
        int N = strleni(str);
        if (f.prop.width > 0) {
          N = f.prop.width;
        }
        for (int i = 0; i < N; i++) {
          *p++ = *str++;
        }
        *p = 0;
        tmp += N;
        break;
      }
    }
    x++;
  } else if ((f.data.spec == 'd') && (!f.prop.acc_flag)) {
    for (;; tmp++, str++) {
      if ((f.data.length == 'h') && (*str > '0') && (*str < ':')) {
        short int *p = va_arg(list, short int *);
        short int n = 0;
        tmp += s21_atox(str, &n, 'h', f.prop.width);
        *p = n;
        break;
      } else if ((*str > '0') && (*str < ':')) {
        int *p = va_arg(list, int *);
        int n = 0;
        int xi = s21_atox(str, &n, 'd', f.prop.width);
        tmp += xi;
        *p = n;
        break;
      }
    }
    x++;
  } else if ((f.data.spec == 'u') && (!f.prop.acc_flag)) {
    for (;; ++tmp, ++str) {
      if ((f.data.length == 'h') && (*str > '0') && (*str < ':')) {
        str += 1;
        short int *p = va_arg(list, short int *);
        short unsigned int n = 0;
        tmp += s21_atox(str, &n, 'h', f.prop.width);
        *p = n;
        break;
      } else if ((f.data.length == 'l') && (*str > '0') && (*str < ':')) {
        str += 1;
        long int *p = va_arg(list, long int *);
        long int n = 0;
        tmp += s21_atox(str, &n, 'l', f.prop.width);
        *p = n;
        break;
      } else if ((*str > '0') && (*str < ':')) {
        str += 1;
        int *p = va_arg(list, int *);
        int n = 0;
        tmp += s21_atox(str, &n, 'd', f.prop.width);
        *p = n;
        break;
      }
    }
    x++;
  } else if ((f.data.spec == 'o') && (!f.prop.acc_flag)) {
    for (;; ++tmp, ++str) {
      if ((f.data.length == 'h') && (*str > '0') && (*str < '8')) {
        short int *p = va_arg(list, short int *);
        *p = converter(str, &tmp, f.prop.width);
        break;
      } else if ((f.data.length == 'l') && (*str > '0') && (*str < '8')) {
        long int *p = va_arg(list, long int *);
        *p = converter(str, &tmp, f.prop.width);
        break;
      } else if ((*str > '0') && (*str < '8')) {
        int *p = va_arg(list, int *);
        *p = converter(str, &tmp, f.prop.width);
        break;
      }
    }
    x++;
  } else if ((f.data.spec == 'n') && (!f.prop.acc_flag)) {
    int *p = va_arg(list, int *);
    *p = *tmp_n;
    x++;
  } else if ((f.data.spec == 'x') || (f.data.spec == 'X')) {
    for (;; ++tmp, ++str) {
      if (str[0] != 32) {
        long *p = va_arg(list, long *);
        char strhex[200] = "0";
        pars_hex(str, strhex, f.prop.width);
        *p = hex_to_int(strhex);
        tmp += strleni(str);
        break;
      }
    }
    x++;
  } else if ((f.data.spec == 'i') && (!f.prop.acc_flag)) {
    for (;; ++tmp, ++str) {
      if ((str[0] == '0') && (str[1] == 'x')) {
        for (;; ++tmp, ++str) {
          long *p = va_arg(list, long *);
          char strhex[200] = "0";
          pars_hex(str, strhex, f.prop.width);
          *p = hex_to_int(strhex);
          tmp += strleni(str);
          break;
        }
        break;
      } else if (str[0] == '0') {
        for (;; ++tmp, ++str) {
          if ((f.data.length == 'h') && (*str > '0') && (*str < '8')) {
            short int *p = va_arg(list, short int *);
            *p = converter(str, &tmp, f.prop.width);
            break;
          } else if ((f.data.length == 'l') && (*str > '0') && (*str < '8')) {
            long int *p = va_arg(list, long int *);
            *p = converter(str, &tmp, f.prop.width);
            break;
          } else if ((*str > '0') && (*str < '8')) {
            int *p = va_arg(list, int *);
            *p = converter(str, &tmp, f.prop.width);
            break;
          }
        }
        break;
      } else if ((*str > '0') && (*str < ':')) {
        for (;; tmp++, str++) {
          if ((f.data.length == 'h') && (*str > '0') && (*str < ':')) {
            short int *p = va_arg(list, short int *);
            short int n = 0;
            tmp += s21_atox(str, &n, 'h', f.prop.width);
            *p = n;
            break;
          } else if ((*str > '0') && (*str < ':')) {
            int *p = va_arg(list, int *);
            int n = 0;
            tmp += s21_atox(str, &n, 'd', f.prop.width);
            *p = n;
            break;
          }
        }
        break;
      }
    }
    x++;
  } else if ((s21_strchr("GefEg", f.data.spec)) && (!f.prop.acc_flag)) {
    for (;; tmp++, str++) {
      if ((*str > '0') & (*str < ':')) {
        if (f.data.length == 'L') {
          long double *p = va_arg(list, long double *);
          long double n = 0, n1 = 0;
          int num1 = 0, num2 = 0, len = 0;
          num1 += s21_atof(str, &n);
          if (*--str == '-') {
            n = -n;
          }
          str++;
          str += num1;
          if (*str == '.') {
            str -= num1;
            n = search_float(str, f, &len);
            num1 = len;
            n > 0 ? str : str--, num1--;
            str += len;
          }
          int minus = 0;
          if (*str == 'e') {
            str++;
            if (*str == '-') {
              minus++;
              str++;
            }
            num2 += s21_atof(str, &n1);
            minus ? num1++ : num1;
          }
          if ((f.prop.width > 0) && (f.prop.width <= num1 + 2)) {
            str -= num2 + num1;
            *p = search_float(str, f, &len);
            tmp += num1 + num2 + 1;
            break;
          }
          if (minus)
            *p = (n / pow(10., n1));
          else
            *p = (n * pow(10., n1));
          tmp += num1 + num2 + 1;
          break;
        } else if (f.data.length == 'l') {
          double *p = va_arg(list, double *);
          long double n = 0, n1 = 0;
          int num1 = 0, num2 = 0, len = 0;
          num1 += s21_atof(str, &n);
          if (*--str == '-') {
            n = -n;
          }
          str++;
          str += num1;
          if (*str == '.') {
            str -= num1;
            n = (double)search_float(str, f, &len);
            num1 = len;
            n > 0 ? str : str--, num1--;
            str += len;
          }
          int minus = 0;
          if (*str == 'e') {
            str++;
            if (*str == '-') {
              minus++;
              str++;
            }
            num2 += s21_atof(str, &n1);
            minus ? num1++ : num1;
          }
          if ((f.prop.width > 0) && (f.prop.width <= num1 + 2)) {
            str -= num2 + num1;
            *p = (double)search_float(str, f, &len);
            tmp += num1 + num2 + 1;
            break;
          }
          if (minus)
            *p = (double)(n / pow(10., n1));
          else
            *p = (double)(n * pow(10., n1));
          tmp += num1 + num2 + 1;
          break;
        } else {
          float *p = va_arg(list, float *);
          long double n = 0, n1 = 0;
          int num1 = 0, num2 = 0, len = 0;
          num1 += s21_atof(str, &n);
          if (*--str == '-') {
            n = -n;
          }
          str++;
          str += num1;
          if (*str == '.') {
            str -= num1;
            n = (float)search_float(str, f, &len);
            num1 = len;
            n > 0 ? str : str--, num1--;
            str += len;
          }
          int minus = 0;
          if (*str == 'e') {
            str++;
            if (*str == '-') {
              minus++;
              str++;
            }
            num2 += s21_atof(str, &n1);
            minus ? num1++ : num1;
          }
          if ((f.prop.width > 0) && (f.prop.width <= num1 + 2)) {
            str -= num2 + num1;
            *p = (float)search_float(str, f, &len);
            tmp += num1 + num2 + 1;
            break;
          }
          if (minus)
            *p = (float)(n / pow(10., n1));
          else
            *p = (float)(n * pow(10., n1));
          tmp += num1 + num2 + 1;
          break;
        }
      }
    }
    x++;
  } else if ((f.data.spec == 'p') && (!f.prop.acc_flag)) {
    for (;; ++tmp, ++str) {
      if (str[0] != 32) {
        long *p = va_arg(list, long *);
        char strhex[200] = "0";
        pars_hex(str, strhex, f.prop.width);
        *p = hex_to_int(strhex);
        tmp += strleni(str);
        break;
      }
    }
    x++;
  } else if (f.data.spec == '%') {
  } else {
    if (f.data.spec == 'c')
      tmp++;
    else
      tmp += strleni(str);
  }
  *tmp_n += tmp;
  *num += x;
  return tmp;
}
// SSCANF
int s21_sscanf(char *str, char *format, ...) {
  int tmp_n = 0, num = 0;
  va_list list;
  va_start(list, format);
  if ((*str == '\0') || (*str == ' ') || (*str == '\n')) {
    num = -1;
  } else {
    while (*format) {
      if (*format == '%') {
        form f = {{0, 0, 0, 0}, {0, 0, 0}, {0, 0}};
        int x = parser(++format, &f);
        format += x;
        str += filling(f, list, str, &tmp_n, &num);
      } else {
        if (s21_strchr(" \t\n\v\r\f", *format)) {
          format++;
          continue;
        }
        if (*str++ == *format++) {
        } else {
          break;
        }
      }
    }
  }
  va_end(list);
  return num;
}

int parser_print(char *format, va_list list, form *f) {
  char *tmp = format;
  // read flags. Magic of binary operations
  while (s21_strchr("0 -+#", *format)) {
    f->flag.zero |= (*format == '0');
    if (f->flag.sign != '+')
      f->flag.sign |= (*format == ' ') * ' ' + (*format == '+') * '+';
    f->flag.align |= (*format == '-');
    f->flag.hash |= (*format == '#');
    format += 1;
  }
  // width reading

  if ((*format > '0') & (*format < ':')) {
    format += s21_atoi(format, &(*f).prop.width);
  } else if (*format == '*') {
    f->prop.width = va_arg(list, s21_size_t);
    format++;
  }
  // accu reading
  if (*format == '.') {
    format++;
    if ((*format >= '0') & (*format < ':')) {
      format += s21_atoi(format, &(*f).prop.accuracy);
    } else if (*format == '*') {
      f->prop.accuracy = va_arg(list, s21_size_t);
      format++;
    }
  } else {
    f->prop.acc_flag = 1;
  }
  // length read
  while (s21_strchr("hlL", *format)) {
    (f->data.length == 'l') ? (*format++) : (f->data.length = *format++);
  }
  if (s21_strchr("cs%diufngGpxXeEo", *format)) f->data.spec = *format++;
  return (format - tmp);
}
int s21_sprintf(char *str, char *format, ...) {
  char *tmp = str;
  va_list list;
  va_start(list, format);
  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
    } else {
      form f = {{0, 0, 0, 0}, {0, 0, 0}, {0, 0}};
      int p = parser_print(++format, list, &f);
      format += p;
      str += strgen(f, list, str, tmp);
    }
  }
  va_end(list);
  return str - tmp + (*str = 0);
}
void form_s(char *format, form f) {
  format[0] = '%';
  char w[1024] = {0};
  int i = 1;
  if (f.flag.align) format[i++] = '-';
  if (f.flag.hash) format[i++] = '#';
  if (f.flag.zero) format[i++] = '0';
  if (f.flag.sign) format[i++] = f.flag.sign;
  format[i++] = 0;
  s21_itoa(f.prop.width, 0, 0, w);
  s21_strcat(format, w);
  i = s21_strlen(format);
  if (!f.prop.acc_flag) {
    format[i++] = '.';
    format[i++] = 0;
    s21_itoa(f.prop.accuracy, 0, 0, w);
    s21_strcat(format, w);
  }
  i = s21_strlen(format);
  if (f.data.length) format[i++] = f.data.length;
  format[i++] = f.data.spec;
  format[i] = 0;
}
void strip(char *str) {
  if (s21_strchr(str, '.')) {
    for (int m = s21_strchr(str, '.') - str; str[m]; m++) str[m] = str[m + 1];
  }
  while (str[0] == '0')
    for (int m = 0; str[m]; m++) str[m] = str[m + 1];
  str[s21_strlen(str)] = 0;
  for (int m = s21_strlen(str); m > 1; m--) str[m] = str[m - 1];
  str[1] = '.';
}
int powerL(long double x) {
  int m = 0;
  if (x < 0) x = -x;
  if (x > 1) {
    for (; x >= 10; x /= 10) m++;
  } else {
    for (; ((x < 1) && (x != 0)); x *= 10) m--;
  }
  return m;
}
int power(double x) {
  int m = 0;
  if (x < 0) x = -x;
  if (x > 1) {
    for (; x >= 10; x /= 10) m++;
  } else {
    for (; ((x < 1) && (x != 0)); x *= 10) m--;
  }
  return m;
}
int strgen(form f, va_list l, char *s, const char *t) {
  char str[1024] = {0}, *tmp = s;
  int len;
  if (f.data.spec == 'c') {
    if (f.flag.align) {
      *s++ = va_arg(l, int);
      for (; --f.prop.width > 0;) *s++ = ' ';
    } else {
      for (; --f.prop.width > 0;) *s++ = 32 + 16 * f.flag.zero;
      *s++ = va_arg(l, int);
    }
  } else if (f.data.spec == 's') {
    char *c = va_arg(l, char *);
    if (f.prop.acc_flag) {
      f.prop.accuracy = s21_strlen(c);
    } else {
      if ((s21_size_t)f.prop.accuracy > s21_strlen(c))
        f.prop.accuracy = s21_strlen(c);
    }
    if (f.flag.align) {
      if (f.prop.width >= (int)s21_strlen(c)) f.prop.width -= s21_strlen(c);
      for (char *i = c; ((*i) && (f.prop.accuracy--)); i++) *s++ = *i;
      for (; (f.prop.width-- > f.prop.accuracy);) *s++ = ' ';
    } else {
      for (; (f.prop.width-- > f.prop.accuracy);) *s++ = ' ' + 16 * f.flag.zero;
      for (char *i = c; ((*i) && (f.prop.accuracy--)); i++) *s++ = *i;
    }
  } else if (s21_strchr("iud", f.data.spec)) {
    if (f.data.length == 'h') {
      (f.data.spec == 'u') ? (s21_uitoa((unsigned short int)va_arg(l, int),
                                        f.prop.accuracy, str))
                           : (s21_itoa((short)va_arg(l, int), f.flag.sign,
                                       f.prop.accuracy, str));
    } else if (f.data.length == 'l') {
      (f.data.spec == 'u') ? (s21_uitoa((unsigned long)va_arg(l, unsigned long),
                                        f.prop.accuracy, str))
                           : (s21_itoa((long int)va_arg(l, long int),
                                       f.flag.sign, f.prop.accuracy, str));
    } else {
      (f.data.spec == 'u')
          ? (s21_uitoa((unsigned int)va_arg(l, int), f.prop.accuracy, str))
          : (s21_itoa(va_arg(l, int), f.flag.sign, f.prop.accuracy, str));
    }
    int i = 0;
    if ((!f.prop.acc_flag) && (f.prop.accuracy == 0)) {
      if ((str[0] == '0') && (str[1] == 0)) str[0] = 0;
      if ((s21_strchr("+- ", str[0])) && (str[1] == '0') && (str[2] == 0))
        str[1] = 0;
    }

    len = s21_strlen(str);
    if (f.flag.align) {
      for (; str[i]; i++) *s++ = str[i];
      for (; (f.prop.width-- > len);) *s++ = ' ';
    } else {
      if ((s21_strchr("+- ", str[0])) && f.flag.zero) *s++ = str[i++];
      for (; (f.prop.width-- > len);) *s++ = ' ' + 16 * f.flag.zero;
      for (; str[i]; i++) *s++ = str[i];
    }
  } else if (f.data.spec == 'f') {
    int n;
    if (f.prop.acc_flag) f.prop.accuracy = 6;
    if (f.data.length == 'L') {
      long double x = (long double)va_arg(l, long double);
      n = isnan(x) + 2 * (x == INFINITY) + 3 * (x == -INFINITY);
      if (!n) s21_ftoa(x, f, str);
    } else {
      double x = va_arg(l, double);
      n = isnan(x) + 2 * (x == INFINITY) + 3 * (x == -INFINITY);
      if (!n) s21_ftoa(x, f, str);
    }
    if (n) {
      char *err[3] = {"nan", "inf", "-inf"};
      if (n == 2) str[0] = f.flag.sign;
      s21_strcat(str, err[n - 1]);
    }
    len = s21_strlen(str);

    if (f.flag.align) {
      for (int i = 0; str[i]; i++) *s++ = str[i];
      for (; (f.prop.width-- > len);) *s++ = ' ';
    } else {
      int i = 0;
      if (((s21_strchr("+- ", str[0])) && f.flag.zero) && (!n)) *s++ = str[i++];
      for (; (f.prop.width-- > len);) *s++ = 32 + 16 * f.flag.zero * (!n);
      for (; str[i]; i++) *s++ = str[i];
    }
  } else if (f.data.spec == '%') {
    *s++ = '%';
  } else if (f.data.spec == 'n') {
    *va_arg(l, int *) = tmp - t;
  } else if (s21_strchr("gG", f.data.spec)) {
    char format[1024];
    if (f.prop.acc_flag) f.prop.accuracy = 6;
    if (f.prop.accuracy < 1) f.prop.accuracy = 1;
    f.prop.acc_flag = 0;
    if (f.data.length == 'L') {
      long double x = va_arg(l, long double);
      if ((powerL(x) < f.prop.accuracy) && (powerL(x) > -5)) {
        f.prop.accuracy -= powerL(x) + 1;
        if (f.prop.accuracy <= 0) f.prop.accuracy = 0;
        f.data.spec = 'f';
        form_s(format, f);
        len = s21_strlen(format);
      } else {
        f.prop.accuracy -= 1;
        f.data.spec = (f.data.spec == 'g') ? 'e' : 'E';
        form_s(format, f);
        len = s21_strlen(format);
      }
      s21_sprintf(str, format, x);
      if (f.flag.hash == 0) {
        int lj = (format[len - 1] == 'f')
                     ? (s21_strlen(str) - 1)
                     : (long unsigned int)(s21_strchr(str, format[len - 1]) -
                                           str - 1);
        int h = 0;
        int beg = s21_strchr(str, '.') - str;
        for (int z = lj; (z > beg); z--) {
          if (str[z] == '0')
            h++;
          else
            break;
        }
        f.prop.accuracy -= h;
        form_s(format, f);
        s21_sprintf(str, format, x);
      }
    } else {
      double x = va_arg(l, double);
      if ((powerL(x) < f.prop.accuracy) && (powerL(x) > -5)) {
        f.prop.accuracy -= powerL(x) + 1;
        if (f.prop.accuracy <= 0) f.prop.accuracy = 0;
        f.data.spec = 'f';
        form_s(format, f);
        len = s21_strlen(format);
      } else {
        f.prop.accuracy -= 1;
        f.data.spec = (f.data.spec == 'g') ? 'e' : 'E';
        form_s(format, f);
        len = s21_strlen(format);
      }
      s21_sprintf(str, format, x);
      if (f.flag.hash == 0) {
        int li = (format[len - 1] == 'f')
                     ? (s21_strlen(str) - 1)
                     : (long unsigned int)(s21_strchr(str, format[len - 1]) -
                                           str - 1);
        int h = 0;
        int beg = s21_strchr(str, '.') - str;
        for (int z = li; (z > beg); z--) {
          if (str[z] == '0')
            h++;
          else
            break;
        }
        f.prop.accuracy -= h;
        form_s(format, f);
        s21_sprintf(str, format, x);
      }
    }
    for (int i = 0; str[i]; i++) *s++ = str[i];

  } else if (s21_strchr("pxX", f.data.spec)) {
    char *hex = "0123456789abcdef", str2[18] = {0};
    if (f.data.spec == 'X') hex = "0123456789ABCDEF";
    s21_size_t x = va_arg(l, s21_size_t);
    int m = 16;
    for (int i = 15; i >= 0; i--) {
      str2[i] = hex[x & 15];
      x >>= 4;
    }
    if (f.data.spec != 'p') {
      s21_reverse(str2);
      if (f.data.length == 'h')
        m = 4;
      else if (f.data.length == 0)
        m = 8;
      str2[m] = 0;
      s21_reverse(str2);
    }
    while (*str2 == '0') {
      for (int i = 0; i < 17; i++) str2[i] = str2[i + 1];
    }
    if (*str2 == 0) {
      *str2 = '0';
      str2[1] = 0;
    }
    len = s21_strlen(str2);
    m = 0;
    if ((f.data.spec == 'p') || (f.flag.hash)) {
      str[0] = '0';
      if ((f.data.spec == 'x') | (f.data.spec == 'p'))
        str[1] = 'x';
      else
        str[1] = 'X';
      m = 2;
    }
    for (; f.prop.accuracy-- > len; m++) str[m] = '0';
    for (int i = 0; str2[i]; i++) str[i + m] = str2[i];
    if ((!f.prop.acc_flag) && (f.prop.accuracy <= 0) && (str[0] == '0') &&
        (str[1] == 0))
      str[0] = 0;

    len = s21_strlen(str);
    if (f.flag.align) {
      if (f.flag.sign && (s21_strchr("po", f.data.spec))) {
        *s++ = f.flag.sign;
        f.prop.width--;
      }
      for (int i = 0; str[i]; i++) *s++ = str[i];
      for (; (f.prop.width-- > len);) *s++ = ' ';
    } else {
      for (; (f.prop.width-- > len);) *s++ = ' ' + 16 * f.flag.zero;
      if (f.flag.sign && (s21_strchr("po", f.data.spec))) {
        *s++ = f.flag.sign;
        // f.prop.width--;
      }
      for (int i = 0; str[i]; i++) *s++ = str[i];
    }
    *s = 0;
  } else if (s21_strchr("o", f.data.spec)) {
    char *hex = "01234567", str2[100] = {0};
    if (f.prop.acc_flag && f.flag.hash) f.prop.accuracy = 4;
    if (f.data.length == 'l') {
      unsigned long long x = (unsigned long long)va_arg(l, unsigned long long);
      int i = 0;
      do {
        str2[i++] = hex[x % 8];
        x /= 8;
      } while (x);
      str2[i] = 0;
      s21_reverse(str2);
    } else if (f.data.length == 'h') {
      unsigned short x = (unsigned short int)va_arg(l, unsigned int);
      for (int i = 15; i >= 0; i--) {
        str2[i] = hex[x & 7];
        x /= 8;
      }
    } else {
      unsigned int x = (unsigned int)va_arg(l, unsigned int);
      for (int i = 15; i >= 0; i--) {
        str2[i] = hex[x & 7];
        x >>= 3;
      }
    }
    int m = 0;
    while (*str2 == '0') {
      for (int i = 0; i < 17; i++) str2[i] = str2[i + 1];
    }
    if ((*str2 == 0) && (f.flag.hash || f.prop.accuracy || f.prop.acc_flag)) {
      *str2 = '0';
      str2[1] = 0;
    }
    len = s21_strlen(str2);
    for (; f.prop.accuracy-- > len; m++) str[m] = '0';
    for (int i = 0; str2[i]; i++) str[i + m] = str2[i];
    len = s21_strlen(str);
    if (f.flag.align) {
      for (int i = 0; str[i]; i++) *s++ = str[i];
      for (; (f.prop.width-- > len);) *s++ = ' ';
    } else {
      for (; (f.prop.width-- > len);) *s++ = ' ' + 16 * f.flag.zero;
      for (int i = 0; str[i]; i++) *s++ = str[i];
    }
  } else if (s21_strchr("eE", f.data.spec)) {
    char str2[1024] = {0};
    int e = 0, chk = 1, sign = 0, n = 0;
    if (f.prop.acc_flag) f.prop.accuracy = 6;
    if (f.data.length == 'L') {
      long double x = (long double)va_arg(l, long double);
      n = isnan(x) + 2 * (x == INFINITY) + 3 * (x == -INFINITY);
      if (!n) {
        if (x < 0) {
          sign = 1;
          x = -x;
        }
        e = powerL(x);
        s21_eftoa(x, f.prop.accuracy - e + 2, str2);
      }
    } else {
      double x = va_arg(l, double);
      n = isnan(x) + 2 * (x == INFINITY) + 3 * (x == -INFINITY);
      if (!n) {
        if (x < 0) {
          sign = 1;
          x = -x;
        }
        e = power(x);
        s21_eftoa(x, f.prop.accuracy - e + 2, str2);
      }
    }
    int last = s21_strlen(str2) - 2 + chk;
    if (((str2[last] > '4') || (str2[last] == '.')) && (!n)) {
      if (e >= 0) {
        for (int i = 0; i < last; i++) {
          if ((str2[i] != '9') && (str2[i] != '.')) chk = 0;
        }
      } else {
        while (str2[--last] == '9') {
        }
        for (int i = 0; i <= last; i++) {
          if ((str2[i] != '0') && (str2[i] != '.')) chk = 0;
        }
      }
    } else {
      chk = 0;
    }
    if (!n) {
      last = s21_strlen(str2) - 1 - chk;
      e += chk;
      if (str2[last] == '.') str2[last--] = 0;
      if ((int)s21_strlen(str2) > f.prop.accuracy + 1) {
        if (str2[last] > '4') {
          str2[last--] = 0;
          str2[last] += 1;
        } else {
          str2[last] = 0;
        }
      }
      for (int j = last; j > 0; j--) {
        if (str2[j] == 58) {
          str2[j] = '0';
          str2[j - 1] += 1;
        } else if (str2[j] == 47) {
          str2[j] = '.';
          str2[j - 1] += 1;
        }
      }
      if (str2[0] == 58) {
        str2[0] = '0';
        for (int j = last; j >= 0; j--) str2[j + 1] = str2[j];
        str2[0] = '1';
      }
      strip(str2);
      for (int i = 0; i < f.prop.accuracy + 2; i++) str[i] = str2[i];
      len = s21_strlen(str);
      if ((str[len - 1] == '.') && (!f.flag.hash)) str[len - 1] = 0;
      len = s21_strlen(str);
      str[len] = f.data.spec;
      str[len + 1] = 0;
      s21_sprintf(str2, "%0+3.2d", e);
      s21_strcat(str, str2);
      len = s21_strlen(str);

      if ((sign) || (f.flag.sign)) {
        for (int m = len; m >= 0; m--) str[m + 1] = str[m];
        if (sign)
          str[0] = '-';
        else
          str[0] = f.flag.sign;
      }

      len = s21_strlen(str);
      if (f.flag.align) {
        for (int i = 0; str[i]; i++) *s++ = str[i];
        for (; (f.prop.width-- > len);) *s++ = ' ';
      } else {
        int i = 0;
        if (((s21_strchr("+- ", str[0])) && f.flag.zero) && (!n))
          *s++ = str[i++];
        for (; (f.prop.width-- > len);) *s++ = 32 + 16 * f.flag.zero * (!n);
        for (; str[i]; i++) *s++ = str[i];
      }

    } else {
      if (n == 2) str[0] = f.flag.sign;
      char *err[3] = {"nan", "inf", "-inf"};
      s21_strcat(str, err[n - 1]);
      len = s21_strlen(str);
      if (f.flag.align) {
        for (int i = 0; str[i]; i++) *s++ = str[i];
        for (; (f.prop.width-- > len);) *s++ = ' ';
      } else {
        int i = 0;
        if (s21_strchr("+- ", str[0])) *s++ = str[i++];
        for (; (f.prop.width-- > len);) *s++ = 32 + 16 * f.flag.zero * (!n);
        for (; str[i]; i++) *s++ = str[i];
      }
    }
  }
  return (s - tmp);
}
void s21_eftoa(long double n, int acc, char *s) {
  int i = 0;
  long long int m = (int)n;
  do {
    s[i++] = m % 10 + '0';
  } while ((m /= 10) > 0);
  s[i] = '\0';
  s21_reverse(s);
  if (acc > 0) s[i++] = '.';
  n -= (long int)n;
  while (--acc > 0) {
    n = n * 10;
    s[i++] = '0' + (int)n;
    n = n - (int)n;
  }
  s[i] = '\0';
}
void s21_uitoa(s21_size_t n, unsigned int eq, char *s) {
  unsigned long int i = 0, m = n;
  for (; m > 0; i++) m /= 10;
  if (eq < i) eq = i;
  i = 0;
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);
  for (; i < eq; i++) s[i] = '0';
  s[i] = '\0';
  s21_reverse(s);
}
int s21_atoi(const char *str, int *n) {
  int ans = 0;
  while ((str[ans] >= '0') && (str[ans] < ':')) *n = *n * 10 + str[ans++] - '0';
  return ans;
}
void s21_itoa(long n, char f, int eq, char *s) {
  long i = 0, m = n;
  if (n == LONG_MIN) {
    char str[100] = "-9223372036854775808";
    for (; str[i]; i++) s[i] = str[i];
    *(str + i) = 0;
  } else {
    long sign;
    if (m < 0) m = -m;
    for (; m > 0; i++) m /= 10;
    if (eq < i) eq = i;
    i = 0;
    if ((sign = n) < 0) n = -n;
    do {
      s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    for (; i < eq; i++) s[i] = '0';
    (sign < 0) ? (s[i++] = '-') : ((f) ? (s[i++] = f) : (s[i] = 0));
    s[i] = '\0';
    s21_reverse(s);
  }
}
void s21_ftoa(long double n, form f, char *s) {
  int i = 0, sign = (n < 0) ? -1 : 1, j = f.prop.accuracy;
  long long int m = (long long int)n;
  if (sign < 0) m = -m;
  do {
    s[i++] = m % 10 + '0';
  } while ((m /= 10) > 0);
  (sign < 0) ? (s[i++] = '-')
             : ((f.flag.sign) ? (s[i++] = f.flag.sign) : (s[i] = 0));
  s[i] = '\0';
  s21_reverse(s);
  if ((++f.prop.accuracy > 0) || (f.flag.hash)) {
    s[i++] = '.';
    if (n < 0) n = -n;
    n -= (int)n;
    for (; f.prop.accuracy--; n -= (int)n) s[i++] = '0' + (int)(n *= 10);
  }
  int k = 0;
  if ((s[0] == '+') || (s[0] == '-') || (s[0] == ' ')) k++;
  if (s[--i] > '4') s[i - 1] += 1;
  for (int u = i; u > k; u--) {
    if (s[u] == 58) {
      s[u] = '0';
      s[u - 1] += 1;
    } else if (s[u] == 47) {
      s[u] = '.';
      s[u - 1] += 1;
    }
  }
  if (s[k] == 58) {
    s[k] = '0';
    for (int u = i; u >= 0; u--) s[u + 1] = s[u];
    s[k] = '1';
    i++;
  }
  if ((j <= 0) && (!f.flag.hash)) *s21_strchr(s, '.') = 0;
  s[i] = '\0';
}
void s21_reverse(char s[]) {
  int i, j;
  for (i = 0, j = s21_strlen(s) - 1; i < j; i++, j--) {
    char c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}
