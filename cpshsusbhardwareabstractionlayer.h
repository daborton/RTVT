#ifndef CPSHSUSBHARDWAREABSTRACTIONLAYER_H
#define CPSHSUSBHARDWAREABSTRACTIONLAYER_H

#include "rtvtglobaldefinitions.h"
#include "cyapi.h"

class CPSHSUSBHardwareAbstractionLayer
{

public:
    CPSHSUSBHardwareAbstractionLayer();
	void makeUSBTransfer();

	// CyAPI Related
	CCyBulkEndPoint *InEpt;
    CCyBulkEndPoint *OutEpt;
	CCyUSBDevice *USBDevice;

	// buffer related
	int bbNextWritePtr;
	int bbNextReadPtr;

	bool isConnected;
    int setupHSUSB();
};

#endif // CPSHSUSBHardwareAbstractionLayer_H
