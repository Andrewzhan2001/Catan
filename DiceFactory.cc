#include "DiceFactory.h"
#include "Dice.h"
#include "FairDice.h"
#include "LoadedDice.h"
std::unique_ptr<Dice> DiceFactory::createObject(const std::string& object_type)
{
	if (object_type == "FairDice") {
		return std::make_unique<FairDice>();
	}
	else if (object_type == "LoadedDice") {
		return std::make_unique<LoadedDice>();
	}
	else {
		return nullptr;
	}
}
