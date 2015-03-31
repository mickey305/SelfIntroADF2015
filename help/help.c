#include "../main.h"

void call_help(void){
	FILE *fp;
	char help_file[] = "documents/help.txt";



	if((fp = fopen(help_file, "r")) == NULL){
		print_helperror();

	}else{

	        print_help(fp);

		fclose(fp);
	}


}

void print_help(FILE *pfp){
	char msg_how[] = "0:メニューへ戻る";
	int center_x,center_y,max_x,max_y;
	int ch,i;
	char buffer[HELP_BUF_SIZE];



	// localeとして環境変数を利用
	setlocale(LC_ALL, "");


	initscr();

	getmaxyx(stdscr, max_y, max_x);
	center_x = max_x/2;
	center_y = max_y/2;


	i =0;
	while(fgets(buffer, HELP_BUF_SIZE, pfp) != NULL){
	  if(i==0)mvprintw(center_y/8 +i, center_x -(strlen(buffer)/2), "%s", buffer);
	  else mvprintw(center_y/8 +i, center_x/3, "%s", buffer);
	  ++i;
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

void print_helperror(void){
	char errmsg[] = "エラー：ヘルプファイルが存在しません。";
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

