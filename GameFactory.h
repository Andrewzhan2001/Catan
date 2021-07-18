#ifndef GAMEFACTORY
#define GAMEFACTORY
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
class GameObject;

class GameFactory{

 public:
  virtual std::unique_ptr<GameObject> createObject(std::string objectType);
};
#endif