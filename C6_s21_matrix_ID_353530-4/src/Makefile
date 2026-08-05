CC = clang
CFLAGS = -Wall -Wextra -Werror -std=gnu11 -g -fsanitize=address
CLIBS = -L/opt/homebrew/lib -lcheck -pthread -lm --coverage 
GCOV = -fprofile-arcs -ftest-coverage

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    CLIBS=-lcheck -lm -lsubunit
endif

all: s21_matrix.a

clean:
	@rm -rf *.o *.gcno *.gcda *.gcov *.a test logs

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h
	rm -f .clang-format

s21_matrix.a:
	$(CC) $(CFLAGS) -c s21_matrix.c -o s21_matrix.o
	ar rcs s21_matrix.a s21_matrix.o

test: clean s21_matrix.a
	@rm -rf test
	$(CC) $(CFLAGS) test_matrix.c s21_matrix.c $(GCOV) $(CLIBS) -o test
	@./test

gcov_report: test
	@rm -rf test-test.gcda test-test.gcno
	@mkdir -p logs
	@gcovr \
		--html-self-contained \
		--html-details \
		--exclude="test_matrix\.c" \
		-o logs/report.html
	@echo "Building report..."
	@open logs/report.html

rebuild: clean all
