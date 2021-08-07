#ifndef GAMEFRAME
#define GAMEFRAME
class GameModel;

class GameFrame {
public:
	// print the board which get from GameModel
	static void printboard(const GameModel* gm);
	// print the help message
	static void printhelp();
};
#endif