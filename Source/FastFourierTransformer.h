/*
  ==============================================================================

    FastFourierTransformer.h
    Created: 3 Aug 2012 8:13:37am
    Author:  Martin Klang

  ==============================================================================
*/

#ifndef __FASTFOURIERTRANSFORMER_H_9F2E8A4F__
#define __FASTFOURIERTRANSFORMER_H_9F2E8A4F__

class FastFourierTransformer {

public:
	
	void processForward(float* channelData, double* fftData, int bufSize);
	void processBackward(double* fftData, float* channelData, int bufSize);
	
	
	
};



#endif  // __FASTFOURIERTRANSFORMER_H_9F2E8A4F__
