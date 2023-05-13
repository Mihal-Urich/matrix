.PHONY: all clean test

NAME = s21_matrix
CC = gcc -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
SOURSES = s21_matrix.c
OBJECT = s21_matrix.o
LINUXFLAGS = -lsubunit -lrt -lpthread -lm 
LIBS= -lcheck
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
 CC += -D OS_MAC
 TEST_FLAGS = $(LIBS)
endif
ifeq ($(OS), Linux)
 CC += -D OS_LINUX
 TEST_FLAGS =-lpthread  $(LIBS) -pthread -lrt -lm -lsubunit
endif

all: s21_matrix.a

$(NAME): $(OBJECT)
	$(CC) $(OBJECT) -o $(NAME)

s21_matrix.a: s21_matrix.o
	$(CC) -c $(SOURSES)
	@ar rcs s21_matrix.a $(OBJECT)

test: unit_test.c s21_matrix.a
ifeq ($(OS), Darwin)
	$(CC) unit_test.c s21_matrix.a -o unit_test  $(LIBS)
else
	$(CC) unit_test.c s21_matrix.a -o unit_test  $(LIBS) $(LINUXFLAGS)
endif
	./unit_test

gcov_report: s21_matrix.a
	@gcc $(GCOVFLAGS) unit_test.c  $(LIBS) $(SOURSES) $(TEST_FLAGS) -o s21_gcov_report
	@./s21_gcov_report
	@lcov -t "s21_gcov_report" -o s21_gcov_report.info -c -d .
	@genhtml -o report s21_gcov_report.info
	@open ./report/index-sort-f.html
	@rm -rf ./*.gcno ./*.gcda ./s21_gcov_report.*  

all_checks: leak clang cpp


leak: s21_matrix.a
	@$(CC) unit_test.c s21_matrix.a $(TEST_FLAGS)
	@CK_FORK=no leaks --atExit -- ./a.out

clang:
	clang-format -style=Google -n *.c *.h

cpp: s21_matrix.a 
	$(CC) unit_test.c s21_matrix.a $(TEST_FLAGS)
	cppcheck *.h *.c

rebuild: clean all

clean:
	rm -rf ./*.o ./*.a ./a.out ./s21_gcov_report ./*.gcno ./*.gcda ./report ./*.info ./string_o ./*.dSYM ./unit_test ./CPPLINT*  ./.clang-format ./.DS_Store

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov
