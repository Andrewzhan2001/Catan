#include "computerPlayer.h"
#include "Board.h"
#include "algorithm"
#include "vector"
using namespace std;


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

bool computerPlayer::chooseColor(std::string &color, std::vector<std::string> v) {
  if (v.size() == 0) {
    cout << "computer can not choose anything" << endl;
    return false;
  }
  shuffle(v.begin(),v.end(), rng);
  color = v[0];
  return true; 
}

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
    if (board->validRoad(i)) {
      return true;
    }
  } 
  cout << "computer can not choose anything" << endl;
  return false;
}

bool computerPlayer::chooseBasementToBuild(Board *board) { 
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

bool computerPlayer::chooseBasementToUpgrade(Board *board) { return true; }
bool computerPlayer::chooseToExchange(std::string &col, std::string &type1, std::string &type2) { return true; }
/* bool computerPlayer::chooseResource(std::string &cmd) { 
  if (resources.size() == 0) {
    resources.push_back("BRICK");
    resources.push_back("ENERGY");
    resources.push_back("GLASS");
    resources.push_back("HEAT");
    resources.push_back("WIFI");
    resources.push_back("PARK");
  }
  shuffle(resources.begin(), resources.end(), rng);
  cmd = resources[0];
  return true;
} */

bool computerPlayer::chooseCommand(std::string &cmd) { 
  if (commands.size() == 0) {
    commands.push_back("fair");
    commands.push_back("roll");
    commands.push_back("board");
    commands.push_back("status");
    commands.push_back("residences");
    commands.push_back("build-road");
    commands.push_back("build-res");
    commands.push_back("improve");
    commands.push_back("next");
  }
  cmd = commands[0];
  commands.erase(commands.begin());
  return true; 
}
