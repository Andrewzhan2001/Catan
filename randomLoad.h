#ifndef RANDOMSET
#define RANDOMSET
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "SetBoardStrategy.h"

class Board;

class randomLoad : public SetBoardStrategy{

 public:

  void loadBoard(Board *b) override;
};
#endif