#ifndef DICE
#define DICE

#include <cstddef>

class Dice {
public:
	virtual ~Dice();
	virtual void setseed(size_t seed);
	virtual int getNum() = 0;
};
#endif