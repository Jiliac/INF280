#include <stdio.h>
#include <iostream>
#include <numeric>
#include <vector>
#include <list>

using namespace std;

void bsf(long, bool[50][50][2520], int, int);
long position(int,int,int,int);
int lcmA(int*, int);
void print(bool[50][50][2520], int, int);

bool visited[6300000]; 

int main() {
  bool first_time = true;
  while(1) {
    int N; cin >> N;
    if(cin.fail()) break;
    if(first_time)
      first_time = false;
    else
      printf("\n");
    bool maps[50][50][2520]; for(int i=0;i<50;++i){for(int j=0;j<50;++j){for(int k=0;k<2520;++k) {maps[i][j][k]=false;}}}
    int time_table[50][50]; for(int i=0;i<50;++i){for(int j=0;j<50;++j) {time_table[i][j]=-1;}}
    int time_intervals[10]; for(int i=0;i<10;++i) {time_intervals[i] = 1;}
    for(int row_nb =0; row_nb < N; ++row_nb) {
      char row[50]; for(int i=0;i<50;++i) {row[i]='x';}
      scanf("%s", row);
      for(int columun_nb = 0; columun_nb < N; ++columun_nb) {
        if(row[columun_nb] == '.')
          maps[row_nb][columun_nb][0] = true;
      }
    }
    for(int row_nb =0; row_nb < N; ++row_nb) {
      char row[50]; for(int i=0;i<50;++i) {row[i]='z';}
      scanf("%s", row);
      for(int columun_nb = 0; columun_nb < N; ++columun_nb) {
        int value = row[columun_nb] - '0';
        time_intervals[value] = value;
        time_table[row_nb][columun_nb] = value;
      }
    }

    time_intervals[0] = 1;
    int period = lcmA(time_intervals, 10);
    long nb_of_cells = N * N * period;
    for(int row_nb = 0; row_nb < N; ++row_nb) {
      for(int columun_nb = 0; columun_nb < N; ++columun_nb) {
        int interval = time_table[row_nb][columun_nb];
        if(interval != 0) {
          for(int t = 1; t < period; ++t) {
            bool change = (((int) (t/interval)%2) == 1);
            maps[row_nb][columun_nb][t] = (maps[row_nb][columun_nb][0] != change);
          }
        } else {
          for(int t = 1; t < period; ++t) {
            maps[row_nb][columun_nb][t] = maps[row_nb][columun_nb][0];
          }
        } 
      }
    }
    //print(maps, N, 0);

    bsf(nb_of_cells, maps, N, period);
    int result = -1;
    for(int t = 0; t < period; ++t) {
      if(visited[position(N-1, N-1, t, N)]) {
        result = t;
        break;
      }
    }
    if(result != -1)
      printf("%i\n", result);
    else
      printf("NO\n");
  }

  return 0;
}

void find_neighbors(list<long>*, long, bool[50][50][2520], int, int);
void bsf(long nb_of_cells, bool maps[50][50][2520], int N, int period) {
  for(long i=0;i<nb_of_cells;++i) {visited[i] = false;}
  list<long> queue;
  queue.push_back(0);
  visited[0] = true;
  while(!queue.empty()) {
    long cell_nb = queue.front();
    queue.pop_front();
    if((cell_nb % (N*N)) == N*N-1) break;
    find_neighbors(&queue, cell_nb, maps, N, period);
  }
}

void find_neighbors(list<long>* queue, long cell_nb, bool maps[50][50][2520], int N, int period) {
  //long for_debug = cell_nb;
  int row_nb, columun_nb, t;
  row_nb = cell_nb % N; cell_nb -= row_nb;
  columun_nb = (cell_nb / N) % N; cell_nb -= columun_nb*N;
  t = (cell_nb / (N*N));
  if(t != period - 1) ++t;
  else t = 0;
  //printf("cell nb: %li, row: %i, columun: %i, t: %i\n", for_debug, row_nb, columun_nb, t);
  if(row_nb != N-1 && maps[row_nb+1][columun_nb][t])
  {
    long pos = position(row_nb+1, columun_nb, t, N);
    if(!visited[pos]) {
      (*queue).push_back(pos);
      visited[pos] = true;
    }
  }
  if(columun_nb != 0 && maps[row_nb][columun_nb-1][t])
  {
    long pos = position(row_nb, columun_nb-1, t, N);
    if(!visited[pos]) {
      (*queue).push_back(pos);
      visited[pos] = true;
    }
  }
  if(maps[row_nb][columun_nb][t])
  {
    long pos = position(row_nb, columun_nb, t, N);
    if(!visited[pos]) {
      (*queue).push_back(pos);
      visited[pos] = true;
    }
  }
  if(row_nb != 0 && maps[row_nb-1][columun_nb][t])
  {
    long pos = position(row_nb-1, columun_nb, t, N);
    if(!visited[pos]) {
      (*queue).push_back(pos);
      visited[pos] = true;
    }
  }
  if(columun_nb != N-1 && maps[row_nb][columun_nb+1][t])
  {
    long pos = position(row_nb, columun_nb+1, t, N);
    if(!visited[pos]) {
      (*queue).push_back(pos);
      visited[pos] = true;
    }
  }
}

long position(int x, int y, int t, int N) {
  return (x + y * N + t * N * N);
}

int lcm(int, int);
int lcmA(int* array, int max) {
  return accumulate(array, array + max, 1, lcm);
}
int gcd(int, int);
int lcm(int a, int b) {
  int temp = gcd(a, b);
  return temp ? (a / temp * b) : 0;
}
int gcd(int a, int b){
  while(1) {
    if (a == 0) return b;
    b %= a;
    if (b == 0) return a;
    a %= b;
  }
}

// FOR DEBUG
void print(bool maps[50][50][2520], int N, int nb_map) {
  printf("===========\n");
  for(int i = 0; i < N; ++i) {
    for(int j = 0; j < N; ++j) {
      if(maps[i][j][nb_map])
        printf(" ");
      else
        printf("X");
    }
    printf("\n");
  }
  printf("===========\n");
}
