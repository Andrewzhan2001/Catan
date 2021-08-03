#ifndef SETBOARDSTRATEGY
#define SETBOARDSTRATEGY
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
class GameModel;

class SetBoardStrategy {
protected:
  std::map<int, std::string> tiles;
  std::map<int, std::string> builders;
public:
  SetBoardStrategy();
  virtual bool loadBoard(GameModel *gm) = 0;
};
#endif