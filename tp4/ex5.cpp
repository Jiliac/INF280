#include <stdio.h>
#include <algorithm>

using namespace std;

struct Road {int city1 = -1, city2 = -1; long danger = -1;};
struct City {int city_nb = -1, parent = -1, rank = 0;};
bool compare(struct Road road1, struct Road road2) {return (road1.danger < road2.danger);}

void kruskal(struct Road*, struct City*, int);

int main() {
  bool first_time = true;
  while(1) {
    int nb_of_cities, nb_of_roads;
    if(scanf("%i %i\n", &nb_of_cities, &nb_of_roads) != 2) break;
    if(first_time) first_time = false;
    else printf("\n");
    struct Road roads[100000];
    struct City cities[50000]; for(int i=0;i<nb_of_cities;++i) {cities[i].city_nb=i; cities[i].parent=i;}
    for(int road_nb = 0; road_nb < nb_of_roads; ++road_nb) {
      scanf("%i %i %li\n", &roads[road_nb].city1, &roads[road_nb].city2, &roads[road_nb].danger);
      --roads[road_nb].city1; --roads[road_nb].city2;
    }
    int q; scanf("%i\n", &q);
    for(int case_nb  = 0; case_nb < q; ++case_nb) {
      int s, t; scanf("%i %i", &s, &t); --s; --t;
    }

    sort(roads, roads + nb_of_roads, compare);
    kruskal(roads, cities, nb_of_roads);
  }

  return 0;
}

int find(struct City*, struct City*);
void union_set(struct City*, struct City*, struct City*);

void kruskal(struct Road* roads, struct City* cities, int nb_of_roads) {
  for(int road_nb = 0; road_nb < nb_of_roads; ++road_nb) {
    struct Road road = roads[road_nb];
    int city1 = road.city1, city2 = road.city2;
    if(find(&cities[city1], cities) != find(&cities[city2], cities)) {
      union_set(&cities[city1], &cities[city2], cities);
    }
  }
}

int find(struct City* city, struct City* cities) {
  if((*city).parent == (*city).city_nb)
    return (*city).city_nb;
  else {
    (*city).parent = find(&cities[(*city).parent], cities);
    return (*city).parent;
  }
}

void union_set(struct City* x, struct City* y, struct City* cities) {
  struct City* xRoot = &cities[find(x, cities)];
  struct City* yRoot = &cities[find(y, cities)];
  if((*xRoot).rank > (*yRoot).rank)
    (*yRoot).parent = (*xRoot).city_nb;
  else if((*xRoot).rank < (*yRoot).rank)
    (*xRoot).parent = (*yRoot).city_nb;
  else if((*xRoot).city_nb != (*yRoot).city_nb) {
    (*yRoot).parent = (*xRoot).city_nb;
    (*xRoot).rank = (*xRoot).rank + 1;
  }
}
