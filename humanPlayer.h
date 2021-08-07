#ifndef HUMANPLAYER
#define HUMANPLAYER
#include <string>
#include <vector>
#include "Player.h"

class humanPlayer : public Player {
public:
	~humanPlayer() override;
	bool chooseBasement(int& n, Board* board) override;
	bool chooseTile(int& n, Board* board) override;
	bool chooseColor(std::string& cmd, std::vector<std::string> v) override;
	bool chooseRoadToBuild(Board* board) override;
	bool chooseBasementToBuild(Board* board) override;
	bool answer(std::string& cmd) override;
	bool chooseToExchange(std::string& col, std::string& type1, 
		                                    std::string& type2) override;
	bool chooseCommand(std::string& cmd) override;
	bool chooseBasementToUpgrade(Board* board) override;
};
#endif