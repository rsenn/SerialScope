#include "Oscilloscope.h"

void Oscilloscope::pushBuffer(const float* data, int numSamples) {
	for (int i = 0; i < numSamples; ++i)
	buffer[++writePos % buffer.size()] = data[i];
}
