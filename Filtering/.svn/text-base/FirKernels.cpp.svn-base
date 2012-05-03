/************************************************************************************************

  FirKernels.cpp - holds a series of simple Finite Impulse Response filter functions
		to do basic and decimating FIR filtering in C++.  Written specifically for 
		the BIC project to be included within data capture software for on-line processing.
		Want to reduce MATLAB work because of the awkwardness of the interface.


  Routines: FirBasic(int iFirLength, int iSignalLength, double* dFilter, 
				double* dSignalSource, double* dOut)	// Basic FIR filter using user supplied storage
			FirDecimate(int iFirLength, int iSignalLength, int iStride, double* dFilter, 
				double* dSignalSource, double* dOut)	// Decimating FIR filter using user supplied storage

  *********************************************************************************************/

#include "FirKernels.h"
#include <stdio.h>

#define MAXFILTPTS 501
#define MAXPOSTFILTPTS 201

int FirKernels::FirBasic(int iFirLength, int iSignalLength, double* dFilter, 
		 double* dSignalSource, double* dOut, double *Max, double *Min)  {
	// Basic FIR filter using user supplied storage. Assumes that:
	// 1. The user will give pointers to the incoming and outgoing data where there is 
	//	  sufficient storage that this routine does not have to test array bounds.
	// 2. That it is acceptable not to produce as many outputs as inputs but just outputs =
	//	  inputs - filter length + 1. A circular version of these routines will address other problem.
	// 3. The number of filter taps will be odd so that can reduce the number of loop tests.
	// 4. Calculates max and min values only after a filter length into data to avoid error
	//	  from the start of each buffer.

	// Returns 0 for success and 1 for inadequate data.


	int i, j, iOutCount, jMax, iFirIndex, iSigIndex, iDebugMax, iBeginMaxMin;
	double dSum, dMax, dMin;	// accumulator variable on stack
	// Calculate the number of expected outputs and check for enough action to justify use

	iOutCount = iSignalLength - iFirLength;	// Might want to eliminate this as recurrent calculation
	jMax = (iFirLength - 1) >> 1;	// Will do loops of 2 multiply adds and finish with 1 extra.
	dMax = -1e6; dMin = +1e6;	// Set variables to capture peak to peak activity

	if (iOutCount < 10) return(1);	// Not enough data to be worth filtering.

	// Set up for max and min limitations
	iBeginMaxMin = iFirLength +5;

	// Double loop to do filtering

	for (i = 0; i < iBeginMaxMin; i++)  {	// Do filtering without max/min for initial steps
		dSum = 0;	// Zero the accumulator
		iFirIndex = 0;
		iSigIndex = i;
		for (j = 0; j < jMax; j++)  {
			// Inner loop over filter coefficients
			//iFirIndex = j << 1;	// Equivalent to 2*j
			//iSigIndex = iFirIndex + i;
			dSum = dFilter[iFirIndex]*dSignalSource[iSigIndex] + dSum;
			iFirIndex += 1;
			iSigIndex += 1;
			dSum = dFilter[iFirIndex]*dSignalSource[iSigIndex] + dSum;
			iFirIndex += 1;
			iSigIndex += 1;
		}
		// Last odd sum
		dSum = dFilter[iFirIndex]*dSignalSource[iSigIndex] + dSum;
		// Store result
		dOut[i] = dSum;
	}

	for (; i < iOutCount; i++)  {	// Finish filtering with max/min
		dSum = 0;	// Zero the accumulator
		iFirIndex = 0;
		iSigIndex = i;
		for (j = 0; j < jMax; j++)  {
			// Inner loop over filter coefficients
			//iFirIndex = j << 1;	// Equivalent to 2*j
			//iSigIndex = iFirIndex + i;
			if(iSigIndex > iOutCount)
				break;
			dSum = dFilter[iFirIndex]*dSignalSource[iSigIndex] + dSum;
			iFirIndex += 1;
			iSigIndex += 1;
			if(iSigIndex > iOutCount)
				break;
			dSum = dFilter[iFirIndex]*dSignalSource[iSigIndex] + dSum;
			iFirIndex += 1;
			iSigIndex += 1;
		}
		// Last odd sum
		dSum = dFilter[iFirIndex]*dSignalSource[iSigIndex] + dSum;
		// Store result
		if(dSum==0)
		{
			int temp = 1;
		}
		dOut[i] = dSum;
		if (dMax < dSum) {dMax = dSum; iDebugMax = i;}
		if (dMin > dSum) dMin = dSum;
	}
	*Max = dMax;	// Pass max and min values to calling program
	*Min = dMin;
	return(0);
}
	
int FirKernels::FirDecimate(int iFirLength, int iSignalLength, int iStride, double* dFilter, 
		 double* dSignalSource, double* dOut, double *Max, double *Min)  {
	// Decimating FIR filter using user supplied storage. Assumes that:
	// 1. The user will give pointers to the incoming and outgoing data where there is 
	//	  sufficient storage that this routine does not have to test array bounds.
	// 2. That it is acceptable not to produce as many outputs as inputs but just outputs =
	//	  inputs - filter length. A circular version of these routines will address other problem.
	// 3. The number of filter taps will be odd so that can reduce the number of loop tests.
	// 4. iStride is the step for decimation through the input set.

	// Returns 0 for success and 1 for inadequate data.


	int i, j, iOutCount, jMax, iFirIndex, iSigIndex, iOutIndex, iBeginMin;
	double dSum, dMax, dMin;	// accumulator variable on stack

	// Calculate the number of expected outputs and check for enough action to justify use

	iOutCount = (iSignalLength - iFirLength);	// Counting output is separate from input - in 
												// decimation this is really input count
	jMax = (iFirLength - 1) >> 1;				// Will do loops of 2 multiply adds and finish with 1 extra.
	iOutIndex = 0;	// Used for indexing data output separately from striding through input

	if (iOutCount < 10) return(1);	// Not enough data to be worth filtering.

	dMax = -1e6; dMin = +1e6;	// Set variables to capture peak to peak activity
	// Double loop to do filtering

	// Set up for max and min limitations
	iBeginMin = iFirLength +5;

	for (i = 0; i < iBeginMin; i +=iStride)  {	// Start filtering without max & min stuff
		dSum = 0;	// Zero the accumulator
		for (j = 0; j < jMax; j++)  {
			// Inner loop over filter coefficients
			iFirIndex = j << 1;	// Equivalent to 2*j
			iSigIndex = iFirIndex + i;
			dSum = dFilter[iFirIndex]*dSignalSource[iSigIndex] + dSum;
			dSum = dFilter[iFirIndex + 1]*dSignalSource[iSigIndex + 1] + dSum;
		}
		// Last odd sum
		dSum = dFilter[iFirIndex + 2]*dSignalSource[iSigIndex + 2] + dSum;
		// Store result
		dOut[iOutIndex] = dSum;
		iOutIndex++; 
	}

	for ( ; i < iOutCount; i +=iStride)  {	// Finish filtering
		dSum = 0;	// Zero the accumulator
		for (j = 0; j < jMax; j++)  {
			// Inner loop over filter coefficients
			iFirIndex = j << 1;	// Equivalent to 2*j
			iSigIndex = iFirIndex + i;
			dSum = dFilter[iFirIndex]*dSignalSource[iSigIndex] + dSum;
			dSum = dFilter[iFirIndex + 1]*dSignalSource[iSigIndex + 1] + dSum;
		}
		// Last odd sum
		dSum = dFilter[iFirIndex + 2]*dSignalSource[iSigIndex + 2] + dSum;
		// Store result
		dOut[iOutIndex] = dSum;
		if (dMax < dSum) dMax = dSum;
		if (dMin > dSum) dMin = dSum;
		iOutIndex++; 
	}
	*Max = dMax;	// Pass max and min values to calling program
	*Min = dMin;
	return(0);
}
	
int FirKernels::SetFilterData(char *czFiltFileName)  {	// Opens file of fir filter data and loads into local storage
	// Returns 0 success, 1 for file open error and 2 for bad data

	FILE *fp_inpdat;	// File pointer for retrieval of filtering data
	char work[512];
	double dWorkVar;
	QString csErrMsg;

	if ((fp_inpdat = fopen(czFiltFileName, "r")) == NULL ) {
		// Error opening file
		iValidFilterDataFlag = 0;
		return(1);
		}
	
	iFilterSize = 0;
	while ((feof(fp_inpdat)) == 0) { // Scan input file until run out of filter coefs.
		if (fgets(work, 256, fp_inpdat) == 0) break;
		if (isalpha((int) work[0]) == 0) {	// This test discards any line beginning with an
			// alphabetic character.  Intended to allow annotation of filter coefficient files
			// by text on first line up to 254 characters
			if (sscanf(work, "%lg", &dWorkVar) != 1) break;
			dFilterData[iFilterSize] = dWorkVar;
			iFilterSize++;
			if (iFilterSize > MAXFILTPTS) {
				//csErrMsg.Format("ERROR: The filter in File: %s has more than %d taps!\r\nThis exceeds the maximum the program can handle and probably more than \r\nis sensible for an FIR filter. No filter data will be set up.",
					//czFiltFileName, iFilterSize);
				//MessageBox(NULL, csErrMsg, " ", MB_OK | MB_ICONINFORMATION );
				return(2);
				}
			}
		}
	fclose(fp_inpdat);
	
	if ((iFilterSize > 2) && ((iFilterSize & 0x1) != 0)) {	// Save file name, 
		// set file valid flag and return
		iValidFilterDataFlag = 1;
		strncpy(czFilterFileName, czFiltFileName, 510);
		return(0);
		}
	else {
		iValidFilterDataFlag = 0;
		//csErrMsg.Format("ERROR: Invalid filter data.  Taps = %d. No filter set up.", iFilterSize);
		iFilterSize = -1;
		//MessageBox(NULL, csErrMsg, " ", MB_OK | MB_ICONINFORMATION );
		return(2);
		}
	
	
	return(2);
}

int FirKernels::SetPostDecimFilterData(char *czFiltFileName)  {	// Opens file of fir filter data and loads into local storage
	// Specialized for unscaled, post-decimation filter
	// Returns 0 success, 1 for file open error and 2 for bad data
	FILE *fp_inpdat;	// File pointer for retrieval of filtering data
	char work[512];
	double dWorkVar;
	QString csErrMsg;

	if ((fp_inpdat = fopen(czFiltFileName, "r")) == NULL ) {
		// Error opening file
		iValidFilterDataFlag = 0;
		return(1);
		}
	
	iPostFilterSize = 0;
	while ((feof(fp_inpdat)) == 0) { // Scan input file until run out of filter coefs.
		if (fgets(work, 256, fp_inpdat) == 0) break;
		if (isalpha((int) work[0]) == 0) {	// This test discards any line beginning with an
			// alphabetic character.  Intended to allow annotation of filter coefficient files
			// by text on first line up to 254 characters
			if (sscanf(work, "%lg", &dWorkVar) != 1) break;
			dFilterData[iFilterSize] = dWorkVar;
			iPostFilterSize++;
			if (iPostFilterSize > MAXPOSTFILTPTS) {
				/*csErrMsg.Format("ERROR: The post-decimation filter in File: %s has more than %d taps!\r\nThis exceeds the maximum the program can handle and probably more than \r\nis sensible for an FIR filter. No filter data will be set up.",
					czFiltFileName, iPostFilterSize);
				MessageBox(NULL, csErrMsg, " ", MB_OK | MB_ICONINFORMATION );*/
				return(2);
				}
			}
		}
	fclose(fp_inpdat);
	
	if ((iPostFilterSize > 2) && ((iPostFilterSize & 0x1) != 0)) {	// Save file name, 
		// set file valid flag and return
		iValidPostFilterFlag = 1;
		strncpy(czFilterFileName, czFiltFileName, 510);
		return(0);
		}
	else {
		iValidPostFilterFlag = 0;
		//csErrMsg.Format("ERROR: Invalid filter data.  Taps = %d. No filter set up.", iFilterSize);
		iFilterSize = -1;
		//MessageBox(NULL, csErrMsg, " ", MB_OK | MB_ICONINFORMATION );
		return(2);
		}
	
	
	return(2);
}

int FirKernels::GetFilterFileName(char *czFiltFileName)  {	// Gets the last filter file name for FileIt
		// Returns 0 for ok name and 1 for no name set

	if (iValidFilterDataFlag == 0) return(1);
	strcpy(czFiltFileName, czFilterFileName);
	
	return(0);
}

int FirKernels::GetFilterLen(void)  {	// Returns length of filter loaded by SetFilterData(); 
	// Returns -1 if not loaded

	return(iFilterSize);
}

int FirKernels::SetFilterType(int iDecimateData, int iNewStride)  {	// Sets flag to call decimating filter
	// Returns 0 for success and 1 for bad argument (< 0) 2 for invalid stride when decimate set

	if ((iDecimateData < 0) || (iDecimateData == 0)) {	// Make stride 1 by default and return
		iStride = 1;
		iDecimateDataFlag = 0;
		return(1);
		}
	iDecimateDataFlag = 1;
	if ((iNewStride < 1) || (iNewStride > 128)) {	// Bad stride so error
		iDecimateDataFlag = 0;	// Cancel setting flag
		iStride = 1;
		return(2);
		}
	iStride = iNewStride;
	return(0);
	}

void FirKernels::GetFilterInfo(int *iDecimateData, int *iStrideDlgMem, int *iPostFilterFlag, QString *p_csPostFilterFileName)  {	
	// Returns decimation info for dialog
	*iDecimateData = iDecimateDataFlag;
	*iStrideDlgMem = iStride;
	*iPostFilterFlag = iValidPostFilterFlag;
	}

int FirKernels::ApplyFilter(int iSignalLength, double *dSignalSource, double *dOut, double *Max, double *Min)  { // Applies
		// predefined filter by calling FirBasic or FirDecimate as set by iDecimateDataFlag
	
	if (iDecimateDataFlag == 0)  {	// apply non-decimating filter
		return(FirBasicApply(iSignalLength, dSignalSource, dOut, Max, Min));
	}
	else
	return(FirDecimateApply(iSignalLength, dSignalSource, dOut, Max, Min));
}
		


int FirKernels::FirBasicApply(int iSignalLength, double *dSignalSource, 
			double *dOut, double *Max, double *Min)  {	// Call to FirBasic
		// using the filter defined by SetFilterData()
		// Returns passthrough value from FirBasic() filtering or 3 for no defined filter
	if (iFilterSize < 1) return(3);
	return(FirBasic(iFilterSize, iSignalLength, dFilterData, dSignalSource, dOut, Max, Min));
}

int FirKernels::FirDecimateApply(int iSignalLength,  
		double *dSignalSource, double *dOut, double *Max, double *Min)  {	
	// Call to decimating filter using the filter defined by SetFilterData()
		// Returns passthrough value from FirDecimate() filtering or 3 for no defined filter
	if (iFilterSize < 1) return(3);
	return(FirDecimate(iFilterSize, iSignalLength, iStride, dFilterData, dSignalSource, dOut, Max, Min));
}
		