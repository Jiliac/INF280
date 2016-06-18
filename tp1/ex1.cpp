#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

float xi[1000], yi[1000];

int main()
{
  while(1) {
    string result = "YES\n";
    int i;
    int nx, ny; float w; 
    cin >> nx;
    cin >> ny;
    cin >> w;
  
    if(nx==0 && ny==0 && w==0) {
      result = "NO\n";
      break;
    }
  
    for (i = 0; i < nx; ++i) {
      cin >> xi[i];
    }
    for (i = 0; i < ny; ++i) {
      cin >> yi[i];
    }
  
    sort(xi, xi + nx);
    sort(yi, yi + ny);
    for (i = 1; i < nx; ++i) {
      if(xi[i] - xi[i - 1] > w){
        result = "NO\n";
      }
    }
    for (i = 1; i < ny; ++i) {
      if(yi[i] - yi[i - 1] > w){
        result = "NO\n";
      }
    }
  
    if (xi[0] > w/2 || yi[0] > w/2 || 75.0 - xi[nx-1] > w/2 || 100.0 - yi[ny-1] > w/2){
      result = "NO\n";
    }
  
    cout << result;
  } 
  return 0;
}
