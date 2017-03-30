// g++ -o SerialTest Source/SerialTest.cpp  -ISource/serial/include


#include "serial/include/serial/serial.h"
#include <iostream>

using namespace serial;

int main(int argc, char *argv[]) {

  Serial sport("COM1");

  if(!sport.isOpen()) {
  
    std::cerr << "Port not open" << std::endl;
    return 1;
  }


return 0;
}