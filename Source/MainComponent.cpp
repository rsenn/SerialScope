/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
    setSize (600, 400);
    
    try {
        serialPort = new serial::Serial("COM14", 38400);
    } catch (const  serial::PortNotOpenedException& e) {
    	AlertWindow::showMessageBox (AlertWindow::InfoIcon, "Info!", "Failed to open serial port");
    //} catch(const serial::IOException& s_io_e) {
    } catch( const std::exception& e) {
      	AlertWindow::showMessageBox (AlertWindow::WarningIcon , "Exception", e.what());
    }
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff001F36));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
