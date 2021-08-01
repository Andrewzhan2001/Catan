#include "humanPlayer.h"

bool humanPlayer::chooseVertex(int& n) {
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

bool humanPlayer::chooseTile(int &n) {
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

bool humanPlayer::choosePlayer(int &n) {
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