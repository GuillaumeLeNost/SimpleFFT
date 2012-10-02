/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  16 Jul 2012 4:45:47pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-  6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_MAINPANEL_MAINPANEL_9929C8B3__
#define __JUCER_HEADER_MAINPANEL_MAINPANEL_9929C8B3__

//[Headers]     -- You can add your own extra header files here --

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/

class MainPanel  : public Component,
                   public SliderListener
{
public:
	
    //==============================================================================
	
    MainPanel(SimpleFftAudioProcessor* ptr);
    ~MainPanel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);

    //==============================================================================
	
    juce_UseDebuggingNewOperator

private:
	
    //[UserVariables]   -- You can add your own custom variables in this section.

	SimpleFftAudioProcessor* processor;

    //[/UserVariables]

    //==============================================================================
	
    Slider* slider;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
	
    MainPanel (const MainPanel&);
    const MainPanel& operator= (const MainPanel&);
};


#endif   // __JUCER_HEADER_MAINPANEL_MAINPANEL_9929C8B3__
