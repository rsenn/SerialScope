/*
  ==============================================================================

   This file is part of the Projucer live coding demo created for
   the JUCE Summit 2015.
   Copyright (c) 2015 - ROLI Ltd.

   Use this code at your own risk & have some fun with C++ live coding!

   This code is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.

  ==============================================================================
*/

#include <array>

#include "JuceHeader.h"

#ifndef OSCILLOSCOPE_H_INCLUDED
#define OSCILLOSCOPE_H_INCLUDED

class Oscilloscope : public Component, private Timer {
public:
  //==========================================================================
  Oscilloscope() : writePos(0) { startTimer(40); }

  //==========================================================================
  void pushBuffer(const float* data, int numSamples);

  //==========================================================================
  void paint(Graphics& g) override;

  void resized();

private:
  //==========================================================================
  void
  timerCallback() override {
    repaint();
  }

  //==========================================================================
  std::array<float, 1024> buffer;
  std::size_t writePos;

  const int bufferSize = 16384;
  const int paintSize = 256;
};
#endif // OSCILLOSCOPE_H_INCLUDED
