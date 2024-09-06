#ifndef GAME_H
#define GAME_H

#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_N 20
#define BOARD_M 10
#define HUD_WIDTH 15
#define MVPRINTW(y, x, ...) \
  mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)
#define BOARDS_BEGIN 2
#define INTRO_MESSAGE_LEN 21
#define INTRO_MESSAGE "Press ENTER to start!"
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)
#define ESCAPE 27
#define PAUSE ' '
#define ENTER_KEY 10
#define CLEAR_BACKPOS(y, x) \
  mvaddch(BOARDS_BEGIN + 1 + (y), BOARDS_BEGIN + (x), ' ')
#define BLOCK_SIZE 2

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  short color;
  short number_figure;
} GameInfo_t;

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

typedef struct {
  int x;
  int y;
  int **curr_figure;
  short color;
  short number_figure;
  int condition;
} curr_position_figure;

typedef enum {
  LONG = 0,
  SQUARE,
  TWO_RIGHT,
  TWO_LEFT,
  TWO_UNDER_TWO_UPPER,
  MIDDLE_UPPER,
  TWO_UPPER_TWO_UNDER
} figure;

typedef enum { Green = 0, Red, Blue } color;

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_overlay(void);
void game_loop(void);
void stats_init(GameInfo_t *stats, curr_position_figure *curr_position);
UserAction_t get_signal(int user_input);
void sigact(UserAction_t state, GameInfo_t *stats,
            curr_position_figure *curr_position);
void print_stats(GameInfo_t *stats);
void clear_figure(curr_position_figure curr_position);
void drawing_figure(curr_position_figure *curr_position);
int find_first_x(int y, curr_position_figure curr_pos);
int find_last_x(int y, curr_position_figure curr_pos);
void implicate_random_figure(GameInfo_t *stats);
void copy_figure(GameInfo_t *figure2, curr_position_figure *figure1);
void check_collision(GameInfo_t *stats, curr_position_figure *curr_position);
void check_row(GameInfo_t *stats);
void print_symbol(int y, int x, short color);
// short check_color(int y, int x);
void print_end_game(GameInfo_t *stats);
bool check_collision_right(curr_position_figure curr_position,
                           GameInfo_t stats);
bool check_collision_left(curr_position_figure curr_position, GameInfo_t stats);
void rotate_figure(curr_position_figure *curr_position);
void clear_matrix(int **figure);
void rotate_long(curr_position_figure *curr_position);
void rotate_two_right(curr_position_figure *curr_position);
void rotate_two_left(curr_position_figure *curr_position);
void rotate_two_under(curr_position_figure *curr_position);
void rotate_two_upper(curr_position_figure *curr_position);
void middle_upper(curr_position_figure *curr_position);
void check_new_record(GameInfo_t *stats);
void check_speed(GameInfo_t *stats);
void free_memory(GameInfo_t *stats, curr_position_figure *curr_position);
void check_game_over(GameInfo_t *stats, curr_position_figure *curr_position,
                     bool *gameActive);

#endif