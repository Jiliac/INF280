#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits>
#include <list>

using namespace std;

struct Point {int x=-1, y=-1, z=-1;};
struct Sphere {struct Point point; double radius = .0;};

void get_volumes(struct Sphere*, double, int, bool*, list<double>*, struct Point, struct Point, int);

int main() {
  int case_nb = 1;
  while(1) {
    int nb_of_points; scanf("%i\n", &nb_of_points);
    if(nb_of_points == 0) break;
    struct Point corner1, corner2;
    scanf("%i %i %i\n%i %i %i\n", &corner1.x, &corner1.y, &corner1.z, &corner2.x, &corner2.y, &corner2.z);
    struct Sphere balloons[6];
    for(int balloon_nb = 0; balloon_nb < nb_of_points; ++balloon_nb)
      scanf("%i %i %i", &balloons[balloon_nb].point.x, &balloons[balloon_nb].point.y, &balloons[balloon_nb].point.z);

    bool visited[6] = {false, false, false, false, false, false};
    list<double> volumes;
    get_volumes(balloons, .0, 0, visited, &volumes, corner1, corner2, nb_of_points);
    volumes.sort();
    double box_volume = abs((corner1.x - corner2.x) * (corner1.y - corner2.y) * (corner1.z - corner2.z));
    printf("Box %i: %i\n\n", case_nb++, (int) round(box_volume - volumes.back()));
  }
  return 0;
}

double dist_to_sphere(struct Point, struct Sphere);
double dist_to_box(struct Point, struct Point, struct Point);
void get_volumes(struct Sphere* balloons, double volume, int step, bool* visited, list<double>* volumes_pt, struct Point corner1, struct Point corner2, int nb_of_points) {
  if(step == nb_of_points) {
    (*volumes_pt).push_back(volume);
    return;
  }
  for(int balloon_nb = 0; balloon_nb < nb_of_points; ++balloon_nb) {
    if(!visited[balloon_nb]) {
      double min_radius = dist_to_box(balloons[balloon_nb].point, corner1, corner2);
      for(int sphere_nb = 0; sphere_nb < nb_of_points; ++sphere_nb) {
        if(visited[sphere_nb]) {
          double dist = dist_to_sphere(balloons[balloon_nb].point, balloons[sphere_nb]);
          if(dist < min_radius)
            min_radius = dist;
        }
      }
      double vol_to_add = 0;
      if(min_radius > 0)
        vol_to_add = 4 * M_PI * pow(min_radius, 3) / 3;
      visited[balloon_nb] = true;
      balloons[balloon_nb].radius = min_radius;
      get_volumes(balloons, volume + vol_to_add, step + 1, visited, volumes_pt, corner1, corner2, nb_of_points); 
      visited[balloon_nb] = false;
    }
  }
}

double dist_to_sphere(struct Point point, struct Sphere sphere) {
  double dist = 0;
  dist += pow(point.x - sphere.point.x,2);
  dist += pow(point.y - sphere.point.y,2);
  dist += pow(point.z - sphere.point.z,2);
  dist = sqrt(dist);
  return dist - sphere.radius;
}

double dist_to_box(struct Point point, struct Point corner1, struct Point corner2) {
  double dist[6];
  dist[0] = abs(point.x - corner1.x);
  dist[1] = abs(point.y - corner1.y);
  dist[2] = abs(point.z - corner1.z);
  dist[3] = abs(point.x - corner2.x);
  dist[4] = abs(point.y - corner2.y);
  dist[5] = abs(point.z - corner2.z);
  double min = numeric_limits<double>::max();
  for(int i=0;i<6;++i)
    if(min > dist[i])
      min = dist[i];
  return min;
}
