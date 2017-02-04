TARGET = SerialScope
QT = core-private
INCLUDEPATH += $$PWD/JuceLibraryCode

INCLUDEPATH += $$PWD/../JUCE/modules
INCLUDEPATH += $$PWD/Source/serial/include

SOURCES = \
  JuceLibraryCode/juce_core.cpp \
  JuceLibraryCode/juce_cryptography.cpp \
  JuceLibraryCode/juce_data_structures.cpp \
  JuceLibraryCode/juce_events.cpp \
  JuceLibraryCode/juce_graphics.cpp \
  JuceLibraryCode/juce_gui_basics.cpp \
  JuceLibraryCode/juce_gui_extra.cpp \
  Source/disphelper.c \
  Source/Main.cpp \
  Source/MainComponent.cpp \
  Source/Oscilloscope.cpp \
  Source/serial/examples/serial_example.cc \
  Source/serial/src/impl/list_ports/list_ports_linux.cc \
  Source/serial/src/impl/list_ports/list_ports_osx.cc \
  Source/serial/src/impl/list_ports/list_ports_win.cc \
  Source/serial/src/impl/unix.cc \
  Source/serial/src/impl/win.cc \
  Source/serial/src/serial.cc \
  Source/serialib/serialib.cpp


LIBS_PRIVATE += -lgdi32 -lcomdlg32 -lsetupapi
