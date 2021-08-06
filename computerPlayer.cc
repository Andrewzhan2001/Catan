#include "computerPlayer.h"
#include "Board.h"
#include "algorithm"
#include "vector"

using namespace std;
computerPlayer::~computerPlayer(){}

// 一开始的时候用
bool computerPlayer::chooseBasement(int& n, Board *board) {
  if (board->getVertexNum() == 0) {
    cout << "computer can not choose anything" << endl;
    return false;
  }
  if (vertex.size() == 0) {
    for (int i = 0; i < board->getVertexNum(); i++) {
      vertex.push_back(i);
    }
  }
  shuffle(vertex.begin(), vertex.end(), rng);
  for (auto &&i : vertex) {
    if (board->validVertex(i)) {
      n = i;
      return true;
    }
  }
  cout << "computer can not choose anything" << endl;
  return false;
}

//扔到7move geese
bool computerPlayer::chooseTile(int &n, Board *board) { 
  if (board->getTileNum() == 0) {
    cout << "computer can not choose anything" << endl;
    return false;
  }
  if (tiles.size() == 0) {
    for (int i = 0; i < board->getTileNum(); i++) {
      tiles.push_back(i);
    }
  }
  shuffle(tiles.begin(), tiles.end(), rng);
  for (auto &&i : tiles) {
    if (!board->haveGeese(i)) {
      n = i;
      return true;
    }
  }
  cout << "computer can not choose anything" << endl;
  return false;
}

// v里面随便选一个
bool computerPlayer::chooseColor(std::string &color, std::vector<std::string> v) {
  if (v.size() == 0) {
    cout << "computer can not choose anything" << endl;
    return false;
  }
  shuffle(v.begin(),v.end(), rng);
  color = v[0];
  return true; 
}

//attempbuild有没有足够的resource，canbuild是规则允不允许
bool computerPlayer::chooseRoadToBuild(Board *board) { 
  if (board->getRoadNum() == 0) {
    cout << "computer can not choose anything" << endl;
    return false;
  }
  if (edges.size() == 0) {
    for (int i = 0; i < board->getRoadNum(); i++) {
      edges.push_back(i);
    }
  }
  shuffle(edges.begin(), edges.end(), rng);
  for (auto &&i : edges) {
    if (board->canBuild(getColor()[0], i, "Road") && 
         attempbuild(i, 'R')) {
      board->create(getColor()[0], i, "road");
      return true;
    }
  }
  cout << "computer can not choose anything" << endl;
  return true;
}

bool computerPlayer::chooseBasementToBuild(Board *board) { 
  if (board->getVertexNum() == 0) {
    cout << "computer can not choose anything" << endl;
    return false;
  }
  if (vertex.size() == 0) {
    for (int i = 0; i < board->getVertexNum(); i++) {
      vertex.push_back(i);
    }
  }
  shuffle(vertex.begin(), vertex.end(), rng);
  for (auto &&i : vertex) {
    if (board->canBuild(getColor()[0], i, "Basement") && 
         attempbuild(i, 'B')) {
      board->create(getColor()[0], i, "Basement");
      return true;
    }
  }
  cout << "computer can not choose anything" << endl;
  return true;
}

bool computerPlayer::answer(std::string &cmd) { 
  std::uniform_int_distribution<> distr(0, 1);
  if (distr(rng) == true) {
    cmd = "yes";
  } else {
    cmd = "no";
  }
  return true;
}

bool computerPlayer::chooseBasementToUpgrade(Board *board) { 
  if (board->getVertexNum() == 0) {
    cout << "computer can not choose anything" << endl;
    return false;
  }
  if (vertex.size() == 0) {
    for (int i = 0; i < board->getVertexNum(); i++) {
      vertex.push_back(i);
    }
  }
  shuffle(vertex.begin(), vertex.end(), rng);
  for (auto &&i : vertex) {
    if (board->canUpgrade(getColor()[0], i) && 
         upgradeResidence(i)) {
      board->upgradeLevel(getColor()[0], i);
      return true;
    }
  }
  cout << "computer can not choose anything" << endl;
  return true; 
}
bool computerPlayer::chooseToExchange(std::string &col, std::string &type1, std::string &type2) { return true; }

bool computerPlayer::chooseCommand(std::string &cmd) { 
  if (commands.size() == 0) {
    commands.push_back("fair");
    commands.push_back("roll");
    commands.push_back("board");
    commands.push_back("status");
    commands.push_back("residences");
    commands.push_back("build-res");
    commands.push_back("improve");
    commands.push_back("build-road");
    commands.push_back("next");
  }
  cmd = commands[0];
  cout << cmd << endl;
  commands.erase(commands.begin());
  return true; 
}
