#include "Player.h"
#include <string>


Player::Player()
    : buildpoints{0}, color{""}, resources{{{"BRICK", 0},
                                               {"ENERGY", 0},
                                               {"GLASS", 0},
                                               {"HEAT", 0},
                                               {"WIFI", 0}}},
      roads{}, residences{} {}

void Player::modifyResources(std::string type, int amount) {
  for (auto it : resources) {
    if (it.first == type) {
      it.second += amount;
    }
  }
}

void Player::addBasement(int x) {
  residences.push_back(std::make_pair(x, 'B'));
}

int Player::getResources(std::string type) {
  int retval = -1;
  for (auto it : resources) {
    if (it.first == type) {
      retval = it.second;
      break;
    }
  }
  return retval;
}

int Player::getTotal() {
  int sum = 0;
  for (auto it : resources) {
    sum += it.second;
  }
  return sum;
}

int Player::getPoints() { return buildpoints; }

void Player::setDiceNum(int dicenum) { this->dicenum = dicenum;}

int Player::getDiceNum() {return dicenum;}

std::string Player::getColor() { return color; }

void Player::setColor(std::string color) { this->color = color; }

void Player::setResource (std::vector<std::pair<std::string, int>> &r) {
  resources = r;
}

void Player::setseed(size_t seed) {
  this->seed = seed;
  this->rng = std::default_random_engine{seed};
}

bool Player::attempbuild(int x, char type) {
  // store the buildingpoint that needs to be added, only add
  // if has enough resource
  int addPoint = 0;
  // store all visited resource numbers, recover if needed
  std::vector<int> oldNum;
  // check resources and modify
  for (auto it = resources.begin(); it != resources.end(); ++it) {
    oldNum.push_back(it->second);
    if ((type == 'B') && (it->first != "HEAT")) {
      it->second = it->second - 1;
      addPoint = 1;
    } else if (type == 'H') {
      if (it->first == "GLASS") {
        it->second = it->second - 2;
      } else if (it->first == "HEAT") {
        it->second = it->second - 3;
      }
      addPoint = 2;
    } else if (type == 'T') {
      if (it->first == "BRICK")
        it->second = it->second - 3;
      if ((it->first == "ENERGY") || (it->first == "GLASS") ||
          (it->first == "HEAT"))
        it->second = it->second - 2;
      if (it->first == "WIFI")
        it->second = it->second - 1;
      addPoint = 3;
    } else if (type == 'R') {
      if ((it->first == "HEAT") || (it->first == "WIFI"))
        it->second = it->second - 1;
      addPoint = 0;
    }
    if (it->second < 0) { // if not enough resource
      // recover modified numbers
      for (int i = 0; i < oldNum.size(); i++) {
        resources[i].second = oldNum[i];
      }
      std::cout << "You do not have enough resources" << std::endl;
      return false;
    }
  } // loop
  // reach here means enough resource
  buildpoints += addPoint;
  // modify residence/road
  if (type == 'R') {
    roads.push_back(x);
  } else {
    residences.push_back(std::make_pair(x, type));
  }
  return true;
}

void Player::loseHalf() {
  int total = getTotal();
  if (total >= 10) {
    total /= 2;
    std::cout << "Builder " << getColor() << " loses " << total
              << " resources to the geese. They lose:" << std::endl;
    while (total > 0) {     // make sure the sum of deduction is half
      for (auto &i : resources) {
        int max = total;
        if (i.second < total) {
          max = i.second;
        }
        std::uniform_int_distribution<> distr(0, max); // define the range
        modifyResources(i.first, -distr(rng)); // generate number and modify
        std::cout << distr(rng) << " " << i.first << std::endl;
        total -= distr(rng);
        if (total <= 0) { // half has been deducted
          return;
        }
      } // for
    }   // while
  }     // if
}

bool Player::belongs(int x, char type) {
  if (type == 'R') {
    for (auto &i : roads) {
      if (i == x)
        return true;
    }
  } else {
    for (auto &i : residences) {
      if ((i.first == x) && (i.second == type))
        return true;
    }
  }
  // not found
  return false;
}

void Player::printBuildings() {
  std::cout << getColor() << " has built" << std::endl;
  for (auto &i : residences) {
    std::cout << i.first << " " << i.second << std::endl;
  }
}

void Player::printStatus() {
  std::cout << getColor() << " has " << buildpoints << "building points, ";
  for (int i = 0; i <= 3; i++) {
    std::cout << resources[i].second << " " << resources[i].first << ", ";
  }
  std::cout << "and" << resources[4].second << " " << resources[4].first << "."
            << std::endl;
}

bool Player::upgradeResidence(int x) {
  for (auto &i : residences) {
    if (i.first == x) {
      if (i.second == 'T') {
        return false;
      } else if (i.second == 'B') {
        // if has enough resource
        if (attempbuild(x, 'H')) {
          buildpoints--;                      // since one basement deleted
          residences.erase(residences.end()); // do not add this residence
          i.second = 'H';                     // upgrade residence
          return true;
        }
      } else if (i.second == 'H') {
        if (attempbuild(x, 'T')) {            // point += 3
          buildpoints -= 2;                   // since one house deleted
          residences.erase(residences.end()); // do not add this residence
          i.second = 'T';                     // upgrade residence
          return true;
        }
      }
      break;
    }
  }
  // for debug: doesn't find location x
  std::cout << "Invalid location" << std::endl;
  return false;
}

void Player::award(int x, std::string type) {
  for (auto &i : residences) {
    if (i.first == x) {
      if (i.second == 'T') {
        modifyResources(type, 3);
      } else if (i.second == 'H') {
        modifyResources(type, 2);
      } else if (i.second == 'B') {
        modifyResources(type, 1);
      }
      return;
    }
  }
  // for debug:
  std::cout << "no residence build at " << x << std::endl;
}

void Player::printData(std::ostream &out) {
  out << resources[0].second << " " << resources[1].second << " ";
  out << resources[2].second << " " << resources[3].second << " ";
  out << resources[4].second << " " << "r ";
  for (auto p : roads) {
    out << p << " ";
  }
  out << "h ";
  for (size_t i = 0; i < residences.size(); ++i) {
    if (i != residences.size() - 1) {
      out << residences[i].first << " " << residences[i].second << " ";
    } else {
      out << residences[i].first << " " << residences[i].second;
    }
  }
}

std::string Player::loseOneResourceRandomly() {
  std::vector<int> hasResource; // store the index of resource that builder has num > 0
  int idx = 0;
  for(auto &i: resources) {
    if(i.second > 0) { // player has this resource
hasResource.push_back(idx);
  }
  idx++;
  }
 std::uniform_int_distribution<int> dist(0, hasResource.size() - 1);
 std::string random_resource = resources[dist(rng)].first;
 return random_resource;
}
