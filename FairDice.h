#ifndef PLAYER
#define PLAYER
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include "GameObject.h"

class FairDice : public GameObject{

 public:
  void setseed(size_t seed);
};
#endif