// universal structs
#ifndef UNIVERSALSTRUCTURES_H
#define UNIVERSALSTRUCTURES_H

#define NUMBER_OF_WAVES_PER_TRIGGER			100
#define DEFAULT_NUMBER_OF_SAMPLES_PER_WAVE			64

struct waveformDatum
{
	// Need to check the data to be okay with shorts here...
	float currentThreshold;
	float waveSamples[NUMBER_OF_WAVES_PER_TRIGGER][DEFAULT_NUMBER_OF_SAMPLES_PER_WAVE];
	unsigned int tickStamps[NUMBER_OF_WAVES_PER_TRIGGER];
	unsigned short channelNumber;
	unsigned short unitNumber;
};

Q_DECLARE_METATYPE(waveformDatum)

#endif