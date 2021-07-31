#ifndef PLAYER
#define PLAYER
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <vector>

class Player {
  int buildpoints;
  int dicenum;
  std::string color;
  std::vector<std::pair<std::string, int>> resources;
  std::vector<int> roads; // store the edges of the roads
  std::vector<std::pair<int, char>> residences;
  size_t seed = 0;
  std::default_random_engine rng{seed};
public:
  Player();
  // returns the number of certain resources of the player
  int getResources(std::string type);
  // returns the number of total resources of the player
  int getTotal();
  // returns buildpoints
  int getPoints();
   // returns color
  std::string getColor();
int getDiceNum();
void setseed(size_t seed);
void setDiceNum(int dicenum);
void setResource (std::vector<std::pair<std::string, int>> &r);
void setColor(std::string color);
  // modifies the certain type of resources by given amounts
  // If amount > 0, then awards the player;
  // If amount < 0, then the player uses resourses;
  void modifyResources(std::string type, int amount);
  // adds location x as a basement for the player
  // Note: this method is only used at the beginning of the game
  void addBasement(int x);
  // determines if the player has enough resources to build certain
  //   type of stuff(basement, house, tower, road). If the player
  //   has enough resources, modify resources, roads/residences,
  //   buildpoints accordingly. If the player does not have enough resources,
  //   it prints out "You do not have enough resources".
  bool attempbuild(int x, char type);
  // loses half of resources randoml
  // NEEDS TO OUTPUT THE MESSAGE ACCORDING TO ASSIGNMENT RULE
  void loseHalf();
  // determines whether given stuff(roads, residences) belongs to the player
  bool belongs(int x, char type);
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
  // loses one resoucres randomly, return the resource type lost see 3.6
  std::string loseOneResourceRandomly();
  void printData(std::ostream &out);
  virtual void chooseInt(int n);
  virtual ~Player() = 0;
};
#endif
