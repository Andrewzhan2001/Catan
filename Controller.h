#ifndef CONTROLLER
#define CONTROLLER
#include <memory>
#include <string>

#include "GameModel.h"

class SetBoardStrategy;
class Controller {
	std::unique_ptr<GameModel> gm;
	// current mod of game: computer or human
	std::string playermod;
	size_t seed = 0;
public:
	Controller(const std::string& players); // constructor
	 // sets the seed for random value;
	void setseed(size_t seed);
	// uses strategy sbs to load the board
	bool loadStrategy(SetBoardStrategy* sbs) const;
	// saves files of the current game
	void saveFile(std::string filename = "backup.sv") const;
	// starts the game
	bool play() const;
	// print the board
	void print() const;
};
#endif