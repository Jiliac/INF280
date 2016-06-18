#include <stdio.h>

using namespace std;

int main() {
  int case_nb = 1;
  while(1) {
    int max = 0;
    int graph[100][100];
    bool pages[100]; for(int i=0;i<100;++i) {pages[i]=false;}
    for(int i=0;i<100;++i) {for(int j=0;j<100;++j) {graph[i][j]=1000000;}}
    int from, to; scanf("%i %i", &from, &to);
    if(from == 0 && to == 0) break;
    while(from != 0 || to != 0) {
      if(from > max) max = from;
      if(to > max) max = to;
      --from; --to;
      graph[from][to] = 1;
      pages[from] = true; pages[to] = true;
      scanf("%i %i", &from, &to);
    }
    for(int i=0;i<max;++i) {graph[i][i]=0;}
    
    for(int k = 0; k < max; ++k) {
      for(int i = 0; i < max; ++i) {
        for(int j = 0; j < max; ++j) {
          int tmp= graph[i][k] + graph[k][j];
          if(tmp < graph[i][j]) graph[i][j] = tmp;
        }
      }
    }
    
    int sum = 0;
    for(int i = 0; i < max; ++i) {
      for(int j = 0; j < max; ++j) {
        if(graph[i][j] != 1000000)
          sum += graph[i][j];
      }
    }
    int nb_pages = 0;
    for(int i = 0; i < max; ++i) {if(pages[i]) ++nb_pages;}
    float average = sum / (1.0 * nb_pages * (nb_pages-1));
    printf("Case %i: average length between pages = %.3f clicks\n", case_nb++, average);
  }

  return 0;
}
