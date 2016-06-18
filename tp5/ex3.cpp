#include <stdio.h>

using namespace std;

int main() {
  int nb_of_cases; scanf("%i", &nb_of_cases);
  for(int case_nb = 0; case_nb < nb_of_cases; ++case_nb) {
    int n, k; scanf("%i %i", &n, &k);
    int remembrance[26]; for(int i=0;i<26;++i) {remembrance[i]=-k-1;}
    char schedule[501]; for(int i=0;i<501;++i) {schedule[i]='\0';}
    scanf("%s", schedule);
    int recognize = 0;
    for(int day = 0; day < n; ++day) {
      if(day - remembrance[schedule[day] - 'A'] <= k)
        ++recognize;
      remembrance[schedule[day] - 'A'] = day;
    }
    printf("Case %i: %i\n", case_nb + 1, recognize);
  }
}
