#ifndef BOARDFACTORY
#define BOARDFACTORY
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

class Board;
class BoardFactory{

 public:
  std::unique_ptr<Board> createObject(std::string objectType);
};
#endif