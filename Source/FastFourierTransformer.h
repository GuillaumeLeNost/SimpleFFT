/*
  ==============================================================================

    FastFourierTransformer.h
    Created: 3 Aug 2012 8:13:37am
    Author:  Martin Klang

  ==============================================================================
*/

#define USE_MATH_DEFINES

#include "fftw3.h"
#include "math.h"

#ifndef __FASTFOURIERTRANSFORMER_H_9F2E8A4F__
#define __FASTFOURIERTRANSFORMER_H_9F2E8A4F__

// fft class

class FastFourierTransformer {

// class methods
	
public:
	
	FastFourierTransformer(int bufSize);
	~FastFourierTransformer();
	
	void processForward(float* channelData, float* fftData, int bufSize);
	void processBackward(float* fftData, float* channelData, int bufSize);
	
	void freqDomainGain(float* fftData, int bufSize, float gain);
	
	void poltocarX (float Pangle, float Pradius);
	void poltocarY (float Pangle, float Pradius);
	void cartopolAngle (float* Cx, float* Cy);
	void cartopolRadius (double Cx, double Cy);
	
						
// member variables
	
private:
	
	fftw_complex    *data, *fft_result, *ifft_result, *fft_temp;	
	fftw_plan       plan_forward, plan_backward;
	float           fftGain, oldFftGain;
	float			*magnitude[];
	float			phase[];
	int             i;
	
};



#endif  // __FASTFOURIERTRANSFORMER_H_9F2E8A4F__
