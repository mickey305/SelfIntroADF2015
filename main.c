#include "main.h"

int main(int argc, char *argv[]){
  int select_signal;
  FLAG move_rank = false,fin_status = false;

  if(argc == 1){

    // 画面サイズ変更
    system("resize -s 40 80");

    while(true){
      select_signal = select_menu();
    	switch(select_signal){
    		// ゲームモード!!
    		case 1:
		        move_rank = call_game();
    			break;
    		// ランキングモード!!
    		case 2:
		        call_rank();
    			break;
    		// ヘルプモード!!
    		case 3:
		        call_help();
    			break;
    		// プログラム終了!!
    		case 0:
		        fin_status = true;
    			break;
    		default:
    			break;
    	}
    	if(move_rank){
	        call_rank();
    		move_rank = false;
    	}
    	if(fin_status){
    		break;
    	}
    }

    // 復帰画面を綺麗にする
    system("clear");

  }else{
  	fprintf(stderr, "エラー：オプションは入力しないでください。\n");
  	exit(2);

  }


  return 0;
}
