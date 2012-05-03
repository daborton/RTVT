#include "cpshsusbhardwareabstractionlayer.h"
#include "rtvtglobaldefinitions.h"
#include <QByteArray>

unsigned char *backByteBuffer;
QByteArray *backQByteBuffer;

static long length = BACK_BUFFER_LENGTH; // this is the Xfer length, not bb length - needs to be bblength/2


CPSHSUSBHardwareAbstractionLayer::CPSHSUSBHardwareAbstractionLayer()
{
    backByteBuffer = (unsigned char *) malloc (sizeof(unsigned char) * length);
	backQByteBuffer = new QByteArray();
	backQByteBuffer->resize(BACK_BUFFER_LENGTH);

	this->bbNextWritePtr = 0;
	this->bbNextReadPtr = 0;
	
	this->isConnected = false;
}

int CPSHSUSBHardwareAbstractionLayer::setupHSUSB()
{
    int error = 11;

    USBDevice = new CCyUSBDevice(NULL,GUID_KNJN_FX2);

    // Look for our device with VID = 04b4, PID = 8613
    int devices = USBDevice->DeviceCount();
    USHORT vID, pID;
    int d = 0;

    do{
        USBDevice->Open(d); // Open automatically calls Close( ) if necessary
        vID = USBDevice->VendorID;
        pID = USBDevice->ProductID;
        d++;
    } while ((d < devices ) && ((vID != 0x04B4) || (pID != 0x8613)));

    if((vID == 0x04B4) && (pID == 0x8613))
    {}

    if((vID != 0x04B4) || (pID != 0x8613))
    {
        USBDevice->Close(); // This is not BIC Device. Close the port.
        error = 1;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int nEndPointCount, nIndex;

    // Find the USB pipe we use for data transfer (endpoint IN 8)
    nEndPointCount = USBDevice->EndPointCount();
    this->InEpt = NULL;
    this->OutEpt = NULL;
    bool success1=false,success2=false;

    if(USBDevice->DeviceCount() && !USBDevice->Open(0))
    {
        USBDevice->Reset();
        USBDevice->Open(0);
    }
    if(USBDevice->IsOpen())
        {
        for (nIndex = 1; nIndex < nEndPointCount; nIndex++)
        {
                bool bIn = USBDevice->EndPoints[nIndex]->bIn;
                bool bBulk = (USBDevice->EndPoints[nIndex]->Attributes == 2);
                if(bBulk && bIn)
                {
                        InEpt = (CCyBulkEndPoint *)USBDevice->EndPoints[nIndex];
                        success1=true;
                }
                if(bBulk && !bIn)
                {
                        OutEpt = (CCyBulkEndPoint *)USBDevice->EndPoints[nIndex];
                        success2=true;
                }
        }
        if (!success1||!success2)
        {
            //std::cout << "::Undable to find endpoint." << std::endl;
            error = 2;
        }
        else
        {
            //std::cout << "::Found endpoints" << std::endl;
            error = 0;
        }
    }

	if(!error)
		this->isConnected = true;

	backByteBuffer[0] = 0;

    return error;
}

void CPSHSUSBHardwareAbstractionLayer::makeUSBTransfer()
{
	unsigned char *buf;
	buf=(unsigned char *) malloc (sizeof(unsigned char) * length);

	backQByteBuffer->clear();

	this->InEpt->XferData(buf, length);		//read data;
	

	memcpy(&backByteBuffer[bbNextWritePtr], buf, length);

	// Increment write/read ptr
	if(this->bbNextWritePtr == 0)
	{
		//this->bbNextWritePtr = (length);
		this->bbNextReadPtr = 0;
	}
	else
	{
		this->bbNextWritePtr = 0;
		//this->bbNextReadPtr = (length);
	}

	//backQByteBuffer->insert(0,(char *)buf);

	delete buf;
}

