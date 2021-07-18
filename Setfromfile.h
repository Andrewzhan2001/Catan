#ifndef SETFROMFILE
#define SETFROMFILE
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "SetBoardStrategy.h"

class Board;
class Setfromfile : public SetBoardStrategy {

 public:
  void loadBoard(Board *b) override;
};
#endif