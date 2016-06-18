#include <stdio.h>
#include <list>
#include <iostream>

using namespace std;

int maxprime = 0;
struct is_not_divisible {
    bool operator() (const int& value) { return (value != maxprime && (value%maxprime) == 0); }
};

int main(){
  int i = 0;
  list<int> primeNumbers;
  for (i = 2; i < 1000000; ++i) {
    primeNumbers.push_back(i);
  }

  list<int>::iterator iterator = primeNumbers.begin();
  while (maxprime < 1000) {
    maxprime = *iterator;
    primeNumbers.remove_if(is_not_divisible());
    ++iterator;
  }

  while(1) {
    start:
    int number;
    cin >> number;
    if (number == 0) {break;}
    else if(number < 4 || number % 2 == 1) {goto start;}

    for (list<int>::iterator it1 = primeNumbers.begin(); it1 != primeNumbers.end(); ++it1){
      for (list<int>::iterator it2 = it1; it2 != primeNumbers.end(); ++it2){
        int test = *it1 + *it2;
        if (test == number) {
          printf("%i = %i + %i\n", number, *it1, *it2);
          goto start;
        }
      }
    }
    printf("Goldbach's conjecture is wrong.");
  }

  return 0;
}
