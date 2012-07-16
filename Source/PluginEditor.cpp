/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SimpleFftAudioProcessorEditor::SimpleFftAudioProcessorEditor (SimpleFftAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
	panel = new MainPanel(ownerFilter);
	addAndMakeVisible(panel);
	
    // This is where our plugin's editor size is set.
    setSize (400, 300);
}

SimpleFftAudioProcessorEditor::~SimpleFftAudioProcessorEditor()
{
	delete panel;
}

//==============================================================================
void SimpleFftAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);
    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!",
                      0, 0, getWidth(), getHeight(),
                      Justification::centred, 1);
}
