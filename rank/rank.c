#include "../main.h"

void call_rank(void){
  FILE *fp;
  char rank_file[] = "documents/rank.txt";



  if((fp = fopen(rank_file, "r")) == NULL){
    print_rankerror();

  }else{
    print_rank(fp);

    fclose(fp);


  }




}


void print_rank(FILE *pfp){
  char msg_how[] = "0:メニューへ戻る";
  char msg_title[] = "ランキング画面";
  char msg_bar[] = "-----------------------+---------------------------------------";
  char msg_bar2[] ="                       |                                       ";
  char msg_head[] = "Rank  Name\t|\tTime(Hour:Minute:Second)";
	int center_x,center_y,max_x,max_y;
	int ch,i,n;
	RANK_BUF rank_array[RANK_NUM];


	// localeとして環境変数を利用
	setlocale(LC_ALL, "");


	initscr();

	getmaxyx(stdscr, max_y, max_x);
	center_x = max_x/2;
	center_y = max_y/2;


	i =0;
	while(fscanf(pfp, "%s %s",rank_array[i].name, rank_array[i].time) != EOF){
	  rank_array[i].hour = atoi(rank_array[i].time) / (60 * 60);
	  rank_array[i].minute = atoi(rank_array[i].time) % (60 * 60) / 60;
	  rank_array[i].second = atoi(rank_array[i].time) % 60;

	  ++i;
	}
	n =i;


	// ランキング順にソーティング
	insertion_sort(rank_array, n);


	mvprintw(center_y/7, center_x -(strlen(msg_title)/3) -2, msg_title);

	mvprintw(center_y/2 -3, center_x*4/5 -(strlen(msg_head)/2), msg_head);
	mvprintw(center_y/2 -2, center_x -(strlen(msg_bar)/2), msg_bar);
	mvprintw(center_y/2 -1, center_x -(strlen(msg_bar2)/2), msg_bar2);

	for(i =0; i < n; ++i){


	  mvprintw(
		   center_y/2 +i,
		   center_x*4/5 -(strlen(msg_head)/2),
		   "%2d :  %s\t|\t%02d:%02d:%02d",
		   i +1,
		   rank_array[i].name,
		   rank_array[i].hour,
		   rank_array[i].minute,
		   rank_array[i].second
		   );

	  if(i == n-1){
	    mvprintw(center_y/2 +i +1, center_x -(strlen(msg_bar2)/2), msg_bar2);
	    mvprintw(center_y/2 +i +2, center_x -(strlen(msg_bar)/2), msg_bar);
	  }

	}



	mvprintw(max_y -center_y/8, center_x -(strlen(msg_how)/2), "%s", msg_how);


	// カーソルを出力しない
	curs_set(0);

	// 文字をバッファーに溜めない
	crmode();

	// 入力文字を出力しない
	noecho();

	while(true){
		ch = getch();
		refresh();
		if(ch == '0'){
			break;
		}
	}

	clear();
	refresh();
	endwin();


}


