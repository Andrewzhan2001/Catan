#ifndef DICE
#define DICE
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

class Dice {
 public:
  virtual ~Dice();
  virtual void setseed(size_t seed);
  virtual int getNum() = 0;
};
#endif