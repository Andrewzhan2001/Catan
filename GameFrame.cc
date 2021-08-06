#include "GameFrame.h"
#include "GameModel.h"
#include <iostream>

using namespace std;

void GameFrame::printboard(const GameModel* gm) {
	Board* b = gm->getBoard();
	b->printBoard(std::cout);
}

void GameFrame::printhelp() {
	cout << "Valid commands:" << endl;
	cout << "board" << endl;
	cout << "status" << endl;
	cout << "residences" << endl;
	cout << "build-road <edge#>" << endl;
	cout << "build-res <housing#>" << endl;
	cout << "improve <housing#>" << endl;
	cout << "trade <colour> <give> <take>" << endl;
	cout << "next" << endl;
	cout << "save <file>" << endl;
	cout << "help" << endl;
}
