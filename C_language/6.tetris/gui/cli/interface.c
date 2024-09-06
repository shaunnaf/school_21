#include "../../game.h"

void print_overlay(void) {
  print_rectangle(0, BOARD_N + 1, 0, BOARD_M + 1);
  print_rectangle(0, BOARD_N + 1, BOARD_M + 2, BOARD_M + HUD_WIDTH + 3);

  print_rectangle(1, 3, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);
  print_rectangle(4, 6, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);
  print_rectangle(7, 9, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);

  MVPRINTW(2, BOARD_M + 5, "RECORD");
  MVPRINTW(5, BOARD_M + 5, "SCORE");
  MVPRINTW(8, BOARD_M + 5, "LINE");
  MVPRINTW(11, BOARD_M + 5, "NEXT");

  MVPRINTW(BOARD_N / 2, (BOARD_M - INTRO_MESSAGE_LEN) / 2 + 1, INTRO_MESSAGE);
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++) MVADDCH(top_y, i, ACS_HLINE);
  MVADDCH(top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    MVADDCH(i, left_x, ACS_VLINE);
    MVADDCH(i, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) MVADDCH(bottom_y, i, ACS_HLINE);
  MVADDCH(bottom_y, i, ACS_LRCORNER);
}

void print_symbol(int y, int x, short color) {
  start_color();
  if (color == Red) {
    init_pair(1, COLOR_WHITE, COLOR_RED);
    attron(COLOR_PAIR(1)); /* use the above combination */
    MVADDCH(y, x, '#');
    attroff(COLOR_PAIR(1)); /* turn color off */
  } else if (color == Green) {
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    attron(COLOR_PAIR(2)); /* use the above combination */
    MVADDCH(y, x, '#');
    attroff(COLOR_PAIR(2)); /* turn color off */
  } else if (color == Blue) {
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    attron(COLOR_PAIR(3)); /* use the above combination */
    MVADDCH(y, x, '#');
    attroff(COLOR_PAIR(3)); /* turn color off */
  }
}

void drawing_figure(curr_position_figure *curr_position) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (curr_position->curr_figure[i][j] == 1 &&
          i + curr_position->y > BOARDS_BEGIN) {
        print_symbol(curr_position->y + i - 2, curr_position->x + j + 1,
                     curr_position->color);
      }
    }
  }
}

void print_stats(GameInfo_t *stats) {
  MVPRINTW(2, BOARD_M + HUD_WIDTH - 3, "%d", stats->high_score);
  MVPRINTW(5, BOARD_M + HUD_WIDTH - 3, "%d", stats->score);
  MVPRINTW(8, BOARD_M + HUD_WIDTH - 3, "%d", stats->level);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      MVPRINTW(HUD_WIDTH - 3 + i, BOARD_M + 7 + j, " ");
      if (stats->next[i][j] == 1) {
        print_symbol(HUD_WIDTH - 3 + i, BOARD_M + 7 + j, stats->color);
      }
    }
  }
}

void print_end_game(GameInfo_t *stats) {
  clear();  // Очищаем экран
  printw("Game Over!\nYour score: %d\nPress any key to exit.", stats->score);
  refresh();
  while (getch() == ERR)
    ;
  endwin();
}