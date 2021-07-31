#include "humanPlayer.h"

void humanPlayer::chooseInt(int n) {
  while (true) {
    if (std::cin >> n) {
      break;
    }
  }
}