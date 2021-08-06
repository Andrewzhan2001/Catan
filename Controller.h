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
	Controller(const std::string& players);
	void setseed(size_t seed); // set the seed for random value;
	bool loadStrategy(SetBoardStrategy* sbs) const; // use strategy sbs to load the board
	void saveFile(std::string filename = "backup.sv") const;
	bool play() const;// start the game

	// for debug
	void print() const;
};
#endif