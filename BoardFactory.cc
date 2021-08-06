#include "BoardFactory.h"
#include "Board.h"
#include "normalBoard.h"
std::unique_ptr<Board> BoardFactory::createObject(const std::string objectType)
{
	if (objectType == "normalBoard") {
		return std::make_unique<normalBoard>();
	}
	else {
		return nullptr;
	}
}
