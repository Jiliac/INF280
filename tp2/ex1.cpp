#include <stdio.h>
#include <iostream>

void printgrid(int maze[100][100], int cell_number);

using namespace std;

int main() {
  int case_number; cin >> case_number;
  for(int case_nb = 0; case_nb < case_number; ++case_nb) {
    int cell_number; cin >> cell_number;
    int exit; cin >> exit; --exit;
    int count_down; cin >> count_down;
    int connection_number; cin >> connection_number;
    int maze[100][100];
    for(int i = 0; i < 100; ++i) {
      for(int j = 0; j < 100; ++j) {
        maze[i][j] = 1000000;
      }
      maze[i][i] = 0;
    }
    for(int connection = 0; connection < connection_number; ++connection) {
      int a, b; cin >> a; cin >> b;
      cin >> maze[a - 1][b - 1];
    }

    //printgrid(maze, cell_number);
    for(int k = 0; k < cell_number; ++k) {
      for(int i = 0; i < cell_number; ++i) {
        for(int j = 0; j < cell_number; ++j) {
          int tmp = maze[i][k] + maze [k][j];
          if (tmp < maze[i][j])
            maze[i][j] = tmp;
        }
      }
    }
    //printgrid(maze, cell_number);
    int result = 0;
    for(int j = 0; j < cell_number; ++j) {
      if (maze[j][exit] <= count_down)
        ++result;
    }
    printf("%i\n", result);
    if(case_nb != case_number - 1)
      printf("\n");
  }

  return 0;
}

void printgrid(int maze[100][100], int cell_number) {
  for(int i = 0; i < cell_number; ++i){
    for(int j = 0; j < cell_number; ++j){
      int tmp = maze[i][j];
      if(tmp > 999999)
        tmp = -1;
      printf("%i ", tmp);
    }
    printf("\n");
  }
  printf("\n");
}
