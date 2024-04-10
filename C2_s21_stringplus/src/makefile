.PHONY: all a clean gcov_report s21_string remove_s21_string linter cppcheck leaks
CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
TEST_LIB = s21_string
TESTFILE = test
GCOV_FLAG = -fprofile-arcs -ftest-coverage
LIBS_FOR_CHECK_PCKG =
D_OS =
OS = $(shell uname -s)
ifeq ($(OS), Linux)
	LIBS_FOR_CHECK_PCKG = -lcheck -lsubunit -lm -lpthread -lrt
	D_OS = -D __My_Linux__
else
	LIBS_FOR_CHECK_PCKG = -lcheck -lm -lpthread
	D_OS = -D __My_APPLE__
endif

all: clean s21_string.a test gcov_report

a: clear clean linter cppchek s21_string.a test gcov_report

test: s21_string.a
	@echo "=========== test ==========="
	$(CC) $(FLAGS) -o a.out test.c $(TEST_LIB).a $(LIBS_FOR_CHECK_PCKG) $(GCOV_FLAG)
	./a.out

gcov_report:
	$(CC) $(D_OS) -c $(FLAGS) $(GCOV_FLAG) $(TEST_LIB).c -o $(TEST_LIB).a
	$(CC) $(FLAGS) $(GCOV_FLAG) $(TEST_LIB).a $(TESTFILE).c $(LIBS_FOR_CHECK_PCKG) -o a2.out
	./a2.out
	@echo "=== gcov start ==="
	gcov a2.out
	lcov -o test.info -c -d .
	genhtml -o report test.info

s21_string.a: remove_s21_string.a
	@echo "=== s21_string compile ==="
	$(CC) $(D_OS) -c $(FLAGS) $(TEST_LIB).c -o $(TEST_LIB).a

remove_s21_string.a:
	rm -f *$(TEST_LIB)*.a *$(TEST_LIB)*.o

linter:
	@echo "########## linter start ##########"
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h

cppcheck:
	@echo "########## cppcheck start ##########"
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

leaks:
	CK_FORK=no leaks --atExit -- ./a.out

clean:
	rm -f *.a *.o *.so *.out $(TESTFILE) *.info *.gcno *.gcda
	rm -rf report
