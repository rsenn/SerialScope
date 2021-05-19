#include "Oscilloscope.h"

void
Oscilloscope::pushBuffer(const float* data, int numSamples) {
  for(int i = 0; i < numSamples; ++i) buffer[++writePos % buffer.size()] = data[i];
}

void
Oscilloscope::resized() {
  // This is called when the MainContentComponent is resized.
  // If you add any child components, this is where you should
  // update their positions.
  // this->setBoundsInset(BorderSize<int>(10,10,getWidth()-10,getHeight()-10));
}
void
Oscilloscope::paint(Graphics& g) {
  g.fillAll(Colour(0xffa0a0a0));
  juce::Rectangle<int> r = getLocalBounds();
  Path path;
  path.startNewSubPath(0, 0.5 * r.getHeight());
  const float bufferYscale = 3.0;
  int paintPos = 1;
  while(paintPos < buffer.size()) {
    if(buffer[paintPos] > buffer[paintPos - 1] && buffer[paintPos] > 0 && buffer[paintPos - 1] < 0)
      break;

    ++paintPos;
  }
  const int posOffset = paintPos;
  while(paintPos < buffer.size()) {
    Point<float> p((paintPos - posOffset) * r.getWidth() / paintSize,
                   0.5 * ((bufferYscale * buffer[paintPos]) + 1) * r.getHeight());
    path.lineTo(p);
    ++paintPos;
  }
  g.setColour(Colours::lime);
  g.strokePath(path, PathStrokeType(2.0f));
}
