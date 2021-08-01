#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <utility>
#include <stdexcept>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <algorithm>
#include "Controller.h"
#include "randomLoad.h"
#include "Setfromfile.h"
#include "loadFromBoard.h"
using namespace std;

int main(int argc, char const *argv[]) {
  bool state = true;
  while (state) {
    auto ctr = make_unique<Controller>();
    Controller *control = ctr.get();
    vector<pair<string,string>> command;
    for (size_t i = 1; i < argc; i++) { // add command to the vector of pairs
      string first = argv[i];
      if (first == "-random-board") {
        command.emplace_back(first,"");
      } else if(first == "-seed" || first == "-load" || first == "-board"){
        ++i;
        command.emplace_back(first,argv[i]);
      }
    }
    // use find_if to find specific command in the vector
    auto it = find_if(command.begin(), command.end(),
      [](const pair<string, size_t>& element){ return element.first == "-seed";});
    if(it != command.end()) {
      control->setseed(stoi(it.base()->second));
    }
    auto itt = find_if(command.begin(), command.end(),
      [](const pair<string, size_t>& element){ return element.first == "-load";});
    if(itt != command.end()) {
      Setfromfile sf{itt.base()->second};
      control->loadStrategy(sf);
    } else {
      //if do not find command line -load check whether here is -board
      auto ittt = find_if(command.begin(), command.end(),
      [](const pair<string, size_t>& element){ return element.first == "-board";});
      if(ittt != command.end()) {
        loadFromBoard fb{ittt.base()->second};
        control->loadStrategy(fb);
      } else {
        // if both command not found, default randomboard
        randomLoad rl;
        control->loadStrategy(rl);
      }
    }
    state = control->play();
  }
  return 0;
}
