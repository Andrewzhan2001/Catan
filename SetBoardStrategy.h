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
  std::map<int, std::string> tiles = {{0, "BRICK"}, {1, "ENERGY"}, {2, "GLASS"},
                                      {3, "HEAT"},  {4, "WIFI"},   {5, "PARK"}};
  std::map<int, std::string> builders = {
      {0, "Blue"}, {1, "Red"}, {2, "Orange"}, {3, "Yellow"}};

public:
  virtual void loadBoard(GameModel *gm);
};
#endif