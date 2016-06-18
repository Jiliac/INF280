#include <stdio.h>
#include <iostream>
#include <set>
#include <list>

using namespace std;

/*********************************************/
/**************** PIECE Class ****************/
/*********************************************/

class Piece {
  private:
    int x, y;
    int previous;
  public:
    Piece() {x=-1; y=-1; previous = -1;}
    void set(int _x, int _y) {x=_x; y=_y;}

    bool moveUp(bool board[8][8]) {
      if(x == 0) { return false;}
      else if(x == 1 && board[x-1][y]) {return false;}
      else if(x > 1 && board[x-1][y]) {x-=2; return true;}
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
void explore(Piece*, set<string>*, int);
bool is_shared_elt(set<string>*, set<string>*);

int main() {
  Piece chessboard1[4];
  Piece chessboard2[4];
  for(int piece_nb = 0; piece_nb < 4; ++piece_nb) {
    int x, y; cin >> x; cin >> y;
    --x; --y;
    chessboard1[piece_nb].set(x, y);
  }
  for(int piece_nb = 0; piece_nb < 4; ++piece_nb) {
    int x, y; cin >> x; cin >> y;
    --x; --y;
    chessboard2[piece_nb].set(x, y);
  }

  set<string> from1;
  set<string> from2;
  explore(chessboard1, &from1, 4);
  explore(chessboard2, &from2, 4);

  if(is_shared_elt(&from1, &from2))
    printf("YES\n");
  else
    printf("NO\n");
  
  return 0;
}

bool is_shared_elt(set<string>* from1, set<string>* from2) {
  for(set<string>::iterator situation1 = (*from1).begin(); situation1 != (*from1).end(); ++situation1) {
    if((*from2).count(*situation1))
      return true;
  }
  return false;
}

list<Piece> branch(Piece*, set<string>*);
void explore(Piece* chessboard, set<string>* from, int nb_of_moves) {
  if(nb_of_moves > 0) {
    list<Piece> newPieces = branch(chessboard, from);
    for(list<Piece>::iterator piece_pointer = newPieces.begin(); piece_pointer != newPieces.end(); ++piece_pointer){
      Piece newChessboard[4];
      (*piece_pointer).getChessboard(newChessboard, chessboard);
      explore(newChessboard, from, nb_of_moves - 1);
    }
  }
}

string tostring(bool[8][8]);
list<Piece> branch(Piece* chessboard, set<string>* from) {
  bool board[8][8];
  for(int i=0;i<8;++i){for(int j=0;j<8;++j){board[i][j]=false;}}
  for(int piece_nb = 0; piece_nb < 4; ++piece_nb) {
    int x = chessboard[piece_nb].getX(); int y = chessboard[piece_nb].getY();
    board[x][y] = true;
  }
  list<Piece> branched_pieces;

  int direction = -1;
  for(int piece_nb = 0; piece_nb < 4; ++piece_nb) {
    for(int direction = 0; direction < 4; ++direction) {
      Piece piece = chessboard[piece_nb];
      switch(direction) {
        case 0:
          if(piece.moveUp(board)) {
            direction = 0;
          }
          break;
        case 1:
          if(piece.moveRight(board)) {
            direction = 1;
          }
          break;
        case 2:
          if(piece.moveDown(board)) {
            direction = 2;
          }
          break;
        case 3:
          if(piece.moveLeft(board)) {
            direction = 3;
          }
          break;
      }

      if(direction!=-1) {
        piece.setPrevious(piece_nb);
        bool newBoard[8][8];
        for(int i=0;i<8;++i){for(int j=0;j<8;++j){newBoard[i][j]=false;}}
        Piece newChessboard[4];
        piece.getChessboard(newChessboard, chessboard);
        for(int piece_nb = 0; piece_nb < 4; ++piece_nb) {
          int x = newChessboard[piece_nb].getX(); int y = newChessboard[piece_nb].getY();
          newBoard[x][y] = true;
        }
        (*from).insert(tostring(newBoard));
        branched_pieces.push_back(piece);
      }
    }
  }
  return branched_pieces;
}

string tostring(bool board[8][8]) {
  string result = "";
  for(int i = 0; i < 8; ++i) {
    for(int j = 0; j < 8; ++j) {
      if(board[i][j])
        result += '1';
      else
        result += '0';
    }
  }
  return result;
}

/********* for debug *********/
void printBoard(bool board[8][8]) {
  printf("\n============\n");
  for(int i = 0; i < 8; ++i) {
    for(int j = 0; j < 8; ++j) {
      printf("%i ", board[i][j]);
    }
    printf("\n");
  }
  printf("============\n");
}
