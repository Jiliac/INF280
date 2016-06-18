#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <vector>

using namespace std;

struct Line {int cmd=-1,arg1=-1,arg2=-1;};

long execution(vector<Line>, int);

int main() {
  char commands[5] = {'i', 'j', 'p', 'l', 'd'};
  while(1) {
    string line;
    vector<Line> lines;
    while ( getline(cin, line) && line != "" ) {
      struct Line newLine;
      char first[5]; sscanf(line.c_str(), "%s", first);
      for(int cmd_nb = 0; cmd_nb < 5; ++cmd_nb) {
        if(tolower(first[0]) == commands[cmd_nb]) newLine.cmd = cmd_nb;
      }
      if(newLine.cmd == 0 || newLine.cmd == 1) sscanf(line.c_str(), "%s %i", first, &newLine.arg1);
      else if(newLine.cmd == 3) sscanf(line.c_str(), "%s %i %i", first, &newLine.arg1, &newLine.arg2);
      --newLine.arg1; --newLine.arg2;
      lines.push_back(newLine);
    }
    long result = execution(lines, 0);
    printf("%li\n", result);
    if(cin.eof()) break;
  }

  return 0;
}

long execution(vector<Line> lines, int next_line) {
  long output;
  switch(lines[next_line].cmd) {
    case 0:
      int out1, out2;
      out1 = execution(lines, (next_line + 1) % lines.size());
      out2 = execution(lines, lines[next_line].arg1);
      if(out1 > out2) output = out1;
      else output = out2;
      break;
    case 1:
      output = execution(lines, lines[next_line].arg1);
      break;
    case 2:
      output = execution(lines, (next_line + 1) % lines.size());
      break;
    case 3:
      if(lines[next_line].arg2 > 0) {
        int tmp = lines[next_line].arg2;
        lines[next_line].arg2 = 0;
        output = 0;
        output = execution(lines, lines[next_line].arg1);
        output *= tmp;
        lines[next_line].arg2 = tmp;
        output += execution(lines, (next_line + 1) % lines.size());
      }
      else if(lines[next_line].arg2 == 0) output = 0;
      break;
    case 4:
      output = 0;
      break;
  }
  ++output;
  return output;
}
