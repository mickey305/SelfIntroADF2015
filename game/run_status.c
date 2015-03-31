#include "../main.h"

void run_status(GAME_BOARD board[][MAX_BOARD_NUM], GAME_FLAG *flag, INPUT_POINT inputed){
  int i,j;


  for(i=0;i<MAX_BOARD_NUM;i++){
    for(j=0;j<MAX_BOARD_NUM;j++){
      reset_searched_point(&board[i][j]);
    }
  }

  print_fieldpoint(board, inputed, flag);


  if(board[inputed.x][inputed.y].bomb_set_point){
    // ゲームオーバー
    set_finish_flag(flag);

    clear();
    refresh();

  }else{
    if(flag->counter == MAX_BOARD_NUM * MAX_BOARD_NUM -BOMB_NUM){
      // 通常終了
      set_finish_flag(flag);
      set_fin_status_flag(flag);

      clear();
      refresh();

    }
    // 継続

  }


}

void print_fieldpoint(GAME_BOARD board[][MAX_BOARD_NUM], INPUT_POINT inputed, GAME_FLAG *flag){
  do_write(board,inputed.x,inputed.y);
  flag->counter =cnt_inpted_point(board);

  // field window clear and rewrite.
  rewrite_field(board);


}

void set_finish_flag(GAME_FLAG *flag){
  flag->finish =true;

}

void set_fin_status_flag(GAME_FLAG *flag){
  flag->fin_status =true;

}

void do_write(GAME_BOARD board[][MAX_BOARD_NUM], int x, int y){
  typedef struct{int x;int y;}INDEX;
  INDEX delta[8]={{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
  INDEX tmp;
  int i;
  int show, show_now =board[x][y].obj_show;
  FLAG isSet,isSearch;


  copy_toShowFromHidden(&board[x][y]);
  set_searched_point(&board[x][y]);
  set_inputed_point(&board[x][y]);


  for(i=0;i<8;i++){
    tmp.x =x +delta[i].x;
    tmp.y =y +delta[i].y;

    if(tmp.x < 0)tmp.x =0;
    if(tmp.x > MAX_BOARD_NUM -1)tmp.x =MAX_BOARD_NUM -1;
    if(tmp.y < 0)tmp.y =0;
    if(tmp.y > MAX_BOARD_NUM -1)tmp.y =MAX_BOARD_NUM -1;

    show =board[tmp.x][tmp.y].obj_show;
    isSet =board[tmp.x][tmp.y].bomb_set_point;
    isSearch =board[tmp.x][tmp.y].searched_point;

    if(show_now ==0 && show < 9 && !isSet && !isSearch){
      do_write(board, tmp.x, tmp.y);
    }

  }

}

void copy_toShowFromHidden(GAME_BOARD *board){
  board->obj_hidden =board->obj_show;

}

void reset_searched_point(GAME_BOARD *board){
  board->searched_point =false;

}

void set_searched_point(GAME_BOARD *board){
  board->searched_point =true;

}

void set_inputed_point(GAME_BOARD *board){
  board->inputed_point =true;

}

int cnt_inpted_point(GAME_BOARD board[][MAX_BOARD_NUM]){
  int i,j;
  int counter =0;

  for(i=0;i<MAX_BOARD_NUM;i++){
    for(j=0;j<MAX_BOARD_NUM;j++){
      if(board[i][j].inputed_point) counter++;
    }
  }

  return (counter);
}

