#include <stdio.h>
#include <set>
#include <list>
#include <algorithm>

using namespace std;

void print(set<int>[400], int);
int* explore(set<int>*, int, int, int, int, int*);

int main() {
  int nb_of_cases; scanf("%i", &nb_of_cases);
  for(int case_nb = 0; case_nb < nb_of_cases; ++case_nb) {
    int nb_of_personnes, nb_of_events;
    scanf("%i\n%i", &nb_of_personnes, &nb_of_events);
    set<int> personnes[400];
    for(int personne_nb = 0; personne_nb < nb_of_personnes; ++personne_nb) {
      char events[400]; for(int i=0;i<400;++i) {events[i]='2';}
      scanf("%s", events);
      for(int event_nb = 0; event_nb < nb_of_events; ++event_nb) {
        if(events[event_nb] == '1')
          personnes[personne_nb].insert(event_nb);
      }
    }
    //print(personnes, nb_of_personnes);
    int done[400]; for(int i=1;i<400;++i) {done[i]=-1;} done[0] = 0;
    int * result = explore(personnes, nb_of_personnes, nb_of_events, 0, 0, done);
    int toprint[400]; for(int i=0;i<400;++i) {toprint[i]=-1;}
    for(int event_nb = 0; event_nb < nb_of_events; ++event_nb)
      toprint[result[event_nb]] = event_nb;
    for(int i = 0; i < nb_of_events; ++i)
      printf("%i\n", toprint[i]);
    if(case_nb != nb_of_cases - 1)
      printf("\n");
  }

  return 0;
}

set<int> find_intersection(list<int>*, set<int>*, int*);
int* explore(set<int>* personnes, int nb_of_personnes, int nb_of_events, int last_event, int step_nb, int* done) {
  if(step_nb == nb_of_events - 1)
    return done;

  list<int> present_personnes;
  for(int personne_nb = 0; personne_nb < nb_of_personnes; ++personne_nb) {
    if(personnes[personne_nb].count(last_event) == 1){
      set<int> personne = personnes[personne_nb];
      for(int event : personne) {
        if(done[event] < 0) {
          present_personnes.push_back(personne_nb);
          break;
        }
      }
    }
  }
  if(present_personnes.empty()) {
    for(int event_nb = 0; event_nb < nb_of_events; ++event_nb) {
      if(done[event_nb] < 0) {
        done[event_nb] = step_nb + 1;
        return explore(personnes, nb_of_personnes, nb_of_events, event_nb, step_nb + 1, done);
      }
    }
  }
  set<int> intersection = find_intersection(&present_personnes, personnes, done);
  if(intersection.size() > 0) {
    for(int event_nb : intersection) {
      int newDone[400]; for(int i=0;i<400;++i) {newDone[i]=done[i];}
      newDone[event_nb] = step_nb + 1;
      int* result = explore(personnes, nb_of_personnes, nb_of_events, event_nb, step_nb + 1, newDone);
      if(result[0] != -2)
        return result;
    }
  }
  done[0] = -2;
  return done;
}

bool equal(set<int>::iterator*, int);
set<int> find_intersection(list<int>* present_personnes, set<int>* personnes, int* done) {
  set<int> intersection;
  int size = (*present_personnes).size();
  if(size == 0)
    return intersection;
  set<int>::iterator iterators[400];
  set<int>::iterator min_end = max_element(personnes[(*present_personnes).front()].begin(), personnes[(*present_personnes).front()].end());
  int index = 0;
  for(int personne_nb : *present_personnes) {
    iterators[index] = personnes[personne_nb].begin();
    ++index;
    set<int>::iterator to_compare = max_element(personnes[personne_nb].begin(), personnes[personne_nb].end());
    if(*to_compare < *min_end)
      min_end = to_compare;
  }
  while(1) {
    int min_index = 0;
    if(equal(iterators, size)) {
      if(done[*(iterators[0])] < 0) 
        intersection.insert(*(iterators[0]));
    }
    for(index = 0; index < size; ++index) {
      if(*(iterators[min_index]) > *(iterators[index]))
        min_index = index;
    }
    if(*(iterators[min_index]) == *min_end)
      break;
    else
      ++iterators[min_index];
  }
  return intersection;
}

bool equal(set<int>::iterator* iterators, int size) {
  for(int index = 0; index < size; ++index) {
    if(*(iterators[0]) != *(iterators[index]))
      return false;
  }
  return true;
}

// FOR DEBUG
void print(set<int> personnes[400], int nb_of_personnes) {
  printf("==========\n");
  for(int personne_nb = 0; personne_nb < nb_of_personnes; ++personne_nb) {
    set<int> personne = personnes[personne_nb];
    printf("personne nb %i: ", personne_nb);
    for(set<int>::iterator it = personne.begin(); it != personne.end(); ++it) {
      printf("%i ", *it);
    }
    printf("\n");
  }
  printf("==========\n");
}
