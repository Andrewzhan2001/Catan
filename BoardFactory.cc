#include "BoardFactory.h"
#include "Board.h"
std::unique_ptr<Board> BoardFactory::createObject(std::string objectType){
 return std::make_unique<normalBoard>();
}
