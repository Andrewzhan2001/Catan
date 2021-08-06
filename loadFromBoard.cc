#include "loadFromBoard.h"
#include "GameModel.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <utility>

loadFromBoard::loadFromBoard(std::string file) :file{std::move(file)} {}

bool loadFromBoard::loadBoard(GameModel* gm) {
	Board* b = gm->getBoard();
	int tile_resource, tile_value;
	std::ifstream infile(file);
	if (!infile) {
		std::cerr << "Couldn't open input file: " << file << std::endl;
		return false;
	}
	// set players color
	for (auto& i : builders) {
		(gm->getPlayer(i.first))->setColor(i.second);
	}
	std::string line;
	std::getline(infile, line);
	std::istringstream ss{ line };
	// set board
	for (int i = 0; i < 19; i++) {
		ss >> tile_resource >> tile_value;
		auto t = tiles.find(tile_resource);
		std::string resource = t->second;
		b->setTile(i, resource, tile_value);
		if (resource == "PARK") {
			b->setGeeseOnTile(i);
		}
	}
	return true;
}