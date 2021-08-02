#include "humanPlayer.h"
#include "Board.h"
#include <algorithm>

bool humanPlayer::chooseVertex(int& n, Board *board) {
  while (true) {
    if (!(std::cin >> n)) {
      if (std::cin.eof()) {
        return false;
      }
      std::cout << "Not an integer!Please input an intger!" << std::endl;
      std::cin.clear();
      std::cin.ignore();
    } else {
      if (!(board->validVertex(n))) {
        std::cout << "You cannot build here. ";
        std::cout << "Please input a valid intger!" << std::endl;
      } else {
        return true;
      }
    }
  }
}


bool humanPlayer::chooseTile(int &n, Board *board) {
  while (true) {
    if (!(std::cin >> n)) {
      if (std::cin.eof()) {
        return false;
      }
      std::cout << "Not an integer!Please input an intger!" << std::endl;
      std::cin.clear();
      std::cin.ignore();
    } else {
      if (n >= board->getTileNum() || n < 0) {
        std::cout << "Invalid tile number!Please input again!" << std::endl;
      } else {
        return true;
      }
    }
  }
}

bool humanPlayer::chooseColor(std::string &color, std::vector<std::string> v) {
  while (true) {
    if (!(std::cin >> color)) {
      if (std::cin.eof()) {
        return false;
      }  
    } else {
      auto it = find(v.begin(), v.end(), color);
      if (it == v.end()) {
        // not found
        std::cout << "You should choose from:";
        std::cout << "[";
        for (unsigned int i = 0; i < v.size(); ++i) {
          std::cout << v[i];
          if (i != v.size() - 1) {
            std::cout << ",";
          }
        }
        std::cout << "]" << std::endl;
        std::cout << "Please input again." << std::endl;
      } else {
        return true;
      }
    }
  }
}

bool humanPlayer::chooseRoad(int &n, Board *board) {
  while (true) {
    if (!(std::cin >> n)) {
      if (std::cin.eof()) {
        return false;
      }
      std::cout << "Not an integer!Please input an intger!" << std::endl;
      std::cin.clear();
      std::cin.ignore();
    } else {
      return true;
    }
  }
}

bool humanPlayer::answer(std::string &cmd) {
  while (true) {
    if (!(std::cin >> cmd)) {
      if (std::cin.eof()) {
        return false;
      }
      std::cout << "Please try again! Please answer yes or no!" << std::endl;
      std::cin.clear();
      std::cin.ignore();
    } else {
      if (cmd != "yes" && cmd != "no") {
        std::cout << "Ahh! The answer must be either yes or no!";
        std::cout << std::endl;
      } else {
        return true;
      }
    }
  }
}

bool humanPlayer::chooseResource(std::string &cmd) {
  while (true) {
    if (!(std::cin >> cmd)) {
      if (std::cin.eof()) {
        return false;
      }
      std::cout << "Please input a kind of resource!" << std::endl;
      std::cin.clear();
      std::cin.ignore();
    } else {
      if (cmd != "BRICK" && cmd != "ENERGY" && cmd != "GLASS" && 
          cmd != "HEAT" && cmd != "WIFI") {
        std::cout << "Your input is not a valid resource! Try again!";
        std::cout << std::endl;
      } else {
        return true;
      }
    }
  }
}

bool humanPlayer::chooseCommand(std::string &cmd) {
  while (true) {
    if (!(std::cin >> cmd)) {
      if (std::cin.eof()) {
        return false;
      }
      std::cout << "Please input a command!" << std::endl;
      std::cin.clear();
      std::cin.ignore();
    } else {
      return true;
    }
  }
}

