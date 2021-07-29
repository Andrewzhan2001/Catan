#ifndef TILE
#define TILE
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include "Board.h"

class Tile {
  int tileNum;
  int resource; 
  int value;
  bool geese; // indicate whether there is a geese on this tile
  std::vector<int> vertex;
  // eg: store vertex which has residence BH as (0, "BH"), "NO" represent no residence
  std::vector<int> edge;  // store the owner of the road on the edge eg: B,R,O,Y
 
  public:
  Tile(int tileNum, int resource, int value);
  int getTileNum();
  int getValue();
  int getResource();
void setGeese(bool has); // set geese true if has is true, otherwise false
// return vertex at index, return the residence if has eg: "BH", 
// otherwise return the vertex number eg:"0"

/* std::string getVertex(int index);  */

 // return edge at index, return the road if has eg: 'B', otherwise return the road number eg:'0'
/* char getEdge(int index); */
// return all the residences index
std::vector<int> getNeighbours(); 
// return all adjacent vertex of edge i
std::vector<int> getAdjacentVertex(int edgeIndex); 
// check whether the tile has type at index
// if type is vertex/edge, check if it has vertex/edge index
// if type is residence, check if it has residence at vertex index
bool has(std::string type, int index);
// check whether vertex/road is occupied by other
bool notOccupied (std::string type, int index); 
/* void buildResidence(std::string residence, int index); // build residence 
void buildRoad(char color, int index);  */




std::vector<std::string> printTile(std::vector<std::string> vertexs, 
                                   std::vector<std::string> edges);

friend Board;
};
#endif
