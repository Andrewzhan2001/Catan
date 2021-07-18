#ifndef SETBOARDSTRATEGY
#define SETBOARDSTRATEGY
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
class Board;

class SetBoardStrategy{

 public:

  virtual void loadBoard(Board *b);
};
#endif