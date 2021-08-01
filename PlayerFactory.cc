#include "PlayerFactory.h"
#include "Player.h"
#include "humanPlayer.h"
std::unique_ptr<Player> PlayerFactory::createObject(std::string objectType) {
  if (objectType == "humanPlayer") {
    return std::make_unique<humanPlayer>();
  } else {
    return nullptr;
  }
  
}
