#ifndef SETBOARDSTRATEGY
#define SETBOARDSTRATEGY
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
class GameModel;

class SetBoardStrategy{

 public:

  virtual void loadBoard(GameModel *gm);
};
#endif