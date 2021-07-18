#ifndef BOARDFACTORY
#define BOARDFACTORY
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include "GameFactory.h"

class BoardFactory : public GameFactory{

 public:
  std::unique_ptr<GameObject> createObject(std::string objectType) override;
};
#endif