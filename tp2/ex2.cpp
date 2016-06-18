#include <stdio.h>
#include <iostream>

bool findaleaf(int * newleaf, int number_of_tasks);
bool findamother(int * mother, int leaf, int number_of_tasks);
void print_rules(int rules[100][100], int number_of_tasks);
int rules[100][100];
bool done[100];

using namespace std;

int main() {
  // record input
  int number_of_case; cin >> number_of_case;
  for(int case_nb = 0; case_nb < number_of_case; ++case_nb) {
    int number_of_tasks; cin >> number_of_tasks;
    int number_of_rules; cin >> number_of_rules;
    for(int i = 0; i < 100; ++i) {
      for(int j = 0; j < 100; ++j) {
        rules[i][j] = 0;
      }
      done[i] = false;
    }
    for(int rules_nb = 0; rules_nb < number_of_rules; ++rules_nb) {
      int target; cin >> target; --target;
      int k; cin >> k;
      for(int kk = 0; kk < k; ++kk){
        int dependency; cin >> dependency; --dependency;
        rules[target][dependency] = 1;
      }
    }
    //printf("number_of_case = %i -- number_of_rules = %i -- number_of_tasks = %i\n", number_of_case, number_of_rules,number_of_tasks);
    //print_rules(rules, number_of_tasks);

    // analyze
    int leaf;
    int mother;
    int leafnb = 0;
    while(findaleaf(&leaf, number_of_tasks)){
      while(findamother(&mother, leaf, number_of_tasks)) {
        rules[mother][leaf] = 0;
      }
      printf("%i", leaf + 1);
      if((++leafnb) != number_of_tasks)
        printf(" ");
      else
        printf("\n");
    }

    if (case_nb != number_of_case - 1)
      printf("\n");
  }

  return 0;
}

bool findaleaf(int * newleaf, int number_of_tasks) {
  int leaf = -1;
  for(int node = 0; node < number_of_tasks; ++node) {
    bool hasDependency = false;
    for(int dependency = 0; dependency < number_of_tasks; ++dependency) {
      if(rules[node][dependency] == 1){
        hasDependency = true;
        break;
      }
    }
    if(!hasDependency) {
      if(!done[node]){
        leaf = node;
        done[leaf] = true;
        break;
      }
    }
  }

  if(leaf == -1)
    return false;
  else {
    *newleaf = leaf;
    return true;
  }
}

bool findamother(int * mother, int leaf, int number_of_tasks) {
  bool found = false;
  for(int node = 0; node < number_of_tasks; ++node) {
    if(rules[node][leaf] == 1) {
      found = true;
      *mother = node;
      break;
    }
  }
  return found;
}

void print_rules(int rules[100][100], int number_of_tasks) {
  printf("=========\n");
  for (int i = 0; i < number_of_tasks; ++i) {
    for (int j = 0; j < number_of_tasks; ++j) {
      printf("%i ", rules[i][j]);
    }
    printf("\n");
  }
  printf("=========\n");
}
