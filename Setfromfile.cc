#include "Setfromfile.h"
#include "GameModel.h"
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <iostream>
#include <utility>

Setfromfile::Setfromfile(std::string file) :file{std::move(file)} {}

bool Setfromfile::loadBoard(GameModel* bm) {
	Board* b = bm->getBoard();
	int CurTurn, numBricks, numEnergies, numGlass, numHeat, numWifi, road,
		residence_idx, tile_resource, tile_value, geeseTile;
	std::string r, residence_type;
	std::ifstream infile(file);
	if (!infile) {
		std::cerr << "Couldn't open input file: " << file << std::endl;
		return false;
	}
	int lineNum = 1;
	std::string line;
	while (std::getline(infile, line)) {
		std::istringstream ss{ line };
		if (lineNum == 1) {
			ss >> CurTurn;
			bm->setTurn(CurTurn);
		}
		else if ((lineNum >= 2) && (lineNum <= 5)) { // builders data
			int builderNum = lineNum - 2;
			Player* builder = bm->getPlayer(builderNum);
			auto it = builders.find(builderNum);
			std::string builderColor = it->second;
			std::string color(1, builderColor[0]);
			// set color
			builder->setColor(builderColor);
			// set player resource
			ss >> numBricks >> numEnergies >> numGlass >> numHeat >> numWifi;
			std::vector<std::pair<std::string, int>> resource{
				{"BRICK", numBricks},
				{"ENERGY", numEnergies},
				{"GLASS", numGlass},
				{"HEAT", numHeat},
				{"WIFI", numWifi} };
			builder->setResource(resource);
			// set roads
			ss >> r; // read "r"
			while (true) {
				ss >> road;
				if (!ss) { // read "h"
					ss.clear();
					ss.ignore();
					break;
				}
				b->setEdge(road, color);
			}
			// set residence
			for (int i = 0; i < 3; i++) {
				ss >> residence_idx >> residence_type;
				b->setVertex(residence_idx, color, residence_type);
			}
		}
		else if (lineNum == 6) { // board
			for (int i = 0; i < 19; i++) {
				ss >> tile_resource >> tile_value;
				auto t = tiles.find(tile_resource);
				std::string resource = t->second;
				b->setTile(i, resource, tile_value);
			}
		}
		else if (lineNum == 7) {
			ss >> geeseTile;
			b->setGeeseOnTile(geeseTile);
		}
		lineNum++;
	}//while
	return true;
}