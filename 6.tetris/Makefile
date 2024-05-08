CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
EXECUTABLE = tetris
GCOVFLAGS = -fprofile-arcs -ftest-coverage
DIR_INTERFACE = ./gui/cli
DIR_GAME = ./brick_game/tetris


all: $(EXECUTABLE)

$(EXECUTABLE):
	mkdir -p bin
	$(CC) $(CFLAGS) -lncurses $(DIR_GAME)/game_logic.c $(DIR_INTERFACE)/interface.c $(DIR_GAME)/main.c -o ./bin/$@

$(EXECUTABLE).a:
	$(CC) $(CFLAGS) -c $(DIR_GAME)/game_logic.c $(DIR_INTERFACE)/interface.c
	ar rcs $@ game_logic.o interface.o
	ranlib $@

install: $(EXECUTABLE)
	cp ./bin/$(EXECUTABLE) tetris

uninstall:
	rm -rf ./bin
	rm -rf tetris

clean:
	-rm -rf ./bin
	-rm -rf test
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./gcov_report
	-rm -rf ./report/
	-rm -rf report.out
	-rm -rf tetris && rm -rf install
	-rm -rf tetris_project.tar.gz

test: clean $(EXECUTABLE).a
	$(CC) $(CFLAGS) -lncurses test.c -L. $(EXECUTABLE).a -lcheck -o test

gcov_report: clean $(EXECUTABLE).a
	$(CC) $(GCOVFLAGS) -lncurses test.c $(DIR_GAME)/game_logic.c $(DIR_INTERFACE)/interface.c -o report.out -lm -lcheck
	./report.out
	gcov -f test.c
	lcov -t "gcov_report" -o Coverage_Report.info -c -d . --no-external
	genhtml -o ./report Coverage_Report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./report/index-sort-f.html

dist:
	tar -cvzf tetris_project.tar.gz ./gui ./brick_game ./Makefile
