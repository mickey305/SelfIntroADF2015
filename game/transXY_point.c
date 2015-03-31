#include "../main.h"

INPUT_POINT transXY_point(INPUT_POINT inputed){
  int x,y,i;
  FLAG isFinX =false, isFinY =false;

  for(i=0;i<9;i++){
    if(inputed.x == '1'+i && !isFinX){
      x =i;
      isFinX =true;
    }
    if((inputed.y == 'a'+i || inputed.y == 'A'+i) && !isFinY){
      y =i;
      isFinY =true;
    }
    if(isFinX && isFinY)break;
  }

  inputed.x =x;
  inputed.y =y;

  return (inputed);
}

