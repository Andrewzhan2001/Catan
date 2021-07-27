#ifndef NORMALBOARD
#define NORMALBOARD
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include "Board.h"

class normalBoard : public Board{

 public:
normalBoard();
bool validVertex(int x) override;
};
#endif
