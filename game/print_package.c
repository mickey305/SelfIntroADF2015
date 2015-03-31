#include "../main.h"

// フィールドに更新された盤面を表示
void rewrite_field(GAME_BOARD board[][MAX_BOARD_NUM]){
  int center_x; int center_y;
  int max_x,max_y;
  int i,j;
  int ch ='a';
  char status[] =" STATUS ";

  // 文字をバッファーに溜めない
  crmode();

  getmaxyx(stdscr, max_y, max_x);
  center_x = max_x/2;
  center_y = max_y/2;
 
  //init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_CYAN);
  init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);

  for(i=0;i<MAX_BOARD_NUM;++i){
    for(j=0;j<MAX_BOARD_NUM;++j){
      if(i ==0 && j ==0){
	mvprintw(4 +i, 4 +j*4, "+");
      }
      if(i ==0){
	mvprintw(3 +i, 6 +j*4, "%c", ch+j);
	mvprintw(4 +i, 5 +j*4, "---+");
      }
      if(j ==0){
	mvprintw(5 +i*2, 2+j*2, "%d", i+1);
	mvprintw(5 +i*2, 4 +j*4, "|");
	mvprintw(6 +i*2, 4 +j*4, "|");
     }

    }
  }

  for(i=0;i<MAX_BOARD_NUM;++i){
    for(j=0;j<MAX_BOARD_NUM;++j){
      if(board[i][j].inputed_point){
	// 数字表示
	if(board[i][j].obj_hidden !=0){
	  if(!board[i][j].bomb_set_point){
	    //mvprintw(5 +i*2, 5 +j*4, " %d |",board[i][j].obj_hidden);
	    move(5 +i*2, 5+j*4);
	    addch(' ');
	    setColorCH( board[i][j].obj_hidden );
	    addch(' ');
	    addch('|');

	    move(6 +i*2, 5 +j*4);
	    //addch("   |");
	    addch(' ');
	    addch(' ');
	    addch(' ');
	    addch('|');
	  }else{
	    //mvprintw(5 +i*2, 5+j*4, " %c |",board[i][j].obj_hidden);
	    move(5 +i*2, 5+j*4);
	    addch(' ');
	    addch(board[i][j].obj_hidden);
	    addch(' ');
	    addch('|');
	    //mvprintw(6 +i*2, 5 +j*4, "   |");
	    move(6 +i*2, 5 +j*4);
	    addch(' ');
	    addch(' ');
	    addch(' ');
	    addch('|');

	  }
	}else{
	  mvprintw(5 +i*2, 5+j*4, " - |");
	  mvprintw(6 +i*2, 5+j*4, "   |");
	}
      }else{
	// 文字表示
	move(5 +i*2, 5 +j*4);
	//addch(' '|COLOR_PAIR(COLOR_CYAN));
	//addch(' '|COLOR_PAIR(COLOR_CYAN));
	//addch(' '|COLOR_PAIR(COLOR_CYAN));
	addch(' '|COLOR_PAIR(COLOR_WHITE));
	addch(' '|COLOR_PAIR(COLOR_WHITE));
	addch(' '|COLOR_PAIR(COLOR_WHITE));
	addch('|');
	mvprintw(6 +i*2, 6 +j*4, "  |");
      }

    }
    mvprintw(6 +i*2, 4, "+---+---+---+---+---+---+---+---+---+");
  }

  for(i=0;i<max_x;i++){
    mvprintw(31, i, "_");
    mvprintw(31, center_x -(strlen(status)/2), "%s", status);
  }
  mvprintw(33, 2, "       X-Y Point Info        ");
  mvprintw(34, 2, "Please input key : Enter or n");
  mvprintw(35, 2, "+---------------------------+");
  mvprintw(36, 2, "|                           |");
  mvprintw(37, 2, "| (X-point, Y-point)=(0, 0) |");
  mvprintw(38, 2, "|                           |");
  mvprintw(39, 2, "+---------------------------+");

  //////////////////////////////////////////////////////////////////////////////////
  #ifdef DEBUG
  for(i=0;i<MAX_BOARD_NUM;++i){
    for(j=0;j<MAX_BOARD_NUM;++j){
      if(board[i][j].inputed_point){
	mvprintw(15 +i, 5+j*2, "1");
      }else{
	mvprintw(15 +i, 5+j*2, "-");
      }
    }
  }

  for(i=0;i<MAX_BOARD_NUM;++i){
    for(j=0;j<MAX_BOARD_NUM;++j){
      if(board[i][j].bomb_set_point){
	mvprintw(25 +i, 5+j*2, "B");
      }else{
	mvprintw(25 +i, 5+j*2, "-");
      }
    }
  }
  #endif
  //////////////////////////////////////////////////////////////////////////////////

}

void setColorCH(int num){
  start_color();

  init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
  init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
  init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);

  switch(num){
  case 1:
    addch(transINTtoCH(num) | COLOR_PAIR(COLOR_BLUE));
    break;
  case 2:
    addch(transINTtoCH(num) | COLOR_PAIR(COLOR_GREEN));
    break;
  case 3:
    addch(transINTtoCH(num) | COLOR_PAIR(COLOR_RED));
    break;
  case 4:
    addch(transINTtoCH(num) | COLOR_PAIR(COLOR_MAGENTA));
    break;
  case 5:
    addch(transINTtoCH(num) | COLOR_PAIR(COLOR_YELLOW));
    break;
  default:
    addch(transINTtoCH(num));
    break;
  }
  refresh();

}

int transINTtoCH(int num){
  int ch, i;
  int tmpCH ='0';

  ch ='0';
  for(i =0; i < 10; i++){
    if(num == i)ch =tmpCH +i;
  }

  return ch;
}

FLAG print_areYouReady(INPUT_POINT point){
  int ch;
  FLAG isOK =false;

  // 文字をバッファーに溜めない
  crmode();

  mvprintw(33, 2, "     Are you ready, OK?      ");
  mvprintw(34, 2, "Please input key : Enter or n");
  mvprintw(35, 2, "+---------------------------+");
  mvprintw(36, 2, "|                           |");
  mvprintw(37, 2, "| (X-point, Y-point)=(%c, %c) |", point.x, point.y);
  mvprintw(38, 2, "|                           |");
  mvprintw(39, 2, "+---------------------------+");

  while(true){
    ch =getch();
    if(ch =='\n'){
      isOK =true;
      break;
    }else if(ch =='n' || ch =='N'){
      mvprintw(33, 2, "       X-Y Point Info        ");
      mvprintw(37, 2, "| (X-point, Y-point)=(0, 0) |");
      isOK =false;
      break;
    }
  }



  return (isOK);
}

void print_gameover(int time){
  char errmsg[] = "GAME OVER";
  char msg_how[] = "0:終了";
	int center_x,center_y,max_x,max_y;
	int ch;

  // 文字をバッファーに溜めない
  crmode();

	getmaxyx(stdscr, max_y, max_x);
	center_x = max_x/2;
	center_y = max_y/2;

	mvprintw(center_y/2, center_x -(strlen(errmsg)/2), "%s", errmsg);
	mvprintw(center_y, center_x -7, "TIME:\t%02d:%02d:%02d",
		 time/(60*60), time%(60*60)/60, time%60);
	mvprintw(max_y -center_y/4, center_x -(strlen(msg_how)/3), "%s", msg_how);



	// カーソルを出力しない
	curs_set(0);

	// 入力文字を出力しない
	noecho();

	while(true){
		ch = getch();
		refresh();
		if(ch == '0'){
			break;
		}
	}


}

FLAG print_clear(int time){
  char errmsg[] = "GAME CLEAR";
  char myname[] = "My name is Koji Misaki!!";
  char msg_how1[] ="0:終了";
  char msg_how2[] ="0:終了  1:ランキング登録";
  char msg_rank1[] ="トップ10にランクインしませんでした";
  char msg_rank2[] ="トップ10にランクインしました";

  int center_x,center_y,max_x,max_y;
  int ch;
  FLAG isRanked;
  int clear_mode;


  // 文字をバッファーに溜めない
  crmode();

	// カーソルを出力しない
	curs_set(0);

	// 入力文字を出力しない
	noecho();


	getmaxyx(stdscr, max_y, max_x);
	center_x = max_x/2;
	center_y = max_y/2;


	clear_mode =check_clear_mode(time);



	mvprintw(center_y/2, center_x -(strlen(errmsg)/2), "%s", errmsg);
	// 名前を出す
	mvprintw(center_y/2 + 2, center_x -(strlen(myname)/2), "%s", myname);
	mvprintw(center_y, center_x -7, "TIME:\t%02d:%02d:%02d",
		 time/(60*60), time%(60*60)/60, time%60);

	if(clear_mode ==0){
	  mvprintw(center_y+2, center_x -(strlen(msg_rank1)/3), "%s", msg_rank1);
	  mvprintw(max_y -center_y/4, center_x -(strlen(msg_how1)/3), "%s", msg_how1);

	}else if(clear_mode ==1){
	  mvprintw(center_y+2, center_x -(strlen(msg_rank2)/3), "%s", msg_rank2);
	  mvprintw(max_y -center_y/4, center_x -(strlen(msg_how2)/3), "%s", msg_how2);

	}else{
	  mvprintw(max_y -center_y/4, center_x -(strlen(msg_how1)/3), "%s", msg_how1);

	}


	while(true){
		ch = getch();
		if(clear_mode ==1){
		  switch(ch){
		  case '0':
		    isRanked =false;
		    break;
		  case '1':
		    isRanked =true;
		    break;
		  default:
		    isRanked =false;
		    break;
		  }

		}else{
		  isRanked =false;
		}
		refresh();
		if(clear_mode ==1){
		  if(ch == '0' || ch == '1'){
		    break;
		  }
		}else{
		  if(ch == '0'){
		    break;
		  }
		}
	}

	return (isRanked);

}

int check_clear_mode(int t){
  FILE *fp;
  char rank_file[] ="documents/rank.txt";
  int i,res =0;
  int max_time =0;
  RANK_BUF rank_bottom;

  if((fp = fopen(rank_file, "r")) == NULL){
    return 3;

  }else{

	i =0;
	while(fscanf(fp, "%s %s",rank_bottom.name, rank_bottom.time) != EOF){
	  if(i ==0){
	    max_time =atoi(rank_bottom.time);

	  }else{
	    max_time =(max_time < atoi(rank_bottom.time)) ? atoi(rank_bottom.time) : max_time;

	  }
	  ++i;
	}

	if(max_time >= t){
	  res =1;

	}else{
	  res =0;

	}



    fclose(fp);
  }

  return (res);
}

