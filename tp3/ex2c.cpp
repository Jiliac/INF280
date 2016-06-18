#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

bool is_categorized(int*, int);
void visit(list<int>*, vector<int>*, int*);
bool impossible_flag = false;

int main() {
  while(1) {
    int nb_of_intersections, nb_of_streets;
    cin >> nb_of_intersections; if(cin.fail()) break;
    cin >> nb_of_streets;
    vector<int> intersections[1000];
    for(int street_nb = 0; street_nb < nb_of_streets; ++street_nb) {
      int inter1, inter2;
      cin >> inter1 >> inter2;
      --inter1; --inter2;
      intersections[inter1].push_back(inter2);
      intersections[inter2].push_back(inter1);
    }

    int category[1000]; for(int i=0; i<1000; ++i) {category[i] = -1;}
    list<int> queue;
    while(!is_categorized(category, nb_of_intersections)) {
      int category_value = -1;
      for(int i = 0; i < 1000; ++i) {
        if(category[i] > category_value) category_value = category[i]; 
        if(category[i] == -1) {
          if(intersections[i].empty()) {category[i] = 2000;}
          else {
            category[i] = category_value + 1;
            queue.push_back(i);
          }
          break;
        }
      }
      visit(&queue, intersections, category);
    }
    int max = 0;
    for(int i=0; i<nb_of_intersections; ++i) {if(category[i]>max) max=category[i];}
    int nb_of_stations = 0;
    for(int value = 0; value < max; value+=2) {
      int nb_cat1 = count(category, category + nb_of_intersections, value);
      int nb_cat2 = count(category, category + nb_of_intersections, value + 1);
      nb_of_stations += (nb_cat1 < nb_cat2) ? nb_cat1 : nb_cat2;
    }
    if(impossible_flag) 
      printf("Impossible\n");
    else
      printf("%i\n", nb_of_stations);
    impossible_flag = false;
  }

  return 0;
}

void visit(list<int>* queue_pointer, vector<int>* intersections, int* category){
  while(!(*queue_pointer).empty()) {
    int intersection_nb = (*queue_pointer).front();
    (*queue_pointer).pop_front();
    int current_category = category[intersection_nb];
    int next_category = (current_category % 2 == 0) ? (current_category + 1) : (current_category - 1);
    vector<int> intersection = intersections[intersection_nb];
    for(int pointed_intersection : intersection) {
      if(category[pointed_intersection] == -1) {
        (*queue_pointer).push_back(pointed_intersection);
        category[pointed_intersection] = next_category;
      } else if(category[pointed_intersection] == current_category) {
        impossible_flag = true;
        break;
      }
    }
  }
}

bool is_categorized(int* category, int nb_of_intersections) {
  for(int i = 0; i < nb_of_intersections; ++i) {
    if(category[i] == -1)
      return false;
  }
  return true;
}
