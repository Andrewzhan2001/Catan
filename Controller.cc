#include "Controller.h"
#include <string>
#include "SetBoardStrategy.h"
#include <fstream>
using namespace std;

void Controller::setseed(size_t seed) {
  this->seed = seed;
  gm->setSeed(seed);
}

void Controller::loadStrategy(SetBoardStrategy sbs) {
  sbs.loadBoard(gm.get());
}

void Controller::saveFile(std::string fname) {
  ofstream fout(fname);
  gm->saveFile(fout);
  fout.close();
}

bool Controller::play() {
  // at beginning of game, assign each player with two basements
  gm->initial();
  while (!gm->ifWin()) {
    cout << "Builder " << gm->getCurColor() << "'s turn.\n";
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
        cout << "Invalid command.\n";
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
        cout << "Valid commands:\n";
        cout << "board\nstatus\nresidences\n";
        cout << "build-road <edge#>\n";
        cout << "build-res <housing#>\n";
        cout << "improve <housing#>\n";
        cout << "trade <colour> <give> <take>\n";
        cout << "next\nsave <file>\nhelp\n";
      }
    }
  }
  cout << "Would you like to play again?\n";
  std::string cmd;
  cin >> cmd;
  if (cmd == "yes") {
    return true;
  } else if (cmd == "no") {
    return false;
  }
}