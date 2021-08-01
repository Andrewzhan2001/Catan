#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <algorithm>
#include "Controller.h"
#include "SetBoardStrategy.h"
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
    for (int i = 1; i < argc; i++) { // add command to the vector of pairs
      string first(argv[i]);
      if (first == "-random-board") {
        command.emplace_back(first,"");
      } else if(first == "-seed" || first == "-load" || first == "-board"){
        ++i;
        string second(argv[i]);
        command.emplace_back(first,second);
      }
    }
    // use find_if to find specific command in the vector
    auto it = find_if(command.begin(), command.end(),
      [](const pair<string, string>& element){ return element.first == "-seed";});
    if(it != command.end()) {
      control->setseed(stoi(it.base()->second));
    }
    auto itt = find_if(command.begin(), command.end(),
      [](const pair<string, string>& element){ return element.first == "-load";});
    if(itt != command.end()) {
      auto sf = make_unique<Setfromfile>(itt.base()->second);
      control->loadStrategy(sf.get());
    } else {
      //if do not find command line -load check whether here is -board
      auto ittt = find_if(command.begin(), command.end(),
      [](const pair<string, string>& element){ return element.first == "-board";});
      if(ittt != command.end()) {
        auto fb = make_unique<loadFromBoard>(ittt.base()->second);
        control->loadStrategy(fb.get());
      } else {
        // if both command not found, default randomboard
        auto rl = make_unique<randomLoad>();
        control->loadStrategy(rl.get());
      }
    }
    control->print();
    state = control->play();
  }
  return 0;
}
