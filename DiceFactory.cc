#include "DiceFactory.h"
#include "Dice.h"
#include "FairDice.h"
#include "LoadedDice.h"
  std::unique_ptr<Dice> DiceFactory::createObject(std::string objectType) {
    if(objectType == "FairDice") {
      return std::make_unique<FairDice>();
    } else if(objectType == "LoadedDice") {
      return std::make_unique<LoadedDice>();
    }
  }
