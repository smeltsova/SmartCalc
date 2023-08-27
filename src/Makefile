

CC = gcc

ASAN = #-fsanitize=address
CFLAGS = -c -g -Wall -Wextra -Werror -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
TEST_FLAGS = -lcheck
ifeq ($(shell uname), Linux)
TEST_FLAGS = -lcheck -lm -lpthread -lrt -lsubunit
endif

TEST_SRC_DIR = ./tests
TEST_OBJ_DIR = ./tests/objs
TEST_SRC:=$(shell find $(TEST_SRC_DIR) -name "*.c")
TEST_OBJS:=$(addprefix $(TEST_OBJ_DIR)/, $(notdir $(TEST_SRC:.c=.o)))

CALC_DIR = ./SmartCalc/calculation
CALC_SRC:=$(shell find $(CALC_DIR) -maxdepth 1 -name "*.c")
CALC_OBJS:=$(CALC_SRC:.c=.o)
CALC_OBJS_GCOV:=$(CALC_SRC:.c=_gcov.o)

ALL_SRC:=$(shell find . -maxdepth 4 -name "*.c")
TARGET:= ./Application/SmartCalc.app

all: install

install:
	mkdir -p build && mkdir -p Application \
	&& cd build && cmake -DEXECUTABLE_OUTPUT_PATH="../Application" ../SmartCalc && cmake --build . 

uninstall:
	rm -rf Application

dist: clean
	mkdir -p SmartCalc_v1.0
	cp -r SmartCalc tests Makefile manual.texi SmartCalc_v1.0
	tar czf SmartCalc_v1.0.tar.gz SmartCalc_v1.0

dvi: manual.html
	open manual.html

manual.html: manual.texi
	makeinfo --no-split --html manual.texi

manual.dvi: manual.texi
	texi2dvi manual.texi

clean:
	rm -rf build Application SmartCalc_v1.0*
	rm -rf *.tar *.gz *.html *.dvi SmartCalc/CMakeLists.txt.user
	rm -rf test gcov_test *.gcno *.gcda *.gcov *gcov.a coverage*
	rm -rf $(CALC_DIR)/*.o $(CALC_DIR)/*.gcno $(CALC_DIR)/*.gcda
	rm -rf $(TEST_OBJ_DIR)/*.o  $(TEST_OBJ_DIR)/*.gcno  $(TEST_OBJ_DIR)/*.gcda  $(TEST_OBJ_DIR)/*.gcov 

$(CALC_OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(ASAN) $< -o $@

test: $(CALC_OBJS) $(TEST_OBJS)
	$(CC) $(ASAN) $(TEST_OBJS) $(CALC_OBJS) -o test $(TEST_FLAGS) 
	./test

$(TEST_OBJS): $(TEST_OBJ_DIR)%.o: $(TEST_SRC_DIR)%.c
	mkdir -p $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) $(ASAN) $< -o $@

gcov_report: clean coverage.html
	open coverage.html

coverage.html: gcov_test
	gcovr -r . --html-details -o coverage.html

gcov_test: $(TEST_OBJS) $(CALC_OBJS_GCOV)
	$(CC) $(TEST_OBJS) $(CALC_OBJS_GCOV) $(TEST_FLAGS) $(GCOV_FLAGS)  -o gcov_test
	./gcov_test

$(CALC_OBJS_GCOV): %_gcov.o: %.c
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(ASAN) $< -o $@

open: $(TARGET)
	open $(TARGET)

$(TARGET): install

rebuild: clean all

valgrind: clean test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

check: test
	CK_FORK=no leaks --atExit -- ./test
	cppcheck --enable=all --suppress=missingIncludeSystem $(ALL_SRC)
	cp ../materials/linters/.clang-format .
	clang-format -n $(ALL_SRC)
