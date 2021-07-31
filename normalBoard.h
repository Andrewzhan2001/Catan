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

std::vector<std::string> temp; // just use to temporary store printing staff
void resettemp();// reset to all blank

// put each tile at specific location in temp
void OutputTile(int x, int y, std::vector<std::string> tilegraph);
 public:
normalBoard();
bool validVertex(int x) override;
bool canBuild(char color, int x, std::string type) override;
std::vector<std::pair<std::string, int>> getResidences(int x) override;
void printBoard(std::ostream &out) override;
};
#endif
