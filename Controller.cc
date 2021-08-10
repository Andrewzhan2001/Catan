#include "Controller.h"
#include <iostream>
#include <memory>
#include <string>

#include "GameFrame.h"
#include "GameModel.h"
#include "SetBoardStrategy.h"

using namespace std;

Controller::Controller(const string& players) :
	gm{ make_unique<GameModel>(players) }, playermod{ players }{}

void Controller::setseed(const size_t seed) {
	this->seed = seed;
	gm->setSeed(seed);
}

bool Controller::loadStrategy(SetBoardStrategy* sbs) const
{
	return sbs->loadBoard(gm.get());
}

void Controller::saveFile(std::string filename) const
{
	gm->saveFile(filename);
}

bool Controller::play() const
{
	if (!gm->getStarted()) {
	  // at beginning of game, assign each player with two basements
	  gm->initial();
	  GameFrame::printboard(gm.get());
	}
	while (!gm->ifWin()) {
		cout << "Builder " << gm->getCurColor() << "'s turn." << endl;
		gm->printTurn();
		while (true) {
			std::string cmd;
			if (!(gm->getCurPlayer()->chooseCommand(cmd))) {
				saveFile();
				return false;
			}
			else if (cmd == "load" || cmd == "fair") {
				gm->getCurPlayer()->setDice(cmd);
			}
			else if (cmd == "roll") {
				gm->rollDice();
				// This ends the "Beginning of the turn".
				break;
			}
			else {
				cout << "Invalid Command." << endl;
			}
		}
		gm->update();
		while (true) {
			std::string cmd;
			if (!(gm->getCurPlayer()->chooseCommand(cmd))) {
				saveFile();
				return false;
			}
			if (cmd == "board") {
				GameFrame::printboard(gm.get());
			}
			else if (cmd == "status") {
				gm->printPlayers();
			}
			else if (cmd == "residences") {
				gm->printBuildings();
			}
			else if (cmd == "build-road") {
				if (!(gm->buildRoad())) {
					saveFile();
					return false;
				}
			}
			else if (cmd == "build-res") {
				if (!(gm->buildBasement())) {
					saveFile();
					return false;
				}
			}
			else if (cmd == "improve") {
				if (!(gm->upgrade())) {
					saveFile();
					return false;
				}
			}
			else if (cmd == "trade") {
				std::string color;
				std::string give;
				std::string take;
				if (!(gm->getCurPlayer()->chooseToExchange(color, give, take))) {
					saveFile();
					return false;
				}
				gm->exchange(color, give, take);
			}
			else if (cmd == "next") {
				gm->switches();
				break;
			}
			else if (cmd == "save") {
				std::string name;
				cin >> name;
				if (cin.eof()) {
					saveFile();
					return false;
				}
				saveFile(name);
				return false;
			}
			else if (cmd == "help") {
				GameFrame::printhelp();
			}
			else {
				cout << "Invalid Command." << endl;
			}
		}
	}
	cout << gm->getCurColor() << " Win ^:^ !!!" << endl;
	cout << "Would you like to play again? (yes/ other answers will exit)" << endl;
	std::string cmd2;
	// if computer mod, let human choose whether to start again
	if (playermod == "computer") {
		if (!(gm->getPlayer(0)->answer(cmd2))) {
			saveFile();
			return false;
		}
	}
	else {
		if (!(gm->getCurPlayer()->answer(cmd2))) {
			saveFile();
			return false;
		}
	}
	if (cmd2 == "yes") {
		return true;
	}
	else if (cmd2 == "no") {
		return false;
	}
	else {
		return false;
	}
}

void Controller::print() const
{
	GameFrame::printboard(gm.get());
}
