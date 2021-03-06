/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINEDITOR_H_C02274F9__
#define __PLUGINEDITOR_H_C02274F9__

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "MainPanel.h"

//==============================================================================
/**
*/

class SimpleFftAudioProcessorEditor  : public AudioProcessorEditor
{
	
public:
	
    SimpleFftAudioProcessorEditor (SimpleFftAudioProcessor* ownerFilter);
    ~SimpleFftAudioProcessorEditor();

    //==============================================================================
	
    // This is just a standard Juce paint method...
    void paint (Graphics& g);
	
private:
	
	MainPanel* panel;
};


#endif  // __PLUGINEDITOR_H_C02274F9__
