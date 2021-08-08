#ifndef PLAYERFACTORY
#define PLAYERFACTORY
#include <string>
#include <memory>

class Player;
class PlayerFactory {
public:
	// create Player instance
	static std::unique_ptr<Player> createObject(std::string objectType);
};
#endif