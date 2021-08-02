#include "computerPlayer.h"


computerPlayer::computerPlayer(){
  for (size_t i = 0; i < 53; i++) {
    vertexnum.push_back(i);
  }
  for (size_t i = 0; i <= 18; i++) {
    Tilenum.push_back(i);
  }
  for (size_t i = 0; i <= 4; i++) {
    vertexnum.push_back(i);
  }
}

bool computerPlayer::chooseVertex(int& n, Board *board) {
  return true;
}
bool computerPlayer::chooseTile(int &n, Board *board) { return true; }

bool computerPlayer::chooseColor(std::string &cmd, std::vector<std::string> v) { return true; }

bool computerPlayer::chooseRoad(int &n, Board *board) { return true; }

bool computerPlayer::answer(std::string &cmd) { return true; }

bool computerPlayer::chooseResource(std::string &cmd) { return true; }

bool computerPlayer::chooseCommand(std::string &cmd) { return true; }
