#ifndef LOADEDDICE
#define LOADEDDICE
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include "Dice.h"
class LoadedDice : public Dice{
 public:
 // if the user input a invalid character(out of range, not an integer)
 //  this function will return -1, otherwise return number between 2 and 12
  int getNum() override;
};
#endif