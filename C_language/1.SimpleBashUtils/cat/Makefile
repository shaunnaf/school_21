CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c11

all: clean s21_cat

s21_cat:
	rm -rf s21_cat
	$(CC) $(CFLAGS) s21_cat.c moduls.c -o s21_cat

clean:
	rm -rf s21_cat
	rm -rf *.o
	rm -rf *.a