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
  std::vector<std::string> vertex;
  std::vector<std::string> edge;
  std::vector<std::unique_ptr<Tile>> tiles;
 public:
normalBoard();
bool validVertex(int x) override;
};
#endif
