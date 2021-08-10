#ifndef GAMEMODEL
#define GAMEMODEL
#include <string>
#include <vector>
#include "Board.h"
#include "Player.h"

class GameModel {
	int number; // total number of player in the game
	size_t seed = 0; // for random generator
	std::default_random_engine rng{ seed };
	std::vector<std::unique_ptr<Player>> players;
	std::unique_ptr<Board> b;
	// current turn
	// 0 represents Blue, 1 represents Red, 2 represents Yellow,
	// 3 represents Orange
	int currentTurn = 0;
	// the dice number the current player rolls
	int diceNum = 0;
    bool ifStarted = false;
public:
	GameModel(std::string players); // constructor
	// returns the number represents current turn
	int getCurrentTurn() const;
	// rolls dice for the current player and sets diceNum
	void rollDice();
	// sets seed 
	void setSeed(size_t n);
	// gets a pointer of player with index idx
	Player* getPlayer(int idx);
	// gets the color of current player
	std::string getCurColor();
	// gets a pointer of current player
	Player* getCurPlayer();
	// gets a pointer of board
	Board* getBoard() const;
	// gets seed 
	size_t getSeed() const;
	// gets ifStarted
	bool getStarted() const;
	// sets ifStarted fields
	void setStarted(bool start);
	// sets currentTurn with turn 
	void setTurn(int turn);
	// chooses two places for basement for each player
	void initial();
	// switches turn from 1,2,3,4
	void switches();
	// prints information of current player
	void printTurn();
	// prints information of players in the game one by one
	void printPlayers();
	// prints residences of current player
	void printBuildings();
	// builds road for current player
	bool buildRoad();
	// builds basement for current player
	bool buildBasement();
	// upgrades residence for current player
	bool upgrade();
	// after the player rolls dice, updates the resources for each
	//   player according to project guidelines
	void update();
	// exchanges between current player and the player with color type
	//  current player offers one type1 resource and asks for one
	//  type2 resource
	void exchange(std::string type, std::string type1, std::string type2);
	// determines whether the game ends
	bool ifWin();
	// save current game into file
	void saveFile(std::string filename = "backup.sv");
	// print the board to cout
	void printBoard() const;
};
#endif