#include <stdio.h>
#include <vector>
#include <list>

using namespace std;

int bfs(vector<int>*, int);

int main() {
  int nb_of_cases; scanf("%i\n\n", &nb_of_cases);
  for(int case_nb = 0; case_nb < nb_of_cases; ++case_nb) {
    int nb_of_trees, nb_of_paths;
    scanf("%i %i\n", &nb_of_trees, &nb_of_paths);
    vector<int> trees[500];
    for(int path_nb = 0; path_nb < nb_of_paths; ++path_nb) {
      int tree1, tree2;
      scanf("%i %i\n", &tree1, &tree2);
      trees[tree1].push_back(tree2);
      trees[tree2].push_back(tree1);
    }

    int min_cycle = 1000;
    for(int tree_nb = 0; tree_nb < nb_of_trees; ++tree_nb) {
      int found_cycle = bfs(trees, tree_nb);
      if(found_cycle != -1 && found_cycle < min_cycle)
        min_cycle = found_cycle;
    }
    if(min_cycle == 1000)
      printf("Case %i: impossible\n", case_nb);
    else
      printf("Case %i: %i\n", case_nb, min_cycle);
  }

  return 0;
}

int bfs(vector<int>* trees, int start) {
  int visited[500]; for(int i=0;i<500;++i) {visited[i]=-1;}
  list<int> queue, previous;
  queue.push_back(start);
  previous.push_back(-1);
  visited[start] = 0;
  while(!queue.empty()) {
    int tree_nb = queue.front(); queue.pop_front();
    int previous_nb = previous.front(); previous.pop_front();
    vector<int> tree = trees[tree_nb];
    for(int adjacent : tree) {
      if(adjacent != previous_nb) {
        if(visited[adjacent] == -1) {
          queue.push_back(adjacent);
          previous.push_back(tree_nb);
          visited[adjacent] = visited[tree_nb] + 1;
        } else {
          return visited[adjacent] + visited[tree_nb] + 1;
        }
      }
    }
  }
  return -1;
}
