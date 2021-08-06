#include "randomLoad.h"
#include "GameModel.h"
#include <string>
#include <random>
#include <algorithm>

bool randomLoad::loadBoard(GameModel* gm) {
	Board* b = gm->getBoard();
	std::default_random_engine rng{ gm->getSeed() };
	// set players color
	for (const auto& i : builders) {
		(gm->getPlayer(i.first))->setColor(i.second);
	}
	// set board
	/*the board consists of the
  following resources: 3 WIFI, 3 HEAT, 4 BRICK, 4 ENERGY, 4 GLASS, and 1 PARK.
  The values on the board will have one tile with value 2, one tile with the value
  12, one tile with the value 7 (the Park), and two tiles each for the values: 3,
  4, 5, 6, 8, 9, 10, and 11.
  */
	std::vector<std::string> resources = {
		"WIFI",  "WIFI",  "WIFI",  "HEAT",   "HEAT",   "HEAT",   "BRICK",
		"BRICK", "BRICK", "BRICK", "ENERGY", "ENERGY", "ENERGY", "ENERGY",
		"GLASS", "GLASS", "GLASS", "GLASS",  "PARK" };
	std::vector<int> values = { 2, 12, 3, 3, 4, 4,  5,  5,  6,
							   6, 8,  8, 9, 9, 10, 10, 11, 11 };
	std::shuffle(resources.begin(), resources.end(), rng);
	std::shuffle(values.begin(), values.end(), rng);
	// find park tile and set to value 7;
	auto it = find(resources.begin(), resources.end(), "PARK");
	const int index = it - resources.begin();
	b->setTile(index, *it, 7);
	b->setGeeseOnTile(index);
	// remove park from resources since already set
	/* resources.erase(resources.begin() + index); */
	// set the other 18 tiles
	for (int i = 0, k = 0; i < 19; i++, k++) {
		if (i != index) {
			b->setTile(i, resources[i], values[k]);
		}
		else {
			k--;
		}
	}
	return true;
}