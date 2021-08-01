#include <string>
#include <fstream>
#include <memory>
#include "SetBoardStrategy.h"
#include "Controller.h"
#include "GameModel.h"

using namespace std;

Controller::Controller():gm{make_unique<GameModel>()}{}

void Controller::setseed(size_t seed) {
  this->seed = seed;
  gm->setSeed(seed);
}

void Controller::loadStrategy(SetBoardStrategy sbs) {
  sbs.loadBoard(gm.get());
}

void Controller::saveFile(std::string fname) {
  gm->saveFile(fname);
}

bool Controller::play() {
  // at beginning of game, assign each player with two basements
  gm->initial();
  while (!gm->ifWin()) {
    cout << "Builder " << gm->getCurColor() << "'s turn." << endl;
    gm->printTurn();
    while (true) {
      std::string cmd;
      cin >> cmd;
      if (cin.eof()) {
        saveFile();
        return false;
      } else if (cmd == "load" || cmd == "fair") {
        gm->setDice(cmd);
      } else if (cmd == "roll") {
        gm->rollDice();
        // This ends the "Beginning of the turn".
        break;
      } else {
        cout << "Invalid command." << endl;
      }
    }
    while (true) {
      std::string cmd;
      cin >> cmd;
      if (cin.eof()) {
        saveFile();
        return false;
      }
      if (cmd == "board") {
        // print board
        // NEEDS TO BE MODIFIED
        cout << "board\n";
      } else if (cmd == "status") {
        gm->printPlayers();
      } else if (cmd == "residences") {
        gm->printBuildings();
      } else if (cmd == "build-road") {
        int idx;
        cin >> idx;
        if (cin.eof()) {
          saveFile();
          return false;
        }
        gm->buildRoad(idx);
      } else if (cmd == "build-res") {
        int idx;
        cin >> idx;
        if (cin.eof()) {
          saveFile();
          return false;
        }
        gm->buildBasement(idx);
      } else if (cmd == "improve") {
        int idx;
        cin >> idx;
        if (cin.eof()) {
          saveFile();
          return false;
        }
        gm->upgrade(idx);
      } else if (cmd == "trade") {
        std::string color;
        std::string give;
        std::string take;
        cin >> color >> give >> take;
        if (cin.eof()) {
          saveFile();
          return false;
        }
        gm->exchange(color, give, take);
      } else if (cmd == "next") {
        gm->switches();
        break;
      } else if (cmd == "save") {
        std::string name;
        cin >> name;
        if (cin.eof()) {
          saveFile();
          return false;
        }
        saveFile(name);
        return false;
      } else if (cmd == "help") {
        cout << "Valid commands:" << endl;
        cout << "board" << endl;
        cout << "status" << endl;
        cout << "residences" << endl;
        cout << "build-road <edge#>" << endl;
        cout << "build-res <housing#>" << endl;
        cout << "improve <housing#>" << endl;
        cout << "trade <colour> <give> <take>" << endl;
        cout << "next" << endl;
        cout << "save <file>" << endl;
        cout << "help" << endl;
      }
    }
  }
  cout << "Would you like to play again?" << endl;
  std::string cmd;
  cin >> cmd;
  if (cmd == "yes") {
    return true;
  } else if (cmd == "no") {
    return false;
  } else {
    return false;
  }
}