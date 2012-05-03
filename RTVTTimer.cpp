#include "RTVTTimer.h"
#include <QDateTime>
#include <QTime>

//#define USE_HS_USB

using namespace std;

#ifdef USE_HS_USB
    LARGE_INTEGER timerFreq_;
    LARGE_INTEGER counterAtStart_;
#else
    int timerFreq_;
    int counterAtStart_;
#endif

RTVTTimer::RTVTTimer()
{
#ifdef USE_HS_USB
    // Time is in ns (integers thereof)
    unsigned int diffTime = 0, lastTime = 0, newTime = 0;
    startTime();
    this->firstTime = calculateElapsedTime();
    cout<<"Start Time = "<<lastTime<<endl;

    newTime = calculateElapsedTime();
    diffTime = newTime - lastTime;

    Sleep(5);
#else
    unsigned int diffTime = 0, lastTime = 0, newTime = 0;

    //startTime();
	theTime = new QTime();
	theTime->start();
    this->startTimeValue = theTime->elapsed();//QTime::currentMSecsSinceEpoch();
#endif
}

void RTVTTimer::startTime()
{
#ifdef USE_HS_USB
  QueryPerformanceFrequency(&timerFreq_);
  QueryPerformanceCounter(&counterAtStart_);
  //cout<<"timerFreq_ = "<<timerFreq_.QuadPart<<endl;
  //cout<<"counterAtStart_ = "<<counterAtStart_.QuadPart<<endl;
  TIMECAPS ptc;
  UINT cbtc = 8;
  MMRESULT result = timeGetDevCaps(&ptc, cbtc);
  /*if (result == TIMERR_NOERROR)
  {
    cout<<"Minimum resolution = "<<ptc.wPeriodMin<<endl;
    cout<<"Maximum resolution = "<<ptc.wPeriodMax<<endl;
  }
  else
  {
    cout<<"result = TIMER ERROR"<<endl;
  }*/
#else
    // Do Nothing
#endif
}

unsigned int RTVTTimer::calculateElapsedTime()
{
    #ifdef USE_HS_USB
  if (timerFreq_.QuadPart == 0)
  {
    return -1;
  }
  else
  {
    LARGE_INTEGER c;
    QueryPerformanceCounter(&c);
    return static_cast<unsigned int>( (c.QuadPart - counterAtStart_.QuadPart) * 1000000 / timerFreq_.QuadPart ); //returned in ms
  }
#else
    int currentTime = theTime->elapsed();//QDateTime::currentMSecsSinceEpoch();
    unsigned int elapsedTime = (unsigned int)(currentTime - this->startTimeValue);
    return elapsedTime;
#endif
}
