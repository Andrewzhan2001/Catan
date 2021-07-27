#include "PlayerFactory.h"
  std::unique_ptr<Player> PlayerFactory::createObject(std::string objectType) {
    return std::make_unique<humanPlayer>();
  }
