/*
 * c++ maze
 * 1853426
 * filename maze.cpp
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

struct pointType {
  int x;
  int y;
};
struct pathType {
  int id;
  struct pointType p;
  int dir;
};
struct pathStack {
  struct pathType *base;
  struct pathType *top;
};

void initMaze(std::vector<std::vector<int> >& maze, bool ifInput) {
  if (ifInput) {
    int row, col;
    printf("Initialize the maze:\nInsert number of rows:");
    scanf("%i", &row);
    printf("Insert number of columns:");
    scanf("%i", &col);
    printf("Please Insert %i chars\n\"#\" or the number \"1\" means a wall in the maze\na blank or the number\"0\" means a space in the maze\nother chars will be ignored:\n", row*col);
    int* arr = (int *)malloc((row*col)*sizeof(int));
    fflush(stdin);
    for (int i = 0; i < row*col;) {
      https:
      char ch = getchar();
      if (ch == '#' || ch == '1') {
        arr[i] = 1;
        i++;
      } else if (ch == ' ' || ch == '0') {
        arr[i] = 0;
        i++;
      } else {
        goto https;
      }
      
    }
    maze.resize(row, std::vector<int>(col));
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        maze[i][j] = arr[i*col + j];
      }
    }
  } else {
    maze.resize(10, std::vector<int>(10));
    int arr[10][10] = {
1,1,1,1,1,1,1,1,1,1,
1,0,0,1,0,0,0,1,0,1,
1,0,0,1,0,0,0,1,0,1,
1,0,0,0,0,1,1,0,0,1,
1,0,1,1,1,0,0,0,0,1,
1,0,0,0,1,0,0,0,0,1,
1,0,1,0,0,0,1,0,0,1,
1,0,1,1,1,0,1,1,0,1,
1,1,0,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,1,1
    };
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        maze[i][j] = arr[i][j];
      }
    }
  }
}

void showMaze(std::vector<std::vector<int> >& maze) {
  for (int i = 0; i < maze.size(); i++) {
    for (int j = 0; j < maze[i].size(); j++) {
      if (maze[i][j] == 1) {
        printf("%c", '#');
      } else if (maze[i][j] == 2) {
        printf("%c", '+');
      } else if (maze[i][j] == 3) {
        printf("%c", '*');
      } else if (maze[i][j] == 4) {
        printf("%c", '*');
      } else {
        printf("%c", ' ');
      }
    }
    printf("%c", '\n');
  }
}

void mazePath(std::vector<std::vector<int> >& maze, int x1, int y1, int x2, int y2) {
  
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

  std::vector<std::vector<int> > maze;
  initMaze(maze, ifInput);

  int x1, x2, y1, y2;
  if (ifInput) {
    showMaze(maze);
      printf("Insert the coordinate of the start and the end point\nTaking the first row and the first column as the origin\nthe start:\nHorizontal axis:x=");
    scanf("%i", x1);
    printf("Vertical axis:y=");
    scanf("%i", y1);
    printf("the end:\nHorizontal axis:x=");
    scanf("%i", x2);
    printf("Vertical axis:y=");
    scanf("%i", y2);
  } else {
    x1 = 1;
    y1 = 1;
    x2 = 8;
    y2 = 8;
  }
  maze[y1][x1] = 3;
  maze[y2][x2] = 4;

  showMaze(maze);

  mazePath(maze, x1, y1, x2, y2);

  printf("result:\n");
  showMaze(maze);

  fflush(stdin);
  printf("Press any key to continue...");
  getchar();
  return 0; 
}
