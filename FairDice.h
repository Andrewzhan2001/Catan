#ifndef FAIRDICE
#define FAIRDICE
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <random>
#include "Dice.h"

class FairDice : public Dice{
  size_t seed = 0;
  std::default_random_engine rng{seed};
  vector<int> numbers = {1,2,3,4,5,6};
 public:
  void setseed(size_t seed) override;
  int getNum() override; // return a random number from 1,2,3,4,5,6
};
#endif