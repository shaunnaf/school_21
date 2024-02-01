CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -pedantic
TARGET=s21_grep

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) s21_grep.c -o $(TARGET) -lpcre 
	rm -rf *.o

clean:
	rm -rf *.o *.out
	rm -rf $(TARGET)

rebuild:
	make clean
	make $(TARGET)

style:  
	clang-format *.c *.h -i --style=Google

test:
	sh greybaca_grep_test_1.sh $(TARGET)