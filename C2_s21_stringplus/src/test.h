#ifndef SRC_TEST_H_
#define SRC_TEST_H_
#include <check.h>
char string1[5][20] = {"heLLo", "wOrlD", "!", " ", ""};
char string2[5][20] = {"hEll", "oRd", " ", "", "!"};

char array_test_to_upper[5][20] = {"HELLO", "WORLD", "!", " ", ""};
char array_test_to_lower[5][20] = {"hello", "world", "!", " ", ""};

char string1_test_insert[5][18] = {"heLLo", "wOrlD", "-><-", "pi", "21"};
char string2_test_insert[5][23] = {"heLLo", "wOrlD", "tyt", "zza", "_sharaga"};
char array_test_insert[5][20] = {"heheLLoLLo", "wOwOrlDrlD", "->tyt<-", "pizza",
                                 "21_sharaga"};
char array_test_trim[5][20] = {"eLLo", "wOrlD", "!", " ", ""};

unsigned char s[10] = "";
char c[5] = {'e', 'w', 'q', ' ', 'f'};
char *st = " levwd !";
int intsscanf, sign(int x);
char *charsscanf;
char str_sscanf_d[10][20] = {"243", "425", "234", "863", "",
                             " ",   "\n",  "5 4", "-72", "+64"};
char str_sscanf_i[14][30] = {"fCe0", "0xB24", "k24F8", "",       " ",
                             "\n",   "F28L2", "-f276", "-0xF2A", "28",
                             "076",  "-72",   "-91",   "-026"};
char str_sscanf_eEfgG[10][30] = {"324.7416",
                                 "23.234",
                                 "456.24735",
                                 "-32.56"
                                 "4.87",
                                 "+2.92834629365",
                                 "",
                                 " ",
                                 "\n",
                                 "7f3.2"};
char str_sscanf_o[10][30] = {"0752",  "-0234", "234", "+4142", "-193452",
                             "06f25", "",      " ",   "\n",    "062346723"};
char str_sscanf_u[10][30] = {"243", "425", "34",  "86j3", "",
                             " ",   "\n",  "5 4", "-72",  "+64"};
char str_sscanf_x[11][30] = {"0xfb2", "0x2aFg78", "a2Bi90", "f25c",
                             "-F26",  "-0xB72",   "+64F",   "+0x56Bf",
                             "",      " ",        "\n"};
char str_sscanf_X[11][30] = {"0xfb2", "0x2aFg78", "a2Bi90", "f25c",
                             "-F26",  "-0xB72",   "+64F",   "+0x56Bf",
                             "",      " ",        "\n"};
char str_sscanf_p[11][30] = {"0xfb2", "0x2aFg78", "a2Bi90", "f25c",
                             "-F26",  "-0xB72",   "+64F",   "+0x56Bf",
                             "",      " ",        "\n"};
char str_sscanf_c[7][10] = {"s", "6", "g23", "fasf", "21", "xc", "\n"};
char str_sscanf_s[6][20] = {"s24", "34d3", "-f43", "", " ", "\n"};

char *format[] = {"%0d", "%i", "%e", "%E", "%f", "%g", "%G",
                  "%o",  "%u", "%x", "%X", "%p", "%n"};
char *format2[] = {"%c", "%s"};

Suite *example_suite_create(void);

#endif  // SRC_TEST_H_
