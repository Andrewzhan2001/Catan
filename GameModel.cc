#include "GameModel.h"
#include <random>
#include <memory>

GameModel::GameModel() {
  std::vector<std::unique_ptr<Player>> players;
  for (int i = 0; i < 4; ++i) {
    auto p = std::make_unique<Player>();
    players.emplace_back(p);
  }
  this->players = players;
}

Player *GameModel::getPlayer(int idx) {
  return players[idx].get();
}

Board *GameModel::getBoard() {
  return b.get();
}
void GameModel::setSeed(size_t n) {
  this->seed = n;
  rng = std::default_random_engine{n};
}

 void GameModel::setTurn(int turn) {
   currentTurn = turn;
 }
std::string getColor(int idx) {
  if (idx == 0) {
    return "Blue";
  } else if (idx == 1) {
    return "Red";
  } else if (idx == 2) {
    return "Orange";
  } else {
    return "Yellow";
  }
}


int getPlayerNum(std::string type) {
  if (type == "Blue") {
    return 0;
  } else if (type == "Red") {
    return 1;
  } else if (type == "Orange") {
    return 2;
  } else {
    return 3;
  }
}

void GameModel::initial() {
  int i = 0;
  while (i < number) {
    Player *cur = getPlayer(i);
    std::string color = getColor(i);
    std::cout << "Builder " << color << ", ";
    std::cout << "where do you want to build a basement?" << std::endl;
    int n;
    // reads in an integer as a vertex
    while (true) {
      cur->chooseInt(n);
      if (b->validVertex(n)) {
        // is a valid vertex
        cur->addBasement(n);
        b->create(i, n, "Basement");
        break;
      }
    }
    ++i;
  }
  while (i > 0) {
    Player *cur = getPlayer(i);
    std::string color = getColor(i);
    std::cout << "Builder " << color << ", ";
    std::cout << "where do you want to build a basement?" << std::endl;
    int n;
    // reads in an integer as a vertex
    while (true) {
      cur->chooseInt(n);
      if (b->validVertex(n)) {
        // is a valid vertex
        cur->addBasement(n);
        b->create(i, n, "Basement");
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

void GameModel::setDice(std::string type) {
  if (type == "fair") {
    currentDice = 0;
  } else if (type == "load") {
    currentDice = 1;
  }
}

int GameModel::rollDice() {
  Dice *cur = d[currentDice].get();
  if (currentDice == 0) {
    // fair dice, roll twice
    diceNum += cur->getNum();
    diceNum += cur->getNum();
  } else {
    diceNum += cur->getNum();
  }
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

void GameModel::buildRoad(int x) { create(x, "Road"); }

void GameModel::buildBasement(int x) { create(x, "Basement"); }

void GameModel::create(int x, std::string type) {
  Player *cur = getPlayer(currentTurn);
  if (b->canBuild(currentTurn, x, type)) {
    if (cur->attempbuild(x, type[0])) {
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
  Player *cur = getPlayer(currentTurn);
  if (diceNum == 7) {
    for (auto &p : players) {
      if (p->getTotal() >= 10) {
       p->loseHalf(seed);
      }
    }
    std::cout << "Choose where to place the GEESE.";
    int n;
    while (true) {
      cur->chooseInt(n);
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
        if (getPlayer(i)->belongs(x, 'B')) {
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
      std::cout << "]" << std::endl;
      std::cout << "Choose a builder to steal from." << std::endl;
      while (true) {
        cur->chooseInt(n);
        if (0 <= n && n < (players.size() - 1)) {
          break;
        }
      }
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
        if (p->belongs(n.second, 'B')) {
          p->award(n.second, n.first);
        }
      }
    }
  }
}

void GameModel::exchange(std::string color, std::string type1, std::string type2) {
  std::cout << getColor(currentTurn);
  std::cout << " offers " << color;
  std::cout << " one " << type1 << " for one " << type2 << "." << std::endl;
  std::cout << "Does " << color << " accept this offer?" << std::endl;
  std::string cmd;
  while (std::cin >> cmd) {
    if (cmd == "yes") {
      getPlayer(currentTurn)->modifyResources(type1, -1);
      getPlayer(currentTurn)->modifyResources(type2, 1);
      getPlayer(getPlayerNum(color))->modifyResources(type1, 1);
      getPlayer(getPlayerNum(color))->modifyResources(type2, -1);
      break;
    } else if (cmd == "no") {
      break;
    }
  }
}

bool GameModel::ifWin() {
  for (auto &p : players) {
    if (p->getPoints() >= 10) {
      return true;
    }
  }
  return false;
}

void GameModel::saveFile(std::ofstream &out) {
  out << currentTurn << std::endl;
  for (auto &p : players) {
    p->printData(out);
    out << std::endl;
  }
}