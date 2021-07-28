#include <iostream>
#include <fstream>

void individual(std::ostream &out) {
  out << "hello" << std::endl;
}

int main() {
  individual(std::cout);
}