// g++ -o SerialTest Source/SerialTest.cpp  -ISource/serial/include

#include "serial/include/serial/serial.h"
#include <iostream>
#include <windows.h>

using namespace serial;

Serial sport("COM1");

uint64_t
now() {
  static LARGE_INTEGER s_frequency;
  static bool s_use_qpc = QueryPerformanceFrequency(&s_frequency);
  if(s_use_qpc) {
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

void
printDSR() {
  static int prevDSR = -2;
  int DSR = (int)sport.getDSR();
  if(prevDSR != DSR) {
    std::cout << "DSR = " << DSR << std::endl;
    prevDSR = DSR;
  }
}

int
main(int argc, char* argv[]) {

  bool rts = false, dtr = false, txd = false;

  if(!sport.isOpen()) {

    std::cerr << "Port not open" << std::endl;
    return 1;
  }

  while(1) {

    uint64_t done = now() + 500;
    sport.setRTS(rts);
    sport.setDTR(dtr);

    while(now() < done) {

      sport.write((const uint8_t*)(txd ? "\xff" : "\x00"), 1);
      // sport.flushOutput();
      printCTS();
      printDSR();
    }

    rts = !rts;
    dtr = !dtr;
    txd = !txd;
  }
  for(;;) {
    printCTS();

    sport.waitForChange();
  }

  return 0;
}
