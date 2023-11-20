CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c11

all: clean s21_grep

s21_grep:
	rm -rf s21_grep
	$(CC) $(CFLAGS)  s21_grep.c moduls.c -o s21_grep

clean:
	rm -rf s21_grep rm -rf *.o rm -rf *.a rm -rf *.out rm -rf *.dSYM