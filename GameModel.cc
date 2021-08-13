#include "GameModel.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include "BoardFactory.h"
#include "humanPlayer.h"
#include "PlayerFactory.h"

GameModel::GameModel(std::string player) : number{ 4 }, ifStarted{ false } {
	if (player == "computerAuto") {
		for (int i = 0; i < 4; ++i) {
			players.emplace_back(PlayerFactory::createObject("computerPlayer"));
		}
	}
	else if (player == "computer") {
		players.emplace_back(PlayerFactory::createObject("humanPlayer"));
		for (int i = 1; i < 4; ++i) {
			players.emplace_back(PlayerFactory::createObject("computerPlayer"));
		}
	}
	else {
		for (int i = 0; i < 4; ++i) {
			players.emplace_back(PlayerFactory::createObject("humanPlayer"));
		}
	}
	
	b = BoardFactory::createObject("normalBoard");
}


int GameModel::getCurrentTurn() const { return currentTurn; }

Player* GameModel::getPlayer(int idx) {
	return players[idx].get();
}

Board* GameModel::getBoard() const
{
	return b.get();
}

void GameModel::rollDice() {
	diceNum = getCurPlayer()->rollDice();
	std::cout << "Player rolls number " << diceNum << "." << std::endl;
}

std::string GameModel::getCurColor() {
	return getCurPlayer()->getColor();
}

Player* GameModel::getCurPlayer() {
	return getPlayer(currentTurn);
}

size_t GameModel::getSeed() const { return seed; }

bool GameModel::getStarted() const { return ifStarted; }

void GameModel::setSeed(size_t n) {
	this->seed = n;
	rng = std::default_random_engine{ n };
	for (size_t i = 0; i < players.size(); ++i) {
		players[i]->setseed(n + i);
	}
}

void GameModel::setTurn(int turn) {
	currentTurn = turn;
}

void GameModel::setStarted(bool started) {
	ifStarted = started;
}

int getPlayerNum(std::string type) {
	if (type == "Blue") {
		return 0;
	}
	else if (type == "Red") {
		return 1;
	}
	else if (type == "Orange") {
		return 2;
	}
	else {
		return 3;
	}
}

void GameModel::initial() {
	int i = 0;
	while (i < number) {
		Player* cur = getPlayer(i);
		std::string color = cur->getColor();
		std::cout << "Builder " << color << ", ";
		std::cout << "where do you want to build a basement?" << std::endl;
		int n = -1;
		// reads in an integer as a vertex
		if (!cur->chooseBasement(n, b.get())) {
			return;
		}
		else {
			cur->addBasement(n);
			cur->pointIncrement();
			b->create(cur->getColor()[0], n, "Basement");
		}
		++i;
	}
	int j = 3;
	while (j >= 0) {
		Player* cur = getPlayer(j);
		std::string color = cur->getColor();
		std::cout << "Builder " << color << ", ";
		std::cout << "where do you want to build a basement?" << std::endl;
		int n = -1;
		// reads in an integer as a vertex
		if (!cur->chooseBasement(n, b.get())) {
			return;
		}
		else {
			cur->addBasement(n);
			cur->pointIncrement();
			b->create(cur->getColor()[0], n, "Basement");
		}
		--j;
	}
}

void GameModel::switches() {
	currentTurn++;
	if (currentTurn >= 4) { currentTurn -= 4; }
}

void GameModel::printTurn() {
	Player* cur = getPlayer(currentTurn);
	cur->printStatus();
}

void GameModel::printPlayers() {
	for (auto& p : players) {
		p->printStatus();
	}
}

void GameModel::printBuildings() {
	Player* cur = getPlayer(currentTurn);
	cur->printBuildings();
}

bool GameModel::buildRoad() {
	Player* cur = getPlayer(currentTurn);
	return cur->chooseRoadToBuild(getBoard());
}

bool GameModel::buildBasement() {
	Player* cur = getPlayer(currentTurn);
	return cur->chooseBasementToBuild(getBoard());
}

bool GameModel::upgrade() {
	Player* cur = getCurPlayer();
	return cur->chooseBasementToUpgrade(getBoard());
}

void GameModel::update() {
	Player* cur = getPlayer(currentTurn);
	if (diceNum == 7) {
		for (auto& p : players) {
			if (p->getTotal() >= 10) {
				p->loseHalf();
			}
		}
		std::cout << "Choose where to place the GEESE." << std::endl;
		int n = -1;
		if (!(cur->chooseTile(n, b.get()))) {
			saveFile();
			return;
		}
		else {
			b->setGeeseOnTile(n);
		}
		const std::vector<int> neighbours = b->getNeighbours(n);
		std::vector<std::string> lists;
		for (auto x : neighbours) {
			for (int i = 0; i < number; ++i) {
				if (i == currentTurn) {
					continue;
				}
				if (getPlayer(i)->belongs(x, 'B')) {
					std::string col = getPlayer(i)->getColor();
					auto it = find(lists.begin(), lists.end(), col);
					if (it == lists.end()) {
						if (getPlayer(getPlayerNum(col))->getTotal() > 0) {
							lists.emplace_back(getPlayer(i)->getColor());
						}
					}
				}
			}
		}
		if (lists.empty()) {
			std::cout << "Builder ";
			std::cout << getCurPlayer()->getColor();
			std::cout << " has no builders to steal from." << std::endl;
		}
		else {
			std::cout << "Builder ";
			std::cout << getCurPlayer()->getColor();
			std::cout << " can choose to steal from [";
			for (size_t i = 0; i < lists.size(); ++i) {
				std::cout << lists[i];
				if (i != lists.size() - 1) {
					std::cout << ",";
				}
			}
			std::cout << "]" << std::endl;
			std::cout << "Choose a builder to steal from." << std::endl;
			std::string cmd;
			if (!(cur->chooseColor(cmd, lists))) {
				saveFile();
				return;
			}
			const std::string type = getPlayer(getPlayerNum(cmd))->loseOneResourceRandomly();
			getPlayer(currentTurn)->modifyResources(type, 1);
			std::cout << "Builder ";
			std::cout << getCurPlayer()->getColor();
			std::cout << " steals a ";
			std::cout << type << " from builder ";
			std::cout << cmd << ".";
		}
	}
	else {
		const std::vector<std::pair<std::string, int>> neighbours = b->getResidences(diceNum);
		if (neighbours.size() == 0) {
			std::cout << "No builders gained resources." << std::endl;
			return;
		}
		std::vector<std::vector<int>> original;
		for (size_t i = 0; i < 4; ++i) {
		  std::vector<int> r;
		  r.emplace_back(getPlayer(i)->getResources("BRICK"));
		  r.emplace_back(getPlayer(i)->getResources("ENERGY"));
		  r.emplace_back(getPlayer(i)->getResources("GLASS"));
		  r.emplace_back(getPlayer(i)->getResources("HEAT"));
		  r.emplace_back(getPlayer(i)->getResources("WIFI"));
		  original.emplace_back(r);
		}
		for (auto n : neighbours) {
			for (auto& p : players) {
				if (p->belongs(n.second, 'B')) {
					p->award(n.second, n.first);
				}
			}
		}
		std::vector<std::vector<int>> after;
		for (size_t i = 0; i < 4; ++i) {
			std::vector<int> r;
		    r.emplace_back(getPlayer(i)->getResources("BRICK"));
		    r.emplace_back(getPlayer(i)->getResources("ENERGY"));
		    r.emplace_back(getPlayer(i)->getResources("GLASS"));
		    r.emplace_back(getPlayer(i)->getResources("HEAT"));
		    r.emplace_back(getPlayer(i)->getResources("WIFI"));
		    after.emplace_back(r);
		}
		for (size_t i = 0; i < 4; ++i) {
		  if (after[i][0] == original[i][0] && after[i][1] == original[i][1]
		    && after[i][2] == original[i][2] && after[i][3] == original[i][3]
			&& after[i][4] == original[i][4]) {
				std::cout <<  "Builder " << getPlayer(i)->getColor();
			    std::cout <<  " gained no resources." << std::endl;
			}
	       else {
			   std::cout << "Builder " << getPlayer(i)->getColor();
			   std::cout << " gained: ";
			   for (size_t j = 0; j < 5; ++j) {
				   if (after[i][j] == original[i][j]) {
					   continue;
				   } else {
					   std::cout << (after[i][j] - original[i][j]);
					   std::cout << " ";
					   if (j == 0) {
						   std::cout << "BRICK";
					   } else if (j == 1) {
						   std::cout << "ENERGY";
					   } else if (j == 2) {
						   std::cout << "GLASS";
					   } else if (j == 3) {
						   std::cout << "HEAT";
					   } else if (j == 4) {
						   std::cout << "WIFI";
					   }
					   std::cout << " ";
				   }
				   std::cout << std::endl; 
			   }
		
		   }
		}
	}
}

bool validType(std::string type1) {
	if (type1 != "BRICK" && type1 != "ENERGY" && type1 != "GLASS" &&
		type1 != "HEAT" && type1 != "WIFI") {
		return false;
	}
	else {
		return true;
	}
}

void GameModel::exchange(std::string color, std::string type1, std::string type2) {
	if (color != "Blue" && color != "Red" && color != "Orange" && color != "Yellow") {
		std::cout << "There is no player with color "; 
		std::cout << color << "!" << std::endl;
		return;
	}
	if (color == getCurColor()) {
		std::cout << "You could not trade with yourself!" << std::endl;
		return;
	}
	if (!validType(type1)) {
		std::cout << type1 << " is not a valid resource in this game!" << std::endl;
		return;
	}
	if (!validType(type2)) {
		std::cout << type2 << " is not a valid resource in this game!" << std::endl;
		return;
	}
	std::cout << getCurPlayer()->getColor();
	std::cout << " offers " << color;
	std::cout << " one " << type1 << " for one " << type2 << "." << std::endl;
	std::string cmd;
	if (!getCurPlayer()->hasType(type1)) {
		std::cout << "Don't be greedy! You don't have enough ";
		std::cout << type1 << " for trading! Try using another resources!";
		std::cout << std::endl;
		return;
	}
	if (!getPlayer(getPlayerNum(color))->hasType(type2)) {
		std::cout << "Don't daydream! Player ";
		std::cout << color << " does not have enough ";
		std::cout << type2 << " for trading! Try using another resources!";
		std::cout << std::endl;
		return;
	}
	std::cout << "Does " << color << " accept this offer?" << std::endl;
	if (!(getPlayer(getPlayerNum(color)))->answer(cmd)) {
		saveFile();
		return;
	}
	if (cmd == "yes") {
		getPlayer(currentTurn)->modifyResources(type1, -1);
		getPlayer(currentTurn)->modifyResources(type2, 1);
		getPlayer(getPlayerNum(color))->modifyResources(type1, 1);
		getPlayer(getPlayerNum(color))->modifyResources(type2, -1);
		std::cout << "Trade completes!" << std::endl;
		std::cout << "Player " << getCurPlayer()->getColor();
		std::cout << " gets one " << type2;
		std::cout << " and loses one " << type1 << std::endl;
		std::cout << "Player " << getPlayer(getPlayerNum(color))->getColor();
		std::cout << " gets one " << type1;
		std::cout << " and loses one " << type2 << std::endl;
	}
	else if (cmd == "no") {
		std::cout << "Player " << color << "does not want to trade with you!";
		std::cout << std::endl;
	}
}

bool GameModel::ifWin() {
	for (auto& p : players) {
		if (p->getPoints() >= 10) {
			return true;
		}
	}
	return false;
}

void GameModel::saveFile(std::string filename) {
	std::ofstream fout(filename);
	fout << getPlayerNum(getCurColor()) << std::endl;
	for (auto& p : players) {
		p->printData(fout);
		fout << std::endl;
	}
	b->saveBoard(fout);
	fout << std::endl;
	fout << b->getGeese() << std::endl;
	fout.close();
}

void GameModel::printBoard() const
{
	b->printBoard(std::cout);
}
