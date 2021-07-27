#include "Tile.h"
Tile::Tile(int tileNum, int resource, int value) : tileNum{tileNum}, resource{resource}, value{value}, geese{false} {
  if(tileNum == 0) {
    vertex = { {0,""}, {1,""}, {3,""}, {4,""}, {8,""}, {9,""} };
    edge = {{0,'\0'}, {1,'\0'}, {2,'\0'}, {6,'\0'}, {7,'\0'}, {10,'\0'} };
  } else if(tileNum == 1) {
    vertex = { {2,""}, {3,""}, {7,""}, {8,""}, {13,""}, {14,""} };
    edge = {{3,'\0'}, {5,'\0'}, {6,'\0'}, {13,'\0'}, {14,'\0'}, {18,'\0'} };
  } else if(tileNum == 2) {
    vertex = { {4,""}, {5,""}, {9,""}, {10,""}, {15,""}, {16,""} };
    edge = {{0,'\0'}, {1,'\0'}, {2,'\0'}, {6,'\0'}, {7,'\0'}, {10,'\0'} };
  } else if(tileNum == 1) {
    vertex = { {0,""}, {1,""}, {3,""}, {4,""}, {8,""}, {9,""} };
    edge = {{0,'\0'}, {1,'\0'}, {2,'\0'}, {6,'\0'}, {7,'\0'}, {10,'\0'} };
  } else if(tileNum == 1) {
    vertex = { {0,""}, {1,""}, {3,""}, {4,""}, {8,""}, {9,""} };
    edge = {{0,'\0'}, {1,'\0'}, {2,'\0'}, {6,'\0'}, {7,'\0'}, {10,'\0'} };
  } else if(tileNum == 1) {
    vertex = { {0,""}, {1,""}, {3,""}, {4,""}, {8,""}, {9,""} };
    edge = {{0,'\0'}, {1,'\0'}, {2,'\0'}, {6,'\0'}, {7,'\0'}, {10,'\0'} };
  } else if(tileNum == 1) {
    vertex = { {0,""}, {1,""}, {3,""}, {4,""}, {8,""}, {9,""} };
    edge = {{0,'\0'}, {1,'\0'}, {2,'\0'}, {6,'\0'}, {7,'\0'}, {10,'\0'} };
  } else if(tileNum == 1) {
    vertex = { {0,""}, {1,""}, {3,""}, {4,""}, {8,""}, {9,""} };
    edge = {{0,'\0'}, {1,'\0'}, {2,'\0'}, {6,'\0'}, {7,'\0'}, {10,'\0'} };
  } else if(tileNum == 1) {
    vertex = { {0,""}, {1,""}, {3,""}, {4,""}, {8,""}, {9,""} };
    edge = {{0,'\0'}, {1,'\0'}, {2,'\0'}, {6,'\0'}, {7,'\0'}, {10,'\0'} };
  } else if(tileNum == 1) {
    vertex = { {0,""}, {1,""}, {3,""}, {4,""}, {8,""}, {9,""} };
    edge = {{0,'\0'}, {1,'\0'}, {2,'\0'}, {6,'\0'}, {7,'\0'}, {10,'\0'} };
  } else if(tileNum == 1) {
    vertex = { {0,""}, {1,""}, {3,""}, {4,""}, {8,""}, {9,""} };
    edge = {{0,'\0'}, {1,'\0'}, {2,'\0'}, {6,'\0'}, {7,'\0'}, {10,'\0'} };
  } else if(tileNum == 1) {
    vertex = { {0,""}, {1,""}, {3,""}, {4,""}, {8,""}, {9,""} };
    edge = {{0,'\0'}, {1,'\0'}, {2,'\0'}, {6,'\0'}, {7,'\0'}, {10,'\0'} };
  } else if(tileNum == 1) {
    vertex = { {0,""}, {1,""}, {3,""}, {4,""}, {8,""}, {9,""} };
    edge = {{0,'\0'}, {1,'\0'}, {2,'\0'}, {6,'\0'}, {7,'\0'}, {10,'\0'} };
  } else if(tileNum == 1) {
    vertex = { {0,""}, {1,""}, {3,""}, {4,""}, {8,""}, {9,""} };
    edge = {{0,'\0'}, {1,'\0'}, {2,'\0'}, {6,'\0'}, {7,'\0'}, {10,'\0'} };
  } else if(tileNum == 1) {
    vertex = { {0,""}, {1,""}, {3,""}, {4,""}, {8,""}, {9,""} };
    edge = {{0,'\0'}, {1,'\0'}, {2,'\0'}, {6,'\0'}, {7,'\0'}, {10,'\0'} };
  } else if(tileNum == 1) {
    vertex = { {0,""}, {1,""}, {3,""}, {4,""}, {8,""}, {9,""} };
    edge = {{0,'\0'}, {1,'\0'}, {2,'\0'}, {6,'\0'}, {7,'\0'}, {10,'\0'} };
  } else if(tileNum == 1) {
    vertex = { {0,""}, {1,""}, {3,""}, {4,""}, {8,""}, {9,""} };
    edge = {{0,'\0'}, {1,'\0'}, {2,'\0'}, {6,'\0'}, {7,'\0'}, {10,'\0'} };
  } else if(tileNum == 1) {
    vertex = { {0,""}, {1,""}, {3,""}, {4,""}, {8,""}, {9,""} };
    edge = {{0,'\0'}, {1,'\0'}, {2,'\0'}, {6,'\0'}, {7,'\0'}, {10,'\0'} };
  } else if(tileNum == 1) {
    vertex = { {0,""}, {1,""}, {3,""}, {4,""}, {8,""}, {9,""} };
    edge = {{0,'\0'}, {1,'\0'}, {2,'\0'}, {6,'\0'}, {7,'\0'}, {10,'\0'} };
  } else if(tileNum == 1) {
    vertex = { {0,""}, {1,""}, {3,""}, {4,""}, {8,""}, {9,""} };
    edge = {{0,'\0'}, {1,'\0'}, {2,'\0'}, {6,'\0'}, {7,'\0'}, {10,'\0'} };
  }
}

int Tile::getTileNum() {return tileNum;}
  int Tile::getValue(){return value;}
  int Tile::getResource(){return resource;}
void Tile::setGeese(bool has) {geese = has;}

bool Tile::has(std::string type, int index) {
  bool retval;
  if(type == "vertex") {
 retval = (vertex.find(index) != vertex.end());
  } else if(type == "edge") {
retval = (edge.find(index) != edge.end());
  } else {
    std::cout << "wrong use of has function" << std::endl;
  }
  return retval;
}

std::string Tile::getVertex(int index) {
  std::string v = "";
 auto it = vertex.find(index);
  if (it != vertex.end()) { 
    if(it->second != "") {
     v = it.second;
      } else {
        v = std::to_string(it->first);
      }
  }
  return v;
}

char Tile::getEdge(int index) {
  char v;
 auto it = edge.find(index);
  if (it != edge.end()) { 
    if(it->second != '\0') {
     v = i.second;
      } else {
        v = '0'+ it->first;
      }
  }
  return v;
}

bool Tile::notOccupied (std::string type, int index) {
  if(has(type, index)) {
if((type == "vertex") && ((vertex.find(index))->second == "" )) {
    return true;
} else if ((type == "road") && ((edge.find(index))->second == '/0' )) {
    return true;
} else {
    return false;
  }
}
  return false;
}

std::vector<int> Tile::getNeighbours() {
  std::vector<int> neighbours;
for(auto &i: vertex) {
  if(i.second != "") {
neighbours.push_back(i.first);
  }
}
return neighbours;
}

std::vector<int> Tile::getAdjacentVertex(int edgeIndex) {
  std::vector<int> adjacentVertex;
 for(int i = 0; i < edge.size(); i++) {
 if(edgeIndex == edge.begin().first) { 
   if(i == 0) {
adjacentVertex.push_back(vertex.begin().first);
adjacentVertex.push_back(vertex.(begin()+1).first);
   } else if (i == edge.size()) {
     adjacentVertex.push_back(vertex.(begin()+4).first);
adjacentVertex.push_back(vertex.(begin()+6).first);
   } else {
     adjacentVertex.push_back(vertex.(begin()+i-1).first);
adjacentVertex.push_back(vertex.(begin()+i+1).first);
   }
 }
 }
  
}

void Tile::buildResidence(std::string residence, int index){
  for(auto & i: vertex) {
    if(i->first == index) {
      i->second = residence;
    }
  }
}

void Tile::buildRoad(char color, int index) {
  for(auto & i: edge) {
    if(i->first == index) {
      i->second = color;
    }
  }
}
