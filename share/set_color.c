#include "../main.h"

void set_color_bkgd_BLACK(void){
  start_color();

  init_pair(COLOR_BLACK, COLOR_BLACK, COLOR_WHITE);

  bkgd(COLOR_PAIR(COLOR_BLACK));
  refresh();

}

void set_color_bkgd_BLUE(void){
  start_color();

  init_pair(COLOR_BLUE, COLOR_WHITE, COLOR_BLUE);

  bkgd(COLOR_PAIR(COLOR_BLUE));
  refresh();

}

void set_color_bkgd_WHITE(void){
  start_color();

  init_pair(COLOR_WHITE, COLOR_BLACK, COLOR_WHITE);

  bkgd(COLOR_PAIR(COLOR_WHITE));
  refresh();

}

void set_color_bkgd_RED(void){
  start_color();

  init_pair(COLOR_RED, COLOR_WHITE, COLOR_RED);

  bkgd(COLOR_PAIR(COLOR_RED));
  refresh();

}

void set_color_bkgd_GREEN(void){
  start_color();

  init_pair(COLOR_GREEN, COLOR_WHITE, COLOR_GREEN);

  bkgd(COLOR_PAIR(COLOR_GREEN));
  refresh();

}

void set_color_bkgd_YELLOW(void){
  start_color();

  init_pair(COLOR_YELLOW, COLOR_WHITE, COLOR_YELLOW);

  bkgd(COLOR_PAIR(COLOR_YELLOW));
  refresh();

}

/*
  init_pair(COLOR_BLUE, COLOR_WHITE, COLOR_BLUE);
  init_pair(COLOR_WHITE, COLOR_BLACK, COLOR_WHITE);
  init_pair(COLOR_RED, COLOR_WHITE, COLOR_RED);
  init_pair(COLOR_GREEN, COLOR_WHITE, COLOR_GREEN);
  init_pair(COLOR_YELLOW, COLOR_WHITE, COLOR_YELLOW);
  init_pair(COLOR_BLACK, COLOR_BLACK, COLOR_WHITE);
*/
