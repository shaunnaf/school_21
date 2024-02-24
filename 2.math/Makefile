CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
FUNCTIONSDIR = s21_function
LIB_NAME = s21_math
OBJDIR = obj
GCOVFLAGS = -fprofile-arcs -ftest-coverage

SRC = $(wildcard $(FUNCTIONSDIR)/*.c)


OBJ = $(patsubst $(FUNCTIONSDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

all: clean $(LIB_NAME).a test gcov_report

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(FUNCTIONSDIR)/%.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(LIB_NAME).a: $(OBJDIR) $(OBJ)
	ar rcs $@ $(OBJ)
	ranlib $@

test: clean $(LIB_NAME).a
	$(CC) $(CFLAGS) test.c -L. $(LIB_NAME).a -lcheck -o test

gcov_report: clean $(LIB_NAME).a
	$(CC) $(GCOVFLAGS) test.c  $(SRC) -o report.out -lm -lcheck
	./report.out
	gcov -f test.c
	lcov -t "gcov_report" -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./report/index-sort-f.html

clean:
	-rm -rf test
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf ./obj
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./gcov_report
	-rm -rf ./report/
	-rm -rf report.out
	

.PHONY: all clean test gcov_report