#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
  int nb_of_cases; scanf("%i", &nb_of_cases);
  for(int case_nb = 0; case_nb < nb_of_cases; ++case_nb) {
    int n, l;
    scanf("%i\n%i", &n, &l);
    int items[100000]; for(int i=0;i<100000;++i) {items[i]=-1;}
    for(int item_nb = 0; item_nb < n; ++item_nb) {
      scanf("%i", items + item_nb);
    }
    sort(items, items + n, greater<int>());
    int left = 0, right = n - 1;
    int nb_of_bins = 0;
    while(left <= right) {
      ++nb_of_bins;
      if(l - items[left] >= items[right])
        --right;
      ++left;
    }
    printf("%i\n", nb_of_bins);
    if(case_nb != nb_of_cases -1) printf("\n");
  }

  return 0;
}
