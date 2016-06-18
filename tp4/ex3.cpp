#include <stdio.h>
#include <algorithm>

using namespace std;

struct Point {int x=-1, y=-1;};
struct Segment {
  struct Point first, second;
  int water = 0;
  int next_segment = -1;
  double slope = .0;
  int output_nb = -1;
};
bool compare_y(struct Segment seg1, struct Segment seg2) {
  int y1 = seg1.first.y, y2 = seg2.first.y;
  if(y1 > seg1.second.y) y1 = seg1.second.y;
  if(y2 > seg2.second.y) y2 = seg2.second.y;
  return (y1 < y2);
}
bool compare(struct Segment seg1, struct Segment seg2) {return (seg1.output_nb < seg2.output_nb);}

void build_tree(struct Segment*, int);
void set_water(struct Segment*, int, int);
void water_fall(struct Segment*, int);

int main() {
  int nb_of_cases; scanf("%i\n\n", &nb_of_cases);
  for(int case_nb = 0; case_nb < nb_of_cases; ++case_nb) {
    int nb_of_segments; scanf("%i\n", &nb_of_segments);
    struct Segment segments[40000];
    int max_X = 0;
    for(int segment_nb = 0; segment_nb < nb_of_segments; ++segment_nb) {
      scanf("%i %i %i %i", &segments[segment_nb].first.x, &segments[segment_nb].first.y, &segments[segment_nb].second.x, &segments[segment_nb].second.y);
      segments[segment_nb].output_nb = segment_nb;
      segments[segment_nb].slope = (segments[segment_nb].first.y - segments[segment_nb].second.y) / ((double) (segments[segment_nb].first.x - segments[segment_nb].second.x));
      if(segments[segment_nb].second.x > max_X) max_X = segments[segment_nb].second.x;
    }

    sort(segments, segments + nb_of_segments, compare_y);
    build_tree(segments, nb_of_segments);
    set_water(segments, max_X, nb_of_segments);
    water_fall(segments, nb_of_segments);
    sort(segments, segments + nb_of_segments, compare);
    for(int segment_nb = 0; segment_nb < nb_of_segments; ++segment_nb)
      printf("%i\n", segments[segment_nb].water);
    if(case_nb != nb_of_cases - 1)
      printf("\n");
  }
  return 0;
}

void water_fall(struct Segment* segments, int nb_of_segments) {
  for(int segment_nb = nb_of_segments-1; segment_nb >= 0; --segment_nb) {
    int next_segment = segments[segment_nb].next_segment;
    if(next_segment != -1)
      segments[next_segment].water += segments[segment_nb].water;
  }
}

struct {int segment_nb = -1; double height = .0;} most_above[1000000];
double get_ordered(int, struct Segment);
void set_water(struct Segment* segments, int max_X, int nb_of_segments) {
  for(int segment_nb = 0; segment_nb < nb_of_segments; ++segment_nb) {
    struct Segment segment = segments[segment_nb];
    for(int x = segment.first.x; x < segment.second.x; ++x) {
      double ordered = get_ordered(x, segment);
      if(most_above[x].segment_nb == -1 || ordered > most_above[x].height) {
        most_above[x].segment_nb = segment_nb;
        most_above[x].height = ordered;
      }
    }
  }
  for(int x = 0; x <= max_X; ++x)
    if(most_above[x].segment_nb != -1)
      segments[most_above[x].segment_nb].water++;
}

bool is_above(struct Point, struct Segment);
bool is_above(int, struct Segment, struct Segment);
void build_tree(struct Segment* segments, int nb_of_segments) {
  for(int segment_nb = 0; segment_nb < nb_of_segments; ++segment_nb) {
    struct Point point;
    if(segments[segment_nb].first.y > segments[segment_nb].second.y)
      point = segments[segment_nb].second;
    else
      point = segments[segment_nb].first;
    for(int other_seg_nb = 0; other_seg_nb < segment_nb; ++other_seg_nb) {
      if(segments[segment_nb].next_segment == -1 && is_above(point, segments[other_seg_nb]))
        segments[segment_nb].next_segment = other_seg_nb;
      else if(segments[segment_nb].next_segment != -1 && is_above(point.x, segments[other_seg_nb], segments[segments[segment_nb].next_segment]))
        segments[segment_nb].next_segment = other_seg_nb;
    }
  }
}

bool is_above(struct Point point, struct Segment segment) {
  if(segment.first.x <= point.x && point.x <= segment.second.x) {
    double ordered = get_ordered(point.x, segment);
    if(ordered < point.y)
      return true;
    else 
      return false;
  } else return false;
}

bool is_above(int x, struct Segment segment1, struct Segment segment2) {
  if(segment1.first.x <= x && x <= segment1.second.x && segment2.first.x <= x && x <= segment2.second.x) {
    double ordered1 = get_ordered(x, segment1);
    double ordered2 = get_ordered(x, segment2);
    if(ordered1 > ordered2)
      return true;
  }
  return false;
}

double get_ordered(int x, struct Segment segment) {
  return segment.first.y + segment.slope * (x - segment.first.x);
}
