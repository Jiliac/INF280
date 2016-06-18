#include <stdio.h>
#include <iostream>
#include <list>

using namespace std;

void look_for_word(char*, char[40][40], bool[40][40], int, int);

int main() {
  while(1) {
    int n, m; cin >> n >> m;
    if(cin.fail()) break;
    int k;
    char words [200][23]; for(int i=0;i<200;++i){for(int j=0;j<23;++j) {words[i][j]=-1;}}
    char grid[40][40]; for(int i=0;i<40;++i){for(int j=0;j<40;++j) {grid[i][j]=-1;}}
    bool highlighting[40][40]; for(int i=0;i<40;++i){for(int j=0;j<40;++j) {highlighting[i][j]=false;}}
    scanf("%i\n", &k);
    for(int word_nb = 0; word_nb < k; ++word_nb) {
      scanf("%s\n", words[word_nb]);
    }
    for(int row = 0; row < n; ++row) {
      scanf("%s", grid[row]);
    }

    for(int word_nb = 0; word_nb < k; ++word_nb) {
      look_for_word(words[word_nb], grid, highlighting, n, m);
    }
    for(int x = 0; x < n; ++x) {
      for(int y = 0; y < m; ++y) {
        if(!highlighting[x][y])
          printf("%c", grid[x][y]);
      }
    }
    printf("\n");
  }

  return 0;
}

struct Coord {int x=-1,y=-1;};
bool in_range(int, int, int, int);
void look_for_word(char* word, char grid[40][40], bool highlighting[40][40], int n, int m) {
  list<Coord> found;
  int word_size;
  int index = 0;
  while(word[index] != '\0') ++index;
  word_size = index;
  for(int row = 0; row < n; ++row) {
    for(int column = 0; column < m; ++column) {
      if(grid[row][column] == word[0]) {
        struct Coord coord;
        coord.x = row;
        coord.y = column;
        found.push_back(coord);
      }
    }
  }
  if(word_size == 1) {
    for(struct Coord coord : found) {
      highlighting[coord.x][coord.y] = true;
    }
    return;
  }
  for(struct Coord coord : found) {
    int x = coord.x, y = coord.y;
    list<Coord> nextCoords; struct Coord nextCoord;
    char nextChar = word[1];
    if(x > 0 && grid[x-1][y] == nextChar) {nextCoord.x = x-1; nextCoord.y = y; nextCoords.push_back(nextCoord);}
    if(x > 0 && y > 0 && grid[x-1][y-1] == nextChar) {nextCoord.x = x-1; nextCoord.y = y-1; nextCoords.push_back(nextCoord);}
    if(y > 0 && grid[x][y-1] == nextChar) {nextCoord.x = x; nextCoord.y = y-1; nextCoords.push_back(nextCoord);}
    if(x < n && y > 0 && grid[x+1][y-1] == nextChar) {nextCoord.x = x+1; nextCoord.y = y-1; nextCoords.push_back(nextCoord);}
    if(x < n && grid[x+1][y] == nextChar) {nextCoord.x = x+1; nextCoord.y=y; nextCoords.push_back(nextCoord);}
    if(x < n && y < m && grid[x+1][y+1] == nextChar) {nextCoord.x = x+1; nextCoord.y = y+1; nextCoords.push_back(nextCoord);}
    if(y < m && grid[x][y+1] == nextChar) {nextCoord.x = x; nextCoord.y = y+1; nextCoords.push_back(nextCoord);}
    if(x > 0 && y < m && grid[x-1][y+1] == nextChar) {nextCoord.x = x-1; nextCoord.y = y+1; nextCoords.push_back(nextCoord);}
    for(struct Coord nextCoord : nextCoords) {
      int dirX = nextCoord.x - x, dirY = nextCoord.y - y;
      index = 1;
      bool result = false;
      while(in_range(x + index*dirX, y + index*dirY, n, m)) {
        if(grid[x + index*dirX][y + index*dirY] == word[index]) {
          ++index;
          if(index == word_size) {
            result = true;
            break;
          }
        } else {
          result = false;
          break;
        }
      }
      if(result) {
        for(index = 0; index < word_size; ++index)
          highlighting[x + index*dirX][y + index*dirY] = true;
      }
    }
  }
}

bool in_range(int x, int y, int n, int m) {
  if(x < 0) return false;
  else if(x >= n) return false;
  else if(y < 0) return false;
  else if(y >= m) return false;
  else return true;
}
