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
  for (int i = 0; i < 41; i++) {
    temp.push_back("");
    temp[i].assign(60,' ');
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