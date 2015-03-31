#include "../main.h"

void init_game(GAME_BOARD board[][MAX_BOARD_NUM]){

  // ランダム配置
  rand_setting(board);

  // フィールド初期化
  init_field(board);

}

void rand_setting(GAME_BOARD board[][MAX_BOARD_NUM]){
  int i,j;
  RAND_POINT point;

  // フラグを全てリセットする
  for(i=0;i<MAX_BOARD_NUM;i++)
  {
    for(j=0;j<MAX_BOARD_NUM;j++)
    {
      reset_flag(&board[i][j]);
    }
  }


  srand((unsigned)time(NULL));

  //（セットする地雷数）while文で回す
  i =0;
  while(i != BOMB_NUM){
    point.x = rand()%MAX_BOARD_NUM;
    point.y = rand()%MAX_BOARD_NUM;

    if(!board[point.x][point.y].bomb_set_point){
      set_flag(&board[point.x][point.y]);
      set_bomb(&board[point.x][point.y]);

      ++i;
    }

  }

   /*
   全ての9×9（81）マスの周囲の地雷をカウントし、結果を配列にセットする
   for文は81回 回る
   */
  for(i =0;i < MAX_BOARD_NUM; ++i)
  {
    for(j =0;j < MAX_BOARD_NUM; ++j)
    {
      if(!board[i][j].bomb_set_point)
	set_strNumToShow(&board[i][j], search_dir8(board,i,j));

    }
  }


}

/* 初期化処理
9×9の配列に同様の文字”X”を格納し、ウィンドウに文字列を表示する

*/
void init_field(GAME_BOARD board[][MAX_BOARD_NUM]){
  int i,j;

  for(i =0; i < MAX_BOARD_NUM; ++i){
    for(j =0; j < MAX_BOARD_NUM; ++j){
      insert_charactorToHidden(&board[i][j], 'X');
      reset_inputed_point(&board[i][j]);
 
    }
  }

  // field window clear and rewrite.
  rewrite_field(board);



}

void insert_charactorToHidden(GAME_BOARD *board, int ch){
  board->obj_hidden =ch;

}

void reset_inputed_point(GAME_BOARD *board){
  board->inputed_point =false;

}

// 指定された座標位置の地雷フラグをリセット
void reset_flag(GAME_BOARD *board){
  board->bomb_set_point =false;

}

// 指定された座標位置に地雷フラグをセット
void set_flag(GAME_BOARD *board){
  board->bomb_set_point =true;

}

// 指定された座標位置に地雷をセット
void set_bomb(GAME_BOARD *board){
  //board[point.x][point.y]->obj_show = "B";
  board->obj_show ='B';

}

/*

現在の座標位置の周囲8方向に存在する地雷数を返す

- 座標位置の配列に地雷フラグがセットされていたら１カウント
- 以降全ての方向に対して同様の操作を行う

 */
int search_dir8(GAME_BOARD board[][MAX_BOARD_NUM],int now_x,int now_y){
  int i;
  int direction_pattern[][2] ={{ 0, 1},{ 1, 1},{ 1, 0},{ 1,-1},
			  { 0,-1},{-1,-1},{-1, 0},{-1, 1}};
  typedef struct{int x,y;}S_INDEX;
  S_INDEX searched_index;
  int counter =0;
  FLAG isJump =false;

  if(!board[now_x][now_y].bomb_set_point){
    for(i =0;i < 8;++i)
      {
	isJump =false;

	searched_index.x = now_x - direction_pattern[i][0]; // x axis
	searched_index.y = now_y - direction_pattern[i][1]; // y axis

	if(searched_index.x < 0)                isJump =true;
	if(searched_index.y < 0)                isJump =true;
	if(searched_index.x > MAX_BOARD_NUM -1) isJump =true;
	if(searched_index.y > MAX_BOARD_NUM -1) isJump =true;

	if(!isJump){
	  if(board[searched_index.x][searched_index.y].bomb_set_point)++counter;
	}


      }
  }

  return (counter);
}

void set_strNumToShow(GAME_BOARD *board, int num){
  board->obj_show =num;

}

