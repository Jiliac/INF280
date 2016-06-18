#include <stdio.h>
#include <stdlib.h>
#include <climits>

using namespace std;

struct Package {
  int x=-1,y=-1,weight=-1;
  int dist_to_origin=-1, dist_to_next=-1;
  int min=-1;
};

int distance (struct Package pack1, struct Package pack2) {
  return abs(pack1.x - pack2.x) + abs(pack1.y - pack2.y);
}

int main() {
  int nb_of_cases; scanf("%i", &nb_of_cases);
  for(int case_nb = 0; case_nb < nb_of_cases; ++case_nb) {
    int capacity, nb_packages;
    scanf("%i%i", &capacity, &nb_packages);
    struct Package packages[100000];
    struct Package origin; origin.x = origin.y = 0;
    for(int pack_nb = 0; pack_nb < nb_packages; ++pack_nb) {
      scanf("%i %i %i", &packages[pack_nb].x, &packages[pack_nb].y, &packages[pack_nb].weight);
      packages[pack_nb].dist_to_origin = distance(packages[pack_nb], origin);
      if(pack_nb != 0)
        packages[pack_nb-1].dist_to_next = distance(packages[pack_nb-1], packages[pack_nb]);
    }

    for(int pack_nb = 0; pack_nb < nb_packages; ++pack_nb) {
      int weight = 0, offset = 0, dist = 0;
      int min_dist = INT_MAX;
      while(pack_nb - offset >= 0 && weight + packages[pack_nb - offset].weight <= capacity) {
        weight += packages[pack_nb - offset].weight;
        if(offset == 0)
          dist += packages[pack_nb].dist_to_origin;
        else
          dist += packages[pack_nb-offset].dist_to_next;
        int current_dist = dist + packages[pack_nb - offset].dist_to_origin;
        if(pack_nb - offset - 1>= 0)
          current_dist += packages[pack_nb - offset - 1].min;
        if(current_dist < min_dist)
          min_dist = current_dist;
        ++offset;
      }
      packages[pack_nb].min = min_dist;
    }

    printf("%i\n", packages[nb_packages-1].min);
    if(case_nb != nb_of_cases - 1)
      printf("\n");
  }

  return 0;
}
