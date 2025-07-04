#include <stdio.h>

typedef struct { 
  enum tagField {pitcher, hitter} role; 
  union { 
    int SO; 
    int HR; 
  } u; 
} playerType; 

typedef struct uniontest
{
    playerType pt;
}uniontest;


int main(void){
    uniontest tmp;
    tmp.pt.role = pitcher;
    
    tmp.pt.u.SO = 1;
    tmp.pt.u.HR = 100;
    if(tmp.pt.role == pitcher)
        printf("SO%d", tmp.pt.u.SO);
}
