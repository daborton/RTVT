#include "rtvtfiltercontroller.h"

RTVTFilterController::RTVTFilterController()
{
}

void RTVTFilterController::decimate(const int from, int to)
{
	// rawData[] will be filled with one second of 16-bit PCM data sampled at 44.1 KHz

	int SAMPLERATE = from;
	int size = from;
	signed long rawData[44100]; 

	int RATIO = (SAMPLERATE/to);
	int size2 = (size/RATIO);
	short* downsampledData = new short[size2];
	signed long summe = 0;
	
	for(int i = 0; i < size; i++)
	{
		summe += rawData[i];
		
		if((i%RATIO) == 0)
			downsampledData[i/RATIO] = summe/RATIO;

		summe = 0;
	}
}