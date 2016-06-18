#include <stdio.h>
#include <set>
#include <algorithm>
#include <math.h>

using namespace std;

struct Link {
  int city1;
  int city2;
  long cost;
};

struct Link links[500000];
long distances[1000][1000];
long distance(int, int, int[1000][2]);
void set_compo(int*, set<int>*, bool*);
void update_links(struct Link*, int*, set<int>*, bool*, long[1000][1000], int);
long kruskal(struct Link*, int);

int main() {
  int nb_of_cases; scanf("%i\n\n", &nb_of_cases);
  for(int case_nb = 0; case_nb < nb_of_cases; ++case_nb) {
    int nb_of_cities, nb_of_subnetworks;
    scanf("%i %i\n", &nb_of_cities, &nb_of_subnetworks);
    set<int> subnetworks[8];
    long subnetwork_costs[8] = {-1, -1, -1, -1, -1, -1 , -1, -1};
    int cities[1000][2]; for(int i=0;i<1000;++i) {cities[i][0]=-1; cities[i][1]=-1;}
    for(int sub_nb = 0; sub_nb < nb_of_subnetworks; ++sub_nb) {
      int nb_of_subcities; long sub_cost;
      scanf("%i %li ", &nb_of_subcities, &sub_cost);
      subnetwork_costs[sub_nb] = sub_cost;
      for(int subcity_nb = 0; subcity_nb < nb_of_subcities; ++subcity_nb) {
        int city_nb;
        scanf("%i", &city_nb);
        subnetworks[sub_nb].insert(city_nb-1);
      }
    }
    for(int city_nb = 0; city_nb < nb_of_cities; ++ city_nb) {
      int x, y; scanf("%i %i\n", &x, &y);
      cities[city_nb][0] = x;
      cities[city_nb][1] = y;
    }
    for(int i=0;i<1000;++i){for(int j=0;j<1000;++j) {distances[i][j]=-1;}}
    for(int city1_nb = 0; city1_nb < nb_of_cities; ++city1_nb) {
      for(int city2_nb = city1_nb + 1; city2_nb < nb_of_cities; ++city2_nb) {
        long dist = distance(city1_nb, city2_nb, cities);
        distances[city1_nb][city2_nb] = dist;
        distances[city2_nb][city1_nb] = dist;
      }
    }

    long min_cost = 20000000;
    for(int chosen_sub_nb = 0; chosen_sub_nb < pow(2, nb_of_subnetworks); ++chosen_sub_nb) {
      bool chosen_subs[8] = {false, false, false, false, false, false, false, false};
      int compo[1000];
      long total_cost = 0;
      for(int sub_nb = 0; sub_nb < nb_of_subnetworks; ++sub_nb) {
        if((chosen_sub_nb & (1 << sub_nb)) > 0) {
          chosen_subs[sub_nb] = true;
          total_cost += subnetwork_costs[sub_nb];
        }
      }
      set_compo(compo, subnetworks, chosen_subs);
      update_links(links, compo, subnetworks, chosen_subs, distances, nb_of_cities);
      printf("before kruskal = %li\n", total_cost);
      total_cost += kruskal(links, nb_of_cities);
      printf("total_cost = %li\n", total_cost);
      if(total_cost < min_cost) min_cost = total_cost;
    }
    printf("%li\n", min_cost);

    if(case_nb != nb_of_cases - 1)
      printf("\n");
  }
  return 0;
}

long kruskal(struct Link* links, int nb_of_cities) {
  int city_in_network = 0;
  bool visited[500000]; for(int i=0;i<500000;++i) {visited[i]=false;}
  long cost = 0;
  int index = 0;
  while(city_in_network < nb_of_cities) {
    struct Link link = links[index];
    if(!visited[link.city1] && !visited[link.city2]) {
      cost += link.cost;
      city_in_network += 2;
    } else if(!visited[link.city1] || !visited[link.city2]) {
      cost += link.cost;
      city_in_network += 1;
    }
    visited[link.city1] = true;
    visited[link.city2] = true;
    ++index;
  }
  return cost;
}

bool compare_link(struct Link link1, struct Link link2) {return (link1.cost < link2.cost);}
void update_links(struct Link* links, int* compo, set<int>* subnetworks, bool* chosen_subs, long distances[1000][1000], int nb_of_cities) {
  for(int i=0;i<500000;++i) {links[i].city1=-1; links[i].city2=-1; links[i].cost=-1;}
  int index = 0;
  for(int city1_nb = 0; city1_nb < nb_of_cities; ++city1_nb) {
    for(int city2_nb = city1_nb + 1; city2_nb < nb_of_cities; ++city2_nb) {
      links[index].city1 = city1_nb;
      links[index].city2 = city2_nb;
      if(compo[city1_nb] != -1 && compo[city1_nb] == compo[city2_nb]) {
        links[index].cost = 0;
      } else if(compo[city1_nb] != compo[city2_nb]) {
        long min = 20000000;
        //if(compo[city1_nb] == -1) {
        //  for(int sub_nb = 0; sub_nb < 8; ++sub_nb) {
        //    if(chosen_subs[sub_nb] && compo[*(subnetworks[sub_nb].begin())] == compo[city2_nb]) {
        //      for(int city : subnetworks[sub_nb]) {
        //        if(min > distances[city1_nb][city])
        //          min = distances[city1_nb][city];
        //      }
        //    }
        //  }
        //  links[index].cost = min;
        //} else if(compo[city2_nb] != -1) {
        //  for(int sub1_nb = 0; sub1_nb < 8; ++sub1_nb) {
        //    for(int sub2_nb = sub1_nb + 1; sub2_nb < 8; ++sub2_nb) {
        //      if(chosen_subs[sub1_nb] && chosen_subs[sub2_nb]
        //          && compo[*(subnetworks[sub1_nb].begin())] == compo[city1_nb]
        //          && compo[*(subnetworks[sub2_nb].begin())] == compo[city2_nb]) {
        //        for(int city1 : subnetworks[sub1_nb]) {
        //          for(int city2 : subnetworks[sub2_nb]) {
        //            if(min > distances[city1][city2])
        //              min = distances[city1][city2];
        //          }
        //        }
        //      }
        //    }
        //  }
        //} else --index;
      } else if (compo[city1_nb] == compo[city2_nb]) {
        links[index].cost = distances[city1_nb][city2_nb];
      ++index;
      }
    }
  } 
  sort(links, links + index, compare_link);
}

void set_compo(int* compo, set<int>* subnetworks, bool* chosen_subs) {
  for(int i=0;i<1000;++i) {compo[i]=-1;}
  for(int sub_nb = 0; sub_nb < 8; ++sub_nb) {
    if(chosen_subs[sub_nb]) {
      int value = -1;
      for(int city : subnetworks[sub_nb]) {
        if(compo[city] != value) {
          value = compo[city];
          break;
        }
      }
      if(value == -1)
        value = *(subnetworks[sub_nb].begin());
      for(int city : subnetworks[sub_nb]) {
        compo[city] = value;
      }
      //compo[value] = 1002;
    }
  }
}

long distance(int city1, int city2, int cities[1000][2]) {
  long cost = (cities[city1][0] - cities[city2][0]) * (cities[city1][0] - cities[city2][0]);
  cost += (cities[city1][1] - cities[city2][1]) * (cities[city1][1] - cities[city2][1]);
  return cost;
}
