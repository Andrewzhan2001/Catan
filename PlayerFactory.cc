#include "PlayerFactory.h"
#include "Player.h"
#include "humanPlayer.h"
#include "computerPlayer.h"
std::unique_ptr<Player> PlayerFactory::createObject(const std::string objectType) {
	if (objectType == "humanPlayer") {
		return std::make_unique<humanPlayer>();
	}
	else if (objectType == "computerPlayer") {
		return std::make_unique<computerPlayer>();
	}
	else {
		return nullptr;
	}
}