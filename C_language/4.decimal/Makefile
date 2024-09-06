CC=gcc
CFLAGS=  -Wall -Werror -Wextra -std=c11
TESTING_FLAGS=-lcheck
GCOVFLAGS = -fprofile-arcs -ftest-coverage --coverage
OPTS_FOR_TEST=-lcheck 



MAIN_TARGET=s21_decimal.a

SOURCE=$(wildcard s21_*.c)
OBJ=$(patsubst %.c,%.o, ${SOURCE})
EXE=test


TEST_DIR=unit_tests/
TEST_SOURCE=$(wildcard $(TEST_DIR)*.c)

# .DELETE_ON_ERROR:
test8:
	$(CC) $(CFLAGS) s21_decimal.c -o ./2
all: clean $(MAIN_TARGET) 

$(MAIN_TARGET): $(SOURCE)
	$(CC) -c $(CFLAGS) $(SOURCE)
	ar rc $(MAIN_TARGET) $(OBJ)

test: test_prepare test_exe

test_prepare:
	$(CC) $(TEST_SOURCE) -c
	$(CC) *.o s21_decimal.a $(OPTS_FOR_TEST) -o $(EXE)

test_exe:
	./$(EXE)

gcov_report: $(MAIN_TARGET)
	$(CC)  $(GCOVFLAGS) $(TEST_SOURCE) $(SOURCE) $(MAIN_TARGET) $(OPTS_FOR_TEST) -o gcov_test
	chmod +x *
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html

style: style-check style-fix style-check

style-check:
	clang-format -n -style=Google *.c
	clang-format -n -style=Google *.h
	clang-format -n -style=Google $(TEST_DIR)*.c
	clang-format -n -style=Google $(TEST_DIR)*.h

style-fix:
	clang-format -i -style=Google *.c
	clang-format -i -style=Google *.h
	clang-format -i -style=Google $(TEST_DIR)*.c
	clang-format -i -style=Google $(TEST_DIR)*.h

clean:
	rm -rf *.o *.a gcov_test *.html *.css ./GcovReport ./*.gcno ./*.gcda ./report ./*.info ./*.dSYM test *.gcov

rebuild: clean all
