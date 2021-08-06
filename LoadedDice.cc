#include <iostream>
#include <random>
#include <algorithm>
#include "LoadedDice.h"
#include "Dice.h"
using namespace std;

LoadedDice::~LoadedDice(){}

int LoadedDice::getNum(){
  while (true) {
    cout << "Input a roll between 2 and 12:" << endl;
    int number;
    cin >> number;
    if (cin.fail()) {
      cin.clear();
      cin.ignore();
      cout << "Invalid roll." << endl;
    } else if (number < 2 || number > 12) {
      cout << "Invalid roll." << endl;
    } else {
      return number;
    }
  }
  
  
  
}