#include "rtvtdataobject.h"
#include <iostream>

//static long alen = 51200;

RTVTDataObject::RTVTDataObject()
{
    this->channelDataArray = new QByteArray();
    this->channelDataArray->clear();
    
    this->lastDisplayPtr = 0;

}

RTVTDataObject::~RTVTDataObject()
{
    delete channelDataArray;
}

void RTVTDataObject::addToChannelArray(QByteArray inByteArray)
{
    this->channelDataArray->append(inByteArray.mid(0,DRAW_BUFFER_LENGTH));

    // increment ptr
    this->lastDisplayPtr = (this->channelDataArray->length()-DRAW_BUFFER_LENGTH);
}

 QList<QString> RTVTDataObject::returnDoubleListOfLengthForChannel(int length, int channel)
 {
     int startCounter = 0;

     // Find frame synch
     for(int f=0;f<15;f++)
     {
         QString temp;
         // Convert to hex for comparrison
        char sTmp1[30],sTmp2[30];
        char out[128];

        temp.sprintf(sTmp1,"0x%x",(int)this->channelDataArray->data()[this->lastDisplayPtr+(f*2)]);
        temp.sprintf(sTmp2,"0x%x",(int)this->channelDataArray->data()[this->lastDisplayPtr+(f*2)+1]); // Why is this ff for synch and not cd????
        out[f*5]=sTmp1[2];
        out[f*5+1]=sTmp1[3];
        out[f*5+2]=sTmp2[2];
        out[f*5+3]=sTmp2[3];
        out[f*5+4]=' ';

        if((sTmp1[2] == '2') && (sTmp1[3] == '1') && (sTmp2[2] == 'f') && (sTmp2[3] == 'f'))
        {
            std::cout << "Found frame synch..." << std::endl;
            startCounter = f;
            f = 15;
        }

     }

     // Move / Convert data for simple display
     int i = 0;
     for(i=(this->lastDisplayPtr+(startCounter*2+(15-channel)*2));i<(this->lastDisplayPtr+length);)
     {
         channelDataList << (QString::number(this->channelDataArray->data()[i+1]*256+this->channelDataArray->data()[i]));
         i=i+16*2; // + 32 move over one frame
     }

     return channelDataList;
 }
