CC = g++
CFLAGS = --std=c++17 -Wall -Wextra -Werror -I /opt/homebrew/Cellar/googletest/1.15.2/include
LIBS = -L/opt/homebrew/lib -lgtest -lgtest_main -lpthread

LIBRARY = s21_matrix_oop.a

TEST_SRC = $(wildcard tests/*.cpp)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

LIB_SRC = $(wildcard *.cpp)
LIB_OBJ = $(LIB_SRC:.cpp=.o)

HEADERS = $(wildcard *.h)

PROGRAM = test

all: s21_matrix_oop.a

test: $(LIBRARY) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(LIBRARY) -o $(PROGRAM) $(LIBS)
	./$(PROGRAM) || true


s21_matrix_oop.a: $(LIB_OBJ)
	ar rcs $(LIBRARY) $(LIB_OBJ)
	ranlib $(LIBRARY)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.a *.o tests/*.o test