/*
  ==============================================================================

    FastFourierTransformer.cpp
    Created: 3 Aug 2012 8:13:37am
    Author:  Martin Klang

  ==============================================================================
*/

#include "fftw3.h"
#include "FastFourierTransformer.h"

//--------------------------------------------------------------

//polar to cartesian conversion functions

double FastFourierTransformer::poltocarX ( double angle, double radius) { 
	
	return cos(angle) * radius;
}

//--------------------------------------------------------------

double FastFourierTransformer::poltocarY ( double angle, double radius) {
	
	return sin(angle) * radius ;
	
}

//--------------------------------------------------------------

//cartesian to polar conversion functions

double FastFourierTransformer::cartopolRadius ( double x, double y) {
		
	return sqrt(y * y + x * x);
	
}

//--------------------------------------------------------------

double FastFourierTransformer::cartopolAngle ( double x, double y)  { 
	
    if (x > 0) { return atan(y/x); }
	if (x < 0 && y >= 0) {return atan(y/x) + M_PI; }
	if (x < 0 && y < 0) {return atan(y/x) - M_PI; }
	if (y > 0) { return M_PI / 2; }
	if (y < 0) { return -M_PI / 2; }
	
	return 0;
	
}

//--------------------------------------------------------------

// simple fft class implementation

// constructor

FastFourierTransformer::FastFourierTransformer(int bufSize) {
	
	data          = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * bufSize);
	fft_result    = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * bufSize);
	ifft_result   = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * bufSize);
	
	plan_forward  = fftw_plan_dft_1d(bufSize, data, fft_result, FFTW_FORWARD, FFTW_MEASURE);
	plan_backward = fftw_plan_dft_1d(bufSize, fft_result, ifft_result, FFTW_BACKWARD, FFTW_MEASURE);	
	
}

//-------------------------------------------------------------

// destructor

FastFourierTransformer::~FastFourierTransformer() {
	
	fftw_free(data);
	fftw_free(fft_result);
	fftw_free(ifft_result);
	
	
	fftw_destroy_plan(plan_forward);	
	fftw_destroy_plan(plan_backward);
	
}

//--------------------------------------------------------------

// initialize FFT variables

void FastFourierTransformer::initFFT(int bufSize) {
	
	for(i = 0; i < bufSize; i++) {
	
		data[i][0]			= 0.0;
		data[i][1]			= 0.0;
		fft_result[i][0]	= 0.0;
		fft_result[i][1]	= 0.0;
		ifft_result[i][0]	= 0.0;
		ifft_result[i][1]	= 0.0;
			
	}	
	
}

//--------------------------------------------------------------

// fft conversion method

void FastFourierTransformer::processForward(float* channelData, fftw_complex* fftData, int bufSize) {
	
	for(i = 0; i < bufSize; i++) {
		
		data[i][0] = channelData[i];       // stick your audio samples in here   
		data[i][1] = 0.0;                  // use this if your data is complex valued
	}
		
	fftw_execute(plan_forward);
	
	for (i = 0; i < bufSize; i++) {
		
		fftData[i][0] = fft_result[i][0];
		fftData[i][1] = fft_result[i][1];
				
	}
	
}

//--------------------------------------------------------------

// inverse fft conversion method

void FastFourierTransformer::processBackward(fftw_complex* fftData, float* channelData, int bufSize) {
			
	for(i = 0; i < bufSize; i++) {
		
		fft_result[i][0] = fftData[i][0];        // stick your fft data in here!
		fft_result[i][1] = fftData[i][1];        // use this if your data is complex valued
	}	
	
	fftw_execute(plan_backward);
		
	for(i = 0; i < bufSize; i++) {
	
		channelData[i] = ifft_result[i][0] / bufSize; 
		
		//it was crunchy because we didn't divide by bufSize originally - see code below	
	}	
	
}

//--------------------------------------------------------------
		
/*  Demo code

void transform(){

int SIZE = 4;

fftw_complex    *data, *fft_result, *ifft_result;
fftw_plan       plan_forward, plan_backward;
int             i;

data        = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * SIZE);
fft_result  = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * SIZE);
ifft_result = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * SIZE);

plan_forward  = fftw_plan_dft_1d(SIZE, data, fft_result,
                                 FFTW_FORWARD, FFTW_ESTIMATE);
plan_backward = fftw_plan_dft_1d(SIZE, fft_result, ifft_result,
                                 FFTW_BACKWARD, FFTW_ESTIMATE);


for( i = 0 ; i < SIZE ; i++ ) {
    data[i][0] = 1.0; // stick your audio samples in here
    data[i][1] = 0.0; // use this if your data is complex valued
}


for( i = 0 ; i < SIZE ; i++ ) {
    fprintf( stdout, "data[%d] = { %2.2f, %2.2f }\n",
			i, data[i][0], data[i][1] );
}

fftw_execute( plan_forward );


for( i = 0 ; i < SIZE ; i++ ) {
    fprintf( stdout, "fft_result[%d] = { %2.2f, %2.2f }\n",
			i, fft_result[i][0], fft_result[i][1] );
}

fftw_execute( plan_backward );


for( i = 0 ; i < SIZE ; i++ ) {
    fprintf( stdout, "ifft_result[%d] = { %2.2f, %2.2f }\n",
			i, ifft_result[i][0] / SIZE, ifft_result[i][1] / SIZE );
}


fftw_destroy_plan( plan_forward );
fftw_destroy_plan( plan_backward );

fftw_free( data );
fftw_free( fft_result );
fftw_free( ifft_result );
}

*/