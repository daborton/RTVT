#ifndef RTVTMOCKDATATRANSFER_H
#define RTVTMOCKDATATRANSFER_H

#include <QByteArray>
#include <QBuffer>

class RTVTMockDataTransfer
{
public:
    // Variables
    QBuffer frontBuffer, backBuffer;

    RTVTMockDataTransfer();
    void makeDataTransfer(void);
    void fillBackBuffer(void);
};

#endif // RTVTMOCKDATATRANSFER_H
