# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

CC = gcc
CXX = g++
CHOST = $(shell $(CROSS_COMPILE)$(CC) -dumpmachine)
CFLAGS = -I../../Sources/JUCE-new/modules -I. -I JuceLibraryCode $(shell $(CROSS_COMPILE)pkg-config --cflags freetype2)
CXXFLAGS = $(CFLAGS)
LDFLAGS = -static-libgcc -static-libstdc++
LIBS = $(shell $(CROSS_COMPILE)pkg-config --libs freetype2)
DEFS = 

SYSTEM := $(word 2,$(subst -, ,$(CHOST)))
ifeq ($(SYSTEM),w64)
  SYSTEM := $(word 3,$(subst -, ,$(CHOST)))
endif
ifeq ($(SYSTEM),pc)
  SYSTEM := $(word 3,$(subst -, ,$(CHOST)))
endif

$(info CHOST: $(CHOST))
$(info SYSTEM: $(SYSTEM))

OUTDIR := build/$(CHOST)
BINDIR := $(OUTDIR)
LIBDIR := $(OUTDIR)
ifeq ($(CONFIG),Debug)
  OBJDIR := $(OUTDIR)/Debug
  DEFS += -DDEBUG=1 -D_DEBUG=1 -UNDEBUG
  CFLAGS += -g -ggdb -O0
endif

ifeq ($(CONFIG),Release)
  OBJDIR := $(OUTDIR)/Release
  DEFS += -UDEBUG -DNDEBUG=1
  CFLAGS += -g -Wall -O3
endif

ifeq ($(SYSTEM),mingw32)
  DEFS += -D__MINGW__=1 -DJUCE_MINGW=1  
  LDFLAGS += -mwindows -static-libgcc -static-libstdc++
  LIBS +=  -lcomdlg32 -lgdi32 -lgdiplus -limm32 -lole32 -loleaut32 -lshell32 -lshlwapi -luuid -lversion -lwininet -lwinmm -lws2_32 -lwsock32 -lopengl32
endif

ifeq ($(SYSTEM),linux)
  DEFS += -DLINUX=1
endif

SerialScope_OBJECTS = $(OBJDIR)/list_ports_linux.o $(OBJDIR)/list_ports_osx.o $(OBJDIR)/list_ports_win.o $(OBJDIR)/unix.o $(OBJDIR)/win.o $(OBJDIR)/serial.o $(OBJDIR)/Oscilloscope.o $(OBJDIR)/MainComponent.o $(OBJDIR)/Main.o $(OBJDIR)/BinaryData.o $(OBJDIR)/juce_core.o $(OBJDIR)/juce_events.o $(OBJDIR)/juce_graphics.o $(OBJDIR)/juce_data_structures.o $(OBJDIR)/juce_gui_basics.o $(OBJDIR)/juce_gui_extra.o $(OBJDIR)/juce_cryptography.o $(OBJDIR)/juce_video.o $(OBJDIR)/juce_opengl.o

all: $(OBJDIR) $(BINDIR)/SerialScope
$(OBJDIR):
	mkdir -p $@

$(BINDIR)/SerialScope: $(OBJDIR)/list_ports_linux.o $(OBJDIR)/list_ports_osx.o $(OBJDIR)/list_ports_win.o $(OBJDIR)/unix.o $(OBJDIR)/win.o $(OBJDIR)/serial.o $(OBJDIR)/Oscilloscope.o $(OBJDIR)/MainComponent.o $(OBJDIR)/Main.o $(OBJDIR)/BinaryData.o $(OBJDIR)/juce_core.o $(OBJDIR)/juce_events.o $(OBJDIR)/juce_graphics.o $(OBJDIR)/juce_data_structures.o $(OBJDIR)/juce_gui_basics.o $(OBJDIR)/juce_gui_extra.o $(OBJDIR)/juce_cryptography.o $(OBJDIR)/juce_video.o $(OBJDIR)/juce_opengl.o
	$(CXX) $(LDFLAGS) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJDIR)/list_ports_linux.o: Source/serial/src/impl/list_ports/list_ports_linux.cc
	$(CXX) $(DEFS) $(CXXFLAGS) -c -o "$@" "$<"

$(OBJDIR)/list_ports_osx.o: Source/serial/src/impl/list_ports/list_ports_osx.cc
	$(CXX) $(DEFS) $(CXXFLAGS) -c -o "$@" "$<"

$(OBJDIR)/list_ports_win.o: Source/serial/src/impl/list_ports/list_ports_win.cc
	$(CXX) $(DEFS) $(CXXFLAGS) -c -o "$@" "$<"

$(OBJDIR)/unix.o: Source/serial/src/impl/unix.cc
	$(CXX) $(DEFS) $(CXXFLAGS) -c -o "$@" "$<"

$(OBJDIR)/win.o: Source/serial/src/impl/win.cc
	$(CXX) $(DEFS) $(CXXFLAGS) -c -o "$@" "$<"

$(OBJDIR)/serial.o: Source/serial/src/serial.cc
	$(CXX) $(DEFS) $(CXXFLAGS) -c -o "$@" "$<"

$(OBJDIR)/Oscilloscope.o: Source/Oscilloscope.cpp
	$(CXX) $(DEFS) $(CXXFLAGS) -c -o "$@" "$<"

$(OBJDIR)/MainComponent.o: Source/MainComponent.cpp
	$(CXX) $(DEFS) $(CXXFLAGS) -c -o "$@" "$<"

$(OBJDIR)/Main.o: Source/Main.cpp
	$(CXX) $(DEFS) $(CXXFLAGS) -c -o "$@" "$<"

$(OBJDIR)/BinaryData.o: JuceLibraryCode/BinaryData.cpp
	$(CXX) $(DEFS) $(CXXFLAGS) -c -o "$@" "$<"

$(OBJDIR)/juce_core.o: ../../Sources/JUCE-new/modules/juce_core/juce_core.cpp
	$(CXX) $(DEFS) $(CXXFLAGS) -c -o "$@" "$<"

$(OBJDIR)/juce_events.o: ../../Sources/JUCE-new/modules/juce_events/juce_events.cpp
	$(CXX) $(DEFS) $(CXXFLAGS) -c -o "$@" "$<"

$(OBJDIR)/juce_graphics.o: ../../Sources/JUCE-new/modules/juce_graphics/juce_graphics.cpp
	$(CXX) $(DEFS) $(CXXFLAGS) -c -o "$@" "$<"

$(OBJDIR)/juce_data_structures.o: ../../Sources/JUCE-new/modules/juce_data_structures/juce_data_structures.cpp
	$(CXX) $(DEFS) $(CXXFLAGS) -c -o "$@" "$<"

$(OBJDIR)/juce_gui_basics.o: ../../Sources/JUCE-new/modules/juce_gui_basics/juce_gui_basics.cpp
	$(CXX) $(DEFS) $(CXXFLAGS) -c -o "$@" "$<"

$(OBJDIR)/juce_gui_extra.o: ../../Sources/JUCE-new/modules/juce_gui_extra/juce_gui_extra.cpp
	$(CXX) $(DEFS) $(CXXFLAGS) -c -o "$@" "$<"

$(OBJDIR)/juce_cryptography.o: ../../Sources/JUCE-new/modules/juce_cryptography/juce_cryptography.cpp
	$(CXX) $(DEFS) $(CXXFLAGS) -c -o "$@" "$<"

$(OBJDIR)/juce_video.o: ../../Sources/JUCE-new/modules/juce_video/juce_video.cpp
	$(CXX) $(DEFS) $(CXXFLAGS) -c -o "$@" "$<"

$(OBJDIR)/juce_opengl.o: ../../Sources/JUCE-new/modules/juce_opengl/juce_opengl.cpp
	$(CXX) $(DEFS) $(CXXFLAGS) -c -o "$@" "$<"

