#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <algorithm>
#include <chrono>
#include "Controller.h"
#include "SetBoardStrategy.h"
#include "randomLoad.h"
#include "Setfromfile.h"
#include "loadFromBoard.h"
using namespace std;

int main(int argc, char const *argv[]) {
  bool state = true;
  while (state) {
    vector<pair<string,string>> command;
    for (int i = 1; i < argc; i++) { // add command to the vector of pairs
      string first(argv[i]);
      if (first == "-random-board" || first == "-computer" || first == "-computerAuto") {
        command.emplace_back(first,"");
      } else if(first == "-seed" || first == "-load" || first == "-board"){
        ++i;
        string second(argv[i]);
        command.emplace_back(first,second);
      }
    }


    unique_ptr<Controller> ctr;
    // use find_if to find specific command in the vector

    // here is for player options
    auto it = find_if(command.begin(), command.end(),
      [](const pair<string, string>& element){ return element.first == "-computerAuto";});
    if(it != command.end()) {
      ctr = make_unique<Controller>("computerAuto");
    } else {
      it = find_if(command.begin(), command.end(),
        [](const pair<string, string>& element){ return element.first == "-computer";});
      if(it != command.end()) {
        ctr = make_unique<Controller>("computer");
      } else {
        ctr = make_unique<Controller>("human");
      }
    }


    it = find_if(command.begin(), command.end(),
      [](const pair<string, string>& element){ return element.first == "-seed";});
    if(it != command.end()) {
      ctr->setseed(stoi(it.base()->second));
    } else {
      ctr->setseed(chrono::system_clock::now().time_since_epoch().count());
    }
    it = find_if(command.begin(), command.end(),
      [](const pair<string, string>& element){ return element.first == "-load";});
    if(it != command.end()) {
      auto sf = make_unique<Setfromfile>(it.base()->second);
      bool check = ctr->loadStrategy(sf.get());
      if (check == false) {
        cout << "File does not exist" << endl;
        return;
      }
      
    } else {
      //if do not find command line -load check whether here is -board
      it = find_if(command.begin(), command.end(),
      [](const pair<string, string>& element){ return element.first == "-board";});
      if(it != command.end()) {
        auto fb = make_unique<loadFromBoard>(it.base()->second);
        bool check = ctr->loadStrategy(fb.get());
        if (check == false) {
          cout << "File does not exist" << endl;
          return;
        }
      } else {
        // if both command not found, default randomboard
        it = find_if(command.begin(), command.end(),
          [](const pair<string, string>& element){ return element.first == "-random-board";});
        if(it != command.end()) {
          auto rl = make_unique<randomLoad>();
          ctr->loadStrategy(rl.get());
        } else {
          auto fb = make_unique<loadFromBoard>("layout.txt");
          ctr->loadStrategy(fb.get());
          if (check == false) {
            cout << "File does not exist" << endl;
            return;
          }
        }
      }
    }
    ctr->print();
    state = ctr->play();
  }
  return 0;
}
