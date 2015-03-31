#include "../main.h"

FLAG call_game(void){
  GAME_FLAG game_bool;
  GAME_BOARD board[MAX_BOARD_NUM][MAX_BOARD_NUM];
  TM tm;
  INPUT_POINT ch;
  int tmp_point;
  FLAG tmp_bool;

  game_bool.ret_main = false;
  game_bool.finish = false;
  game_bool.fin_status = false;

  // localeとして環境変数を利用
  setlocale(LC_ALL, "");

  initscr();

  // 文字をバッファーに溜めない
  crmode();

  // ゲーム初期設定
  init_game(board);


  // 時間計測範囲 (開始) ----------------------------------------------
  tm.start = time(NULL);
  game_bool.counter =0;
  while(!game_bool.finish){
    // 座標入力
    do{
      while(true){
	tmp_bool =false;
	while(true){
	  ch.x = getch();
	  if(ch.x >= '1' && ch.x <= '9'){
	    refresh();
	    break;
	  }else if((ch.x >= 'a' && ch.x <= 'i')||(ch.x >= 'A' && ch.x <= 'I')){
	    tmp_bool =true;
	    tmp_point =ch.x;
	    break;
	  }
	  refresh();
	}
	while(true){
	  ch.y = getch();
	  if(!tmp_bool){
	    if((ch.y >= 'a' && ch.y <= 'i')||(ch.y >= 'A' && ch.y <= 'I')){
	      refresh();
	      break;
	    }
	  }else{
	    if(ch.y >= '1' && ch.y <= '9'){
	      ch.x =ch.y;
	      ch.y =tmp_point;
	      break;
	    }
	  }
	  refresh();
	}
	if(print_areYouReady(ch)){
	  break;
	}

      }
      #ifdef DEBUG
      mvprintw(1,1,"%d %d",ch.x,ch.y);
      #endif

      ch =transXY_point(ch);

      #ifdef DEBUG
      mvprintw(2,1,"%d %d",ch.x,ch.y);
      #endif

    }while(board[ch.x][ch.y].inputed_point);

    run_status(board, &game_bool, ch);

  }
  tm.end = time(NULL);
  // int型で小数点以下は省略して出力。
  tm.res = (int)(tm.end - tm.start);
  // 時間計測範囲 (終了) ----------------------------------------------



  if(!game_bool.fin_status){
    print_gameover(tm.res);

  }else{
    game_bool.add_rank = print_clear(tm.res);
    if(game_bool.add_rank){
      // ランク表示 ＋ 返却値をセット
      game_bool.ret_main = add_rank(tm.res);

    }


  }


  clear();
  refresh();
  endwin();

  return (game_bool.ret_main);

}

