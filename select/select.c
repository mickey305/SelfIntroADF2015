#include "../main.h"

int select_menu(void){
  int i,max_x,max_y,center_x,center_y;
	int ch;
	int signal_num;
	char msg_title[][75] = {
	  " 13B4144652   228  5151   34   5-50-53    246            32  45  03    ",
	  "      465    331         34      153     121           45    2-        ",
	  "  3B 44-   611 8        31     50 53   243 5  45125   -4     27   14-41",
	  "   413         3  515-1-     31    01      6         32      45        "
	};
	char msg_list[4][MENU_LIST_BUF_SIZE] = {"1.START  ","2.RANKING","3.HELP   ","0.EXIT   "};
	char msg_how[] = "実行する番号を入力してください";

	// localeとして環境変数を利用
	setlocale(LC_ALL, "");

	initscr();


	set_color_bkgd_BLACK();


	getmaxyx(stdscr, max_y, max_x);
	center_x = max_x/2;
	center_y = max_y/2;

	// カーソルを出力しない
	curs_set(0);

	// 文字をバッファーに溜めない
	crmode();

	// 入力文字を出力しない
	noecho();


	#ifdef DEBUG
	mvprintw(center_y/2, center_x -(strlen(msg_title)/3), "%s", msg_title);
	#endif

	for(i=0;i<4;i++){
	  mvprintw(center_y/3 +i, 3, "%s", msg_title[i]);
	}
	for(i=0;i<4;i++){
		mvprintw(center_y -2 +i*2, center_x -(strlen(msg_list[i])/2), "%s", msg_list[i]);
	}
	mvprintw(center_y +center_y/2, center_x -(strlen(msg_how)/3), "%s", msg_how);


	while(true){

		ch = getch();
		switch(ch){
			case '1':
				signal_num = 1;
				break;
			case '2':
				signal_num = 2;
				break;
			case '3':
				signal_num = 3;
				break;
			case '0':
				signal_num = 0;
				break;
			default:
				break;
		}
		if(ch == '0' || ch == '1' || ch == '2' || ch == '3'){
		        refresh();
			break;
		}
		refresh();
	}


	//beep();

	clear();
	refresh();
	endwin();


	return (signal_num);
}


