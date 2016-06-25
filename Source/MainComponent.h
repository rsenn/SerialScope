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

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component, private Timer
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    bool startPlotting(const String& port) {
    int ret;
    String portstr = "\\\\.\\"+port;
    
        if((ret = serialPort->Open(portstr.toStdString().c_str(), 38400)) != 1) {
               AlertWindow::showMessageBox (AlertWindow::InfoIcon, "Info!", "Failed to open serial port: " + String(ret));               
               return false;
        }
        
        
            std::cerr << "Serial port open" << std::endl;
             	
        recvBytes.resize(3);
        recvIndex = 0;
        
      startTimer (40);
      return true;
    
    }
    
    
    void paint (Graphics&) override;
    void resized() override;
    
    Oscilloscope&
    getOscilloscope() { return *scope; }

private:
    //==========================================================================
    void timerCallback() override
    {
        int ret;
        char ch;
        if((ret = serialPort->ReadChar(&ch, 100)) == 1) {
            
            std::cerr << "Got byte: " << (int)ch << std::endl;
            
            if(ch == 0xff) recvIndex = 0;
            
            recvBytes.getReference(recvIndex) = ch;
            ++recvIndex;
            
            if(recvIndex == 3) {
                int16_t val = recvBytes[1] * 256 + recvBytes[2];
                float fval = (float)val / 32768 - 1.0;
                
                scope->pushBuffer(&fval, 1);
            }
            
            recvIndex %= 3;            
        }
                   std::cerr << "ReadChar() = " << ret << std::endl;
    }
    
    Array<char> recvBytes;
    int recvIndex;

    ScopedPointer<Oscilloscope> scope;

    ScopedPointer<serialib> serialPort;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
