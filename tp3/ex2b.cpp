#include <stdio.h>
#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

bool compare_intersections(list<int> inter1, list<int> inter2){ return (inter1.size() > inter2.size());}

int main() {
  while(1) {
    int nb_of_intersections, nb_of_streets;
    cin >> nb_of_intersections;
    if(cin.fail()) break;
    cin >> nb_of_streets;
    list<int> intersections[1000];
    for(int street_nb = 0; street_nb < nb_of_streets; ++street_nb) {
      int inter1, inter2;
      cin >> inter1 >> inter2;
      intersections[inter1 - 1].push_back(street_nb);
      intersections[inter2 - 1].push_back(street_nb);
    }

    bool secured_street[10000];
    int nb_of_stations = 0;
    for(int i=0; i<10000; ++i) {secured_street[i]=false;}
    sort(intersections, intersections + nb_of_intersections, compare_intersections);
    for(int analysis_index = 0; analysis_index < nb_of_intersections; ++ analysis_index) {
      list<int> intersection = intersections[analysis_index];
      bool to_secure = false;
      for(int street : intersection) {to_secure = to_secure || secured_street[street];}
      if(!to_secure) {
        for(int street : intersection) {secured_street[street] = true;}
        ++nb_of_stations;
        bool safer_streets = true;
        for(int i = 0; i < nb_of_streets; ++i) {safer_streets = safer_streets && secured_street[i];}
        if(safer_streets) break;
      }
    }
    bool safer_streets = true;
    for(int i = 0; i < nb_of_streets; ++i) {safer_streets = safer_streets && secured_street[i];}
    if(safer_streets)
      printf("%i\n", nb_of_stations);
    else
      printf("Impossible\n");
  }

  return 0;
}
