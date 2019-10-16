/*
 * c++ maze
 * 1853426
 * filename maze.cpp
 *
 */

/*
insert:

##########
#S #   # #
#  #   # #
#    ##  #
# ###    #
#   #    #
# #   #  #
# ### ## #
##      E#
##########
*/


#include<stdio.h> 
#include<stdlib.h>
#include<string.h> 
#define Maxsize 1010 
#define Increment 100
typedef struct{
  int r, c; 
}PosType;
typedef struct{
  int ord;  
  PosType seat;
  int di;
}SElemType;
typedef struct{
  int c;
  int r;
  char arr[10][10];
}MazeType; 
typedef struct{ 
  SElemType *base;
  SElemType *top;
  int stacksize; 
}SqStack;
int Init(SqStack &S){
  S.base=(SElemType *)malloc(Maxsize*sizeof(SElemType));
  if(!S.base)  return 0;
  S.top=S.base;
  S.stacksize=Maxsize;
  return 1;
}
int Push(SqStack &S,SElemType x){ 
  if(S.top-S.base>=S.stacksize){
    S.base=(SElemType *)realloc(S.base,
      (S.stacksize+Increment)*sizeof(SElemType));
      if(!S.base)
        return 0;
    S.top=S.base+S.stacksize;
    S.stacksize+=Increment;
  } 
  *S.top++=x;
  return 1;
}
int Pop(SqStack &S, SElemType &x){ 
  if(S.top==S.base)  return 0;
  x=*--S.top;
  return 1;
}
bool Pass(MazeType maze, PosType curpos){
  return maze.arr[curpos.r][curpos.c]==' ' || maze.arr[curpos.r][curpos.c]=='S'
    || maze.arr[curpos.r][curpos.c]=='E';
}
int FootPrint(MazeType &maze, PosType curpos){
    maze.arr[curpos.r][curpos.c]='o';
  return 1;
}
PosType NextPos(PosType curpos, int di){ 
  PosType pos=curpos;
  switch(di)
  {
    case 1: pos.c++; break;    //右 
    case 2: pos.r++; break;    //下 
    case 3: pos.c--; break;    //左 
    case 4: pos.r--; break;    //上 
  }
  return pos;  
}
int MazePath(MazeType &maze, PosType start, PosType end){
  SqStack S; 
  PosType curpos;
  int curstep; 
  SElemType e; 
  Init(S);
  curpos=start;
  curstep=1;
  do
  {
    if(Pass(maze, curpos)) 
    {
      FootPrint(maze, curpos); 
      e.di = 1;
            e.ord = curstep;
            e.seat = curpos; 
      Push(S, e);
       if(curpos.c == end.c &&curpos.r == end.r )
        return 1;
      curpos=NextPos(curpos, e.di); 
      curstep++;
    }
    else
    {
      if(S.top!=S.base)
      {
        Pop(S, e);
        while(e.di==4 && S.top!=S.base) 
        {
          maze.arr[e.seat.r][e.seat.c]='!';
          Pop(S, e);
        }
        if(e.di<4)
        {
          e.di++;
          Push(S, e); 
          curpos=NextPos(e.seat, e.di);
        }
      }
    }
  } while(S.top!=S.base);
  return 0;
} 
int main()
{
  int i,j;
  MazeType maze;
  maze.r=10, maze.c=10;
  for(i=0; i<maze.r; i++)
  {  
    for(int j=0;j<maze.c; j++)
      scanf("%c", &maze.arr[i][j]);
    getchar();
  }
  PosType start, end;
  for(i=0; i<10; i++)
  {
    for(j=0; j<10; j++)
    {
      if(maze.arr[i][j]=='S')
      {
        start.r=i;
        start.c=j;
      }
      if(maze.arr[i][j]=='E')
      {
        end.r=i;
        end.c=j;
      }
    }
  }
  MazePath(maze, start, end);
  for(i=0; i<maze.r; i++)
  {
    for(j=0; j<maze.c; j++)
      printf("%c", maze.arr[i][j]);
    printf("\n");
  }
  printf("%i--%i", sizeof(char), sizeof(int));
  return 0; 
}
