#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits>

using namespace std;

struct Point {int x=-1,y=-1;};

int main() {
  int case_nb = 1;
  while(1) {
    int n, m; scanf("%i %i", &n, &m);
    if(n == 0 && m == 0) break;
    printf("Instance %i:\n", case_nb++);
    struct Point first_poly[10000], second_poly[10000];
    for(int point_nb = 0; point_nb < n; ++point_nb)
      scanf("%i %i", &first_poly[point_nb].x, &first_poly[point_nb].y);
    for(int point_nb = 0; point_nb < m; ++point_nb)
      scanf("%i %i", &second_poly[point_nb].x, &second_poly[point_nb].y);

    double min_theta = numeric_limits<double>::max();
    double max_theta = numeric_limits<double>::min();
    for(int point1_nb = 0; point1_nb < n; ++point1_nb) {
      for(int point2_nb = 0; point2_nb < m; ++point2_nb) {
        struct Point point1 = first_poly[point1_nb];
        struct Point point2 = second_poly[point2_nb];
        int diffX = point1.x - point2.x;
        int diffY = point1.y - point2.y;
        double theta = atan2((double) diffX, (double) diffY);
        if(theta < min_theta) min_theta = theta;
        if(theta > max_theta) max_theta = theta;
      }
    }
    printf("%.3f %.3f\n", min_theta, max_theta);
    double min_slope = tan(min_theta);
    double max_slope = tan(max_theta);
    long long tocompare = (1 << 30);
    if(llabs(max_slope) > tocompare) printf("VERTICAL\n");
    else printf("%.3f\n", max_slope);
    if(llabs(min_slope) > tocompare) printf("VERTICAL\n");
    else printf("%.3f\n", min_slope);
  }

  return 0;
}
