#ifndef BOARDFACTORY
#define BOARDFACTORY
#include <string>
#include <memory>

class Board;
class BoardFactory {
public:
	// create Board instance
	static std::unique_ptr<Board> createObject(std::string objectType);
};
#endif