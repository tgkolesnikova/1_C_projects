CC = gcc -std=c11
FLAGS = -Wall -Werror -Wextra -g

TARGET = 3DViewer
GUI_DIR = viewer
BUILD_DIR = ../build
INSTALL_DIR = $(HOME)/Applications/3DViewer1.0
DOCS_DIR = generated-docs/html

NAME = 3DViewer
DIR = ./backend/
LIBS = $(shell pkg-config --cflags --libs check)  # автоопределение флагов, кот. нужны под разные ОС
OS = $(shell uname)
ifeq ($(OS), Darwin)
	LEAK_CHECK = leaks -atExit --
	OPEN_CMD = open
endif
ifeq ($(OS), Linux)
	LEAK_CHECK = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s
	OPEN_CMD = xdg-open
endif


all: install

build:
	@mkdir -p $(BUILD_DIR)
	@cd $(GUI_DIR) && qmake && make && make clean && rm -rf Makefile && mv $(GUI_DIR) ../$(BUILD_DIR)/$(TARGET).app

install: clean build
	@mkdir -p $(INSTALL_DIR)
	@cp -R $(BUILD_DIR)/$(TARGET).app $(INSTALL_DIR)/$(TARGET).app
	@doxygen
	@cp -R $(DOCS_DIR) $(INSTALL_DIR)
	@cd $(INSTALL_DIR) && ln -s ./html/index.html ./manual
	@echo "The installation was successful."
	@echo "The project is located in the build folder and in the $(INSTALL_DIR) folder."

uninstall:
	@rm -rf $(INSTALL_DIR) $(BUILD_DIR)
	@echo "Uninstall completed successfully"

dist: clean build
	@doxygen
	@cp -R $(DOCS_DIR) $(BUILD_DIR)
	@cd $(BUILD_DIR) && ln -s ./html/index.html ./manual
	@cd $(BUILD_DIR) && tar cvzf $(TARGET)_v1.0.tgz *
	@cd $(BUILD_DIR) && rm -rf html manual
	@echo "The build was successfully archived to the $(BUILD_DIR) folder."


clean:
	-rm -rf *.o && rm -rf *.gcno 
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.gch && rm -rf $(NAME)
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./gcov_report
	-rm -rf ./report/
	-rm -rf ./generated-docs/
	-rm -rf $(NAME)_tests
	-rm -rf distr_$(NAME).tgz
	-rm -rf viewer/.qmake.stash
	-rm -rf ../build
	-rm -rf build-viewer-Desktop-Debug
	-rm -rf viewer/viewer.pro.user


dvi: clean
	doxygen
	$(OPEN_CMD) ./generated-docs/html/index.html


tests: build_tests
	./$(NAME)_tests

build_tests: clean
	$(CC) $(FLAGS) --coverage $(DIR)s21_parser.c $(DIR)s21_transform.c $(DIR)s21_tests.c $(LIBS) -lm -o $(NAME)_tests


gcov_report: clean tests
	gcov -o report.info -c -d .
	lcov -t "3DViewer_v1_0_tests_report" -o report.info -c -q -d .
	genhtml -o report report.info 
	$(OPEN_CMD) ./report/index.html


leaks: build_tests
	${LEAK_CHECK} ./${NAME}_tests


check: clean
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -n -verbose ./backend/*.c ./backend/*.h
	cppcheck ./backend/*.c ./backend/*.h

style_check:
	clang-format -n -verbose --style=Google backend/*.c backend/*.h $(GUI_DIR)/*.cpp $(GUI_DIR)/*.h

style_format:
	clang-format -i --style=Google backend/*.c backend/*.h $(GUI_DIR)/*.cpp $(GUI_DIR)/*.h

