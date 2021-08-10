#ifndef PLAYER
#define PLAYER
#include <memory>
#include <random>
#include <string>
#include <vector>
#include <iostream>
#include "Board.h"
#include "Dice.h"

class Player {
	int buildpoints; // buildpoints of a player
	std::string color;  // player's color
	std::vector<std::pair<std::string, int>> resources;
	std::vector<int> roads; // store the edges of the roads
	std::vector<std::pair<int, char>> residences; 
	std::string dice;  // type of the dice the player currently uses
	// d[0] represents fair dice, d[1] represents loaded dice
	std::vector<std::unique_ptr<Dice>> d;  
	Dice* getDice();
protected:
	size_t seed = 0;
	std::default_random_engine rng{ seed };
public:
	Player(); // constructor
	virtual ~Player();  // destructor
	// sets dice type to type
	void setDice(std::string type); 
	// rolls current dice the player uses and returns the number
	int rollDice();
	// adds the buildpoints by 1 
	void pointIncrement();
	// returns the number of certain type resources of the player
	int getResources(std::string type);
	// returns the number of total resources of the player
	int getTotal();
	// returns buildpoints of the player
	int getPoints() const;
	// returns color of the player
	std::string getColor() const;
	// sets the seed with given number
	void setseed(size_t seed);
	// set buildpoint
	void setBuildPoints(int point);
	// sets resources of the player
	void setResource(const std::vector<std::pair<std::string, int>>& r);
	// sets color of the player
	void setColor(std::string color);
	// modifies the certain type of resources by given amounts
	// If amount > 0, then awards the player;
	// If amount < 0, then the player uses resourses;
	void modifyResources(std::string type, int amount);
	// adds location x as a basement for the player
	// Note: this method is only used at the beginning of the game
	void addBasement(int x);
	// determines if the player has enough resources to build certain
	//   type of stuff(Basement, House, Tower, Road). If the player
	//   has enough resources, modify resources, roads/residences,
	//   buildpoints accordingly. If the player does not have enough resources,
	//   it returns false.
	// Note: the parameter type must be one of 'R', 'H', 'T', 'R'
	bool attempbuild(int x, char type);
	// loses half of resources randomlY and outputs the message
	void loseHalf();
	// determines whether given Roads or Residences belongs to the player
	bool belongs(int x, char type);
	// prints buildings of the player according to project guidline
	void printBuildings();
	// prints the status of the player according to the project guideline
	void printStatus();
	// upgrade location x to a upper level. If location x has already been a
	//  tower, then do nothing. If player does not have enough resources,
	//  it returns false
	bool upgradeResidence(int x);
	// awards the player and gives the player certain amounts of resources 
	//  based on what location x is 
	void award(int x, std::string type);
	// loses one resoucres randomly, return the resource type lost
	std::string loseOneResourceRandomly();
	// prints data of the player
	void printData(std::ostream& out);
	// determines whether the player has certain type of resource
	bool hasType(std::string type);
	// chooses a vertex to build a basement
	// This method is only called at the beginning of the game
	virtual bool chooseBasement(int& n, Board* board) = 0;
	// chooses a tile number for moving geese
	virtual bool chooseTile(int& n, Board* board) = 0;
	// chooses a color from vector v
	virtual bool chooseColor(std::string& cmd, std::vector<std::string> v) = 0;
	// chooses a road to build
	virtual bool chooseRoadToBuild(Board* board) = 0;
	// chooses a basement to build 
	virtual bool chooseBasementToBuild(Board* board) = 0;
	// chooses a basement to upgrade
	virtual bool chooseBasementToUpgrade(Board* board) = 0;
	// answers yes or no
	virtual bool answer(std::string& cmd) = 0;
	// chooses a color, two types of resources(type 1, type 2)
	// This method is called when exchanging resource with 
	//  another player
	virtual bool chooseToExchange(std::string& col, std::string& type1, 
		                                            std::string& type2) = 0;
	// chooses a kind of command
	virtual bool chooseCommand(std::string& cmd) = 0;
};
#endif
