#ifndef DICEFACTORY
#define DICEFACTORY
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

class Dice;

class DiceFactory{
  
 public:
  std::unique_ptr<Dice> createObject(std::string objectType);
};
#endif