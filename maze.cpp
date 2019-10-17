/*
 * lang can be compiled as c / c++ by gcc / g++
 * 1853426
 * filename maze.cpp
 * maze
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mapMax 10000

typedef struct {
  int row;
  int col;
} pointType;
typedef struct {
  int id;
  pointType p;
  int dir;
} pathStackType;
typedef struct {
  int row;
  int col;
  char ** map;
  pointType start;
  pointType end;
} mazeType;

void initMaze(mazeType * maze, pathStackType ** pathStack, bool ifInput) {
  if (ifInput) {
    int row, col;
    printf("Initialize the maze:\nInsert number of rows:");
    scanf("%i", &((*maze).row));
    printf("Insert number of columns:");
    scanf("%i", &((*maze).col));
    printf("Please Insert %i chars\n\"#\" or the number \"1\" means a wall in the maze\na blank or the number\"0\" means a space in the maze\nother chars will be ignored:\n", row*col);
    if (((*maze).row*(*maze).col) > mapMax) {
      printf("the map is too big\n");
      exit(0);
    }
    (*maze).map = (char**)malloc(sizeof(char)*(*maze).row);;
    for (int i = 0; i < (*maze).row; i++) {
      (*maze).map[i] = (char*)malloc(sizeof(char)*(*maze).col);
      for (int j = 0; j < (*maze).col; j++) {
        invalidChar:
        char ch = getchar();
        if (ch == '#' || ch == '1') {
          (*maze).map[i][j] = '1';
        } else if (ch == ' ' || ch == '0') {
          (*maze).map[i][j] = '0';
        } else {
          goto invalidChar;
        }
      }
    }
    { /* init end start point*/
      int i;
      bool startStatus = false, endStatus = false;
      printf("insert the start and the end point:\n");
      {
        mazeStartInsertWrong:
        mazeStartRowInsertWrong:
        printf("start: row(from 1 to %i):", (*maze).row);
        fflush(stdin);
        scanf("%i", &i);
        i--;
        if (i >= 0 && i < (*maze).row) {
          (*maze).start.row = i;
        } else {
          printf("Input out of range, re-enter\n");
          goto mazeStartRowInsertWrong;
        }
        mazeStartColInsertWrong:
        printf("start: col(from 1 to %i):", (*maze).col);
        fflush(stdin);
        scanf("%i", &i);
        i--;
        if (i >= 0 && i < (*maze).col) {
          (*maze).start.col = i;
        } else {
          printf("Input out of range, re-enter\n");
          goto mazeStartColInsertWrong;
        }
        if ((*maze).map[(*maze).start.row][(*maze).start.col] == '0') {
          (*maze).map[(*maze).start.row][(*maze).start.col] = '3';
        } else {
          printf("start point occupied, re-enter\n");
          goto mazeStartInsertWrong;
        }
      }
      {
        mazeEndInsertWrong:
        mazeEndRowInsertWrong:
        printf("end: row(from 1 to %i):", (*maze).row);
        fflush(stdin);
        scanf("%i", &i);
        i--;
        if (i >= 0 && i < (*maze).row) {
          (*maze).end.row = i;
        } else {
          printf("Input out of range, re-enter\n");
          goto mazeEndRowInsertWrong;
        }
        mazeEndColInsertWrong:
        printf("end: col(from 1 to %i):", (*maze).col);
        fflush(stdin);
        scanf("%i", &i);
        i--;
        if (i >= 0 && i < (*maze).col) {
          (*maze).end.col = i;
        } else {
          printf("Input out of range, re-enter\n");
          goto mazeEndColInsertWrong;
        }
        if ((*maze).map[(*maze).end.row][(*maze).end.col] == '0') {
          (*maze).map[(*maze).end.row][(*maze).end.col] = '4';
        } else {
          printf("end point occupied, re-enter\n");
          goto mazeEndInsertWrong;
        }
      }
    }
  } else { /* the default maze */
    /* 1 wall 0 space */
    char ch[10][10] = {
'1','1','1','1','1','1','1','1','1','1',
'1','0','0','1','0','0','0','1','0','1',
'1','0','0','1','0','0','0','1','0','1',
'1','0','0','0','0','1','1','0','0','1',
'1','0','1','1','1','0','0','0','0','1',
'1','0','0','0','1','0','0','0','0','1',
'1','0','1','0','0','0','1','0','0','1',
'1','0','1','1','1','0','1','1','0','1',
'1','1','0','0','0','0','0','0','0','1',
'1','1','1','1','1','1','1','1','1','1'
    };
    (*maze).row = 10;
    (*maze).col = 10;
    (*maze).map = (char**)malloc(sizeof(char*)*(*maze).row);
    for (int i = 0; i < (*maze).row; i++) {
      (*maze).map[i] = (char*)malloc(sizeof(char)*(*maze).col);
    }
    for (int i = 0; i < (*maze).row; i++) {
      for (int j = 0; j < (*maze).col; j++) {
        (*maze).map[i][j] = ch[i][j];
      }
    }
    (*maze).start.row = 1;
    (*maze).start.col = 1;
    (*maze).end.row = 8;
    (*maze).end.col = 8;
    
  }
  { /* init stack */
    pathStackType *p = (pathStackType*)malloc(((*maze).row)*((*maze).col)*sizeof(pathStackType));
    *pathStack = p;
  }
}

void showMaze(mazeType * maze) {
  for (int i = 0; i < (*maze).row; i++) {
    for (int j = 0; j < (*maze).col; j++) {
      if ((i == (*maze).start.row && j == (*maze).start.col) || (i == (*maze).end.row && j == (*maze).end.col)) {
        printf("%c", '*');
      } else if ((*maze).map[i][j] == '1') {
        printf("%c", '#');
      } else if ((*maze).map[i][j] == '2') {
        printf("%c", 'o');
      } else {
        printf("%c", ' ');
      }
    }
    printf("\n");
  }
  printf("start:[%i,%i] end:[%i,%i]\n", (*maze).start.row, (*maze).start.col, (*maze).end.row, (*maze).end.col);
}

int mazePath(mazeType * maze, pathStackType ** pathStack) {
  int pathNum = 0;
  int top = 0;
  int row, col, dir, find;
  (*pathStack)[top].p.row = 1;
  (*pathStack)[top].p.col = 1;
  (*pathStack)[top].dir = -1;
  (*maze).map[1][1] = '2';
  while (top > -1) {
    row = (*pathStack)[top].p.row;
    col = (*pathStack)[top].p.col;
    dir = (*pathStack)[top].dir;
    if (row==8 && col==8) {
      printf("%i:\n", pathNum+1);
      pathNum++;
      showMaze(maze);
      (*maze).map[(*pathStack)[top].p.row][(*pathStack)[top].p.col]='0';
      top--;
      row=(*pathStack)[top].p.row;
      col=(*pathStack)[top].p.col;
      dir=(*pathStack)[top].dir;
    }
    find=0;
    while (dir < 4 && find == 0) {
      dir++;
      switch (dir) {
        case 0:
        row = (*pathStack)[top].p.row - 1;
        col = (*pathStack)[top].p.col;
        break;
        case 1:
        row = (*pathStack)[top].p.row;
        col = (*pathStack)[top].p.col + 1;
        break;
        case 2:
        row = (*pathStack)[top].p.row + 1;
        col = (*pathStack)[top].p.col;
        break;
        case 3:
        row = (*pathStack)[top].p.row;
        col = (*pathStack)[top].p.col - 1;
        break;
      }
      if ((*maze).map[row][col] == '0') {
        find = 1;
      }
    }
    if (find == 1) {
            (*pathStack)[top].dir = dir;
            top++;
            (*pathStack)[top].p.row = row;
            (*pathStack)[top].p.col = col;
            (*pathStack)[top].dir = -1;
            (*maze).map[row][col] = '2';
    } else {
      (*maze).map[(*pathStack)[top].p.row][(*pathStack)[top].p.col] = '0';
      top--;
    }
  }
  return pathNum;
}

int main(int argc, char **argv) {

  bool ifInput = false;
  for(int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      printf("%s","Usage: maze [options]\nOptions:\n  -h                       Display this information.\n  --help                   Display this information.\n  -i                       Refuse to use the default maze.\n  --input                  Refuse to use the default maze.\n");
      return 0;
    } else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
      ifInput = true;
    }
  }

  mazeType maze;
  pathStackType * pathStack;
  initMaze(&maze, &pathStack, ifInput);

  printf("the map of the maze:\n");
  showMaze(&maze);

  int pathNum = mazePath(&maze, &pathStack);
  if (!pathNum) {
    printf("path not found\n");
  } else {
    printf("%i paths from start to end\n", pathNum);
  }

  fflush(stdin);
  printf("Press enter to continue...");
  getchar();

  return 0; 
}
