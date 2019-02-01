#include "Oscilloscope.h"

void Oscilloscope::pushBuffer(const float* data, int numSamples) {
	for (int i = 0; i < numSamples; ++i)
	buffer[++writePos % buffer.size()] = data[i];
}

void Oscilloscope::paint(Graphics& g) {
	g.fillAll(Colours::black);
	juce::Rectangle<int> r = getLocalBounds();
	Path path;
	path.startNewSubPath(0, 0.5 * r.getHeight());
	const float bufferYscale = 3.0;
	int paintPos = 1;
	while (paintPos < buffer.size()) {
		if (buffer[paintPos] > buffer[paintPos - 1] && buffer[paintPos] > 0
				&& buffer[paintPos - 1] < 0)
			break;

		++paintPos;
	}
	const int posOffset = paintPos;
	while (paintPos < buffer.size()) {
		Point<float> p((paintPos - posOffset) * r.getWidth() / paintSize,
				0.5 * ((bufferYscale * buffer[paintPos]) + 1) * r.getHeight());
		path.lineTo(p);
		++paintPos;
	}
	g.setColour(Colours::lime);
	g.strokePath(path, PathStrokeType(2.0f));
}
