#include "../main.h"


void print_rankerror(void){
  char errmsg[] = "エラー：ランクファイルが存在しません。";
  char msg_how[] = "0:メニューへ戻る";
	int center_x,center_y,max_x,max_y;
	int ch;


	// localeとして環境変数を利用
	setlocale(LC_ALL, "");


	initscr();



	getmaxyx(stdscr, max_y, max_x);
	center_x = max_x/2;
	center_y = max_y/2;

	mvprintw(center_y/2, center_x -(strlen(errmsg)/3), "%s", errmsg);
	mvprintw(max_y -center_y/4, center_x -(strlen(msg_how)/3), "%s", msg_how);



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


void insertion_sort(RANK_BUF ary[], int num){
  int i,j;

  for(i =1; i < num; i++){
    j =i;
    while(j >= 1 && atoi(ary[j -1].time) > atoi(ary[j].time)){
      do_swap(&ary[j], &ary[j -1]);
      --j;
    }
  }


}

void do_swap(RANK_BUF *now, RANK_BUF *pre){
  RANK_BUF temp = *now;
  *now = *pre;
  *pre = temp;

}

