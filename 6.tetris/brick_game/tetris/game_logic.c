#include "../../game.h"

void game_loop(void) {
  int signal = 0;
  GameInfo_t stats;
  curr_position_figure curr_position;
  stats_init(&stats, &curr_position);
  copy_figure(&stats, &curr_position);
  implicate_random_figure(&stats);

  UserAction_t state = Start;
  nodelay(stdscr, TRUE);

  bool gameActive = TRUE;
  while (gameActive) {
    signal = getch();
    state = get_signal(signal);

    if (state == Terminate) {
      gameActive = FALSE;
      free_memory(&stats, &curr_position);
      continue;
    }

    if (state == Pause) {
      while (getch() != ' ')
        ;
      continue;
    }

    sigact(state, &stats, &curr_position);
    check_game_over(&stats, &curr_position, &gameActive);
    timeout(500 / stats.speed);
  }
}

void free_memory(GameInfo_t *stats, curr_position_figure *curr_position) {
  for (int i = 0; i < 21; i++) {
    free(stats->field[i]);
  }
  free(stats->field);
  stats->field = NULL;
  for (int i = 0; i < 4; i++) {
    free(stats->next[i]);
  }
  free(stats->next);
  stats->next = NULL;
  for (int i = 0; i < 4; i++) {
    free(curr_position->curr_figure[i]);
  }
  free(curr_position->curr_figure);
  curr_position->curr_figure = NULL;
}

void stats_init(GameInfo_t *stats, curr_position_figure *curr_position) {
  stats->field = calloc(21, sizeof(int *));
  for (int i = 0; i < 21; i++) {
    stats->field[i] = calloc(10, sizeof(int));
  }
  for (int i = 0; i < 10; i++) {
    stats->field[20][i] = 1;
  }

  stats->next = calloc(4, sizeof(int *));
  for (int i = 0; i < 10; i++) {
    stats->next[i] = calloc(4, sizeof(int));
  }

  FILE *mf;
  mf = fopen("record.txt", "r");
  fscanf(mf, "%d", &stats->high_score);
  fclose(mf);
  stats->level = 0;
  stats->score = 0;
  stats->pause = 0;
  stats->speed = 1;

  curr_position->curr_figure = calloc(4, sizeof(int *));
  for (int i = 0; i < 4; i++) {
    curr_position->curr_figure[i] = calloc(4, sizeof(int));
  }

  implicate_random_figure(stats);
}

void implicate_random_figure(GameInfo_t *stats) {
  clear_matrix(stats->next);
  int r = rand() % 7;
  if (r == LONG) {
    for (int i = 0; i < 4; i++) {
      stats->next[2][i] = 1;
    }
    stats->color = Blue;
    stats->number_figure = LONG;
  } else if (r == TWO_LEFT) {
    stats->next[2][0] = 1;
    for (int i = 0; i < 3; i++) {
      stats->next[3][i] = 1;
    }
    stats->color = Red;
    stats->number_figure = TWO_LEFT;
  } else if (r == TWO_RIGHT) {
    stats->next[2][2] = 1;
    for (int i = 0; i < 3; i++) {
      stats->next[3][i] = 1;
    }
    stats->color = Red;
    stats->number_figure = TWO_RIGHT;
  } else if (r == SQUARE) {
    stats->next[2][0] = 1;
    stats->next[2][1] = 1;
    stats->next[3][0] = 1;
    stats->next[3][1] = 1;
    stats->color = Blue;
    stats->number_figure = SQUARE;
  } else if (r == TWO_UNDER_TWO_UPPER) {
    stats->next[2][1] = 1;
    stats->next[2][2] = 1;
    stats->next[3][0] = 1;
    stats->next[3][1] = 1;
    stats->color = Green;
    stats->number_figure = TWO_UNDER_TWO_UPPER;
  } else if (r == TWO_UPPER_TWO_UNDER) {
    stats->next[2][0] = 1;
    stats->next[2][1] = 1;
    stats->next[3][1] = 1;
    stats->next[3][2] = 1;
    stats->color = Green;
    stats->number_figure = TWO_UPPER_TWO_UNDER;
  } else if (r == MIDDLE_UPPER) {
    stats->next[2][1] = 1;
    for (int i = 0; i < 3; i++) {
      stats->next[3][i] = 1;
    }
    stats->color = Blue;
    stats->number_figure = MIDDLE_UPPER;
  }
}

UserAction_t get_signal(int user_input) {
  UserAction_t rc = Start;

  if (user_input == KEY_UP)
    rc = Action;
  else if (user_input == KEY_DOWN)
    rc = Down;
  else if (user_input == KEY_LEFT)
    rc = Left;
  else if (user_input == KEY_RIGHT)
    rc = Right;
  else if (user_input == ESCAPE)
    rc = Terminate;
  else if (user_input == PAUSE)
    rc = Pause;
  return rc;
}

void sigact(UserAction_t state, GameInfo_t *stats,
            curr_position_figure *curr_position) {
  print_stats(stats);
  if (state == Left) {
    if (check_collision_left(*curr_position, *stats)) {
      clear_figure(*curr_position);
      curr_position->x -= 1;
    }
  } else if (state == Right) {
    if (check_collision_right(*curr_position, *stats)) {
      clear_figure(*curr_position);
      curr_position->x += 1;
    }
  } else if (state == Down || state == Start) {
    clear_figure(*curr_position);
    curr_position->y += 1;
  } else if (state == Action) {
    rotate_figure(curr_position);
  }
  drawing_figure(curr_position);
  check_collision(stats, curr_position);
  check_row(stats);
}

void rotate_figure(curr_position_figure *curr_position) {
  switch (curr_position->number_figure) {
    case LONG:
      rotate_long(curr_position);
      break;
    case TWO_RIGHT:
      rotate_two_right(curr_position);
      break;
    case TWO_LEFT:
      rotate_two_left(curr_position);
      break;
    case TWO_UNDER_TWO_UPPER:
      rotate_two_under(curr_position);
      break;
    case TWO_UPPER_TWO_UNDER:
      rotate_two_upper(curr_position);
      break;
    case MIDDLE_UPPER:
      middle_upper(curr_position);
      break;
  }
}

void middle_upper(curr_position_figure *curr_position) {
  if (curr_position->condition % 4 == 0) {
    if (curr_position->y > 0) {
      clear_figure(*curr_position);
      clear_matrix(curr_position->curr_figure);
      curr_position->curr_figure[1][1] = 1;
      curr_position->curr_figure[2][1] = 1;
      curr_position->curr_figure[3][1] = 1;
      curr_position->curr_figure[2][2] = 1;
      curr_position->condition += 1;
    }
  } else if (curr_position->condition % 4 == 1) {
    if (curr_position->x > -1) {
      clear_figure(*curr_position);
      clear_matrix(curr_position->curr_figure);
      curr_position->curr_figure[2][0] = 1;
      curr_position->curr_figure[2][1] = 1;
      curr_position->curr_figure[2][2] = 1;
      curr_position->curr_figure[3][1] = 1;
      curr_position->condition += 1;
    }
  } else if (curr_position->condition % 4 == 2) {
    clear_figure(*curr_position);
    clear_matrix(curr_position->curr_figure);
    curr_position->curr_figure[1][1] = 1;
    curr_position->curr_figure[2][1] = 1;
    curr_position->curr_figure[3][1] = 1;
    curr_position->curr_figure[2][0] = 1;
    curr_position->condition += 1;
  } else {
    if (curr_position->x < 8) {
      clear_figure(*curr_position);
      clear_matrix(curr_position->curr_figure);
      curr_position->curr_figure[2][0] = 1;
      curr_position->curr_figure[2][1] = 1;
      curr_position->curr_figure[2][2] = 1;
      curr_position->curr_figure[1][1] = 1;
      curr_position->condition += 1;
    }
  }
}

void rotate_two_upper(curr_position_figure *curr_position) {
  if (curr_position->condition % 4 == 0) {
    if (curr_position->y > 0) {
      clear_figure(*curr_position);
      clear_matrix(curr_position->curr_figure);
      curr_position->curr_figure[1][2] = 1;
      curr_position->curr_figure[2][2] = 1;
      curr_position->curr_figure[2][1] = 1;
      curr_position->curr_figure[3][1] = 1;
      curr_position->condition += 1;
    }
  } else if (curr_position->condition % 4 == 1) {
    if (curr_position->x > -1) {
      clear_figure(*curr_position);
      clear_matrix(curr_position->curr_figure);
      curr_position->curr_figure[2][0] = 1;
      curr_position->curr_figure[2][1] = 1;
      curr_position->curr_figure[3][1] = 1;
      curr_position->curr_figure[3][2] = 1;
      curr_position->condition += 1;
    }
  } else if (curr_position->condition % 4 == 2) {
    clear_figure(*curr_position);
    clear_matrix(curr_position->curr_figure);
    curr_position->curr_figure[1][1] = 1;
    curr_position->curr_figure[2][1] = 1;
    curr_position->curr_figure[2][0] = 1;
    curr_position->curr_figure[3][0] = 1;
    curr_position->condition += 1;
  } else {
    if (curr_position->x < 8) {
      clear_figure(*curr_position);
      clear_matrix(curr_position->curr_figure);
      curr_position->curr_figure[1][0] = 1;
      curr_position->curr_figure[1][1] = 1;
      curr_position->curr_figure[2][1] = 1;
      curr_position->curr_figure[2][2] = 1;
      curr_position->condition += 1;
    }
  }
}

void rotate_two_under(curr_position_figure *curr_position) {
  if (curr_position->condition % 4 == 0) {
    if (curr_position->y > 0) {
      clear_figure(*curr_position);
      clear_matrix(curr_position->curr_figure);
      curr_position->curr_figure[1][1] = 1;
      curr_position->curr_figure[2][1] = 1;
      curr_position->curr_figure[2][2] = 1;
      curr_position->curr_figure[3][2] = 1;
      curr_position->condition += 1;
    }
  } else if (curr_position->condition % 4 == 1) {
    if (curr_position->x > -1) {
      clear_figure(*curr_position);
      clear_matrix(curr_position->curr_figure);
      curr_position->curr_figure[3][0] = 1;
      curr_position->curr_figure[3][1] = 1;
      curr_position->curr_figure[2][1] = 1;
      curr_position->curr_figure[2][2] = 1;
      curr_position->condition += 1;
    }
  } else if (curr_position->condition % 4 == 2) {
    clear_figure(*curr_position);
    clear_matrix(curr_position->curr_figure);
    curr_position->curr_figure[1][0] = 1;
    curr_position->curr_figure[2][0] = 1;
    curr_position->curr_figure[2][1] = 1;
    curr_position->curr_figure[3][1] = 1;
    curr_position->condition += 1;
  } else {
    if (curr_position->x < 8) {
      clear_figure(*curr_position);
      clear_matrix(curr_position->curr_figure);
      curr_position->curr_figure[2][0] = 1;
      curr_position->curr_figure[2][1] = 1;
      curr_position->curr_figure[1][1] = 1;
      curr_position->curr_figure[1][2] = 1;
      curr_position->condition += 1;
    }
  }
}

void rotate_two_left(curr_position_figure *curr_position) {
  if (curr_position->condition % 4 == 0) {
    if (curr_position->y > 0) {
      clear_figure(*curr_position);
      clear_matrix(curr_position->curr_figure);
      curr_position->curr_figure[1][2] = 1;
      curr_position->curr_figure[3][1] = 1;
      curr_position->curr_figure[2][1] = 1;
      curr_position->curr_figure[1][1] = 1;
      curr_position->condition += 1;
    }
  } else if (curr_position->condition % 4 == 1) {
    if (curr_position->x > -1) {
      clear_figure(*curr_position);
      clear_matrix(curr_position->curr_figure);
      curr_position->curr_figure[3][2] = 1;
      curr_position->curr_figure[2][0] = 1;
      curr_position->curr_figure[2][1] = 1;
      curr_position->curr_figure[2][2] = 1;
      curr_position->condition += 1;
    }
  } else if (curr_position->condition % 4 == 2) {
    clear_figure(*curr_position);
    clear_matrix(curr_position->curr_figure);
    curr_position->curr_figure[3][0] = 1;
    curr_position->curr_figure[1][1] = 1;
    curr_position->curr_figure[2][1] = 1;
    curr_position->curr_figure[3][1] = 1;
    curr_position->condition += 1;
  } else {
    if (curr_position->x < 8) {
      clear_figure(*curr_position);
      clear_matrix(curr_position->curr_figure);
      curr_position->curr_figure[1][0] = 1;
      curr_position->curr_figure[2][0] = 1;
      curr_position->curr_figure[2][1] = 1;
      curr_position->curr_figure[2][2] = 1;
      curr_position->condition += 1;
    }
  }
}

void rotate_two_right(curr_position_figure *curr_position) {
  if (curr_position->condition % 4 == 0) {
    if (curr_position->y > 0) {
      clear_figure(*curr_position);
      clear_matrix(curr_position->curr_figure);
      curr_position->curr_figure[3][2] = 1;
      curr_position->curr_figure[3][1] = 1;
      curr_position->curr_figure[2][1] = 1;
      curr_position->curr_figure[1][1] = 1;
      curr_position->condition += 1;
    }
  } else if (curr_position->condition % 4 == 1) {
    if (curr_position->x > -1) {
      clear_figure(*curr_position);
      clear_matrix(curr_position->curr_figure);
      curr_position->curr_figure[3][0] = 1;
      curr_position->curr_figure[2][0] = 1;
      curr_position->curr_figure[2][1] = 1;
      curr_position->curr_figure[2][2] = 1;
      curr_position->condition += 1;
    }
  } else if (curr_position->condition % 4 == 2) {
    clear_figure(*curr_position);
    clear_matrix(curr_position->curr_figure);
    curr_position->curr_figure[1][0] = 1;
    curr_position->curr_figure[1][1] = 1;
    curr_position->curr_figure[2][1] = 1;
    curr_position->curr_figure[3][1] = 1;
    curr_position->condition += 1;
  } else {
    if (curr_position->x < 8) {
      clear_figure(*curr_position);
      clear_matrix(curr_position->curr_figure);
      curr_position->curr_figure[1][2] = 1;
      curr_position->curr_figure[2][0] = 1;
      curr_position->curr_figure[2][1] = 1;
      curr_position->curr_figure[2][2] = 1;
      curr_position->condition += 1;
    }
  }
}

void rotate_long(curr_position_figure *curr_position) {
  if (curr_position->condition % 4 == 0) {
    if (curr_position->y > 1 && curr_position->y < 20) {
      clear_figure(*curr_position);
      clear_matrix(curr_position->curr_figure);
      for (int i = 0; i < 4; i++) {
        curr_position->curr_figure[i][2] = 1;
      }
      curr_position->condition += 1;
    }
  } else if (curr_position->condition % 4 == 1) {
    if (curr_position->x > -1 && curr_position->x < 7) {
      clear_figure(*curr_position);
      clear_matrix(curr_position->curr_figure);
      for (int i = 0; i < 4; i++) {
        curr_position->curr_figure[3][i] = 1;
      }
      curr_position->condition += 1;
    }
  } else if (curr_position->condition % 4 == 2) {
    if (curr_position->y > 1 && curr_position->y < 20) {
      clear_figure(*curr_position);
      clear_matrix(curr_position->curr_figure);
      for (int i = 0; i < 4; i++) {
        curr_position->curr_figure[i][1] = 1;
      }
      curr_position->condition += 1;
    }
  } else {
    if (curr_position->x > -1 && curr_position->x < 7) {
      clear_figure(*curr_position);
      clear_matrix(curr_position->curr_figure);
      for (int i = 0; i < 4; i++) {
        curr_position->curr_figure[2][i] = 1;
      }
      curr_position->condition += 1;
    }
  }
}

void clear_matrix(int **figure) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      figure[i][j] = 0;
    }
  }
}

bool check_collision_left(curr_position_figure curr_position,
                          GameInfo_t stats) {
  bool ans = 1;
  int first_x[4];
  for (int y = 0; y < 4; y++) {
    first_x[y] = find_first_x(y, curr_position);
  }

  for (int y = 0; y < 4; y++) {
    if (first_x[y] + curr_position.x <= 0) {
      ans = 0;
      break;
    }
  }

  for (int y = 0; y <= curr_position.y && y < 4; y++) {
    if (stats.field[curr_position.y - y]
                   [curr_position.x + first_x[3 - y] - 1] == 1) {
      ans = 0;
      break;
    }
  }
  return ans;
}

bool check_collision_right(curr_position_figure curr_position,
                           GameInfo_t stats) {
  bool ans = 1;
  int last_x[4];
  for (int y = 0; y < 4; ++y) {
    last_x[y] = find_last_x(y, curr_position);
  }

  for (int y = 0; y < 4; y++) {
    if (last_x[y] + curr_position.x >= 9) {
      ans = 0;
      break;
    }
  }

  for (int y = 0; y <= curr_position.y && y < 4; y++) {
    if (stats.field[curr_position.y - y][curr_position.x + last_x[3 - y] + 1] ==
        1) {
      ans = 0;
      break;
    }
  }
  return ans;
}

void check_row(GameInfo_t *stats) {
  int curr_line = 0;
  for (int i = 0; i < 20; i++) {
    if (stats->field[i][0] == 1 && stats->field[i][1] == 1 &&
        stats->field[i][2] == 1 && stats->field[i][3] == 1 &&
        stats->field[i][4] == 1 && stats->field[i][5] == 1 &&
        stats->field[i][6] == 1 && stats->field[i][7] == 1 &&
        stats->field[i][8] == 1 && stats->field[i][9] == 1) {
      curr_line += 1;
      for (int j = 0; j < 10; j++) {
        stats->field[i][j] = 0;
        CLEAR_BACKPOS(i, j + 1);
      }
      short color;
      for (int j = i - 1; j >= 0; j--) {
        for (int k = 0; k < 10; k++) {
          if (stats->field[j][k] == 1) {
            stats->field[j + 1][k] = 1;
            stats->field[j][k] = 0;
            // color = check_color(j + 3, k + 3);
            CLEAR_BACKPOS(j, k + 1);
            color = rand() % 3;
            print_symbol(j + 2, k + 1, color);
          }
        }
      }
    }
  }
  if (curr_line == 1)
    stats->score += 100;
  else if (curr_line == 2)
    stats->score += 300;
  else if (curr_line == 3)
    stats->score += 700;
  else if (curr_line == 4)
    stats->score += 1500;
  check_new_record(stats);
  stats->level += curr_line;
  check_speed(stats);
}

void check_speed(GameInfo_t *stats) {
  if (stats->score < 600) {
    stats->speed = 1;
  } else {
    stats->speed = stats->score / 600 + 1;
    if (stats->speed > 10) stats->speed = 10;
  }
}

void check_new_record(GameInfo_t *stats) {
  if (stats->score > stats->high_score) {
    stats->high_score = stats->score;
    FILE *mf;
    mf = fopen("record.txt", "w");
    fprintf(mf, "%d", stats->high_score);
    fclose(mf);
  }
}

/*
short check_color(int y, int x) {
  move(y, x);
  refresh();
  attr_t attributes;  // Переменная для хранения атрибутов
  short color_pair;  // Переменная для хранения номера цветовой пары

  attr_get(&attributes, &color_pair, NULL);
  short foreground, background;

  pair_content(color_pair, &foreground, &background);
  short ans;
  if (background == COLOR_RED || foreground == COLOR_RED)
    ans = Red;
  else if (background == COLOR_BLUE || foreground == COLOR_BLUE)
    ans = Blue;
  else if (background == COLOR_GREEN || foreground == COLOR_GREEN)
    ans = Green;
  else
    ans = 0;
  return ans;
}
*/

void check_collision(GameInfo_t *stats, curr_position_figure *curr_position) {
  int flag = 0;
  for (int m = 3; m >= 0; m--) {
    for (int j = 3; j >= 0; j--) {
      if (curr_position->curr_figure[m][j] == 1 &&
          stats->field[curr_position->y + 1 + m - 3][curr_position->x + j] ==
              1) {
        for (int i = 0; i < 4; i++) {
          for (int k = 0; k < 4; k++) {
            if (curr_position->curr_figure[i][k] == 1)
              stats->field[curr_position->y + i - 3][curr_position->x + k] = 1;
          }
        }
        copy_figure(stats, curr_position);
        implicate_random_figure(stats);
        flag = 1;
      }
      if (flag) break;
    }
    if (flag) break;
  }
}

void copy_figure(GameInfo_t *stats, curr_position_figure *curr_position) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      curr_position->curr_figure[i][j] = stats->next[i][j];
      curr_position->color = stats->color;
      curr_position->y = 0;
      curr_position->x = 3;
      curr_position->condition = 0;
      curr_position->number_figure = stats->number_figure;
    }
  }
}

int find_first_x(int y, curr_position_figure curr_pos) {
  int ans = 3;
  for (int i = 0; i < 4; i++) {
    if (curr_pos.curr_figure[y][i] == 1) {
      return i;
    }
  }
  return ans;
}

int find_last_x(int y, curr_position_figure curr_pos) {
  int ans = 0;
  for (int j = 0; j < 4; j++) {
    if (curr_pos.curr_figure[y][j] == 1) {
      ans = j;
    }
  }
  return ans;
}

void clear_figure(curr_position_figure curr_position) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i + curr_position.y > BOARDS_BEGIN &&
          curr_position.curr_figure[i][j] == 1)
        CLEAR_BACKPOS(curr_position.y + i - 3, curr_position.x + j + 1);
    }
  }
}

void check_game_over(GameInfo_t *stats, curr_position_figure *curr_position,
                     bool *gameActive) {
  for (int i = 0; i < BOARD_M; i++) {
    if (stats->field[1][i] != 0) {
      *gameActive = FALSE;
      free_memory(stats, curr_position);
      print_end_game(stats);
      break;
    }
  }
}
