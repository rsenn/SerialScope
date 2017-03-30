TARGET = SerialTest
QT = core-private

INCLUDEPATH += $$PWD/Source/serial/include

SOURCES = \
  Source/SerialTest.cpp \
  Source/serial/src/impl/unix.cc \
  Source/serial/src/impl/win.cc \
  Source/serial/src/serial.cc \
  Source/serialib/serialib.cpp

#SOURCES +=  Source/serial/src/impl/list_ports/list_ports_linux.cc  Source/serial/src/impl/list_ports/list_ports_osx.cc  Source/serial/src/impl/list_ports/list_ports_win.cc
  
LIBS_PRIVATE += -lgdi32 -lcomdlg32 -lsetupapi
