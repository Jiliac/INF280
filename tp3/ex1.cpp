#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

int seek(vector< vector<int> > *, int, int);

int main() {
  int number_of_cases; cin >> number_of_cases;
  for(int case_nb = 0; case_nb < number_of_cases; ++case_nb) {
    int nb_of_camarades; cin >> nb_of_camarades;
    vector<vector<int> > graph;
    graph.reserve(nb_of_camarades);
    for(int cam_nb = 0; cam_nb < nb_of_camarades; ++cam_nb) {
      vector<int> camarade;
      int camarade_index; cin >> camarade_index;
      int nb_of_links; cin >> nb_of_links;
      for(int link = 0; link < nb_of_links; ++link) {
        int cam_link; cin >> cam_link;
        camarade.push_back(cam_link);
      }
      graph[camarade_index] = camarade;
    }
    int seeking_help, savior; cin >> seeking_help; cin >> savior;
    int result = seek(&graph, seeking_help, savior);
    if(result != -1)
      printf("%i %i %i\n", seeking_help, savior, result);
    else
      printf("PROB!!");

    if(case_nb != number_of_cases - 1)
      printf("\n");
  }

  return 0;
}

int seek(vector< vector<int> > * graph_pointer, int seeking_help, int savior) {
  int visited[100000];
  for(int i = 0; i < 100000; ++i) {visited[i] = -1;}
  list<int> queue;
  queue.push_back(seeking_help);

  while(!queue.empty()){
    int v = queue.front();
    queue.pop_front();
    int depth = visited[v];
    if(v == savior)
      return depth;
    vector<int> tovisit = (*graph_pointer)[v];
    for(int adjacent_node : tovisit) {
      if(visited[adjacent_node] == -1 || visited[adjacent_node] > depth) {
        visited[adjacent_node] = depth + 1;
        queue.push_back(adjacent_node);
      }
    }
  }

  return -1;
}
