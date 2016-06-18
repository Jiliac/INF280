#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <list>
#include <map>

using namespace std;

/*********************************************/
/**************** PIECE Class ****************/
/*********************************************/

class Piece {
  private:
    int x, y;
    int previous;
    int dist;
  public:
    Piece() {x=-1; y=-1; previous = -1; dist = -1;}
    void set(int _x, int _y) {x=_x; y=_y;}

    bool moveUp(bool board[8][8]) {
      if(x == 0) { return false;}
      else if(x == 1 && board[x-1][y]) {return false;}
      else if(x < 1 && board[x-1][y]) {x-=2; return true;}
      else { --x; return true;}
    }
    bool moveRight(bool board[8][8]) {
      if(y == 7) {return false;}
      else if(y == 6 && board[x][y+1]) {return false;}
      else if(y < 6 && board[x][y+1]) {y+=2; return true;}
      else {++y; return true;}
    }
    bool moveDown(bool board[8][8]) {
      if(x == 7) {return false;}
      else if(x == 6 && board[x+1][y]) {return false;}
      else if(x < 6 && board[x+1][y]) {x+=2; return true;}
      else {++x; return true;}
    }
    bool moveLeft(bool board[8][8]) {
      if(y == 0) {return false;}
      else if(y == 1 && board[x][y-1]) {return false;}
      else if(y > 1 && board[x][y-1]) {y-=2; return true;}
      else {--y; return true;}
    }

    int getX() {return x;}
    int getY() {return y;}
    void setPrevious(int _previous) {previous = _previous;}
    int getPrevious() {return previous;}
    void setDist(int _dist) {dist = _dist;}
    int getDist() {return dist;}

    void getChessboard(Piece* newChessboard, Piece* previousChessboard) {
      for(int piece_nb = 0; piece_nb < 4; ++piece_nb) {
        if(piece_nb == previous)
          newChessboard[piece_nb].set(x,y);
        else
          newChessboard[piece_nb] = previousChessboard[piece_nb];
      }
    }
};

/*********************************************/
/****************** MAIN *********************/
/*********************************************/

int board_distance(Piece*, Piece*);
bool search(Piece*, Piece*, int);

int main() {
  //record
  Piece chessboard[4];
  Piece chess_goal[4];
  for(int tmp = 0; tmp < 4; ++tmp) {
    int x, y; cin >> x; cin >> y;
    --x; --y;
    chessboard[tmp].set(x, y);
  }
  for(int tmp = 0; tmp < 4; ++tmp) {
    int x, y; cin >> x; cin >> y;
    --x; --y;
    chess_goal[tmp].set(x, y);
  }

  //analyse
  if(search(chessboard, chess_goal, 8)) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }

  return 0;
}

/*********************************************/
/*************** BRANCH & BOUND **************/
/*********************************************/



list<Piece> branch(Piece*, int);
list<Piece> bound(list<Piece>, Piece*, Piece*, int);
map<string, int> board_map;
bool search(Piece* chessboard, Piece* chess_goal, int nb_of_moves) {
  bool search_result = false;
  int dist = board_distance(chessboard, chess_goal);
  printf("dist %i= and nb of moves = %i\n", dist, nb_of_moves);
  if(dist <= nb_of_moves){
    return true;
  } else {
    list<Piece> branched_pieces = branch(chessboard, nb_of_moves);
    list<Piece> bounded_pieces = bound(branched_pieces, chessboard, chess_goal, nb_of_moves);
    for(list<Piece>::iterator piece_pointer = bounded_pieces.begin(); piece_pointer != bounded_pieces.end(); ++piece_pointer) {
      Piece newChessboard[4];
      (*piece_pointer).getChessboard(newChessboard, chessboard);
      if(search(newChessboard, chess_goal, nb_of_moves - 1))
        return true;
    }
  }
  return search_result;
}

struct toDelete{
  int maxDist;
  toDelete(int nb_of_moves){maxDist = 2 * nb_of_moves;}
  bool operator() (Piece& piece) {
    return (piece.getDist() >= maxDist);
  }
};
bool compare_piece(Piece piece1, Piece piece2) {
  int dist1, dist2; dist1 = piece1.getDist(); dist2 = piece2.getDist();
  return (dist1 < dist2);
}
list<Piece> bound(list<Piece> pieces, Piece* previousChessboard, Piece* chess_goal, int nb_of_moves){
  for(list<Piece>::iterator piece_pointer = pieces.begin(); piece_pointer != pieces.end(); ++piece_pointer) {
    Piece chessboard[4];
    (*piece_pointer).getChessboard(chessboard, previousChessboard);
    int dist = board_distance(chessboard, chess_goal);
    (*piece_pointer).setDist(dist);
  }

  pieces.remove_if(toDelete(nb_of_moves));
  pieces.sort(compare_piece);

  return pieces;
}

string tostring(bool[8][8]);
list<Piece> branch(Piece* chessboard, int nb_of_moves) {
  bool board[8][8];
  for(int i=0;i<8;++i){for(int j=0;j<8;++j){board[i][j]=false;}}
  for(int tmp = 0; tmp < 4; ++tmp) {
    int x = chessboard[tmp].getX(); int y = chessboard[tmp].getY();
    board[x][y] = true;
  }
  list<Piece> branched_pieces;

  if(board_map.count(tostring(board))>0) {
    if(board_map[tostring(board)]>nb_of_moves){
      return branched_pieces;
    }
  } else {board_map[tostring(board)] = nb_of_moves;}
  
  for(int piece_nb = 0; piece_nb < 4; ++piece_nb) {
    for(int direction = 0; direction < 4; ++direction) {
      Piece piece = chessboard[piece_nb];
      switch(direction) {
        case 0:
          if(piece.moveUp(board)) {
            piece.setPrevious(piece_nb);
            branched_pieces.push_back(piece);
          }
          break;
        case 1:
          if(piece.moveRight(board)) {
            piece.setPrevious(piece_nb);
            branched_pieces.push_back(piece);
          }
          break;
        case 2:
          if(piece.moveDown(board)) {
            piece.setPrevious(piece_nb);
            branched_pieces.push_back(piece);
          }
          break;
        case 3:
          if(piece.moveLeft(board)) {
            piece.setPrevious(piece_nb);
            branched_pieces.push_back(piece);
          }
          break;
      }
    }
  }
  return branched_pieces;
}

/*********************************************/
/************** DISTANCE *********************/
/*********************************************/

int piece_distance(Piece piece1, Piece piece2) {
  int distX = piece1.getX() - piece2.getX();
  int distY = piece1.getY() - piece2.getY();
  if(distX < 0) {distX = -distX;}
  if(distY < 0) {distY = -distY;}
  return (distX + distY);
}

bool non_equal(int, int, int, int);
int board_distance(Piece* chessboard, Piece* chess_goal) {
  int distances[4][4];
  for(int i = 0; i < 4; ++i) {
    for(int j = 0; j < 4; ++j) {
      distances[i][j] = piece_distance(chessboard[i], chess_goal[j]);
    }
  }

  int cumul_distances[24];
  int cumul_distance_index = 0;
  for(int index0 = 0; index0 < 4; ++index0) {
    for(int index1 = 0; index1 < 4; ++index1) {
      for(int index2 = 0; index2 < 4; ++index2) {
        for(int index3 = 0; index3 < 4; ++index3) {
          if(non_equal(index0, index1, index2, index3)){
            cumul_distances[cumul_distance_index] = distances[0][index0] + distances[1][index1] + distances[2][index2] + distances[3][index3];
            ++cumul_distance_index;
          }
        }
      }
    }
  }
  sort(cumul_distances, cumul_distances + 24);
  return cumul_distances[0];
}

bool non_equal(int i0, int i1, int i2, int i3) {
  return (i0!=i1 && i0!=i2 && i0!=i3
      && i1!=i2 && i1!=i3
      && i2!=i3);
}

string tostring(bool board[8][8]){
  string str = "";
  for(int i = 0; i < 8; ++i) {
    for(int j = 0; j < 8; ++j) {
      if(board[i][j])
        str += "1";
      else
        str += "0";
    }
  }
  return str;
}
