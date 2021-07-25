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
   // determines whether player with color can build a stuff at location x
   virtual bool canbuild(int color, int x, std::string type);
   // creates a basement/road at location x for player with color
   virtual void create(int color, int x, std::string type);
   // upgrades the residence at location x for player with color
   // upgrades to house from basement, upgrades to tower from house 
   //   and does nothing if location x is already a tower
   virtual void upgrade(int color, int x);
   // returns a vector of residences which are adjacent to tile x
   virtual std::vector<int> getNeighbour(int x);

};
#endif