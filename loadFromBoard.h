#ifndef LOADFROMBOARD
#define LOADFROMBOARD
#include <string>
#include "SetBoardStrategy.h"
class GameModel;
class loadFromBoard : public SetBoardStrategy {
	std::string file;
public:
	loadFromBoard(std::string file);
	bool loadBoard(GameModel* gm) override;
};
#endif