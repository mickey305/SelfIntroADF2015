#include "../main.h"

FLAG add_rank(int time){
  FILE *fp;
  char rank_file[] ="documents/rank.txt";
  RANK_BUF rank_buf[RANK_NUM];
  int num =0;

  if((fp = fopen(rank_file, "r+")) == NULL){
    print_rankerror();
    return (false);

  }else{

    num =read_rank(fp, rank_buf);
    insertion_sort(rank_buf, num);
    write_rank(fp, rank_buf, num, time);


    fclose(fp);
  }

  return (true);
}

int read_rank(FILE *fp, RANK_BUF rank_array[]){
  int i,num;
  RANK_BUF buf[RANK_NUM];

  i =0;
  while(fscanf(fp, "%s %s", buf[i].name, buf[i].time) != EOF){
    insert_rankArray(&rank_array[i] ,&buf[i]);

    ++i;
  }
  num =i;

  return (num);
}

/*
ランキングの情報が格納された配列の最後尾にあるデータを
入力で取得した情報に置き換える。

名前の入力文字は半角英数字とし、文字数は4〜10文字以内とする

 */
void write_rank(FILE *fp, RANK_BUF rank_array[], int num, int time){
  RANK_BUF inbuf;
  char msg_name[] ="名前を半角英数字で4〜10文字入力";
  int center_x,center_y,max_x,max_y;
  int ch,i;
  FLAG isEnter =false;
  char tmp[3];

  getmaxyx(stdscr, max_y, max_x);
  center_x = max_x/2;
  center_y = max_y/2;


  // 文字をバッファーに溜めない
  crmode();
 
  i =0;
  while(true){
    if(i ==0){
      clear();
      mvprintw(max_y -center_y/2, center_x -(strlen(msg_name)/3), msg_name);
      mvprintw(center_y +1, center_x -5, "----------");
      move(center_y, center_x -5);
    }

    isEnter =false;
    ch = getch();
 
    if(isupper(ch) != 0){
      strcpy(tmp, ch_AZ_to_res(ch, tmp));
      if(i ==0){
	strcpy(inbuf.name, "");
      }
      strcat(inbuf.name, tmp);
      mvprintw(center_y, center_x -5, "%s", inbuf.name);
      ++i;
    }else if(islower(ch) !=0){
      strcpy(tmp, ch_az_to_res(ch, tmp));
      if(i ==0){
	strcpy(inbuf.name, "");
      }
      strcat(inbuf.name, tmp);
      mvprintw(center_y, center_x -5, "%s", inbuf.name);
      ++i;
    }else if(isdigit(ch) != 0){
      strcpy(tmp, ch_09_to_res(ch, tmp));
      if(i ==0){
	strcpy(inbuf.name, "");
      }
      strcat(inbuf.name, tmp);
      mvprintw(center_y, center_x -5, "%s", inbuf.name);
      ++i;
    }else if(ch == '\n'){
      isEnter =true;
    }

    if(isEnter){
      if(i <= 10 && i >= 4){
	goto FINISH;
      }else{
	strcpy(inbuf.name, "");
	i =0;
      }
    }

    refresh();
  }
 FINISH:


  if(num != 0){
    if(num < RANK_NUM){
      strcat(inbuf.name, "");
      strcpy(inbuf.time, itoa(time, inbuf.time, 10));
      // num番目の配列に代入
      insert_rankArray(&rank_array[num], &inbuf);
      num ++;
    }else{
      strcat(inbuf.name, "");
      strcpy(inbuf.time, itoa(time, inbuf.time, 10));
      // num-1番目の配列に代入
      insert_rankArray(&rank_array[num -1], &inbuf);
    }
  }

  toWrite_rankFile(fp, rank_array, num);


}

void insert_rankArray(RANK_BUF *buf, RANK_BUF *tmp){
  strcpy(buf->name, tmp->name);
  strcpy(buf->time, tmp->time);
  buf->hour = atoi(buf->time) / (60 * 60);
  buf->minute = atoi(buf->time) % (60 * 60) / 60;
  buf->second = atoi(buf->time) % 60;

}

char *itoa(int val, char *a, int radix){
  char *p = a;
  unsigned int v = val;//作業用(変換対象の値)
  int n = 1;//変換文字列の桁数記憶用
  while(v >= radix){//桁数を求める
    v /= radix;
    n++;
  }
  p = a + n;//最下位の位置から設定する
  v = val;
  *p = '\0';//文字列終端の設定
  do{
    --p;
    *p = v % radix + '0';//1桁の数値を文字に変換
    if(*p > '9'){//変換した文字が10進で表現できない場合
      *p = v % radix - 10 + 'A'; //アルファベットを使う
    }
    v /= radix;
  }while( p != a);

  return a;
}

char *ch_AZ_to_res(int ch, char *res){
  // requisite include files
  // (stdio.h) stdbool.h string.h
  //
  int ch_A ='A';
  char *buf ="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char *pointer =res;
  int index,len;
  bool retflag =false;

  // be setting null-charactor to defind end-symbol
  ++pointer;
  *pointer ='\0';
  --pointer;

  // matching process -----------------------------
  index =0;
  len =strlen(buf);
  while(index < len){
    if(ch == ch_A +index){
      retflag =true;
      break;
    }
    ++buf;
    ++index;
  }

  // return process--------------------------------
  if(retflag){
    strncpy(pointer, buf, 1);
    return res;

  }else{
    return "\0";

  }
}

char *ch_az_to_res(int ch, char *res){
  // requisite include files
  // (stdio.h) stdbool.h string.h
  //
  int ch_A ='a';
  char *buf ="abcdefghijklmnopqrstuvwxyz";
  char *pointer =res;
  int index,len;
  bool retflag =false;

  // be setting null-charactor to defind end-symbol
  ++pointer;
  *pointer ='\0';
  --pointer;

  // matching process -----------------------------
  index =0;
  len =strlen(buf);
  while(index < len){
    if(ch == ch_A +index){
      retflag =true;
      break;
    }
    ++buf;
    ++index;
  }

  // return process--------------------------------
  if(retflag){
    strncpy(pointer, buf, 1);
    return res;

  }else{
    return "\0";

  }
}

char *ch_09_to_res(int ch, char *res){
  // requisite include files
  // (stdio.h) stdbool.h string.h
  //
  int ch_A ='0';
  char *buf ="0123456789";
  char *pointer =res;
  int index,len;
  bool retflag =false;

  // be setting null-charactor to defind end-symbol
  ++pointer;
  *pointer ='\0';
  --pointer;

  // matching process -----------------------------
  index =0;
  len =strlen(buf);
  while(index < len){
    if(ch == ch_A +index){
      retflag =true;
      break;
    }
    ++buf;
    ++index;
  }

  // return process--------------------------------
  if(retflag){
    strncpy(pointer, buf, 1);
    return res;

  }else{
    return "\0";

  }
}

void toWrite_rankFile(FILE *fp, RANK_BUF rank[], int file_num){
  int i;
  char tmp[TMP_BUF_SIZE_NORMAL];


  // ファイルの内容をクリア           
  system("> documents/rank.txt");

  fseek(fp, 0L, SEEK_SET);
  for(i=0;i<file_num;i++){
    mergeRANK(tmp, &rank[i]);

    //////////////////////////////////////////////////////////////////
    #ifdef DEBUG
    mvprintw(30 +i, 5, "%s", tmp);
    mvprintw(1,1,"%d", file_num);
    #endif
    //////////////////////////////////////////////////////////////////

    fputs(tmp, fp);
  }
  ///////////////////////////////////////////////////////
  #ifdef DEBUG
  while(true){
    i =getch();
    if(i =='0')break;
    refresh();
  }
  #endif
  ///////////////////////////////////////////////////////


}

void mergeRANK(char *res, RANK_BUF *buf){
  strcpy(res, buf->name);
  strcat(res, "\t");
  strcat(res, buf->time);
  strcat(res, "\n");

}

