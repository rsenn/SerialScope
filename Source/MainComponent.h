/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "JuceHeader.h"
#include "serialib/serialib.h"
#include "Oscilloscope.h"

#include <deque>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent : public Component, private Timer {
public:
  //==============================================================================
  MainContentComponent();
  ~MainContentComponent();

  bool startPlotting(const String& port);

  void paint(Graphics&) override;
  void resized() override;

  Oscilloscope&
  getOscilloscope() {
    return *scope;
  }

private:
  void fillQueue();
  void timerCallback() override;

  std::deque<unsigned char> recvQueue;

  unsigned int value;

  Oscilloscope* scope;

 serialib * serialPort;

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};
#endif // MAINCOMPONENT_H_INCLUDED
