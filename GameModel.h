#ifndef GAMEMODEL
#define GAMEMODEL
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "Board.h"
#include "Dice.h"
#include "Player.h"

class GameModel{
  int number; // total number of players 
  std::vector<std::unique_ptr<Player>> players;
  std::unique_ptr<Board> b;
  std::unique_ptr<Dice> d;
  int currentTurn;
  int diceNum;
  
  Player *getPlayer(int idx);

  public:
  // constructor
  // each player chooses two places for basement
  void initial(); 
  // switches turn from 1,2,3,4 
  void switches(); 
  // create a residence/road at location x
  void create(int x, std::string type);
  // prints current turn
  void printTurn();
  int rollDice(std::string type);
  void printPlayers();
  void printBuildings();
  void buildRoad(int x);
  void buildBasement(int x);
  void upgrade(int x);
  void update();
  void exchange(int p, std::string type1, std::string type2);
};
#endif