#ifndef PLAYERFACTORY
#define PLAYERFACTORY
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

class Player;
class PlayerFactory{

 public:
  std::unique_ptr<Player> createObject(std::string objectType);
};
#endif