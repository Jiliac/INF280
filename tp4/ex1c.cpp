#include <stdio.h>
#include <set>
#include <algorithm>

using namespace std;

struct Link {
  int city1=-1, city2=-1;
  long cost=-1;
};
bool compare_links(struct Link link1, struct Link link2) {return (link1.cost < link2.cost);}

long distance(int, int, int[1000][2]);
long kruskal(int*, struct Link*, int, int);
void set_union(int*, set<int>*, bool*, int);

int main() {
  int nb_of_cases; scanf("%i\n\n", &nb_of_cases);
  for(int case_nb = 0; case_nb < nb_of_cases; ++case_nb) {
    int nb_of_cities, nb_of_subnetworks;
    scanf("%i %i\n", &nb_of_cities, &nb_of_subnetworks);
    set<int> subnetworks[8];
    int subcosts[8] = {-1, -1, -1, -1, -1, -1, -1 ,-1};
    int cities[1000][2]; for(int i=0;i<1000;++i) {cities[i][0]=-1;cities[i][1]=-1;}
    struct Link links[500000];
    int sets[1000];
    for(int subnetwork_nb = 0; subnetwork_nb < nb_of_subnetworks; ++subnetwork_nb) {
      int nb_of_subcities, cost;
      scanf("%i %i", &nb_of_subcities, &cost);
      subcosts[subnetwork_nb] = cost;
      for(int subcity_nb = 0; subcity_nb < nb_of_subcities; ++ subcity_nb) {
        int city; scanf("%i", &city);
        subnetworks[subnetwork_nb].insert(city-1);
      }
    }
    for(int city_nb = 0; city_nb < nb_of_cities; ++city_nb) {
      int x, y;
      scanf("%i %i", &x, &y);
      cities[city_nb][0] = x;
      cities[city_nb][1] = y;
    }

    int index = 0;
    for(int city1 = 0; city1 < nb_of_cities; ++city1) {
      for(int city2 = city1 + 1; city2 < nb_of_cities; ++city2) {
        long cost = distance(city1, city2, cities);
        links[index].city1 = city1;
        links[index].city2 = city2;
        links[index].cost = cost;
        ++index;
      }
    }
    sort(links, links + index, compare_links);

    long min_cost = 20000000;
    for(int subs = 0; subs < (1 << nb_of_subnetworks); ++subs) {
      bool chosen_subs[8] = {false, false, false, false, false, false, false, false};
      long total_cost = 0;
      for(int sub_nb = 0; sub_nb < nb_of_subnetworks; ++sub_nb) {
        if(((subs & (1 << sub_nb)) >> sub_nb) == 1) {
          chosen_subs[sub_nb] = true;
          total_cost += subcosts[sub_nb];
        }
      }
      set_union(sets, subnetworks, chosen_subs, nb_of_subnetworks);
      total_cost += kruskal(sets, links, nb_of_cities, index);
      if(total_cost < min_cost) min_cost = total_cost;
    }

    printf("%li\n", min_cost);
    if(case_nb != nb_of_cases - 1) printf("\n");
  }

  return 0;
}

long kruskal(int* sets, struct Link* links, int nb_of_cities, int max_index) {
  int visited_cities = 0;
  long cost = 0;
  int max_category = -1;
  for(int city = 0; city < nb_of_cities; ++city) {
    if(sets[city] > max_category)
      max_category = sets[city];
  }

  int index = 0;
  while(index < max_index) {
    struct Link link = links[index];
    ++index;
    int city1 = link.city1, city2 = link.city2;
    if(sets[city1] == -1 || sets[city1] != sets[city2]) {
      cost += link.cost;
      if(sets[city1] == -1) ++visited_cities;
      if(sets[city2] == -1) ++visited_cities;
      if(sets[city1] == sets[city2]) {
        ++max_category;
        sets[city1] = max_category;
        sets[city2] = max_category;
      } else if(sets[city1] == -1) {sets[city1] = sets[city2];}
      else if(sets[city2] == -1) {sets[city2] = sets[city1];}
      else {
        int new_value = sets[city1];
        int ancient_value = sets[city2];
        for(int city = 0; city < nb_of_cities; ++city) {
          if(sets[city] == ancient_value)
            sets[city] = new_value;
        }
      }
    }
  }
  return cost;
}

void set_union(int* sets, set<int>* subnetworks, bool* chosen_subs, int nb_of_subnetworks) {
  for(int i=0; i<1000;++i) {sets[i]=-1;}
  int max_category = -1;
  for(int sub_nb = 0; sub_nb < nb_of_subnetworks; ++sub_nb) {
    if(chosen_subs[sub_nb]) {
      int value = -1;
      for(int city : subnetworks[sub_nb]) {
        if(sets[city] != value) {
          value = sets[city];
          break;
        }
      }
      if(value == -1)
        value = ++max_category;
      for(int city : subnetworks[sub_nb])
        sets[city] = value;
    }
  }
}

long distance(int city1, int city2, int cities[1000][2]) {
  int distX = cities[city1][0] - cities[city2][0];
  int distY = cities[city1][1] - cities[city2][1];
  return distX * distX + distY * distY;
}
