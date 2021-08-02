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
#include <fstream>

class GameModel{
  int number; // total number of players 
  size_t seed = 0; // for random generator
  std::default_random_engine rng{seed};
  std::vector<std::unique_ptr<Player>> players;
  std::unique_ptr<Board> b;
  int currentTurn;
  int diceNum;

  public:
  GameModel(std::string players);
  int getNum();
  int getCurrentTurn();
  void rollDice();
  void setSeed(size_t n);
  Player *getPlayer(int idx);
  std::string getCurColor();
  Player *getCurPlayer();
  Board *getBoard();
  size_t getSeed();
  void setTurn(int turn);
  // constructor
  // each player chooses two places for basement
  void initial(); 
  // switches turn from 1,2,3,4 
  void switches(); 
  // create a residence/road at location x
  void create(int x, std::string type);
  // prints current turn
  void printTurn();
  void printPlayers();
  void printBuildings();
  void buildRoad(int x);
  void buildBasement(int x);
  void upgrade(int x);
  void update();
  void exchange(std::string type, std::string type1, std::string type2);
  bool ifWin();
  // void printData();
  void saveFile(std::string filename = "backup.sv");
  void printBoard();
};
#endif