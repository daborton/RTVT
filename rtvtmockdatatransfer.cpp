#include "rtvtmockdatatransfer.h"

static long alen = 51200;

RTVTMockDataTransfer::RTVTMockDataTransfer()
{
}

void RTVTMockDataTransfer::makeDataTransfer()
{

    QByteArray buf;
    QByteArray s;

    buf.resize(alen);
    buf.clear();
    s.clear();

    this->fillBackBuffer();

}

void RTVTMockDataTransfer::fillBackBuffer()
{

}

//
