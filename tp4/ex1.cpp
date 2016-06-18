#include <stdio.h>
#include <set>
#include <algorithm>
#include <math.h>

using namespace std;

bool compare_link(long long link1, long long link2) {return (link1/1000000 < link2/1000000);}
bool get_bit(int, int);
long kruskal(int);
void update_links(bool*, set<int>*, int[1000][2], int);

long long links[500000];

int main() {
  int nb_of_cases; scanf("%i\n\n", &nb_of_cases);
  for(int case_nb = 0; case_nb < nb_of_cases; ++case_nb) {
    int nb_of_cities, nb_of_subnetwork;
    scanf("%i %i\n", &nb_of_cities, &nb_of_subnetwork);
    int cities[1000][2]; for(int i=0;i<1000;++i) {cities[i][0]=-1;cities[i][1]=-1;}
    set<int> subnetworks[8];
    long subnetwork_cost[8]; for(int i=0;i<8;++i) {subnetwork_cost[i]=-1;}
    for(int sub_nb = 0; sub_nb < nb_of_subnetwork; ++sub_nb) {
      int nb_of_subcities; long cost;
      scanf("%i %li ", &nb_of_subcities, &cost);
      subnetwork_cost[sub_nb] = cost;
      for(int subcity_nb = 0; subcity_nb < nb_of_subcities; ++subcity_nb) {
        int subcity; scanf("%i", &subcity);
        subnetworks[sub_nb].insert(subcity-1);
      }
    }
    for(int city_nb = 0; city_nb < nb_of_cities; ++city_nb) {
      int x, y; scanf("%i %i\n", &x, &y);
      cities[city_nb][0] = x; cities[city_nb][1] = y;
    }

    bool chosen_subnetwork[8]; for(int i=0;i<8;++i) {chosen_subnetwork[i] = false;}
    long min_cost = 20000000;
    for(int bits = 0; bits < pow(2, nb_of_subnetwork); ++bits) {
      long total_cost = 0;
      for(int sub_nb = 0; sub_nb < nb_of_subnetwork; ++sub_nb) {
        if(get_bit(bits, sub_nb)) {
          chosen_subnetwork[sub_nb] = true;
          total_cost += subnetwork_cost[sub_nb];
        } else chosen_subnetwork[sub_nb] = false;
      } 
      update_links(chosen_subnetwork, subnetworks, cities, nb_of_cities);
      total_cost += kruskal(nb_of_cities);
      if(min_cost > total_cost) min_cost = total_cost;
    }
    printf("%li\n", min_cost);

    if(case_nb != nb_of_cases - 1)
      printf("\n");
  }

  return 0;
}

long kruskal(int nb_of_cities) {
  int city_in_network = 0;
  bool visited[500000]; for(int i=0; i<500000;++i) {visited[i]=false;}
  int index = 0;
  long total_cost = 0;
  while(city_in_network < nb_of_cities) {
    long long link = links[index];
    int city1 = link % 1000, city2=(link/1000) % 1000;
    long cost = link/1000000;
    if(!visited[city1] && !visited[city2]) {
      visited[city1] = true; visited[city2] = true;
      city_in_network += 2;
      total_cost += cost;
    } else if(!visited[city1] || !visited[city2]) {
      visited[city1] = true; visited[city2] = true;
      city_in_network += 1;
      total_cost += cost;
    }
    ++index;
  }
  printf("cost = %li\n", total_cost);
  return total_cost;
}

long long position(int, int, long); 
long distance(int, int, int[1000][2]);
void update_links(bool* chosen_subnetwork, set<int>* subnetworks, int cities[1000][2], int nb_of_cities) {
  set<int> sub_union;
  for(int sub_nb = 0; sub_nb < 8; ++sub_nb) {
    if(chosen_subnetwork[sub_nb]) {
      for(int city : subnetworks[sub_nb]) {
        sub_union.insert(city);
      }
    }
  }
  int index = 0;
  for(int city1 = 0; city1 < nb_of_cities; ++city1) {
    for(int city2 = city1 + 1; city2 < nb_of_cities; ++city2) {
      if(sub_union.count(city1) + sub_union.count(city2) == 2) {
        links[index] = position(city1, city2, 0);
      } else if(sub_union.count(city1) == 1) {
        long min = 20000000;
        for(int city : sub_union) {
          long dist = distance(city, city2, cities);
          if(dist < min) min = dist;
        }
        links[index] = position(city1, city2, min);
      } else if(sub_union.count(city2) == 1) {
        long min = 20000000;
        for(int city : sub_union) {
          long dist = distance(city1, city, cities);
          if(dist < min) min = dist;
        }
        links[index] = position(city1, city2, min);
      } else {
        links[index] = position(city1, city2, distance(city1, city2, cities));
      }
      ++index;
    }
  }
  sort(links, links + index, compare_link);
}

long long position(int city1, int city2, long cost) { 
  return city1 + city2 * 1000 + cost * 10000000;
}

bool get_bit(int n, int k) {
  int bit = (n & (1 << k)) >> k;
  if(bit == 1)
    return true;
  else
    return false;
}

long distance(int city1, int city2, int cities[1000][2]) {
  long cost = (cities[city1][0] - cities[city2][0]) * (cities[city1][0] - cities[city2][0]);
  cost += (cities[city1][1] - cities[city2][1]) * (cities[city1][1] - cities[city2][1]);
  return cost;
}
