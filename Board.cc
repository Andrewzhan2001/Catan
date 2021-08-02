#include "Board.h"
#include "Tile.h"
#include <memory>
#include <string>
#include <vector>

int Board::getPlayerNum() { return playerNum; }

int Board::getTileNum() { return tiles.size(); }

int Board::getRoadNum() { return edge.size(); }

void Board::setGeese(int x) { tiles[x]->setGeese(true); }

void Board::setVertex(int idx, std::string builder, std::string residence) {
  vertex[idx] = builder + residence;
}

void Board::setEdge(int idx, std::string builder) { edge[idx] = builder + "R"; }

void Board::setTile(int n, std::string resource, int value) {
  tiles[n]->setResourceValue(resource, value);
}

void Board::setGeeseOnTile(int tilenum) {
  for (auto &&i : tiles) {
    if (i->geese == true) {
      i->setGeese(false);
    }
  }
  tiles[tilenum]->setGeese(true);
}

bool Board::notOccupied(std::string type, int x) {
  bool retval = false;
  std::string original = " ";
  if (x < 10) {
    original = original + std::to_string(x);
  } else {
    original = std::to_string(x);
  }
  if (type == "vertex") {
    // true if vertex x is still its index, not name
    retval = (vertex[x] == original);
  } else if (type == "edge") {
    retval = (edge[x] == original);
  } else {
    std::cerr << "invalid parameter of notOccupied function" << std::endl;
  }
  return retval;
}

std::vector<int> Board::getNeighbours(int x) {
  std::vector<int> n;
  // get all vertex of tile x, find those who have residence on it
  for (auto &i : tiles[x]->getVertex()) {
    if (!notOccupied("vertex", i)) {
      n.push_back(i);
    }
  }
  return n;
}

std::vector<int> Board::findTile(std::string type, int x) {
  std::vector<int> tilen;
  int num = 0;
  for (auto &i : tiles) {
    if (i->has(type, x)) {
      tilen.push_back(num);
    }
    num++;
  }
  return tilen;
}

void Board::create(char color, int x, std::string type) {
  std::string color_str(1, color);
  if (type == "road") {
    edge[x] = color_str + "R";
  } else if (type == "Basement") {
    vertex[x] = color_str + "B";
  }
}

bool Board::canUpgrade(char color, int x) {
  if ((vertex[x][0] == color) && (vertex[x][1] != 'T')) {
    return true;
  }
  return false;
}

void Board::upgradeLevel(char color, int x) {
  if (canUpgrade(color, x)) {
    if (vertex[x][1] == 'B') {
      vertex[x][1] = 'H';
    } else if (vertex[x][1] == 'H') {
      vertex[x][1] = 'T';
    }
  }
}
