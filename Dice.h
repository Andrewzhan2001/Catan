#ifndef DICE
#define DICE

#include <cstddef>

class Dice {
public:
	virtual ~Dice();
	// set the seed of dice(main use for FairDice)
	virtual void setseed(size_t seed);
	// let the dice generate the number(roll the dice)
	virtual int getNum() = 0;
};
#endif