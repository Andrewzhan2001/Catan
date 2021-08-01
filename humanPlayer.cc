#include "humanPlayer.h"

bool humanPlayer::chooseVertex(int& n) {
  while (true) {
    if (!(std::cin >> n)) {
      if (std::cin.eof()) {
        return false;
      }
      std::cout << "Not an integer!Please input an intger!" << std::endl;
    } else {
      return true;
    }
  }
}

bool chooseTile(int &n) {
  while (true) {
    if (!(std::cin >> n)) {
      if (std::cin.eof()) {
        return false;
      }
      std::cout << "Not an integer!Please input an intger!" << std::endl;
    } else {
      return true;
    }
  }
}

bool choosePlayer(int &n) {
  while (true) {
    if (!(std::cin >> n)) {
      if (std::cin.eof()) {
        return false;
      }
      std::cout << "Not an integer!Please input an intger!" << std::endl;
    } else {
      return true;
    }
  }
}