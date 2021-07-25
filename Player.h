#ifndef PLAYER
#define PLAYER
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

class Player {
  int buildpoints;
  std::vector<std::pair<std::string,int>> resources;
  std::vector<int> roads;
  std::vector<std::pair<int, char>> residences;

  public:
    // returns the number of certain resources of the player
    virtual int getResources(std::string type);
    // prints the status of the player according to the project guideline
    virtual void printStatus();
    // modifies the certain type of resources by given amounts
    // If amount > 0, then awards the player;
    // If amount < 0, then the player uses resourses;
    virtual void modifyResources(std::string type, int amount);  
    // returns buildpoints
    virtual int getPoints();
    // determines if the player has enough resources to build certain
    //   type of stuff(basement, house, tower, road). If the player
    //   has enough resources, modify resources, roads/residences, 
    //   buildpoints accordingly. If the player does not have enough resources, ///   it prints out "You do not have enough resources".
    virtual bool attempbuild(int x, std::string type);
    // loses half of resources randomly
    virtual void loseHalf();
    // determines whether given stuff(roads, residences) belongs to the player
    virtual bool belongs(int x, std::string type);

};
#endif