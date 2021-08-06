#ifndef GAMEFRAME
#define GAMEFRAME
class GameModel;

class GameFrame {
public:
	static void printboard(const GameModel* gm);
	static void printhelp();
};
#endif