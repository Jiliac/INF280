#include <stdio.h>
#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

bool compare_intersection(list<int> inter1, list<int> inter2) {
  return (inter1.size() > inter2.size());
}
bool are_streets_secured(bool street_secured[10000], int nb_of_streets) {
  bool result = true;
  for(int i = 0; i < nb_of_streets; ++i) {
    result = result && street_secured[i];
  }
  return result;
}

int main() {
  while(1) {
    int nb_of_intersections, nb_of_streets;
    cin >> nb_of_intersections >> nb_of_streets;
    if(cin.fail()) break;
    bool street_secured[10000];
    for(int i = 0; i < 10000; ++i) {street_secured[i] = false;}
    list<int> intersections[1000];
    for(int street_nb = 0; street_nb < nb_of_streets; ++street_nb) {
      int intersection1, intersection2; 
      cin >> intersection1 >> intersection2;
      --intersection1; --intersection2;
      intersections[intersection1].push_back(street_nb);
      intersections[intersection2].push_back(street_nb);
    }

    sort(intersections, intersections + nb_of_intersections, compare_intersection);
    int nb_of_stations = 0;
    for(int analysis_index = 0; analysis_index < nb_of_intersections; ++analysis_index) {
      list<int> intersection = intersections[analysis_index];
      bool not_to_take = false;
      for(int street : intersection){
        not_to_take = not_to_take || street_secured[street];
      }
      if(!not_to_take) {
        ++nb_of_stations;
        for(int street : intersection) {
          street_secured[street] = true;
        }
      }
      if(are_streets_secured(street_secured, nb_of_streets))
        break;
    }

    if(are_streets_secured(street_secured, nb_of_streets))
      printf("%i\n", nb_of_stations);
    else
      printf("Impossible\n");
  }

  return 0;
}
