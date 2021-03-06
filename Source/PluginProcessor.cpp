/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================

SimpleFftAudioProcessor::SimpleFftAudioProcessor()
{
	fft = NULL;
}

SimpleFftAudioProcessor::~SimpleFftAudioProcessor()
{
	deleteAndZero(fft);
}

//==============================================================================

const String SimpleFftAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int SimpleFftAudioProcessor::getNumParameters()
{
	//return 1 parameter (in this case, gain)
    return 1;
}

float SimpleFftAudioProcessor::getParameter (int index)
{
	//this is relative to the value given in MainPanel.cpp
	
	if (index == 3)
		return gain;
	
    return 0.0f;
}

void SimpleFftAudioProcessor::setParameter (int index, float newValue)
{	
	//set gain to value recieved from control at index 3
	
	if(index == 3)
		gain = newValue;
}

const String SimpleFftAudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String SimpleFftAudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String SimpleFftAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String SimpleFftAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool SimpleFftAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool SimpleFftAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool SimpleFftAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool SimpleFftAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

int SimpleFftAudioProcessor::getNumPrograms()
{
    return 0;
}

int SimpleFftAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleFftAudioProcessor::setCurrentProgram (int index)
{
}

const String SimpleFftAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void SimpleFftAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================

void SimpleFftAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	
	// this seems to work for size of the fft, even though we use buffer.getNumSamples() later
	
    int bufsize = samplesPerBlock; 
		
	/* likewise, allocating memory for this complex variable also seems to work OK using the
	 samplesPerBlock in place of buffer.getNumSamples() */
	
	fftData = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * bufsize);	
	
	/* instantiating FFT here seems to work OK, rather than in processBlock where I sometimes got 
	 memory error messages in Logic */
	
	if(fft == NULL) {
		
		fft = new FastFourierTransformer(bufsize);
	}
	
	gain = 1.0;		// initialize variables for gain control
	oldGain = 0.0;
		
}

void SimpleFftAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
	
	deleteAndZero(fft);
}

void SimpleFftAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)

{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
	
	int    bufsize = buffer.getNumSamples();	
	
	float  gainStep = (gain - oldGain) / bufsize;	//local variable for incrementing gain	
	
//main process loop
	
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
	{
		
        float* channelData = buffer.getSampleData (channel);		
		
		fft->processForward(channelData, fftData, bufsize);	 //fft
		
		fft->gainFFT(fftData, oldGain, gainStep, bufsize);	 // FFT gain control - moved into FFT class
					
		fft->processBackward(fftData, channelData, bufsize); // inverse fft
		
    }
	
	oldGain = gain;
		
    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
	
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, bufsize);
    }
	
}

//==============================================================================

bool SimpleFftAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SimpleFftAudioProcessor::createEditor()
{
    return new SimpleFftAudioProcessorEditor (this);
}

//==============================================================================

void SimpleFftAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SimpleFftAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleFftAudioProcessor();
}
