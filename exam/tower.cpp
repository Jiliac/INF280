#include <stdio.h>

using namespace std;

struct Car {int floor=-1,pos=-1;};

int main() {
  int nb_of_cases; scanf("%i", &nb_of_cases);
  for(int case_nb = 0; case_nb < nb_of_cases; ++case_nb) {
    int h, l; scanf("%i %i", &h, &l);
    int tower[50][50]; for(int i=0;i<50;++i) {for(int j=0;j<50;++j) {tower[i][j]=-3;}}
    struct Car cars[2500];
    int max_cust = 0;
    for(int floor = 0; floor < h; ++floor) {
      for(int pos = 0; pos < l; ++pos) {
        int cust; scanf("%i", &cust);
        if(cust > max_cust) max_cust = --cust;
        tower[floor][pos] = cust;
        printf("cust : %i\n", cust);
        if(cust >= 0) {
          cars[cust].floor = floor;
          cars[cust].pos = pos;
        }
      }
    }

    int total_time = 0;
    int floor_diff[50]; for(int i=0;i<50;++i) {floor_diff[i]=0;}
    for(int customer = 0; customer < max_cust; ++customer) {
      struct Car car = cars[customer];
      int floor = car.floor;
      int time = 2 * 10 * floor;
      printf("time: %i\n", time);
      int clockwise = 1;
      int diff = (car.pos + floor_diff[floor]) % l;
      if(diff < 0) diff += l;
      int other = (l - car.pos + floor_diff[floor]) % l;
      if(other < 0) other += l;
      printf("diff: %i, other: %i\n", diff, other);
      if(diff > other) {
        clockwise = -1;
        diff = other;
      }
      printf("final diff: %i\n", diff);
      time += diff * 5;
      total_time += time;
      floor_diff[floor] += diff * clockwise;
    }

    printf("%i\n", total_time);
  }

  return 0;
}
