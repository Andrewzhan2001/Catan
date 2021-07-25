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
    // modifies the certain type of resources by given amounts
  // If amount > 0, then awards the player;
  // If amount < 0, then the player uses resourses;
  void modifyResources(std::string type, int amount); 
    // adds location x as a basement for the player
    // Note: this method is only used at the beginning of the game
    void addBasement(int x);
    // returns the number of certain resources of the player
    int getResources(std::string type);
    // returns the number of total resources of the player
    int getTotal();
    // returns buildpoints
    int getPoints();
    // determines if the player has enough resources to build certain
    //   type of stuff(basement, house, tower, road). If the player
    //   has enough resources, modify resources, roads/residences, 
    //   buildpoints accordingly. If the player does not have enough resources,
    //   it prints out "You do not have enough resources".
    bool attempbuild(int x, std::string type);
    // loses half of resources randoml
    // NEEDS TO OUTPUT THE MESSAGE ACCORDING TO ASSIGNMENT RULE
    void loseHalf();
    // determines whether given stuff(roads, residences) belongs to the player
    bool belongs(int x, std::string type);
    // prints buildings of the player according to project guidline
    void printBuildings();
    // prints the status of the player according to the project guideline
    void printStatus();
    // upgrade location x to a upper level. If location x has already been a
    //  tower, then do nothing. If player does not have enough resources,
    //  it prints out "You do not have enough resources".
    bool upgradeResidence(int x);
    // awards the player
    // gives the player certain amounts of resources based on what location
    //  x is
    void award(int x, std::string type);
    // loses one resoucres randomly, see 3.6
    std::string loseOneResourceRandomly();

};
#endif