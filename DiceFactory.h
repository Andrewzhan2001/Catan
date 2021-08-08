#ifndef DICEFACTORY
#define DICEFACTORY
#include <string>
#include <memory>

class Dice;

class DiceFactory {
public:
	// create Dice instance
	static std::unique_ptr<Dice> createObject(const std::string& object_type);
};
#endif