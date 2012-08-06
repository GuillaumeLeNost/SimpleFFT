/*
  ==============================================================================

    FastFourierTransformer.cpp
    Created: 3 Aug 2012 8:13:37am
    Author:  Martin Klang

  ==============================================================================
*/

#include "fftw3.h"
#include "FastFourierTransformer.h"


FastFourierTransformer::FastFourierTransformer(int bufSize) {
	
	data        = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * bufSize);
	fft_result  = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * bufSize);
	ifft_result = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * bufSize);
	
	
	plan_forward  = fftw_plan_dft_1d(bufSize, data, fft_result, FFTW_FORWARD, FFTW_ESTIMATE);
	plan_backward = fftw_plan_dft_1d(bufSize, data, ifft_result, FFTW_BACKWARD, FFTW_ESTIMATE);	
	
}

FastFourierTransformer::~FastFourierTransformer() {
	fftw_free( data );
	fftw_free( fft_result );
	fftw_free( ifft_result );
	
	
	fftw_destroy_plan( plan_forward);	
	fftw_destroy_plan( plan_backward);		
}


void FastFourierTransformer::processForward(float* channelData, double* fftData, int bufSize) {
	
//	int             i;	
//	data        = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * bufSize);
//	fft_result  = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * bufSize);
//	plan_forward  = fftw_plan_dft_1d(bufSize, data, fft_result, FFTW_FORWARD, FFTW_ESTIMATE);

	for( i = 0 ; i < bufSize ; i++ ) {
		data[i][0] = channelData[bufSize]; // stick your audio samples in here
		data[i][1] = 0.0; // use this if your data is complex valued
	}
	
/*	
	for( i = 0 ; i < bufSize ; i++ ) {
		
		fprintf( stdout, "data[%d] = { %2.2f, %2.2f }\n",		
				i, data[i][0], data[i][1] );
	}
*/
	
	fftw_execute( plan_forward );
	
	
	for( i = 0 ; i < bufSize ; i++ ) {
		//fprintf( stdout, "fft_result[%d] = { %2.2f, %2.2f }\n",
		//		i, fft_result[i][0], fft_result[i][1] );		
		fftData[i] = fft_result[i][0];
	}
	
}

void FastFourierTransformer::processBackward(double* fftData, float* channelData, int bufSize) {
	
//	fftw_complex    *data, *ifft_result;	
//	fftw_plan       plan_backward;
//	int             i;	
	

//	data        = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * bufSize);
//	ifft_result = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * bufSize);
//	plan_backward = fftw_plan_dft_1d(bufSize, data, ifft_result, FFTW_BACKWARD, FFTW_ESTIMATE);
	
	for( i = 0 ; i < bufSize ; i++ ) {
		data[i][0] = fftData[i]; // stick your audio samples in here
		data[i][1] = 0.0; // use this if your data is complex valued
	}	
	
	fftw_execute( plan_backward );
		
	for( i = 0 ; i < bufSize ; i++ ) {
		//fprintf( stdout, "ifft_result[%d] = { %2.2f, %2.2f }\n", 
		//		i, ifft_result[i][0] / bufSize, ifft_result[i][1] / bufSize );		
		fftData[i] = ifft_result[i][0];
	}	
	
}
	
	
/*  Martin demo code

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