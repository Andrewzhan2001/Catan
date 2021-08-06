#ifndef LOADEDDICE
#define LOADEDDICE
#include "Dice.h"
class LoadedDice : public Dice {
public:
	~LoadedDice() override;
	// return number between 2 and 12 which reads from input
	int getNum() override;
};
#endif