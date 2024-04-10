CC = gcc -std=c11
FLAGS = -Wall -Werror -Wextra -g
NAME = s21_smartcalc_v1
BUILD_DIR = .
LIBS = $(shell pkg-config --cflags --libs check)  # автоопределение флагов, кот. нужны под разные ОС

OS = $(shell uname)
ifeq (${OS}, Darwin)
	LEAK_CHECK = leaks -atExit --
	# LIBS = -lcheck
endif
ifeq (${OS}, Linux)
	LEAK_CHECK = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s
	# LIBS = -lcheck -lsubunit -lrt -lpthread -lm
endif


all: clean install
	

build:  
	mkdir build/
	cp *.h *.c *.cpp *.ui *.pro *.user  ./build/
	cd ./build/; qmake s21_smartcalc_v1.pro
	make -C ./build/
	cd ./build/; rm -rf *.h *.c *.cpp *.ui

rebuild: clean uninstall build


install: build


uninstall: clean
	-rm -rf ./build/


clean: 
	-rm -rf *.o && rm -rf *.gcno 
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.gch && rm -rf s21_matrix
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./gcov_report
	-rm -rf ./report/
	-rm -rf ./generated-docs/
	-rm -rf s21_smartcalc_tests s21_smartcalc_v1
	-rm -rf distr_SmartCalc_v1.tgz


dvi: clean
	doxygen
    ifeq ($(OS), 'Darwin')
        open ./generated-docs/html/index.html
    endif
    ifeq (${OS}, 'Linux')
        xdg-open ./generated-docs/html/index.html
    endif


dist: clean
	mkdir -p release/
	cp *.h *.c *.cpp *.ui *.pro *.user Makefile Doxyfile *.ico *.jpg ./release/
	tar cvzf distr_SmartCalc_v1.tgz ./release/
	rm -rf ./release/


test: clean
	${CC} ${FLAGS} --coverage ${NAME}.c s21_smartcalc_tests.c ${LIBS} -lm -o s21_smartcalc_tests
	./s21_smartcalc_tests


gcov_report: clean test
	gcov -o report.info -c -d ${BUILD_DIR}
	lcov -t "s21_smartcalc_tests_report" -o report.info -c -q -d ${BUILD_DIR}
	genhtml -o report report.info
    ifeq (${OS}, 'Darwin')
        open ./report/index.html
    endif
    ifeq (${OS}, 'Linux')
        xdg-open ./report/index.html
    endif


leaks_with_tests: clean
	${CC} ${FLAGS} --coverage ${NAME}.c s21_smartcalc_tests.c ${LIBS} -lm -o s21_smartcalc_tests
	${LEAK_CHECK} ./s21_smartcalc_tests

leaks_with_main: clean   # uncomment main() in s21_smartcalc_v1.c before!
	${CC} ${FLAGS} ${NAME}.c ${LIBS} -lm -o s21_smartcalc_v1
	${LEAK_CHECK} ./${NAME}


check: clean
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -n -verbose $(NAME).c $(NAME).h s21_smartcalc_tests.c
	cppcheck $(NAME).c $(NAME).h
