#ifndef BOARD
#define BOARD
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

class Tile;
class Board {
 private:
  bool notOccupied(std::string type, int x);
 protected:
  std::vector<std::string> vertex;
  std::vector<std::string> edge;
  std::vector<std::unique_ptr<Tile>> tiles;
 public:
   // set Geese to tile x
   virtual void setGeese(int x);
   // set vertex at index as builder+residence type
   void setVertex(int idx, std::string builder, std::string residence);
   // set vertex at index as builder+"R"
   void setEdge(int idx, std::string builder);
   // set tile x resource and value
   void setTile(int n, std::string resource, int value);
   // determines whether int x represents a valid vertex 
   // A valid vertex must satisfy: 
   //   1. The vertex must be in range
   //   2. The vertex has not been occupied
   // IF INVALID, OUTPUTS "You cannot build here."
   virtual bool validVertex(int x);
   // gets all residence of tile x  
   virtual std::vector<int> getNeighbours(int x);
   // find all the tiles that has vertex/edge i 
   std::vector<int> findTile(std::string type, int x);
   // determines whether player with color can build a basement/road 
   //   at location x.
   // Note: type could only be either "road" or "basement"
   virtual bool canBuild(char color, int x, std::string type) = 0;
   // creates a basement/road at location x for player with color
   // Note: type could only be either "road" or "basement"
   virtual void create(char color, int x, std::string type);
   // determines whether player with color can upgrade residence
   //   at location x.
   virtual bool canUpgrade(char color, int x) = 0;
   // upgrades the residence at location x for player with color
   // upgrades to house from basement, upgrades to tower from house 
   //   and does nothing if location x is already a tower
   virtual void upgradeLevel(char color, int x);
   // returns a vector of residences that are adjacent to the tiles
   //  with tile value x, the string type represents the kind of resources
   //  will be awarded for this location
   virtual std::vector<std::pair<std::string, int>> getResidences(int x) = 0;

   virtual void printBoard(std::ostream &out) = 0;
   virtual ~Board() = 0;
};
#endif