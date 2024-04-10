CC = gcc -std=c11
FLAGS = -Wall -Werror -Wextra
NAME = s21_matrix
BUILD_DIR = .
LIBS = -lcheck -lsubunit -lrt -lpthread -lm
# LIBS = $(shell pkg-config --cflags --libs check)  # автоопределение флагов, кот. нужны под разные ОС

OS = $(shell uname)
ifeq (${OS}, Darwin)
	LEAK_CHECK = leaks -atExit --
endif
ifeq (${OS}, Linux)
	LEAK_CHECK = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes
endif


all: clean s21_matrix.a

build: all
	
rebuild: clean build


clean: 
	-rm -rf *.o && rm -rf *.gcno 
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.gch && rm -rf s21_matrix
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./gcov_report
	-rm -rf ./report/


test: clean
	${CC} ${FLAGS} ${NAME}.c matrix_test.c ${LIBS} -o ${NAME}
	${BUILD_DIR}/${NAME}


s21_matrix.a:
	${CC} -c ${FLAGS} ${NAME}.c
	ar rc ${NAME}.a *.o
	rm *.o


gcov_report: clean
	${CC} ${FLAGS} --coverage ${NAME}.c matrix_test.c ${LIBS} -o ${NAME}
	${BUILD_DIR}/${NAME}
	gcov -o report.info -c -d ${BUILD_DIR}
	lcov -t "s21_matrix" -o report.info -c -q -d ${BUILD_DIR}
	genhtml -o report report.info
	open ./report/index.html


leaks: clean
	${CC} ${FLAGS} -g ${NAME}.c ${NAME}.h main.c -lm -o ${NAME}
	${LEAK_CHECK} ${BUILD_DIR}/${NAME}


check: clean
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -n s21_matrix.*
	clang-format -n main.c matrix_test.c
	cppcheck s21_matrix.*