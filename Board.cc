#include "Board.h"
void Board::setGeese(int x) { tiles[x]->setGeese(true); }

bool Board::notOccupied(std::string type, int x) {
  bool retval = false;
  if (type == "vertex") {
      // true if vertex x is still its index, not name 
      retval = (vertex[x] == std::to_string(x));
  } else if (type == "edge") {
      retval = (edge[x] == std::to_string(x));
  } else {
    std::cerr << "invalid parameter of notOccupied function" << std::endl;
  }
  return retval;
}

std::vector<int> Board::getNeighbours(int x) {
  std::vector<int> n;
  // get all vertex of tile x, find those who have residence on it
  for (auto &i : tiles[x]->getVertex()) {
  if(!notOccupied("vertex", i)) {
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

bool Board::canBuild(char color, int x, std::string type) {
  if(!notOccupied(type, x)) { // if this place is occupied by someone
    return false;
  }
  if (type == "road") {
    // find all adjacent vertex 
     std::vector<int> adj;
    for(auto &it : findTile("edge", x)){ // find all tiles that has edge x
    std::vector<int> b = tiles[it]->getAdjacentVertex(x);
    adj.insert(adj.end(), b.begin(), b.end());
    }
    for (auto i : adj) {
      if (!notOccupied("vertex", i)) { // if adjacent vertex is occupied
        return (vertex[i][0] ==
                color); // check if it's owned by the same color user
      }
    }
  } else if (type == "basement") {
    // find all adjacent edges
    std::vector<int> adjE;
    for(auto &it : findTile("vertex", x)){
      std::vector<int> be = tiles[it]->getAdjacentEdge(x);
adjE.insert(adjE.end(), be.begin(), be.end());
    }
    for (auto i : adjE) {
      // if find any one of the adjacent edges is occupied by the same owner
      if (!notOccupied("edge", i) && (edge[i][0] == color)) { 
       return true;
      }
    }
  }
  // if not satisfied any condition
  return true;
}

void Board::create(char color, int x, std::string type) {
  if (type == "road") {
       std::string color_str(1,color);
      edge[x] = color_str;
  } else if (type == "basement") {
     std::string color_str(1,color);
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
    if (vertex[x][1] = 'B') {
      vertex[x][1] = 'H';
    } else if (vertex[x][1] = 'H') {
      vertex[x][1] = 'T';
    }
  }
}

std::vector<std::pair<std::string, int>> Board::getResidences(int x) {
  // find all tiles that has value x
  std::vector<int> tilesV;
  int n = 0;
  for (auto &i : tiles) {
    if (i->getValue() == x) {
      tilesV.push_back(n);
    }
    n++;
  }
  // find all residences of tileV
  std::vector<std::pair<std::string, int>> result;
  for (auto &it : tilesV) {
    for (auto &i : getNeighbours(it)) {
      result.push_back(std::make_pair(tiles[it]->getResource(), i));
    }
  }
  return result;
}
