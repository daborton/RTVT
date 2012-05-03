#ifndef RTVTTIMER_H
#define RTVTTIMER_H

#include <iostream>
#include <QtGlobal>
#include <QTime>

#ifdef IS_WINDOWS_PC
    #include <Windows.h>
#endif

class RTVTTimer
{

public:
    unsigned int firstTime;
    qint64  startTimeValue;
	QTime *theTime;
    // Functions
    RTVTTimer();
    void startTime();
    unsigned int calculateElapsedTime();

};

#endif
