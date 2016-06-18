#include <stdio.h>
#include <math.h>

using namespace std;

struct Sphere {
  int x, y, z;
  double r;
};

double dist_to_sphere(struct Sphere, struct Sphere);
int dist_to_box(struct Sphere, int*, int*);

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
    if(corner1[0] > corner2[0]) {int a=corner2[0]; corner2[0]=corner1[0]; corner1[0]=a;}
    if(corner1[1] > corner2[1]) {int a=corner2[1]; corner2[1]=corner1[1]; corner1[1]=a;}
    if(corner1[2] > corner2[2]) {int a=corner2[2]; corner2[2]=corner1[2]; corner1[2]=a;}
    for(int point_nb = 0; point_nb < nb_of_points; ++point_nb) {
      scanf("%i %i %i", &spheres[point_nb].x, &spheres[point_nb].y, &spheres[point_nb].z);
    }

    double max_volume = 0.0;
    for(int possibility = 0; possibility < pow(nb_of_points, nb_of_points); ++possibility) {
      int balloon_order[6] = {-1, -1, -1, -1, -1, -1};
      int possibility_value = possibility;
      for(int balloon_nb = 0; balloon_nb < nb_of_points; ++balloon_nb) {
        balloon_order[balloon_nb] = possibility_value % nb_of_points;
        possibility_value = possibility_value / nb_of_points;
      }
      bool valid_possibility = true;
      for(int balloon_nb = 0; balloon_nb < nb_of_points; ++balloon_nb) {
        for(int other_balloon = 0; other_balloon < balloon_nb; ++other_balloon) {
          if(balloon_order[balloon_nb] == balloon_order[other_balloon])
            valid_possibility = false;
        }
      }

      if(valid_possibility) {
        for(int balloon_index = 0; balloon_index < nb_of_points; ++balloon_index) {
          int balloon_nb = balloon_order[balloon_index];
          double distances[7] = {-3, -3, -3, -3, -3, -3, -3};
          distances[0] = dist_to_box(spheres[balloon_nb], corner1, corner2);
          for(int other_balloon_index = 0; other_balloon_index < balloon_index; ++other_balloon_index) {
            int other_balloon = balloon_order[other_balloon_index];
            distances[other_balloon_index + 1] = dist_to_sphere(spheres[balloon_nb], spheres[other_balloon]);
          }
          bool valid_test = true;
          double min_radius = distances[0];
          for(int other_balloon_index = 0; other_balloon_index < balloon_index; ++other_balloon_index) {
            if(distances[other_balloon_index + 1] < 0) {
              valid_test = false;
              break;
            } else if(distances[other_balloon_index + 1] < min_radius)
              min_radius = distances[other_balloon_index + 1];
          }
          if(valid_test)
            spheres[balloon_nb].r = min_radius;
          else
            spheres[balloon_nb].r = -4;
        }
        double volume = 0;
        for(int balloon_index = 0; balloon_index < nb_of_points; ++balloon_index) {
          int balloon_nb = balloon_order[balloon_index];
          if(spheres[balloon_nb].r >= 0)
            volume += pow(spheres[balloon_nb].r, 3) * M_PI * 4 / 3;
        }
        if(volume > max_volume)
          max_volume = volume;
      }
    }

    double not_occupied_volume = (corner2[0] - corner1[0]) * (corner2[1] - corner1[1]) * (corner2[2] - corner1[2]);
    printf("Box %i: %li\n\n", case_nb++, (long) (not_occupied_volume - max_volume + 0.5));
  }
  return 0;
}

double dist_to_sphere(struct Sphere sphere_from, struct Sphere sphere_to) {
  int dist = 0;
  dist += (sphere_from.x - sphere_to.x) * (sphere_from.x - sphere_to.x);
  dist += (sphere_from.y - sphere_to.y) * (sphere_from.y - sphere_to.y);
  dist += (sphere_from.z - sphere_to.z) * (sphere_from.z - sphere_to.z);
  int radius = sphere_to.r * sphere_to.r;
  if(dist < radius)
    return -1;
  else
    return sqrt(dist - radius);
}

int dist_to_box(struct Sphere sphere, int* corner1, int* corner2) {
  int dist[6];
  dist[0] = sphere.x - corner1[0];
  dist[1] = sphere.y - corner1[1];
  dist[2] = sphere.z - corner1[2];
  dist[3] = corner2[0] - sphere.x;
  dist[4] = corner2[1] - sphere.y;
  dist[5] = corner2[2] - sphere.z;
  int min = 2000000;
  for(int i = 0; i < 6; ++i) {
    if(dist[i] < 0)
      return -2;
    else {
      if(min > dist[i])
        min = dist[i];
    }
  }
  return min;
}
