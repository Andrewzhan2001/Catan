#include "GameModel.h"
#include <random>
#include <memory>
#include "PlayerFactory.h"
#include "BoardFactory.h"
#include "DiceFactory.h"
#include <algorithm>

GameModel::GameModel() : number{4} {
  for (int i = 0; i < 4; ++i) {
    PlayerFactory pf;
    players.emplace_back(pf.createObject("humanPlayer"));
  }
  BoardFactory bf;
  b = bf.createObject("normalBoard");
  DiceFactory df;
  d.emplace_back(df.createObject("FairDice"));
  d.emplace_back(df.createObject("LoadedDice"));
}

Player *GameModel::getPlayer(int idx) {
  return players[idx].get();
}

Board *GameModel::getBoard() {
  return b.get();
}

std::string GameModel::getCurColor() {
  return getCurPlayer()->getColor();
}

Player *GameModel::getCurPlayer(){
  return getPlayer(currentTurn);
}

size_t GameModel::getSeed() { return seed; }

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
    int n = -1;
    // reads in an integer as a vertex
    while (true) {
      if (!(cur->chooseVertex(n))) {
        // end-of-file signal reaches
        saveFile();
        return;
      } else {
        if (!(b->validVertex(n))) {
          std::cout << "You cannot build here." << std::endl;
        } else {
          // is a valid vertex
          cur->addBasement(n);
          b->create(color[0], n, "Basement");
          break;
        }
      }
    }
    ++i;
  }
  int j = 3;
  while (j >= 0) {
    Player *cur = getPlayer(j);
    std::string color = getColor(j);
    std::cout << "Builder " << color << ", ";
    std::cout << "where do you want to build a basement?" << std::endl;
    int n = -1;
    // reads in an integer as a vertex
    while (true) {
      if (!(cur->chooseVertex(n))) {
        // end-of-file signale reaches
        saveFile();
        return;
      } else {
        if (!(b->validVertex(n))) {
          std::cout << "You cannot build here." << std::endl;
        } else {
          // is a valid vertex
          cur->addBasement(n);
          b->create(color[0], n, "Basement");
          break;
        }
      }
    }
    --j;
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
  diceNum = 0;
  Dice *cur = d[currentDice].get();
  if (currentDice == 0) {
    // fair dice, roll twice
    diceNum += cur->getNum();
    diceNum += cur->getNum();
  } else {
    diceNum += cur->getNum();
  }
  return diceNum;
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
  std::string col = cur->getColor();
  if (!(b->canBuild(currentTurn, x, type))) {
    std::cout << "You cannot build here!" << std::endl;
  } else {
    if (cur->attempbuild(x, type[0])) {
      b->create(col[0], x, type);
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
  std::cout << diceNum << std::endl;
  Player *cur = getPlayer(currentTurn);
  if (diceNum == 7) {
    for (auto &p : players) {
      if (p->getTotal() >= 10) {
       p->loseHalf();
      }
    }
    std::cout << "Choose where to place the GEESE." << std::endl;
    int n = -1;
    while (true) {
      if (!(cur->chooseTile(n))) {
        saveFile();
        return;
      } else {
        if (n >= b->getTileNum() || n < 0) {
          std::cout << "Invalid tile number!Please input again!" << std::endl;
        } else {
          b->setGeese(n);
          break;
        }
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
          std::string col = getPlayer(i)->getColor();
          auto it = find(lists.begin(), lists.end(), col);
          if (it != lists.end()) {
            lists.emplace_back(getPlayer(i)->getColor());
          }
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
      for (size_t i = 0; i < lists.size(); ++i) {
        std::cout << lists[i];
        if (i != lists.size() - 1) {
          std::cout << ",";
        }
      }
      std::cout << "]" << std::endl;
      std::cout << "Choose a builder to steal from." << std::endl;
      while (true) {
        if (!(cur->choosePlayer(n))) {
          saveFile();
          return;
        } else {
          if (0 <= n && n < (int)(players.size() - 1)) {
            std::string c = getPlayer(n)->getColor();
            auto it = find(lists.begin(), lists.end(), c);
            if (it == lists.end()) {
              // not found
              std::cout <<  "You cannot steal from this player.";
              std::cout << "Please input again." << std::endl;
            } else {
              break;
            }
          } else {
            std::cout << "Invalid player number!Please input again!" << std::endl;
          }
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
    std::cout << "yes" << std::endl;
    std::vector<std::pair<std::string, int>> neighbours = b->getResidences(diceNum);
    for (auto n : neighbours) {
      std::cout << n.first << std::endl;
      std::cout << n.second << std::endl;
    }
    std::cout << std::endl;
    for (auto n : neighbours) {
      for (auto &p : players) {
        if (p.get()->belongs(n.second, 'B')) {
          p.get()->award(n.second, n.first);
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

void GameModel::saveFile(std::string filename) {
  std::ofstream fout(filename);
  fout << currentTurn << std::endl;
  for (auto &p : players) {
    p->printData(fout);
    fout << std::endl;
  }
  fout.close();
}

void GameModel::printBoard() {
  b->printBoard(std::cout);
}