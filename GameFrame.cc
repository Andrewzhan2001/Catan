#include "GameFrame.h"
#include "GameModel.h"
void GameFrame::printboard(GameModel *gm) {
  Board *b = gm->getBoard();
  b->printBoard(std::cout);
}
