#ifndef SETBOARDSTRATEGY
#define SETBOARDSTRATEGY
#include <map>
#include <string>
class GameModel;

class SetBoardStrategy {
protected:
	std::map<int, std::string> tiles;
	std::map<int, std::string> builders;
public:
	virtual ~SetBoardStrategy() = default;
	SetBoardStrategy();
	// load the game to GameModel which contians all players, board, dices.
	virtual bool loadBoard(GameModel* gm) = 0;
};
#endif