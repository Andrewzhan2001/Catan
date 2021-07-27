#include "Board.h"

void Board::setGeese(int x) { tiles[x]->setGeese(true); }

std::vector<int> Board::getNeighbours(int x) {
  return tiles[x]->getNeighbours();
}

int Board::findTile(std::string type, int x) {
  int num = 0;
  for (auto &i : tiles) {
    if (i->has(type, x)) {
      return num;
    }
    num++;
  }
  return num;
}

bool Board::canBuild(char color, int x, std::string type) {
  int tileN = findTile(type, x);
  if (type == "road") {
    std::vector<int> residence = tiles[tileN]->getAdjacentVertex(x);
    for (auto i : residence) {
      std::string v = tiles[tileN]->getVertex(i);
      if (!(v == "") ||
          (v[0] = color)) { // adjacent vertex not empty or is occupied by other
        return false;
      }
    }
  } else if (type == "basement") { // vertex is occupied
    if (!tiles[tileN]->notOccupied("vertex", x)) {
      return false;
    }
  }
  return true;
}
