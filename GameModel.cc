#include "GameModel.h"

Player *GameModel::getPlayer(int idx) {
  return players[idx].get();
}

std::string getColor(int idx) {
  if (idx == 0) {
    return "Blue";
  } else if (idx == 1) {
    return "Red";
  } else if (idx == 2) {
    return "Orange";
  } else {
    return "Red";
  }
}

void GameModel::initial() {
  int i = 0;
  while (i < number) {
    Player *cur = getPlayer(i);
    std::string color = getColor(i);
    std::cout << "Builder " << color << ", ";
    std::cout << "where do you want to build a basement?\n";
    int n;
    // reads in an integer as a vertex
    while (std::cin >> n) {
      if (b->validVertex(n)) {
        // is a valid vertex
        cur->addBasement(n);
        b->create(i, n, "basement");
        break;
      }
    }
    ++i;
  }
  while (i > 0) {
    Player *cur = getPlayer(i);
    std::string color = getColor(i);
    std::cout << "Builder " << color << ", ";
    std::cout << "where do you want to build a basement?\n";
    int n;
    // reads in an integer as a vertex
    while (std::cin >> n) {
      if (b->validVertex(n)) {
        // is a valid vertex
        cur->addBasement(n);
        b->create(i, n, "basement");
        break;
      }
    }
    ++i;
  }
}

void GameModel::switches() {
  currentTurn++;
  if (currentTurn >= 4) { currentTurn -= 4; }
}


void GameModel::printTurn() {
  Player *cur = getPlayer(currentTurn);
  cur->printStatus();
}

int GameModel::rollDice(std::string type) {
  // construct dices according to type
  diceNum = d->getNum();
}

void GameModel::printPlayers() {
  for (auto &p : players) {
    p->printStatus();
  }
}

void GameModel::printBuildings() {
  Player *cur = getPlayer(currentTurn);
  cur->printBuildings();
}

void GameModel::buildRoad(int x) { create(x, "road"); }

void GameModel::buildBasement(int x) { create(x, "basement"); }

void GameModel::create(int x, std::string type) {
  Player *cur = getPlayer(currentTurn);
  if (b->canBuild(currentTurn, x, type)) {
    if (cur->attempbuild(x, type)) {
      b->create(currentTurn, x, type);
    }
  }
}

void GameModel::upgrade(int x) {
  Player *cur = getPlayer(x);
  if (b->canUpgrade(currentTurn, x)) {
    if (cur->upgradeResidence(x)) {
      b->upgradeLevel(currentTurn, x);
    }
  }
}

void GameModel::update() {
  if (diceNum == 7) {
    for (auto &p : players) {
      if (p->getTotal() >= 10) {
       p->loseHalf();
      }
    }
    std::cout << "Choose where to place the GEESE.";
    int n;
    while (std::cin >> n) {
      if(b->validVertex(n)) {
        b->setGeese(n);
      }
    }
    std::vector<int> neighbours = b->getNeighbours(n);
    std::vector<std::string> lists;
    for (auto x : neighbours) {
      for (int i = 0; i < number; ++i) {
        if (i == currentTurn) {
          continue;
        } 
        if (getPlayer(i)->belongs(x, "basement")) {
          lists.emplace_back(getColor(i));
        }   
      }
    }
    if (lists.size() == 0) {
      std::cout << "Builder ";
      std::cout << getColor(currentTurn);
      std::cout << " has no builders to steal from";
    } else {
      std::cout << "Builder ";
      std::cout << getColor(currentTurn);
      std::cout << "can choose to steal from ["; 
      for (int i = 0; i < lists.size(); ++i) {
        std::cout << lists[i];
        if (i != lists.size() - 1) {
          std::cout << ",";
        }
      }
      std::cout << "]\n";
      std::cout << "Choose a builder to steal from.\n";
      std::cin >> n;
      std::string type = getPlayer(n)->loseOneResourceRandomly();
      getPlayer(currentTurn)->modifyResources(type, 1);
      std::cout << "Builder ";
      std::cout << getColor(currentTurn);
      std::cout << " steals ";
      std::cout << type << " from builder ";
      std::cout << getColor(n) << " .";
    }
  } else {
    std::vector<std::pair<std::string, int>> neighbours = b->getResidences(diceNum);
    for (auto n : neighbours) {
      for (auto &p : players) {
        if (p->belongs(n.second, "basement")) {
          p->award(n.second, n.first);
        }
      }
    }
  }
}

void GameModel::exchange(int p, std::string type1, std::string type2) {
  std::cout << getColor(currentTurn);
  std::cout << " offers " << getColor(p);
  std::cout << " one " << type1 << " for one " << type2 << ".\n";
  std::cout << "Does " << getColor(p) << " accept this offer?\n";
  std::string cmd;
  while (std::cin >> cmd) {
    if (cmd == "yes") {
      getPlayer(currentTurn)->modifyResources(type1, -1);
      getPlayer(currentTurn)->modifyResources(type2, 1);
      getPlayer(p)->modifyResources(type1, 1);
      getPlayer(p)->modifyResources(type2, -1);
      break;
    } else if (cmd == "no") {
      break;
    }
  }
}