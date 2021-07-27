#include "normalBoard.h"
#include "Board.h"
using namespace std;

normalBoard::normalBoard() :Board{} {
  for (int i = 0; i < 19; i++) {
    tiles.push_back(std::make_unique<Tile>(i));
  }

  for (int i = 0; i < 53; i++) {
    string space = " ";
    space = space + to_string(i);
    vertex.push_back(space);
    edge.push_back(space);
  }
  
}

bool normalBoard::validVertex(int x) {
  if ((x >= 0) && (x <= 53)) { // the last vertex is 53
    for (auto &it : tiles) {
      if (it->notOccupied("vertex", x)) {
        return true;
      }
    }
  }
  return false;
}

