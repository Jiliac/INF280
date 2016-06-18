#include <stdio.h>
#include <stdlib.h>
#include <limits>
#include <math.h>

using namespace std;

struct Sphere {
  int x, y, z;
  double r;
};

double get_volume(int, bool[6], struct Sphere*, int*, int*, int);

int main() {
  int case_nb = 1;
  while(1) {
    int nb_of_points; scanf("%i\n", &nb_of_points);
    if(nb_of_points == 0) break;
    int corner1[3], corner2[3];
    struct Sphere spheres[6];
    for(int i=0;i<6;++i) {spheres[i].x=-1;spheres[i].y=-1;spheres[i].z=-1;spheres[i].r=-1;}
    scanf("%i %i %i\n", corner1, corner1 + 1, corner1 + 2);
    scanf("%i %i %i\n", corner2, corner2 + 1, corner2 + 2);
    for(int point_nb = 0; point_nb < nb_of_points; ++point_nb) {
      scanf("%i %i %i", &spheres[point_nb].x, &spheres[point_nb].y, &spheres[point_nb].z);
      spheres[point_nb].r = .0;
    }

    bool visited[6] = {false, false, false, false, false, false};
    double volume = get_volume(0, visited, spheres, corner1, corner2, nb_of_points);

    double box_volume = abs((corner2[0] - corner1[0]) * (corner2[1] - corner1[1]) * (corner2[2] - corner1[2]));
    printf("Box %i: %li\n\n", case_nb++, (long) round(box_volume - volume));
  }
  return 0;
}


double dist_to_sphere(struct Sphere, struct Sphere);
double dist_to_box(struct Sphere, int*, int*);
double get_volume(int step, bool visited[6], struct Sphere* spheres, int* corner1, int* corner2, int nb_of_points) {
  double max_volume = 0;
  for(int point_nb = 0; point_nb < nb_of_points; ++point_nb) {
    if(!visited[point_nb]) {
      double min_radius = dist_to_box(spheres[point_nb], corner1, corner2);
      for(int sphere_nb = 0; sphere_nb < nb_of_points; ++sphere_nb) {
        if(visited[sphere_nb]) {
          double dist = dist_to_sphere(spheres[point_nb], spheres[sphere_nb]);
          if(dist < min_radius) min_radius = dist;
        }
      }
        visited[point_nb] = true;
        double volume;
        if(min_radius > 0)
          volume = 4 * M_PI * pow(min_radius, 3) / 3;
        else
          volume = .0;
        spheres[point_nb].r = min_radius;
        volume += get_volume(step + 1, visited, spheres, corner1, corner2, nb_of_points);
        if(volume > max_volume) max_volume = volume;
        visited[point_nb] = false;
    }
  }
  return max_volume;
}

double dist_to_sphere(struct Sphere sphere_from, struct Sphere sphere_to) {
  double dist = 0;
  dist += (sphere_from.x - sphere_to.x) * (sphere_from.x - sphere_to.x);
  dist += (sphere_from.y - sphere_to.y) * (sphere_from.y - sphere_to.y);
  dist += (sphere_from.z - sphere_to.z) * (sphere_from.z - sphere_to.z);
  double radius = sphere_to.r * sphere_to.r;
  if(dist < radius)
    return -1;
  else
    return sqrt(dist - radius);
}

double dist_to_box(struct Sphere sphere, int* corner1, int* corner2) {
  double dist[6];
  dist[0] = abs(sphere.x - corner1[0]);
  dist[1] = abs(sphere.y - corner1[1]);
  dist[2] = abs(sphere.z - corner1[2]);
  dist[3] = abs(corner2[0] - sphere.x);
  dist[4] = abs(corner2[1] - sphere.y);
  dist[5] = abs(corner2[2] - sphere.z);
  double min = numeric_limits<double>::max();
  for(int i = 0; i < 6; ++i) {
    if(min > dist[i])
      min = dist[i];
  }
  return min;
}
