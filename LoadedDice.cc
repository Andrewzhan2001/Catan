#include <iostream>
#include <random>
#include <algorithm>
#include "LoadedDice.h"
using namespace std;


int LoadedDice::getNum(){
  cout << "Input a roll between 2 and 12:" << endl;
  int number;
  cin >> number;
  if (cin.fail()) {
    cin.clear();
    cin.ignore();
    cout << "Invalid roll." << endl;
    return -1;
  } else if (number < 2 || number > 12) {
    cout << "Invalid roll." << endl;
    return -1;
  } else {
    return number;
  }
  
}