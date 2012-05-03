#ifndef RTVTDATAOBJECT_H
#define RTVTDATAOBJECT_H

#include <QByteArray>
#include <QDataStream>

#include "rtvtglobaldefinitions.h"

class RTVTDataObject
{
public:
    // Variables
    QByteArray *channelDataArray;
    QList<QString> channelDataList;
    int lastDisplayPtr, firstStep;

    RTVTDataObject();
    ~RTVTDataObject();
    void addToChannelArray(QByteArray inByteArray);
    QList<QString> returnDoubleListOfLengthForChannel(int length, int channel);
};

#endif // RTVTDATAOBJECT_H
