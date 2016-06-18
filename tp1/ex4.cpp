#include <stdio.h>
#include <string>
#include <iostream>
#include <list>

using namespace std;

int result = 0;

string tomorse(char);
string tomorse(string);
list<string> tomorse(list<string>);
void find_phrases(list<string> *, string);

int main(){
  // just save inputs
  int number_of_cases;
  int case_nb;
  cin >> number_of_cases;
  for(case_nb = 0; case_nb < number_of_cases; ++case_nb) {
    result = 0;
    string morse_string;
    int nb_word;
    cin >> morse_string;
    cin >> nb_word;
    list<string> words;
    for(int i = 0; i < nb_word; ++i) {
      string new_word;
      cin >> new_word;
      words.push_back(new_word);
    }

    // start analysing
    list<string> morse_words = tomorse(words);
    find_phrases(&morse_words, morse_string);
    printf("%i\n\n", result);
  }

  return 0;
}

string tomorse(char letter) {
  string result;
  switch(letter) {
    case 'A': result = ".-"; break;
    case 'B': result = "-..."; break;
    case 'C': result = "-.-."; break;
    case 'D': result = "-.."; break;
    case 'E': result = "."; break;
    case 'F': result = "..-."; break;
    case 'G': result = "--."; break;
    case 'H': result = "...."; break;
    case 'I': result = ".."; break;
    case 'J': result = ".---"; break;
    case 'K': result = "-.-"; break;
    case 'L': result = ".-.."; break;
    case 'M': result = "--"; break;
    case 'N': result = "-."; break;
    case 'O': result = "---"; break;
    case 'P': result = ".--."; break;
    case 'Q': result = "--.-"; break;
    case 'R': result = ".-."; break;
    case 'S': result = "..."; break;
    case 'T': result = "-"; break;
    case 'U': result = "..-"; break;
    case 'V': result = "...-"; break;
    case 'W': result = ".--"; break;
    case 'X': result = "-..-"; break;
    case 'Y': result = "-.--"; break;
    case 'Z': result = "--.."; break;
    default: result = "TOTO";
  }
  return result;
}

string tomorse(string word){
  string result = "";
  for(unsigned int i = 0; i < word.size(); ++i) {
    string morse = tomorse(word[i]);
    result += morse;
  }
  return result;
}

list<string> tomorse(list<string> words){
  list<string> morse_words;
  for(list<string>::iterator it = words.begin(); it != words.end(); ++it) {
    string one_morse_word;
    one_morse_word = tomorse(*it);
    morse_words.push_back(one_morse_word);
  }
  return morse_words;
}

void find_phrases(list<string> * morse_words, string analyzed_string) {
  //printf("morse string: %s\n" , analyzed_string.c_str());
  for(list<string>::iterator it = (*morse_words).begin(); it != (*morse_words).end(); ++it) {
    string morse_word = *it;
    if (analyzed_string.compare(0, morse_word.size(), morse_word) == 0) {
      //printf("found word: %s\n", morse_word.c_str());
      string word_to_pass = analyzed_string.substr(morse_word.size());
      if (word_to_pass.size() == 0) {
        ++result;
      } else {
        find_phrases(morse_words, word_to_pass);
      }
    }
  }
} 
