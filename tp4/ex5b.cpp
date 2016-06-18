#include <stdio.h>
#include <algorithm>
#include <set>

using namespace std;

struct City {int city_nb = -1, set_nb = -1, rank = 0; set<int> probs;};
struct Road {int city1 = -1, city2 = -1; long danger = -1;};
bool compare (struct Road road1, struct Road road2) {return (road1.danger < road2.danger);}

void kruskal(set<int>*, struct City*, struct Road*, int, int*, int*, int*);

int main() {
  bool first_time = true;
  while(1) {
    int nb_of_cities, nb_of_roads;
    if(scanf("%i %i\n", &nb_of_cities, &nb_of_roads) != 2) break;
    if(first_time) first_time = false;
    else printf("\n");
    struct Road roads[100000];
    struct City cities[50000]; for(int i=0;i<nb_of_cities;++i) {cities[i].city_nb = i; cities[i].set_nb = i;}
    set<int> sets[50000]; for(int i=0;i<nb_of_cities;++i) {sets[i].insert(i);}
    int s[50000], t[50000], answers[50000]; for(int i=0;i<50000;++i) {s[i]=-1;t[i]=-1;answers[i]=-2;}
    for(int road_nb = 0; road_nb < nb_of_roads; ++road_nb) {
      int city1, city2;
      scanf("%i %i %li", &city1, &city2, &roads[road_nb].danger);
      --city1; --city2;
      roads[road_nb].city1 = city1; roads[road_nb].city2 = city2;
    }
    int q; scanf("%i", &q);
    for(int prob = 0; prob < q; ++prob) {
      scanf("%i %i", s + prob, t + prob);
      --s[prob]; --t[prob];
      cities[s[prob]].probs.insert(prob);
      cities[t[prob]].probs.insert(prob);
    }

    sort(roads, roads + nb_of_roads, compare);
    kruskal(sets, cities, roads, nb_of_roads, s, t, answers);
    for(int prob = 0; prob < q; ++prob)
      printf("%i\n", answers[prob]);
  }

  return 0;
}

int find(int, struct City*, set<int>*);
void union_set(int, int, struct City*, set<int>* sets);

void kruskal(set<int>* sets, struct City* cities, struct Road* roads, int nb_of_roads, int* s, int* t, int* answers) {
  for(int road_nb = 0; road_nb < nb_of_roads; ++road_nb) {
    struct Road road = roads[road_nb];
    int city1_nb = road.city1, city2_nb = road.city2;
    int set1 = find(city1_nb, cities, sets), set2 = find(city2_nb, cities, sets);
    if(set1 != set2) {
      for(int city_nb : sets[set1]) {
        for(int prob : cities[city_nb].probs) {
          int ss = s[prob], tt = t[prob];
          if(sets[set1].count(ss) + sets[set2].count(tt) == 2 || sets[set1].count(tt) + sets[set2].count(ss) == 2) {
            answers[prob] = road.danger;
            s[prob] = -3;
            t[prob] = -3;
          }
        }
      }
      union_set(city1_nb, city2_nb, cities, sets);
    }
  }
}

int find(int city_nb, struct City* cities, set<int>* sets) {
  struct City* city = cities + city_nb;
  if((*city).set_nb == (*city).city_nb)
    return (*city).city_nb;
  else {
    int new_set_nb = find((*city).set_nb, cities, sets);
    sets[new_set_nb].insert(city_nb);
    return new_set_nb;
  }
}

void union_set(int city1_nb, int city2_nb, struct City* cities, set<int>* sets) {
  int xRoot_nb = find(city1_nb, cities, sets); struct City* xRoot = cities + xRoot_nb;
  int yRoot_nb = find(city2_nb, cities, sets); struct City* yRoot = cities + yRoot_nb;
  if((*xRoot).rank > (*yRoot).rank) {
    (*yRoot).set_nb = (*xRoot).city_nb;
    sets[(*xRoot).set_nb].insert((*yRoot).city_nb);
  } else if((*xRoot).rank < (*yRoot).rank) {
    (*xRoot).set_nb = (*yRoot).city_nb;
    sets[(*yRoot).set_nb].insert((*xRoot).city_nb);
  } else if((*xRoot).city_nb != (*yRoot).city_nb) {
    (*yRoot).set_nb = (*xRoot).city_nb;
    sets[(*xRoot).set_nb].insert((*yRoot).city_nb);
    (*xRoot).rank = (*xRoot).rank + 1;
  }
}
