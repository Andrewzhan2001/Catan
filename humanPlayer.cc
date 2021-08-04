#include "humanPlayer.h"
#include "Board.h"
#include <algorithm>

bool humanPlayer::chooseBasement(int& n, Board *board) {
  int temp = -1;
  while (true) {
    if (!(std::cin >> temp)) {
      if (std::cin.eof()) {
        return false;
      }
      std::cout << "Not an integer!" << std::endl;
      std::cout << "Please input an intger: ";
      std::cin.clear();
      std::cin.ignore();
    } else {
      if (!(board->validVertex(temp))) {
        std::cout << "You cannot build here." << std::endl;
        std::cout << "Please try another place for basement: ";
      } else {
        n = temp;
        return true;
      }
    }
  }
}


bool humanPlayer::chooseTile(int &n, Board *board) {
  int temp = -1; 
  while (true) {
    if (!(std::cin >> temp)) {
      if (std::cin.eof()) {
        return false;
      }
      std::cout << "Not an integer!" << std::endl;
      std::cout << "Please input an intger:";
      std::cin.clear();
      std::cin.ignore();
    } else {
      if (temp >= board->getTileNum() || temp < 0) {
        std::cout << "Invalid tile number!" << std::endl;
        std::cout << "Please try again: ";
      } else if (temp == board->getGeese()){
        std::cout << "Oops!You must move geese to another tile!";
        std::cout << "Please try again: ";
      } else {
        n = temp;
        return true;
      }
    }
  }
}

bool humanPlayer::chooseColor(std::string &color, std::vector<std::string> v) {
  std::string temp = "";
  while (true) {
    if (!(std::cin >> temp)) {
      if (std::cin.eof()) {
        return false;
      }  
    } else {
      auto it = find(v.begin(), v.end(), temp);
      if (it == v.end()) {
        std::cout << "You should choose from:";
        std::cout << "[";
        for (unsigned int i = 0; i < v.size(); ++i) {
          std::cout << v[i];
          if (i != v.size() - 1) {
            std::cout << ",";
          }
        }
        std::cout << "]" << std::endl;
        std::cout << "Please input again: " << std::endl;
      } else {
        color = temp;
        return true;
      }
    }
  }
}

bool humanPlayer::chooseRoadToBuild(Board *board) {
  int temp = -1;
  if (!(std::cin >> temp)) {
    if (std::cin.eof()) {
      return false;
    }
    std::cout << "You do not enter an integer as road!" << std::endl;
    std::cin.clear();
    std::cin.ignore();
    return true;
  } else {
    if (temp >= board->getRoadNum() || temp < 0) {
      std::cout << "Invalid road number!You cannot build here." << std::endl;
    } else if (!(board->canBuild(getColor()[0], temp, "Road"))) {
      std::cout << "You cannot build here." << std::endl;
    } else if (attempbuild(temp, 'R')) {
      board->create(getColor()[0], temp, "road");
    }
    return true;
  }
}

bool humanPlayer::chooseBasementToBuild(Board *board) {
  int temp = -1;
  if (!(std::cin >> temp)) {
    if (std::cin.eof()) {
      return false;
    }
    std::cout << "You do not enter an integer as basement!" << std::endl;
    std::cin.clear();
    std::cin.ignore();
    return true;
  } else {
    if (temp >= board->getVertexNum() || temp < 0) {
      std::cout << "Invalid residence number!";
      std::cout << "You cannot build here." << std::endl;
    } else if (!(board->canBuild(getColor()[0], temp, "Basement"))) {
      std::cout << "You cannot build here." << std::endl;
    } else if (attempbuild(temp, 'B')) {
      board->create(getColor()[0], temp, "Basement");
    }
    return true;
  }
}

bool humanPlayer::chooseBasementToUpgrade(Board *board) {
  int temp = -1;
  if (!(std::cin >> temp)) {
    if (std::cin.eof()) {
      return false;
    }
    std::cout << "You do not enter an integer as basement!" << std::endl;
    std::cin.clear();
    std::cin.ignore();
    return true;
  } else {
    if (temp >= board->getVertexNum() || temp < 0) {
      std::cout << "Invalid residence number!";
      std::cout << "You cannot build here." << std::endl;
    } else if (!(board->canUpgrade(getColor()[0], temp))) {
      std::cout << "You cannot upgrade buildings here." << std::endl;
    } else if (upgradeResidence(temp)) {
      board->upgradeLevel(getColor()[0], temp);
    }
    return true;
  }
}

bool humanPlayer::answer(std::string &cmd) {
  std::string temp;
  while (true) {
    if (!(std::cin >> temp)) {
      if (std::cin.eof()) {
        return false;
      }
    } else {
      if (temp != "yes" && temp != "no") {
        std::cout << "Ahh! The answer must be either yes or no!";
        std::cout << std::endl;
        std::cout << "Please try again: ";
      } else {
        cmd = temp;
        return true;
      }
    }
  }
}

bool humanPlayer::chooseToExchange(std::string &col, std::string &type1, std::string &type2) {
  std::string temp1 = "";
  std::string temp2 = "";
  std::string temp3 = "";
  if (!(std::cin >> temp1)) {
    if (std::cin.eof()) {
      return false;
    }
  }
  if (!(std::cin >> temp2)) {
    if (std::cin.eof()) {
      return false;
    }
  }
  if (!(std::cin >> temp3)) {
    if (std::cin.eof()) {
      return false;
    }
  }
  col = temp1;
  type1 = temp2;
  type2 = temp3;
  return true;
}

bool humanPlayer::chooseCommand(std::string &cmd) {
  std::string temp;
  if (!(std::cin >> temp)) {
    if (std::cin.eof()) {
      return false;
    }
  } else {
    cmd = temp;
    return true;
  }
}

