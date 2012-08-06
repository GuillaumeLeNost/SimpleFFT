/*
  ==============================================================================

    FastFourierTransformer.h
    Created: 3 Aug 2012 8:13:37am
    Author:  Martin Klang

  ==============================================================================
*/

#ifndef __FASTFOURIERTRANSFORMER_H_9F2E8A4F__
#define __FASTFOURIERTRANSFORMER_H_9F2E8A4F__

#include "fftw3.h"


class FastFourierTransformer {
	
	
public:
	
	FastFourierTransformer(int bufSize);
	~FastFourierTransformer();
	
	void processForward(float* channelData, double* fftData, int bufSize);
	void processBackward(double* fftData, float* channelData, int bufSize);
	
private:
	
	fftw_complex    *data, *fft_result, *ifft_result;	
	fftw_plan       plan_forward, plan_backward;
	int i;
	
};



#endif  // __FASTFOURIERTRANSFORMER_H_9F2E8A4F__
