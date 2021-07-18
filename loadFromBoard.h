#ifndef LOADFROMBOARD
#define LOADFROMBOARD
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "SetBoardStrategy.h"
class Board;
class loadFromBoard : public SetBoardStrategy{

 public:

  void loadBoard(Board *b) override;
};
#endif