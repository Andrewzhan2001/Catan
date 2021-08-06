#ifndef FAIRDICE
#define FAIRDICE
#include <iostream>
#include <vector>
#include <random>
#include "Dice.h"

class FairDice : public Dice {
	size_t seed = 0;
	std::default_random_engine rng{ seed };
	std::vector<int> numbers = { 1,2,3,4,5,6 };
public:
	~FairDice() override;
	void setseed(size_t seed) override;
	int getNum() override; // return a random number from 1,2,3,4,5,6
};
#endif