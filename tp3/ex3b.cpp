#include <stdio.h>
#include <vector>
#include <list>

using namespace std;

class Leaf {
  private:
    int tree;
    int last;
  public:
    Leaf(int _tree) {tree = _tree; last = -2;}
    void add(int newLeaf) {
      last = tree;
      tree = newLeaf;
    }
    int getTree() {return tree;}
    int getLast() {return last;}
};

int cycle_search(vector<int>*, int, int);

int main() {
  int nb_of_cases; scanf("%i\n\n", &nb_of_cases);
  for(int case_nb = 0; case_nb < nb_of_cases; ++case_nb) {
    int nb_of_trees, nb_of_paths;
    scanf("%i %i", &nb_of_trees, &nb_of_paths);
    vector<int> trees[500];
    for(int path_nb = 0; path_nb < nb_of_paths; ++path_nb) {
      int tree1, tree2;
      scanf("%i %i", &tree1, &tree2);
      trees[tree1].push_back(tree2);
      trees[tree2].push_back(tree1);
    }

    int min_cycle = 1000;
    for(int tree = 0; tree < nb_of_trees; ++tree) {
      int found_cycle = cycle_search(trees, tree, nb_of_trees);
      if(found_cycle != -1 && found_cycle < min_cycle)
        min_cycle = found_cycle;
    }
    if(min_cycle <= nb_of_trees)
      printf("Case %i: %i\n", case_nb + 1, min_cycle);
    else
      printf("Case %i: impossible\n", case_nb + 1);
  }

  return 0;
}

int cycle_search(vector<int>* trees, int start, int nb_of_trees) {
  list<Leaf> queue;
  int visited[500]; for(int i=0;i<500;++i) {visited[i]=-1;}
  int depth = 0;
  queue.push_back(Leaf(start));
  visited[start] = 0;
  while(!queue.empty() && depth < nb_of_trees){
    Leaf to_analyze = queue.front();
    queue.pop_front();
    depth = visited[to_analyze.getTree()];
    vector<int> nextTrees = trees[to_analyze.getTree()];
    for(int tree : nextTrees) {
      if(tree !=  to_analyze.getLast()) {
        if(visited[tree] == -1) {
          visited[tree] = depth + 1;
          Leaf newLeaf = to_analyze;
          newLeaf.add(tree);
          queue.push_back(newLeaf);
        } else {
          return visited[tree] + visited[to_analyze.getTree()] + 1;
        }
      }
    }
  }
  return -1;
}
