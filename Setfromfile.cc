#include "Setfromfile.h"
#include "GameModel.h"
#include <fstream>
#include <map>
#include <sstream>
#include <string>
void Setfromfile::loadBoard(GameModel *bm) override {
  Board *b = bm->getBoard();
  // set player vector ???
  int CurTurn, numBricks, numEnergies, numGlass, numHeat, numWifi, roads,
      housing, B_num, T_num, H_num;
  char r, B, T, H;
  std::map<int, std::string> builders = {
      {0, "Blue"}, {1, "Red"}, {2, "Orange"}, {3, "Yellow"}};
  std::ifstream infile("savefile.txt");
  if (!infile) {
    std::cerr << "Couldn't open input file.\n";
    return 1;
  }
  int lineNum = 1;
  std::string line;
  while (std::getline(infile, line)) {
    // note this version is only for 4 players, needs to add countlines function
    // for extra builders
    if (lineNum == 1) {
      std::cin >> CurTurn;
      bm->setTurn(CurTurn);
    } else if ((lineNum >= 2) && (lineNum <= 5)) {
      int builderNum = lineNum - 2;
      Player *builder = bm->getPlayer(builderNum);
       auto it = builders.find(builderNum);
      std::string builderColor = it->second;
      // set color
builder->setColor(builderColor);
       // set player resource
      std::cin >> numBricks >> numEnergies >> numGlass >> numHeat;
          numWifi std::vector<std::pair<std::string, int>> resource{
              {"BRICK", numBricks},
              {"ENERGY", numEnergies},
              {"GLASS", numGlass},
              {"HEAT", numHeat},
              {"WIFI", numWifi}};
      builder->setResource(resource);
      // set roads
      std::cin >> r;
      int road;
     while(true) {
       std::cin >> road;
       if(!cin) {
          std::cin.clear();
         std::cin.ignore();
         break;
       }
       b->setEdge(road, builderColor[0]);
     }
     // set residence
std::cin >> B_num >> B >> T_num >> H_num >> H;

  }

  bm->setTurn()
}
