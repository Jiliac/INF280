#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Package {int x=-1, y=-1, weight=-1, dist_to_office=-1, dist_to_next=-1, dist = -1;};

int diff_weight(int i, int j, int* weight_sum) {return weight_sum[i] - weight_sum[j];}
int diff_dist(int i, int j, int* dist_to_next_sum) {return dist_to_next_sum[i+1] - dist_to_next_sum[j+1];}

int main() {
  int nb_of_cases; scanf("%i", &nb_of_cases);
  for(int case_nb = 0; case_nb < nb_of_cases; ++case_nb) {
    int capacity, nb_of_pack;
    int weight_sum[100000], dist_to_next_sum[100000], index[100000];
    for(int i=0;i<100000;++i) {weight_sum[i]=-1;dist_to_next_sum[i]=-1;index[i]=0;}
    struct Package packages[100000];
    scanf("%i\n\n%i", &capacity, &nb_of_pack);
    for(int pack_nb = 0; pack_nb < nb_of_pack; ++pack_nb) {
      scanf("%i %i %i", &packages[pack_nb].x, &packages[pack_nb].y, &packages[pack_nb].weight);
      packages[pack_nb].dist_to_office = packages[pack_nb].x + packages[pack_nb].y;
    }
    weight_sum[0] = packages[0].weight; dist_to_next_sum[0] = 0;
    for(int pack_nb = 1; pack_nb < nb_of_pack; ++pack_nb) {
      int distX = packages[pack_nb-1].x - packages[pack_nb].x;
      int distY = packages[pack_nb-1].y - packages[pack_nb].y;
      packages[pack_nb-1].dist_to_next = abs(distX) + abs(distY);
      weight_sum[pack_nb] = weight_sum[pack_nb-1] + packages[pack_nb].weight;
      dist_to_next_sum[pack_nb] = dist_to_next_sum[pack_nb-1] + packages[pack_nb-1].dist_to_next;
    }

    int front = 0, back = 0;
    for(int pack_nb = 0; pack_nb < nb_of_pack; ++pack_nb) {
      while(front <= back && diff_weight(pack_nb, index[front], weight_sum) > capacity)
        ++front; 
      packages[pack_nb].dist = packages[index[front]+1].dist_to_office
        + packages[pack_nb].dist_to_office
        + diff_dist(pack_nb, index[front]+1, dist_to_next_sum)
        + packages[index[front]].dist;
      while(front <= back && diff_dist(pack_nb, index[back], dist_to_next_sum) + packages[pack_nb].dist_to_office - packages[pack_nb].dist_to_office
          + packages[pack_nb].dist - packages[index[front]].dist <= 0)
        --back;
      ++back;
      index[back] = pack_nb;
    }
    printf("%i\n", packages[nb_of_pack-1].dist);
  }
  return 0;
}
