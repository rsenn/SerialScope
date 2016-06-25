#ifndef JUCE_HEADER_H
#define JUCE_HEADER_H

//#include "JuceLibraryCode/AppConfig.h"

#ifndef JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED
#define JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED 1
#endif


#include "../../Sources/JUCE-new/modules/juce_core/juce_core.h"
#include "../../Sources/JUCE-new/modules/juce_events/juce_events.h"
#include "../../Sources/JUCE-new/modules/juce_graphics/juce_graphics.h"
#include "../../Sources/JUCE-new/modules/juce_data_structures/juce_data_structures.h"
#include "../../Sources/JUCE-new/modules/juce_gui_basics/juce_gui_basics.h"
#include "../../Sources/JUCE-new/modules/juce_gui_extra/juce_gui_extra.h"
#include "../../Sources/JUCE-new/modules/juce_cryptography/juce_cryptography.h"
#include "../../Sources/JUCE-new/modules/juce_video/juce_video.h"
#include "../../Sources/JUCE-new/modules/juce_opengl/juce_opengl.h"

#if ! DONT_SET_USING_JUCE_NAMESPACE
// If your code uses a lot of JUCE classes, then this will obviously save you
// a lot of typing, but can be disabled by setting DONT_SET_USING_JUCE_NAMESPACE.
using namespace juce;
#endif

#if ! JUCE_DONT_DECLARE_PROJECTINFO
namespace ProjectInfo
{
    const char* const  projectName    = "SerialScope";
    const char* const  versionString  = "1.0.0";
    const int          versionNumber  = 0;
}
#endif

#endif //JUCE_HEADER_H
