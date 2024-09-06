#include "../../game.h"

int main(void) {
  srand(time(NULL));
  initscr();
  refresh();
  curs_set(0);
  keypad(stdscr, 1);
  noecho();
  print_overlay();
  game_loop();
  endwin();
  return 0;
}