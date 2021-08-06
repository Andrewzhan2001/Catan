#ifndef PLAYERFACTORY
#define PLAYERFACTORY
#include <string>
#include <memory>

class Player;
class PlayerFactory {
public:
	static std::unique_ptr<Player> createObject(std::string objectType);
};
#endif