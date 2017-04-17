// g++ -o SerialTest Source/SerialTest.cpp  -ISource/serial/include


#include "serial/include/serial/serial.h"
#include <iostream>
#include <windows.h>

using namespace serial;

Serial sport("COM1");

uint64_t now() {
    static LARGE_INTEGER s_frequency;
    static bool s_use_qpc = QueryPerformanceFrequency(&s_frequency);
    if (s_use_qpc) {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        return (1000LL * now.QuadPart) / s_frequency.QuadPart;
    } else {
        return GetTickCount();
    }
}

void
printCTS() {
    static int prevCTS = -2;

    int CTS = (int)sport.getCTS();

    if(prevCTS != CTS) {

        std::cout << "CTS = " << CTS << std::endl;
        prevCTS = CTS;
    }
}

int main(int argc, char *argv[]) {


  if(!sport.isOpen()) {
  
    std::cerr << "Port not open" << std::endl;
    return 1;
  }
  sport.setRTS(true);
    uint64_t done = now() + 2000;

    while(now() < done) {

      sport.write((const uint8_t*)"\x00\xff\xff\xff\xff\xff\xff\xff", 1);
      //sport.flushOutput();
    }


  for(;;) {
    printCTS();

    sport.waitForChange();
  }

return 0;
}
