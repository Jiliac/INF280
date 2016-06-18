#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

bool compare(float* i, float* j) { return (i[0] < j[0]);}
float get_volume(float, float*);
float get_volume(float, vector<float*>);

int main() {
  int number_of_cases; cin >> number_of_cases;
  for(int case_nb = 0; case_nb < number_of_cases; ++case_nb) {
    int number_of_cisterns; cin >> number_of_cisterns;
    vector<float*> cisterns;
    vector<float> stops;
    for (int cistern_nb = 0; cistern_nb < number_of_cisterns; ++cistern_nb){
      float base_level; cin >> base_level;
      float height; cin >> height;
      float width; cin >> width;
      float depth; cin >> depth;
      float * cistern = (float *) malloc(4 * sizeof(float));
      cistern[0] = base_level; cistern[1] = height; cistern[2] = width; cistern[3] = depth;
      cisterns.push_back(cistern);
      stops.push_back(base_level);
      stops.push_back(base_level + height);
    }
    float requested_volume; cin >> requested_volume;

    sort(stops.begin(), stops.end());
    float previous_stop = 0.0; float current_stop = 0.0;
    for(vector<float>::iterator it = stops.begin(); it != stops.end(); ++it) {
      current_stop = *it;
      float max_volume = get_volume(current_stop, cisterns);
      if (max_volume > requested_volume)
        break;
      previous_stop = current_stop;
    }
    if(previous_stop == current_stop)
      printf("OVERFLOW\n");
    else {
      float min_vol = get_volume(previous_stop, cisterns);
      float max_vol = get_volume(current_stop, cisterns);
      float augmentation = (max_vol - min_vol) / (current_stop - previous_stop);
      float height = (requested_volume - min_vol) / augmentation;
      float reached_water_height = previous_stop + height;
      printf("%.2f\n", reached_water_height);
    }

    if(case_nb != number_of_cases - 1)
      printf("\n");
  }

  return 0;
}

float get_volume(float water_height, float * cistern) {
  float water_volume;
  float base_area = cistern[2] * cistern[3];
  if(water_height < cistern[0]) {
    water_volume = 0.0;
  } else if (water_height < cistern[0] + cistern[1]) {
    water_volume = base_area * (water_height - cistern[0]);
  } else {
    water_volume = base_area * cistern[1];
  }
  return water_volume;
}

float get_volume(float water_height, vector<float*> cisterns){
  float water_volume = 0;
  for(vector<float*>::iterator it = cisterns.begin(); it != cisterns.end(); ++it) {
    water_volume += get_volume(water_height, (*it));
  }
  return water_volume;
}
