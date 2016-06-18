#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main(){
  int number_of_cases;
  int case_nb;
  cin >> number_of_cases;
  for(case_nb = 0; case_nb < number_of_cases; ++case_nb) {
    // recording inputs
    int amount; cin >> amount;
    int number_of_value; cin >> number_of_value;
    int value_nb;
    int values [5] = {0, 0, 0, 0, 0};
    for (value_nb = 0; value_nb < number_of_value; ++value_nb){
      cin >> values[value_nb];
    }

    // solving problem
    string result = "NO";
    int max_values_use = amount / values[0];
    int values_use[5];
    for (values_use[0] = 0; values_use[0] < max_values_use; ++values_use[0]) {
      for (values_use[1] = 0; values_use[1] <= values_use[0]; ++values_use[1]) {
        for (values_use[2] = 0; values_use[2] <= values_use[1]; ++values_use[2]) {
          for (values_use[3] = 0; values_use[3] <= values_use[2]; ++values_use[3]) {
            for (values_use[4] = 0; values_use[4] <= values_use[3]; ++values_use[4]) {
              int paid = values[0] * values_use[0] +values[1] * values_use[1] + values[2] * values_use[2] +   values[3] * values_use[3] + values[4] * values_use[4];  
              if(paid == amount){result = "YES"; goto end;}                                                 
            }
          }
        }
      }
    }
    end: 
    printf("%s\n\n", result.c_str());
  }
  return 0;
}
