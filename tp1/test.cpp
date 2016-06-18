#include <stdio.h>
#include <string>

using namespace std;

int main(){
  string test = "tititoto";
  int first = test.find("titi");
  int second = test.find("toto");
  string test2 = test.substr(4);

  printf("first = %i, second = %i\n substr = %s et str = %s\n", first, second, test2.c_str(), test.c_str());

  return 0;
}
