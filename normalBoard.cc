#include "normalBoard.h"
#include "Board.h"
#include "Tile.h"
using namespace std;

normalBoard::normalBoard() : Board{} {
  for (int i = 0; i < 53; i++) {
    string space = " ";
    space = space + to_string(i);
    vertex.push_back(space);
    edge.push_back(space);
  }
  for (int i = 0; i < 41; i++) {
    temp.push_back("");
    temp[i].assign(60,' ');
  }
  

}

bool normalBoard::validVertex(int x) {
  if ((x >= 0) && (x <= 53)) { // the last vertex is 53
      if (notOccupied("vertex", x)) {
        return true;
    }
  }
  return false;
}

bool normalBoard::canBuild(char color, int x, std::string type) {
  if (!notOccupied(type, x)) { // if this place is occupied by someone
    return false;
  }
  if (type == "road") {
    // find all adjacent vertex
    std::vector<int> adj;
    for (auto &it : findTile("edge", x)) { // find all tiles that has edge x
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
    for (auto &it : findTile("vertex", x)) {
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

std::vector<std::pair<std::string, int>> normalBoard::getResidences(int x) {
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

void normalBoard::resettemp() {
  for (int i = 0; i < 41; i++) {
    temp[i].assign(60,' ');
  }
}


void normalBoard::OutputTile(int x, int y, vector<string> tilegraph) {
  for (auto &&i : tilegraph) {
    temp[x].replace(y,i.length(),i);
    ++x;
  }
  
}

void normalBoard::printBoard(std::ostream &out) {
  int x = 0;
  int y = 26;
  for (auto &&i : tiles) {
    vector<string> tilegraph = i.get()->printTile(vertex,edge);
    OutputTile(x,y,tilegraph);
    if (x == 0 && y == 26) {
      x = 4;
      y = 16;
    } else if (x == 28 && y == 36){
      x += 4;
      y = 26;
    } else if (y == 36){
      x += 4;
      y = 6;
    } else if (y == 46) {
      x += 4;
      y = 16;
    } else {
      y += 20;
    }
  }
  for (auto &&i : temp)
  {
    out << i << endl;
  }
}
