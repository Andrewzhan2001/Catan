#ifndef SETFROMFILE
#define SETFROMFILE
#include <string>
#include "SetBoardStrategy.h"

class GameModel;
class Setfromfile : public SetBoardStrategy {
	std::string file;
public:
	Setfromfile(std::string file);
	bool loadBoard(GameModel* bm) override;
};
#endif