////////////////////////////////////////////////////////////////
//#define DEBUG
////////////////////////////////////////////////////////////////
#define MAX_BOARD_NUM         9
#define BOARD_BUF_SIZE        2

#define MENU_LIST_BUF_SIZE   10

#define HELP_BUF_SIZE       512

#define RANK_NAME_BUF_SIZE   11
#define RANK_TIME_BUF_SIZE   64
#define RANK_NUM             10

#define BOMB_NUM             10

#define TMP_BUF_SIZE_BIG   1024
#define TMP_BUF_SIZE_NORMAL 256
#define TMP_BUF_SIZE_MIN    64

#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h> /* 必須 */
#include <ctype.h>
#include <math.h>
#include <locale.h>


#ifndef FLAG
#define FLAG bool
#endif


// ----------------------------------------------------------------------
// 構造体 ---------------------------------------------------------------
// ----------------------------------------------------------------------


// ゲーム初期化構造体 --------------------------------------------------
typedef struct{
  int x;
  int y;

}RAND_POINT;

// ゲームメイン構造体 --------------------------------------------------
typedef struct{
  FLAG finish;
  FLAG fin_status;
  FLAG add_rank;
  int counter;

  FLAG ret_main;

}GAME_FLAG;

typedef struct{
  int obj_hidden;
  int obj_show;
  FLAG inputed_point;
  FLAG bomb_set_point;
  FLAG searched_point;

}GAME_BOARD;

typedef struct{
  time_t start;
  time_t end;

  int res;

}TM;

typedef struct{
  int x;
  int y;

}INPUT_POINT;

// ランクメイン構造体 ---------------------------------------------------------
typedef struct{
  // 4文字以上10文字以下
  char name[RANK_NAME_BUF_SIZE];
  char time[RANK_TIME_BUF_SIZE];
  // 時間単位ごとにタイムを格納
  int hour;
  int minute;
  int second;
  //int sorted_index_info;

}RANK_BUF;

// ---------------------------------------------------------------------------
// モジュール関数 -------------------------------------------------------------
// ---------------------------------------------------------------------------


// 共通モジュール ------------------------------------------------------------
//// rank_module
void do_swap(RANK_BUF *now, RANK_BUF *pre);
void insertion_sort(RANK_BUF ary[], int num);
void print_rankerror(void);
//// set_color_bkgd
void set_color_bkgd_BLACK(void);
void set_color_bkgd_WHITE(void);
void set_color_bkgd_RED(void);
void set_color_bkgd_GREEN(void);
void set_color_bkgd_BLUE(void);
void set_color_bkgd_YELLOW(void);

// ランキング追加モジュール ---------------------------------------------------
void mergeRANK(char *res, RANK_BUF *buf);
void toWrite_rankFile(FILE *fp, RANK_BUF rank[], int file_num);
char *ch_09_to_res(int ch, char *res);
char *ch_az_to_res(int ch, char *res);
char *ch_AZ_to_res(int ch, char *res);
char *itoa(int val, char *a, int radix);
void insert_rankArray(RANK_BUF *buf, RANK_BUF *tmp);
void write_rank(FILE *fp, RANK_BUF rank_array[], int num, int time);
int read_rank(FILE *fp, RANK_BUF rank_array[]);

// ゲーム結果表示パッケージモジュール ------------------------------------------
int check_clear_mode(int t);

// ゲーム状況処理もジュール ---------------------------------------------------
int cnt_inpted_point(GAME_BOARD board[][MAX_BOARD_NUM]);
void do_write(GAME_BOARD board[][MAX_BOARD_NUM], int x, int y);
void print_fieldpoint(GAME_BOARD board[][MAX_BOARD_NUM], INPUT_POINT inputed, GAME_FLAG *flag);
void set_finish_flag(GAME_FLAG *flag);
void set_fin_status_flag(GAME_FLAG *flag);

// ゲーム初期化モジュール -----------------------------------------------------
void set_inputed_point(GAME_BOARD *board);
void reset_searched_point(GAME_BOARD *board);
void set_searched_point(GAME_BOARD *board);
void copy_toShowFromHidden(GAME_BOARD *board);
void set_strNumToShow(GAME_BOARD *board, int num);
int search_dir8(GAME_BOARD board[][MAX_BOARD_NUM], int now_x, int now_y);
void set_bomb(GAME_BOARD *board);
void reset_flag(GAME_BOARD *board);
void set_flag(GAME_BOARD *board);
void reset_inputed_point(GAME_BOARD *board);
void insert_charactorToHidden(GAME_BOARD *board, int ch);
void init_field(GAME_BOARD board[][MAX_BOARD_NUM]);
void rand_setting(GAME_BOARD board[][MAX_BOARD_NUM]);

// ゲームモジュール ----------------------------------------------------------
int transINTtoCH(int num);
void setColorCH(int num);
void rewrite_field(GAME_BOARD board[][MAX_BOARD_NUM]); // ゲーム共通モジュール
INPUT_POINT transXY_point(INPUT_POINT inputed);
FLAG add_rank(int time);
FLAG print_clear(int time);
void print_gameover(int time);
void run_status(GAME_BOARD board[][MAX_BOARD_NUM], GAME_FLAG *flag, INPUT_POINT inputed);
FLAG print_areYouReady(INPUT_POINT point);
void init_game(GAME_BOARD board[][MAX_BOARD_NUM]);

// ランクモジュール ----------------------------------------------------------
void print_rank(FILE *pfp);

// ヘルプモジュール ----------------------------------------------------------
void print_help(FILE *pfp);
void print_helperror(void);

// メーンモジュール ----------------------------------------------------------
int select_menu(void);
FLAG call_game(void);
void call_rank(void);
void call_help(void);

