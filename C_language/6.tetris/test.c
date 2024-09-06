#include <check.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"

START_TEST(test_stats_init) {
  GameInfo_t stats;
  curr_position_figure curr_position;

  stats_init(&stats, &curr_position);

  ck_assert_int_eq(stats.level, 0);
  ck_assert_int_eq(stats.speed, 1);

  free(stats.field);
  free(stats.next);
  free(curr_position.curr_figure);
}
END_TEST

START_TEST(test_rotate_long) {
  curr_position_figure curr_position;

  curr_position.curr_figure = calloc(4, sizeof(int *));
  for (int i = 0; i < 4; i++) {
    curr_position.curr_figure[i] = calloc(4, sizeof(int));
  }
  curr_position.y = 0;
  curr_position.x = 0;
  curr_position.condition = 0;
  curr_position.number_figure = LONG;

  rotate_long(&curr_position);

  ck_assert_int_eq(curr_position.condition, 0);
  curr_position.y = 2;
  rotate_long(&curr_position);
  ck_assert_int_eq(curr_position.condition, 1);
  ck_assert_int_eq(curr_position.curr_figure[2][2], 1);
  ck_assert_int_eq(curr_position.number_figure, 0);
  curr_position.x = 8;
  rotate_long(&curr_position);
  ck_assert_int_eq(curr_position.condition, 1);
  curr_position.x = 6;
  rotate_long(&curr_position);
  ck_assert_int_eq(curr_position.condition, 2);
  ck_assert_int_eq(curr_position.curr_figure[3][0], 1);
  ck_assert_int_eq(curr_position.curr_figure[2][2], 0);
  rotate_long(&curr_position);
  ck_assert_int_eq(curr_position.condition, 3);
  ck_assert_int_eq(curr_position.curr_figure[3][0], 0);
  ck_assert_int_eq(curr_position.curr_figure[2][1], 1);
  rotate_long(&curr_position);
  ck_assert_int_eq(curr_position.condition % 4, 0);
  ck_assert_int_eq(curr_position.curr_figure[2][0], 1);
  ck_assert_int_eq(curr_position.curr_figure[3][0], 0);

  for (int i = 0; i < 4; i++) {
    free(curr_position.curr_figure[i]);
  }
  free(curr_position.curr_figure);
}
END_TEST

START_TEST(test_free_memory) {
  GameInfo_t stats;
  curr_position_figure curr_position;
  stats.field = malloc(21 * sizeof(int *));
  for (int i = 0; i < 21; i++) {
    stats.field[i] = malloc(10 * sizeof(int));
  }
  stats.next = malloc(4 * sizeof(int *));
  for (int i = 0; i < 4; i++) {
    stats.next[i] = malloc(4 * sizeof(int));
  }

  curr_position.curr_figure = malloc(4 * sizeof(int *));
  for (int i = 0; i < 4; i++) {
    curr_position.curr_figure[i] = malloc(4 * sizeof(int));
  }

  free_memory(&stats, &curr_position);
  ck_assert_ptr_null(stats.next);
  ck_assert_ptr_null(stats.field);
  ck_assert_ptr_null(curr_position.curr_figure);
}
END_TEST

START_TEST(test_implicate_random_figure) {
  srand(time(NULL));
  GameInfo_t stats;
  curr_position_figure curr_position;
  stats.field = malloc(21 * sizeof(int *));
  for (int i = 0; i < 21; i++) {
    stats.field[i] = malloc(10 * sizeof(int));
  }
  stats.next = malloc(4 * sizeof(int *));
  for (int i = 0; i < 4; i++) {
    stats.next[i] = malloc(4 * sizeof(int));
  }

  curr_position.curr_figure = malloc(4 * sizeof(int *));
  for (int i = 0; i < 4; i++) {
    curr_position.curr_figure[i] = malloc(4 * sizeof(int));
  }
  int signal = KEY_UP;

  while (stats.number_figure != LONG) {
    implicate_random_figure(&stats);
  }
  copy_figure(&stats, &curr_position);
  sigact(get_signal(signal), &stats, &curr_position);

  while (stats.number_figure != TWO_LEFT) {
    implicate_random_figure(&stats);
  }
  copy_figure(&stats, &curr_position);
  curr_position.y = 1;
  sigact(get_signal(signal), &stats, &curr_position);
  sigact(get_signal(signal), &stats, &curr_position);
  sigact(get_signal(signal), &stats, &curr_position);
  sigact(get_signal(signal), &stats, &curr_position);

  while (stats.number_figure != TWO_RIGHT) {
    implicate_random_figure(&stats);
  }
  copy_figure(&stats, &curr_position);
  curr_position.y = 1;
  sigact(get_signal(signal), &stats, &curr_position);
  sigact(get_signal(signal), &stats, &curr_position);
  sigact(get_signal(signal), &stats, &curr_position);
  sigact(get_signal(signal), &stats, &curr_position);

  while (stats.number_figure != SQUARE) {
    implicate_random_figure(&stats);
  }
  copy_figure(&stats, &curr_position);
  sigact(get_signal(signal), &stats, &curr_position);
  while (stats.number_figure != TWO_UNDER_TWO_UPPER) {
    implicate_random_figure(&stats);
  }
  copy_figure(&stats, &curr_position);
  curr_position.y = 2;
  sigact(get_signal(signal), &stats, &curr_position);
  sigact(get_signal(signal), &stats, &curr_position);
  sigact(get_signal(signal), &stats, &curr_position);
  sigact(get_signal(signal), &stats, &curr_position);

  while (stats.number_figure != TWO_UPPER_TWO_UNDER) {
    implicate_random_figure(&stats);
  }
  copy_figure(&stats, &curr_position);
  curr_position.y = 1;
  sigact(get_signal(signal), &stats, &curr_position);
  sigact(get_signal(signal), &stats, &curr_position);
  sigact(get_signal(signal), &stats, &curr_position);
  sigact(get_signal(signal), &stats, &curr_position);

  while (stats.number_figure != MIDDLE_UPPER) {
    implicate_random_figure(&stats);
  }
  copy_figure(&stats, &curr_position);
  curr_position.y = 2;
  curr_position.x = 2;
  sigact(get_signal(signal), &stats, &curr_position);
  sigact(get_signal(signal), &stats, &curr_position);
  sigact(get_signal(signal), &stats, &curr_position);
  sigact(get_signal(signal), &stats, &curr_position);

  for (int i = 0; i < 10; i++) {
    stats.field[19][i] = 1;
  }
  sigact(get_signal(signal), &stats, &curr_position);

  for (int i = 0; i < 10; i++) {
    stats.field[19][i] = 1;
    stats.field[18][i] = 1;
  }
  sigact(get_signal(signal), &stats, &curr_position);
  for (int i = 0; i < 10; i++) {
    stats.field[19][i] = 1;
    stats.field[17][i] = 1;
    stats.field[18][i] = 1;
  }
  sigact(get_signal(signal), &stats, &curr_position);
  curr_position.y = 8;
  curr_position.x = 3;
  stats.field[9][4] = 1;
  for (int i = 0; i < 10; i++) {
    stats.field[19][i] = 1;
    stats.field[16][i] = 1;
    stats.field[18][i] = 1;
    stats.field[17][i] = 1;
  }
  sigact(get_signal(signal), &stats, &curr_position);
  free_memory(&stats, &curr_position);
}
END_TEST

START_TEST(test_game_over) {
  GameInfo_t stats;
  curr_position_figure curr_position;
  stats.field = calloc(21, sizeof(int *));
  for (int i = 0; i < 21; i++) {
    stats.field[i] = calloc(10, sizeof(int));
  }
  stats.next = calloc(4, sizeof(int *));
  for (int i = 0; i < 4; i++) {
    stats.next[i] = calloc(4, sizeof(int));
  }

  curr_position.curr_figure = calloc(4, sizeof(int *));
  for (int i = 0; i < 4; i++) {
    curr_position.curr_figure[i] = calloc(4, sizeof(int));
  }
  bool game_active;
  check_game_over(&stats, &curr_position, &game_active);
  free_memory(&stats, &curr_position);
}
END_TEST

START_TEST(test_sigact) {
  GameInfo_t stats;
  int signal = 0;
  curr_position_figure curr_position;
  UserAction_t state = Start;
  stats_init(&stats, &curr_position);
  copy_figure(&stats, &curr_position);
  implicate_random_figure(&stats);
  signal = KEY_UP;
  state = get_signal(signal);
  sigact(state, &stats, &curr_position);
  signal = KEY_DOWN;
  state = get_signal(signal);
  sigact(state, &stats, &curr_position);
  signal = KEY_LEFT;
  state = get_signal(signal);
  sigact(state, &stats, &curr_position);
  signal = KEY_RIGHT;
  state = get_signal(signal);
  sigact(state, &stats, &curr_position);
  signal = KEY_RIGHT;
  state = get_signal(signal);
  sigact(state, &stats, &curr_position);
  signal = ESCAPE;
  state = get_signal(signal);
  sigact(state, &stats, &curr_position);
  signal = ' ';
  state = get_signal(signal);
  sigact(state, &stats, &curr_position);
}
END_TEST

START_TEST(test_print_overlay) { print_overlay(); }
END_TEST

START_TEST(test_collision) {
  GameInfo_t stats;
  int signal = 0;
  curr_position_figure curr_position;
  UserAction_t state = Start;
  stats_init(&stats, &curr_position);
  copy_figure(&stats, &curr_position);
  while (stats.number_figure != MIDDLE_UPPER) {
    implicate_random_figure(&stats);
  }
  copy_figure(&stats, &curr_position);
  implicate_random_figure(&stats);
  curr_position.x = -5;
  curr_position.y = 2;
  signal = KEY_LEFT;
  state = get_signal(signal);
  sigact(state, &stats, &curr_position);
  curr_position.x = 8;
  sigact(state, &stats, &curr_position);
  curr_position.x = 4;
  stats.field[2][7] = 1;
  sigact(state, &stats, &curr_position);
  signal = KEY_RIGHT;
  state = get_signal(signal);
  curr_position.x = 10;
  sigact(state, &stats, &curr_position);

  state = Start;
  curr_position.x = 8;
  curr_position.y = 2;
  for (int i = 0; i < 10; i++) {
    stats.field[3][i] = 1;
  }
  sigact(state, &stats, &curr_position);
}
END_TEST

Suite *suite_create_tetris(void) {
  Suite *suite = suite_create("s21_tetris");
  // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
  TCase *tcase_core = tcase_create("tetris");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, test_stats_init);
  tcase_add_test(tcase_core, test_rotate_long);
  tcase_add_test(tcase_core, test_free_memory);
  tcase_add_test(tcase_core, test_implicate_random_figure);
  tcase_add_test(tcase_core, test_sigact);
  tcase_add_test(tcase_core, test_game_over);
  tcase_add_test(tcase_core, test_collision);
  tcase_add_test(tcase_core, test_print_overlay);

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main(void) {
  int failed_count;
  Suite *suite = suite_create_tetris();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count =
      srunner_ntests_failed(suite_runner);  // запускаем все тестовые случаи
  srunner_free(suite_runner);
  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
