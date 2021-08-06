#ifndef RANDOMLOAD
#define RANDOMLOAD
#include "SetBoardStrategy.h"

class GameModel;

class randomLoad : public SetBoardStrategy {
public:
	bool loadBoard(GameModel* bm) override;
};
#endif