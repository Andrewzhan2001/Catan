#ifndef FAIRDICE
#define FAIRDICE
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include "Dice.h"

class FairDice : public Dice{

 public:
  void setseed(size_t seed) override;
};
#endif