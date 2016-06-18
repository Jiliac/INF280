#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int absolute_to_day(int*);
void day_to_absolute(int, int*);
void print_absolute(int*);
void plus_one_day(int*);
void to_maya_date(string tzolkin, string haab, int * maya_date);
int PERIOD = 18980;

int main() {
  int number_of_case; cin >> number_of_case;
  for (int case_nb = 0; case_nb < number_of_case; ++case_nb) {
    string tzolkin; cin >> tzolkin;
    string haab; cin >> haab;
    int maya_date[4] = {0, 0, 0, 0};
    to_maya_date(tzolkin, haab, maya_date);
    //printf("coef = %i, day = %i -- day = %i, month = %i\n", maya_date[0],maya_date[1],maya_date[2], maya_date[3]);
    int date_to_compare[4] = {9, 20, 3, 3};
    int day = 0;
    bool sol_exist = false;
    while(day < PERIOD) {
      //printf("coef = %i, day = %i -- day = %i, month = %i\n", date_to_compare[0],date_to_compare[1],date_to_compare[2], date_to_compare[3]);
      if(memcmp(maya_date, date_to_compare, sizeof(maya_date)) == 0) {
        sol_exist = true;
        break;
      } else {
        plus_one_day(date_to_compare);
        ++day;
      }
    }

    if (sol_exist) {
      int absolute_day[5] = {0, 0, 0, 0, 0};
      day_to_absolute(day, absolute_day);
      while(absolute_day[0] < 2) {
        print_absolute(absolute_day);
        day += PERIOD;
        day_to_absolute(day, absolute_day);
      }
    } else { printf("NO SOLUTION\n");}

    if(case_nb != number_of_case - 1)
      printf("\n");
  }

  return 0;
}

int absolute_to_day(int * absolute_date) {
  int baktun = absolute_date[0] - 8;
  int katun = absolute_date[1] + 20 * baktun;
  int tun = absolute_date[2] + 20 * katun;
  int winal = absolute_date[3] + 18 * tun;
  int kin = absolute_date[4] + 20 * winal;
  return kin;
}

void day_to_absolute(int kin, int * absolute) {
  absolute[0] = kin / 144000; kin -= 144000 * absolute[0];
  absolute[1] = kin / 7200; kin -= 7200 * absolute[1];
  absolute[2] = kin / 360; kin -= 360 * absolute[2];
  absolute[3] = kin / 20; kin -= 20 * absolute[3];
  absolute[4] = kin;
}

void print_absolute(int * absolute) {
  printf("%i.%i.%i.%i.%i\n", absolute[0] + 8, absolute[1], absolute[2], absolute[3], absolute[4]);
}

void plus_one_day(int * maya_date) {
  if(maya_date[0] < 13)
    ++maya_date[0];
  else
    maya_date[0] = 1;
  if(maya_date[1] < 20)
    ++maya_date[1];
  else
    maya_date[1] = 1;

  if(maya_date[3] < 19) {
    if(maya_date[2] < 20)
      ++maya_date[2];
    else {
      maya_date[2] = 1;
      ++maya_date[3];
    }
  } else {
    if(maya_date[2] < 5)
      ++maya_date[2];
    else {
      maya_date[2] = 1;
      maya_date[3] = 1;
    }
  }
}

void to_maya_date(string tzolkin, string haab, int * maya_date) {
  int point = tzolkin.find('.');
  maya_date[0] = atoi(tzolkin.substr(0, point).c_str());
  string day_name = tzolkin.substr(point + 1);
  point = haab.find('.');
  maya_date[2] = atoi(haab.substr(0, point).c_str());
  string month_name = haab.substr(point + 1);

  if (day_name.compare("Imix") == 0) { maya_date[1] = 1;}
  else if (day_name.compare("Ik") == 0) { maya_date[1] = 2;}
  else if (day_name.compare("Akbal") == 0) { maya_date[1] = 3;}
  else if (day_name.compare("Kan") == 0) { maya_date[1] = 4;}
  else if (day_name.compare("Chikchan") == 0) { maya_date[1] = 5;}
  else if (day_name.compare("Kimi") == 0) { maya_date[1] = 6;}
  else if (day_name.compare("Manik") == 0) { maya_date[1] = 7;}
  else if (day_name.compare("Lamat") == 0) { maya_date[1] = 8;}
  else if (day_name.compare("Muluk") == 0) { maya_date[1] = 9;}
  else if (day_name.compare("Ok") == 0) { maya_date[1] = 10;}
  else if (day_name.compare("Chuen") == 0) { maya_date[1] = 11;}
  else if (day_name.compare("Eb") == 0) { maya_date[1] = 12;}
  else if (day_name.compare("Ben") == 0) { maya_date[1] = 13;}
  else if (day_name.compare("Ix") == 0) { maya_date[1] = 14;}
  else if (day_name.compare("Men") == 0) { maya_date[1] = 15;}
  else if (day_name.compare("Kib") == 0) { maya_date[1] = 16;}
  else if (day_name.compare("Kaban") == 0) { maya_date[1] = 17;}
  else if (day_name.compare("Etznab") == 0) { maya_date[1] = 18;}
  else if (day_name.compare("Kawak") == 0) { maya_date[1] = 19;}
  else if (day_name.compare("Ajaw") == 0) { maya_date[1] = 20;}
  else { maya_date[2] = 0; printf("ERROR\n");}

  if (month_name.compare("Pohp") == 0) { maya_date[3] = 1;printf("TOTO\n");}
  else if (month_name.compare("Wo") == 0) { maya_date[3] = 2;}
  else if (month_name.compare("Sip") == 0) { maya_date[3] = 3;}
  else if (month_name.compare("Zotz") == 0) { maya_date[3] = 4;}
  else if (month_name.compare("Sek") == 0) { maya_date[3] = 5;}
  else if (month_name.compare("Xul") == 0) { maya_date[3] = 6;}
  else if (month_name.compare("Yaxkin") == 0) { maya_date[3] = 7;}
  else if (month_name.compare("Mol") == 0) { maya_date[3] = 8;}
  else if (month_name.compare("Chen") == 0) { maya_date[3] = 9;}
  else if (month_name.compare("Yax") == 0) { maya_date[3] = 10;}
  else if (month_name.compare("Sak") == 0) { maya_date[3] = 11;}
  else if (month_name.compare("Keh") == 0) { maya_date[3] = 12;}
  else if (month_name.compare("Mak") == 0) { maya_date[3] = 13;}
  else if (month_name.compare("Kankin") == 0) { maya_date[3] = 14;}
  else if (month_name.compare("Muan") == 0) { maya_date[3] = 15;}
  else if (month_name.compare("Pax") == 0) { maya_date[3] = 16;}
  else if (month_name.compare("Kayab") == 0) { maya_date[3] = 17;}
  else if (month_name.compare("Kumku") == 0) { maya_date[3] = 18;}
  else if (month_name.compare("Wayeb") == 0) { maya_date[3] = 19;}
  else { maya_date[3] = 0; printf("ERROR\n");}
}
