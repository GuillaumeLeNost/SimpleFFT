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
	
	void processForward(float* channelData, fftw_complex* fftData, int bufSize);
	void processBackward(fftw_complex* fftData, float* channelData, int bufSize);
	
	void freqDomainGain(int bufSize, float gain);
	
	double poltocarX (double Pangle, double Pradius);
	double poltocarY (double Pangle, double Pradius);
	double cartopolAngle (double Cx, double Cy);
	double cartopolRadius (double Cx, double Cy);
	
						
// member variables
	
private:
	
	fftw_complex    *data, *fft_result, *ifft_result;	
	fftw_plan       plan_forward, plan_backward;
	double          fftGain, oldFftGain;
	double			magnitude[];
	double			phase[];
	int             i;
	
};



#endif  // __FASTFOURIERTRANSFORMER_H_9F2E8A4F__
