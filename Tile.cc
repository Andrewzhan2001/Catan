#include "Tile.h"
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

Tile::Tile(int tileNum) : tileNum{tileNum}, resource{""}, value{0}, geese{false} {
  if(tileNum == 0) {
    vertex = {0,1,3,4,8,9}; 
    edge = {0,1,2,6,7,10};
  } else if(tileNum == 1) {
    vertex = {2,3,7,8,13,14};
    edge = {3,5,6,13,14,18};
  } else if(tileNum == 2) {
    vertex = {4,5,9,10,15,16};
    edge = {4,7,8,15,16,19};
  } else if(tileNum == 3) {
    vertex = {6,7,12,13,18,19};
    edge = {9,12,13,20,21,26};
  } else if(tileNum == 4) {
    vertex = {8,9,14,15,20,21};
    edge = {10,14,15,22,23,27};
  } else if(tileNum == 5) {
    vertex = {10,11,16,17,22,23};
    edge = {11,16,17,24,25,28};
  } else if(tileNum == 6) {
    vertex = {13,14,19,20,25,26};
    edge = {18,21,22,30,31,35};
  } else if(tileNum == 7) {
    vertex = {15,16,21,22,27,28};
    edge = {19,23,24,32,33,36};
  } else if(tileNum == 8) {
    vertex = {18,19,24,25,30,31};
    edge = {26,29,30,37,38,43};
  } else if(tileNum == 9) {
    vertex = {20,21,26,27,32,33};
    edge = {27,31,32,39,40,44};
  } else if(tileNum == 10) {
    vertex = {22,23,28,29,34,35};
    edge = {28,33,34,41,42,45};
  } else if(tileNum == 11) {
    vertex = {25,26,31,32,37,38};
    edge = {35,38,39,47,48,52};
  } else if(tileNum == 12) {
    vertex = {27,28,33,34,39,40};
    edge = {36,40,41,49,50,53};
  } else if(tileNum == 13) {
    vertex = {30,31,36,37,42,43};
    edge = {43,46,47,54,55,60};
  } else if(tileNum == 14) {
    vertex = {32,33,38,39,44,45};
    edge = {44,48,49,56,57,61};
  } else if(tileNum == 15) {
    vertex = {34,35,40,41,46,47};
    edge = {45,50,51,58,59,62};
  } else if(tileNum == 16) {
    vertex = {37,38,43,44,48,49};
    edge = {52,55,56,63,64,67};
  } else if(tileNum == 17) {
    vertex = {39,40,45,46,50,51};
    edge = {53,57,58,65,66,68};
  } else if(tileNum == 18) {
    vertex = {44,45,49,50,52,53};
    edge = {61,64,65,69,70,71};
  }
}

int Tile::getTileNum() {return tileNum;}
int Tile::getValue(){return value;}
std::string Tile::getResource(){return resource;}

void Tile::setGeese(bool has) {geese = has;}
void Tile::setResourceValue(std::string r, int v){
  resource = r;
  value = v;
}

bool Tile::has(std::string type, int index) {
  bool retval = false;
  if(type == "vertex") {
    retval = (find(vertex.begin(),vertex.end(),index) != vertex.end());
  } else if(type == "edge") {
    retval = (find(edge.begin(),edge.end(),index) != edge.end());
  } else {
    std::cout << "wrong use of has function" << std::endl;
  }
  return retval;
}

std::vector<int> Tile::getAdjacentVertex(int edgeIndex) {
  std::vector<int> adjacentVertex;
  for (size_t i = 0; i < edge.size(); i++) {
    // find the edge 
    if (edgeIndex == edge[i]) {
      if (i == 0) {
        adjacentVertex.push_back(vertex[0]);
        adjacentVertex.push_back(vertex[1]);
      } else if (i == edge.size()) {
        adjacentVertex.push_back(vertex[4]);
        adjacentVertex.push_back(vertex[6]);
      } else {
        adjacentVertex.push_back(vertex[i - 1]);
        adjacentVertex.push_back(vertex[i + 1]);
      }
    }
  }
  return adjacentVertex;
}

std::vector<int> Tile::getAdjacentEdge(int edgeIndex) {
  std::vector<int> adjacentEdge;
  for (size_t i = 0; i < vertex.size(); i++) {
    // find the vertex 
    if (edgeIndex == vertex[i]) {
      if(i == 0) { // if it's the first vertex
        adjacentEdge.push_back(edge[0]);
        adjacentEdge.push_back(edge[1]);
      } else if(i == 5) {
        adjacentEdge.push_back(edge[5]);
        adjacentEdge.push_back(edge[4]);
      } else {
        adjacentEdge.push_back(edge[i-1]);
        adjacentEdge.push_back(edge[i+1]);
      }
    }
  }
  return adjacentEdge;
}

std::vector<int> Tile::getVertex() {
  std::vector<int> vertices;
  for (auto i : vertex) {
    vertices.push_back(i);
  }
  return vertices;
}

vector<string> Tile::printTile(vector<string> vertexs, vector<string> edges) {
  vector<string> output{"|  |--  --|  |",
                        "  |         | ",
                        "              ",
                        "  |         | ",
                        "|  |      |  |",
                        "  |         | ",
                        "              ",
                        "  |         | ",
                        "|  |--  --|  |",};
  // put tileNum into output
  if (tileNum >= 10) {
    output[2].replace(6,2,to_string(tileNum));
  } else {
    output[2].replace(7,1,to_string(tileNum));
  }
  // put resources into output
  output[3].replace(5,7,resource);

  // put value into output
  if (value != 7) {
    if (value >= 10) {
      output[4].replace(6,2,to_string(value));
    } else {
      output[4].replace(7,1,to_string(value));
    }
  }

  // put geese into output
  if (geese == true) {
    if (value == 7) {
      output[4].replace(5,5, "GEESE");
    } else {
      output[5].replace(5,5, "GEESE");
    }
    
  }
  
  // put vertices into output
  int x = 0, y = 1;
  for (auto &&i : this->vertex) {
    output[x].replace(y,2,vertexs[i],0,2);
    y+=10;
    if (y > 11) {
      x+= 4;
      y = 1;
    }
  }

  // put edges into output
  x = 2;
  y = 1;
  for (int i = 1; i < 5; i++) {
    output[x].replace(y,2,edges[this->edge[i]],0,2);
    y+=10;
    if (y > 11) {
      x+= 4;
      y = 1;
    }
  }
  output[0].replace(6,2,edges[this->edge[0]],0,2);
  output[8].replace(6,2,edges[this->edge[5]],0,2);
  return output;
}
