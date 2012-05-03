#ifndef RTVTGLOBALDEFINITIONS_H
#define RTVTGLOBALDEFINITIONS_H

#define USES_TWO_WIRE_ADDRESSING

#ifdef USES_TWO_WIRE_ADDRESSING
    #define DEFAULT_NUM_CHANNELS_IN_DATA            101//33												// The is the number of channels in the data + 1 for framesynch
    #define DEFAULT_NUM_CHANNEL_VIEWS               100//32
    #define SAMPLE_FRAME_LENGTH                     12
    #define DEFAULT_SYNCH_CHANNEL                   101//33	// 0 == no synch channel is set - this is not really used right now...
    #define STORAGE_BUFFER_LENGTH                   20480000//102400000 // == 100MB	// 51200000 = 50Mb // 20480000 = (16 seconds per channel)
	#define DEFAULT_WIRE_ADDRESSING					2
	#define SYSTEM_CLOCK_RATE						24000000//24000000//13560000//24000000 //13.56 MHz	
#endif
#ifdef USES_FOUR_WIRE_ADDRESSING
    #define DEFAULT_NUM_CHANNELS_IN_DATA            16												// The is the number of channels in the data + 1 for framesynch
    #define DEFAULT_NUM_CHANNEL_VIEWS               16
    #define SAMPLE_FRAME_LENGTH                     24
    #define DEFAULT_SYNCH_CHANNEL                   16	// 0 == no synch channel is set - this is not really used right now...
    #define STORAGE_BUFFER_LENGTH                   20480000 //40680000 // 40680000000==30 seconds/ch	// 51200000 = 50Mb // 20480000 = (1.6 seconds per channel)
	#define DEFAULT_WIRE_ADDRESSING					4
	#define SYSTEM_CLOCK_RATE						13560000 //13.56 MHz
#endif

#define TWO_WIRE_SAMPLE_FRAME_LENGTH                12
#define FOUR_WIRE_SAMPLE_FRAME_LENGTH               24
#define DATA_RATE                                   SYSTEM_CLOCK_RATE/SAMPLE_FRAME_LENGTH/DEFAULT_NUM_CHANNELS_IN_DATA	// 40 Ksps

#define BACK_BUFFER_LENGTH                          2048000															// (100ms) 56500 = 1ms // was using 1280000 on jan182011
#define DRAW_BUFFER_LENGTH                          8000															//512000		// 512000// 1.6ms second for each channel
#define DRAW_FRAME_LENGTH                           2000//BACK_BUFFER_LENGTH/2/DEFAULT_NUM_CHANNELS_IN_DATA/4				// How much to pull from the drawingBuffer for immediate display (512000/16)
#define AUDIO_BUFFER_LENGTH                         40000															// 1/2 second of audio data for one channel
#define CHANNEL_BUFFER_LENGTH                       STORAGE_BUFFER_LENGTH/DEFAULT_NUM_CHANNELS_IN_DATA

#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
	#define OS_WIN
#else
	#define IS_MACOSX
#endif

#ifdef OS_WIN
	#define	USE_USB
	#define	IS_WINDOWS_PC // For PC specific calls / paths
#endif

//#define USE_QWT_PLOT

#ifdef USE_USB
    #define USE_HS_USB
#endif

/*	Make some defines incase we want to use them - 
	should not need to for these since code should be amp 
	independant - just need # of channels 
*/
#define AMP_LITLE_PEARL				0			// definition for using big pearl - 16ch
#define AMP_BIG_PEARL				1			// definition for using big pearl - 100ch

#define CONTROLLER_MULTIPLIER		2			// RChip requires *2 multiplier, YFP is 1

#define FILE_DATA_PATH_TYPE			0
#define HSUSB_DATA_PATH_TYPE		1
#define NI_CEREBUS_DATA_PATH_TYPE	2

#define TEST_VECTOR_DATA_TYPE		0
#define BIC_DATA_TYPE				1
#define FILE_DATA_TYPE				2

// For channel views
#define WAVE_AND_CONTINUOUS_VIEW_TYPE	1;
#define WAVE_VIEW_TYPE					0;

#define MAX_NUMBER_OF_FILTERS		10
#define MAX_DATA_TO_FILTER			BACK_BUFFER_LENGTH+1002	// Maximum length of data that would ever be filtered. Set to 

#define FOUR_WIRE_ADDRESSING           4
#define TWO_WIRE_ADDRESSING            2

#define ADC_RANGE                       2.4

/**** Definitions from the old Buffer Control Code */

#define NIBUFFERLEN				80000	// Two second buffer length - do filter/empty every second?
//#define MAX_DATA_TO_FILTER		41002	// Maximum length of data that would ever be filtered. 
#define OVERLAYSIZE				800		// Maximum number of samples in an overlay plot; used to set array sizes

// Default run parameters may be overridden by user

#define SAVELEN			20000000	//20000000//400000	// When storing data to a file, save this number of samples as default
#define	DISPTIME		0.04		// Seconds before writing over a display

// Sensor gain is also defined in FirKernels.h and if changed must be changed both places
#define PEARL
#define SENSORMEAN    1.45	// Mean output of sensor under nominal conditions
// Work-around for scaling raw data to use in audio output

#define RAWMEAN		2526

#endif // RTVTGLOBALDEFINITIONS_H
