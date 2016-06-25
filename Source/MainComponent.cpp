/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
  : scope(new Oscilloscope)
{
    setSize (600, 400);
    
    serialPort = new serialib();


        
    
 	addAndMakeVisible(scope);

}

MainContentComponent::~MainContentComponent()
{
}

bool MainContentComponent::startPlotting(const String& port) {
	int ret;
	String portstr = "\\\\.\\" + port;
	if ((ret = serialPort->Open(portstr.toStdString().c_str(), 38400)) != 1) {
		AlertWindow::showMessageBox(AlertWindow::InfoIcon, "Info!",
				"Failed to open serial port: " + String(ret));
		return false;
	}
	std::cerr << "Serial port open" << std::endl;
	/*     recvBytes.resize(3);
	 recvIndex = 0;
	 */
	startTimer(40);
	return true;
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff001F36));
/*
    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);*/
    
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    scope->setBoundsInset(BorderSize<int>(40, 40, 200, 40));
}

void MainContentComponent::fillQueue() {
	char ch;
	int ret;
	while ((ret = serialPort->ReadChar(&ch, 10)) == 1 && recvQueue.size() <= 5) {
		//std::cerr << "Queued byte (" << recvQueue.size() << "): " <<  String::formatted("0x%02x", (unsigned)ch) << std::endl;
		recvQueue.push_back(ch);
	}
}

//==========================================================================
void MainContentComponent::timerCallback()
{

      fillQueue();


      while(recvQueue.size() >= 3) {

          unsigned int newval;

          if(recvQueue.front() != 0xff) {
              recvQueue.pop_front();
              continue;
          }
          
          
          recvQueue.pop_front();
          newval = recvQueue.front();
          if(newval & 0xc0) continue;
          newval <<= 6;
          recvQueue.pop_front();
          if(recvQueue.front() & 0xc0) continue;
          newval |= recvQueue.front();
          recvQueue.pop_front();
          
          if(newval != value) {
//                 std::cerr << "Got new value: " << String::formatted("0x%04x",newval) << std::endl;
                 value = newval;
          }
      }

  }
