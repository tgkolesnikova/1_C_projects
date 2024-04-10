CC=gcc
FLAGS=-Wall -Wextra -Werror
ROAD=.
NAME=s21_math
BUILD_DIR = .
OUTFILE_TEST = s21_math_test
SOURCES = s21_math.c

GCOV= --coverage
CHECKFLAGS=`pkg-config --cflags --libs check`
OS=$(shell uname)

ifeq ($(OS), Linux)
  LIBS=-lcheck -lpthread -lrt -lsubunit -lm
  OPEN=xdg-open
else
  LIBS=-lcheck
  OPEN=open
endif

all: clean s21_math.a gcov_report

gcov_report:
	gcc $(GCOV) -g $(ROAD)/$(NAME).c -std=c11 $(LIBS) s21_math_test.c -o $(BUILD_DIR)/$(OUTFILE_TEST)
	$(BUILD_DIR)/$(OUTFILE_TEST)
	lcov -o test.info -c -d . 
	genhtml -o report test.info

s21_math.a:
	$(CC) $(FLAGS) -c $(SOURCES) -o s21_math.o
	ar rc s21_math.a s21_math.o


s21_math: s21_math.o
	$(CC) $(FLAGS) -g $(ROAD)/$(NAME).o -o -lm $(ROAD)/$(NAME)

s21_math.o: $(ROAD)/$(NAME).c $(ROAD)/$(NAME).h
	gcc -c $(FLAGS) -g $(ROAD)/$(NAME).c -D $(OS) -o -lm $(ROAD)/$(NAME).o

lcov:
	brew install lcov

run:
	$(ROAD)/$(NAME)

clean:
	rm -rf *.dSYM *.out *.gcda *.gcno *.info *.gcov *.a *.o *FILE report

style:
	cp ../materials/linters/CPPLINT.cfg ./CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --recursive --extensions=c ../src/

leaks:
	gcc -Wall -Wextra -Werror s21_math.c s21_math.h main.c
	leaks -atExit -- ./a.out

check:
	cppcheck s21_math.c *.h

gr:
	 valgrind ./$(OUTFILE_TEST) --leak-check=full
