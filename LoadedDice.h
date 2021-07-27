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
 // return number between 2 and 12 which reads from input
  int getNum() override;
};
#endif