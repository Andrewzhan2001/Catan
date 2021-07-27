#include "normalBoard"
#include "Board.h"

normalBoard::normalBoard() {
  for (int i = 0; i < 19; i++) {
    tiles.push_back(std::make_unique<Tile>(i));
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

