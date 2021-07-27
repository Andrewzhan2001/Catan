#include "Controller.h"
#include <string>
#include "SetBoardStrategy.h"
using namespace std;

void Controller::setseed(size_t seed) {
  this->seed = seed;
  gm->setSeed(seed);
}

void Controller::loadStrategy(SetBoardStrategy sbs) {
  sbs.loadBoard(gm.get());
}

void Controller::play() {
  // at beginning of game, assign each player with two basements
  gm->initial();
  while (!gm->ifWin()) {
    cout << "Builder " << gm->getCurColor() << "'s turn.\n";
    gm->printTurn();
    while (true) {
      std::string cmd;
      cin >> cmd;
      if (cin.eof()) {
        // saving files
        return;
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
        // saving files
        // NEEDS  TO BE MODIFIED
        return;
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
          // saving files
          // NEEDS  TO BE MODIFIED
          return;
        }
        gm->buildRoad(idx);
      } else if (cmd == "build-res") {
        int idx;
        cin >> idx;
        if (cin.eof()) {
          // saving files
          // NEEDS  TO BE MODIFIED
          return;
        }
        gm->buildBasement(idx);
      } else if (cmd == "improve") {
        int idx;
        cin >> idx;
        if (cin.eof()) {
          // saving files
          // NEEDS  TO BE MODIFIED
          return;
        }
        gm->upgrade(idx);
      } else if (cmd == "trade") {
        std::string color;
        std::string give;
        std::string take;
        cin >> color >> give >> take;
        if (cin.eof()) {
          //saving files
          // NEEDS TO BE MODIFIED
        }
        gm->exchange(color, give, take);
      } else if (cmd == "next") {
        gm->switches();
        break;
      } else if (cmd == "save") {
        // save
        // NEEDS TO BE UPDATE
        return;
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
}