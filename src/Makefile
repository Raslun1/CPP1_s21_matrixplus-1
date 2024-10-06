CC = g++ -std=c++17 -g
FLAGS = -Wall -Werror -Wextra
OS = $(shell uname)
LIBSOURCES = s21_matrix_oop.cpp test_matrix.cpp

ifeq ($(OS), Linux)
	CHECKFLAGS=-lgtest -lgtest_main -lrt -lm -lstdc++ -pthread -fprofile-arcs -ftest-coverage
else
	CHECKFLAGS=-lgtest -lgtest_main -lm -lpthread -fprofile-arcs -ftest-coverage -lstdc++
endif

all: test
	
s21_matrix_oop.a:
	$(CC) $(FLAGS) -c s21_matrix_oop.cpp
	ar -crs libs21_matrix_oop.a s21_matrix_oop.o

test: clean
	$(CC) $(FLAGS) $(LIBSOURCES) -o a.out $(CHECKFLAGS) -lgcov --coverage
	./a.out


test_leaks: test
	leaks --atExit -- ./a.out


valgrind: test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./a.out


clean:
	rm -rf report *.a *.info *.gcda  *.gcno  *.o *.dSYM  a.out *.gch .clang-format