#include <stdio.h>
#include <algorithm>

using namespace std;

float dichotomy(int, int, int*, int, int);

int main() {
  int nb_of_cases; scanf("%i\n", &nb_of_cases);
  for(int case_nb = 0; case_nb < nb_of_cases; ++case_nb) {
    int nb_wifi, nb_houses;
    scanf("%i %i\n", &nb_wifi, &nb_houses);
    int houses[100000]; for(int i=0;i<100000;++i) {houses[i]=-1;}
    for(int house_nb = 0; house_nb < nb_houses; ++house_nb) {
      int house; scanf("%i", &house);
      houses[house_nb] = house;
    }
    sort(houses, houses + nb_houses);
    float result = dichotomy(0, 2*(houses[nb_houses-1] - houses[0] + 1), houses, nb_wifi, nb_houses);
    printf("%.1f\n", result);
  }

  return 0;
}

float dichotomy(int left, int right, int* houses, int nb_wifi, int nb_houses) {
  int middle = (left + right) / 2;
  int from = houses[0];
  int wifi_nb = 1;
  for(int house_nb = 0; house_nb < nb_houses; ++house_nb) {
    if(houses[house_nb] > from + middle) {
      from = houses[house_nb];
      ++wifi_nb;
    }
  }
  if(wifi_nb <= nb_wifi)
    right = middle;
  else
    left = middle + 1;
  if(left < right)
    return dichotomy(left, right, houses, nb_wifi, nb_houses);
  else
    return right/2.;
}
