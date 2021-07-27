#include <iostream>
#include <random>
#include <algorithm>
#include "FairDice.h"
using namespace std;

void FairDice::setseed(size_t seed) {
  this->seed = seed;
  this->rng = default_random_engine{seed};
}

int FairDice::getNum(){
  shuffle(numbers.begin(), numbers.end(), rng);
  return numbers[0];
}