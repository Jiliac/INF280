#include <stdio.h>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Leaf {
  private:
    list<int> walk;
    int tree;
  public:
    Leaf(int _tree) {tree = _tree;}
//    ~Leaf() {delete &walk;}
    void add(int newLeaf) {
      walk.push_back(tree);
      tree = newLeaf;
    }
    bool already_seen(int tree){
      list<int>::iterator elt = find(walk.begin(), walk.end(), tree);
      if (tree == walk.back())
        return true;
      else if (elt == walk.end()) 
        return false;
      else
        return true;
    }
    int getTree() {return tree;}
    int getLast() {
      if (!walk.empty()) return walk.back();
      else return -2;
    }
    int getDepth() {return walk.size();}
};

void bsf(int, vector<int>[500], int[500][500][2]);
bool search_cycle(int[500][500][2], int, int);
void print(int[500][500][2], int);

int main() {
  int nb_of_cases;
  scanf("%i[^\n]", &nb_of_cases);
  for(int case_nb = 0; case_nb < nb_of_cases; ++case_nb) {
    printf("Case %i: ", case_nb);
    int nb_of_trees, nb_of_paths;
    scanf("%i %i\n", &nb_of_trees, &nb_of_paths);
    vector<int> paths[20000];
    int graph[500][500][2];
    for(int i=0;i<500;++i) {for(int j=0;j<500;++j) {graph[i][j][0]=-1; graph[i][j][1]=-1;}}
    for(int path_nb = 0; path_nb < nb_of_paths; ++path_nb) {
      int from, to;
      scanf("%i %i", &from, &to);
      paths[from].push_back(to);
      paths[to].push_back(from);
    }

    for(int tree_nb = 0; tree_nb < nb_of_trees; ++tree_nb) {
      bsf(tree_nb, paths, graph);
    }
    int result = 0;
    for(int cycle_length = 3; cycle_length <= nb_of_trees; ++cycle_length) {
      if(search_cycle(graph, nb_of_trees, cycle_length)) {
        result = cycle_length;
        break;
      }
    }
    if(result != 0)
      printf("%i\n", result);
    else
      printf("impossible\n");
    //print(graph, nb_of_trees);
    scanf("[^\n]");
  }
  return 0;
}

void bsf(int start, vector<int> paths[500], int graph[500][500][2]) {
  list<Leaf> queue;
  queue.push_back(Leaf(start));
  while(!queue.empty()) {
    Leaf to_analyze = queue.front();
    queue.pop_front();
    vector<int> tree_paths = paths[to_analyze.getTree()];
    for(int tree : tree_paths) {
      Leaf newLeaf = to_analyze;
      if(tree != to_analyze.getLast() && tree != start) {
        newLeaf.add(tree);
        int depth = newLeaf.getDepth();
        if(graph[start][tree][0] == -1) {
          graph[start][tree][0] = depth;
          queue.push_back(newLeaf);
        } else if (graph[start][tree][0] == depth){
          queue.push_back(newLeaf);
          graph[start][tree][1] = depth;
        } else if(graph[start][tree][1] == -1 && !to_analyze.already_seen(tree)) {
          graph[start][tree][1] = depth;
        }
      }
    }
  }
}

bool search_cycle(int graph[500][500][2], int nb_of_trees, int cycle_length) {
  for(int i = 0; i < nb_of_trees; ++i) {
    for(int j = i + 1; j < nb_of_trees; ++j) {
      if (graph[i][j][0] + graph[i][j][1] == cycle_length && graph[i][j][1] == graph[i][j][0] + (cycle_length%2))
        return true;
    }
  }
  return false;
}

// FOR DEBUG
void print(int graph[500][500][2], int nb_of_trees) {
  printf("==========\n");
  for (int i = 0; i < nb_of_trees; ++i) {
    for(int j = 0; j < nb_of_trees; ++j) {
      printf("%i ", graph[i][j][0]);
    }
    printf("\n");
  }
  printf("==========\n");
  for (int i = 0; i < nb_of_trees; ++i) {
    for(int j = 0; j < nb_of_trees; ++j) {
      printf("%i ", graph[i][j][1]);
    }
    printf("\n");
  }
  printf("==========\n");
}
