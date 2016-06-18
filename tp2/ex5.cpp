#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <list>
#include <string>

using namespace std;

/**************************************************/
/******************* MY PIECE OBJECT ***************/
/**************************************************/

class Piece {
  private:
    int x, y;
    int previous;
    int dist;
  public:
    Piece() {x=-1; y=-1; previous = -1; dist = -1;}
    void set(int _x, int _y) {
      x = _x;
      y = _y;
    }      
    bool moveUp(bool** board) {
      if(x == 0) {return false;}
      else if(x > 1 && board[x-1][y]){x-=2; return true;}
      else {--x; return true;}
    }
    bool moveDown(bool** board) {
      if(x == 7) {return false;}
      else if(x < 6 && board[x+1][y]){x+=2; return true;}
      else {++x; return true;}
    }
    bool moveLeft(bool** board) {
      if (y == 0) {return false;}
      else if(y > 1 && board[y-1][x]){y-=2; return true;}
      else {--y; return true;}
    }
    bool moveRight(bool** board) {
      if (y == 7) {return false;}
      else if( y < 6 && board[y+1][x]){y+=2; return true;}
      else {++y; return true;}
    }
    int getX() {return x;}
    int getY() {return y;}
    void setPrevious(int _previous){previous = _previous;}
    int getPrevious() {return previous;}
    void setDist(int _dist){dist = _dist;}
    int getDist() {return dist;}
    void print(){
      printf("dist = %i, x = %i and y = %i\n", dist, x, y);
    }
};

/**************************************************/
/******************* MAIN & Declaration ***********/
/**************************************************/

bool search(Piece*, Piece*);
list<Piece> branch_and_bound(Piece*, Piece*);
int distance_piece(Piece, Piece);
int distance_pieces(Piece*, Piece*);
string result_to_print = "NO\n";

int main() {
  Piece chessboard1[4];
  Piece chessboard2[4];
  for(int i = 0; i < 4; ++i) {
    int x, y; cin >> x; cin >> y;
    --x; --y;
    chessboard1[i].set(x, y);
  }
  for(int i = 0; i < 4; ++i) {
    int x, y; cin >> x; cin >> y;
    --x; --y;
    chessboard2[i].set(x, y);
  }

  if(distance_pieces(chessboard1, chessboard2) <= 3){
    printf("WTF!!!\n");
  }
  //else if(search(chessboard1, chessboard2))
  //  result_to_print = "YES\n";
  //printf("TOOO\n");
  printf("%s", result_to_print.c_str());

  return 0;
}

/******************** SEARCH ********************/
bool search(Piece* chessboard1, Piece* chessboard2) {
  printf("TOTO\n");
  list<Piece> subset = branch_and_bound(chessboard1, chessboard2);
  bool result = false;
  for(list<Piece>::iterator it = subset.begin(); it != subset.end(); ++it) {
    if((*it).getDist() <= 8){
      (*it).print();
      return true;
    }
    Piece newChessboard[4];
    int previous = (*it).getPrevious();
    for(int index = 0; index < 4; ++index) {
      if(index == previous)
        newChessboard[index] = (*it);
      else
        newChessboard[index] = chessboard1[index];
    }
    if(search(newChessboard, chessboard2))
      return true;
  }
  return result;
}

/**************************************************/
/************************* BRANCH & BOUND *********************/
/**************************************************/

bool compare_piece(Piece piece1,Piece piece2) {
  int dist1, dist2;
  dist1 = piece1.getDist();
  dist2 = piece2.getDist();
  return (dist1 < dist2);
}

list<Piece> branch_and_bound(Piece* chessboard1, Piece* chessboard2) {
  // initialize
  list<Piece> branched_pieces;
  bool** board;
  board = (bool**) malloc(8 * sizeof(bool*));
  for(int tito = 0; tito < 8; ++tito){board[tito] = (bool*) malloc(8 * sizeof(bool));}
  for(int x=0;x<8;++x){for(int y=0;y<8;++y){board[x][y]=false;}} //init array at false
  for(int index = 0; index < 4; ++index) {
    Piece piece = chessboard1[index];
  printf("TOTO\n");
    int x, y; x = piece.getX(); y = piece.getY();
    board[x][y] = true;
  }
  
  // BRANCH !!
  for(int piece_index = 0; piece_index < 4; ++piece_index) {
    for(int case_nb = 0; case_nb < 4; ++case_nb) {
      switch(case_nb){
        case 0:
          {
            Piece piece; piece.set(chessboard1[piece_index].getX(), chessboard1[piece_index].getY());
            piece.setPrevious(case_nb);
            if(piece.moveUp(board))
              branched_pieces.push_back(piece);
            break;
          }
        case 1:
          {
            Piece piece; piece.set(chessboard1[piece_index].getX(), chessboard1[piece_index].getY());
            piece.setPrevious(case_nb);
            if(piece.moveRight(board))
              branched_pieces.push_back(piece);
            break;
          }
        case 2:
          {
            Piece piece; piece.set(chessboard1[piece_index].getX(), chessboard1[piece_index].getY());
            piece.setPrevious(case_nb);
            if(piece.moveDown(board))
              branched_pieces.push_back(piece);
            break;
          }
        case 3:
          {
            Piece piece; piece.set(chessboard1[piece_index].getX(), chessboard1[piece_index].getY());
            piece.setPrevious(case_nb);
            if(piece.moveLeft(board))
              branched_pieces.push_back(piece);
            break;
          }
      }
    }
  }

  //remove impossible branch, ie BOUND !
  list<Piece>::iterator it = branched_pieces.begin();
  while(it != branched_pieces.end()) {
    Piece newChessboard[4];
    int previous = (*it).getPrevious();
    for(int index = 0; index < 4; ++index) {
      if(index == previous)
        newChessboard[index] = (*it);
      else
        newChessboard[index] = chessboard1[index];
    }
    int dist = distance_pieces(newChessboard, chessboard2);
    (*it).setDist(dist);
    if(dist > 16) {
      it = branched_pieces.erase(it);
      if(branched_pieces.empty())
        break;
    }
    else
      ++it;
  }

  //sort
  branched_pieces.sort(compare_piece);

  //finish
  for(int tito = 0; tito < 8; ++tito) {free(board[tito]);}
  free(board);

  return branched_pieces;
}

/**************************************************/
/**************** COMPUTE MIN DISTANCE ************/
/**************************************************/

int distance_piece(Piece piece1, Piece piece2){
  int distX;
  int x1 = piece1.getX(); int x2 = piece2.getX();
  if(x1 < x2) {distX = x2 - x1;}
  else {distX = x1 - x2;}
  int distY;
  int y1 = piece1.getY(); int y2 = piece2.getY();
  if(y1 < y2) {distY = y2 - y1;}
  else {distY = y1 - y2;}
  return (distX + distY);
}

int distance_pieces(Piece* chessboard1, Piece* chessboard2) {
  int distances[4][4];
  for(int i = 0; i < 4; ++i) {
    for(int j = 0; j < 4; ++j) {
      Piece start_piece = chessboard1[i]; Piece arrival_piece = chessboard2[j];
      int dist = distance_piece(start_piece, arrival_piece);
      distances[i][j] = dist;
    }
  }

  int cumulative_distances[24];
  int cumulative_index = 0;
  for(int index0 = 0; index0 < 4; ++index0) {
    for(int index1 = 0; index1 < 4; ++index1) {
      if(index1 == index0) {if(index1!=3){++index1;}else{break;}}
      for(int index2 = 0; index2 < 4; ++index2) {
        if(index2 == index0 || index2 == index1) {if(index2!=3){++index2;}else{break;}}
        for(int index3 = 0; index3 < 4; ++index3) {
          if(index3 == index0 || index3 == index1 || index3 == index2){if(index3!=3){++index3;}else{break;}}

          cumulative_distances[cumulative_index] = distances[0][index0] + distances[1][index1] + distances[2][index2] + distances[3][index3];
          ++cumulative_index;
        }
      }
    }
  }
  sort(cumulative_distances, cumulative_distances + 24);
  return cumulative_distances[0];
}
