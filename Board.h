#ifndef BOARD
#define BOARD
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

class Board {
  
 public:
   // set Geese to location x
   void setGeese(int x);
   // determines whether int x represents a valid vertex 
   // A valid vertex must satisfy: 
   //   1. The vertex must be in range
   //   2. The vertex has not been occupied
   // IF INVALID, OUTPUTS "You cannot build here."
   bool validVertex(int x);
   // determines whether player with color can build a basement/road 
   //   at location x.
   // Note: type could only be either "road" or "basement"
   bool canBuild(int color, int x, std::string type);
   // creates a basement/road at location x for player with color
   // Note: type could only be either "road" or "basement"
   void create(int color, int x, std::string type);
   // determines whether player with color can upgrade residence
   //   at location x.
   bool canUpgrade(int color, int x);
   // upgrades the residence at location x for player with color
   // upgrades to house from basement, upgrades to tower from house 
   //   and does nothing if location x is already a tower
   void upgradeLevel(int color, int x);
   // returns a vector of tiles that have a tile value x
   //  Note: this method is useful for getNeighbour, could be private
   std::vector<int> getTile(int x);
   // returns a vector of residences that are adjacent to the tiles
   //  with tile value x, the string type represents the kind of resources
   //  will be awarded for this location
   std::vector<std::pair<std::string, int>> getResidences(int x);
   // gets all neighbours of tile which has tile number x  
   std::vector<int> getNeighbours(int x);
   
};
#endif