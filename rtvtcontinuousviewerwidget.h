#ifndef RTVTCONTINUOUSVIEWERWIDGET_H
#define RTVTCONTINUOUSVIEWERWIDGET_H

#include <QWidget>
#include <QBrush>
#include <QPen>
#include "rtvtglobaldefinitions.h"

#define MEAN_WINDOW 6400
#define LEFT_BYTE_PAD 3200
#define RIGHT_BYTE_PAD 3200
#define LEFT_PAD_PERCENT 5
#define RIGHT_PAD_PERCENT 5
#define TOP_PAD_PERCENT 5

class QTimer;

class RTVTContinuousViewerWidget : public QWidget
{
	Q_OBJECT

    public:
    
	// Variables
    bool lineSmoothingEnabled;
    double aspectRatio, vpWidth, vpHeight, fov, zFromCamera, interSampleLength;
    float timeWindowInS;
    int sampleRate, numberOfSamples;
    bool drawingFromData;
    bool viewNeedsRedraw;
    bool smooth;
	bool isPlaying;
    int assignedViewerChannel;
    double yPeakToPeak;
    double yDragOrigin, xDragOrigin, thresholdOrigin;
	double xScaleFactor;
	double yScaleFactor;
    bool setThresholdMode, setYScaleMode;
    double thresholdPP;
	int readFromDrawBufferFramePtr;		// What frame are we on?
	int readFromChannelDataPtr;
	unsigned int readFromChannelFilterDataPtr;
	unsigned int nextFilterWriteLocation;
	int readStartPositionForChannel;
	unsigned int readByteOffset;
	unsigned int drawPixelOffset;
	int drawWindowWidth;
	int baseline;
	bool askedToClear;
	double storedYValueForNextFrame;
	int storedXValueForNextFrame;
	int secondCounter;
	bool showInformation;
	int meanCounter;
	double meanSource[MEAN_WINDOW]; // Probably should be a filter length here...

	// Data Variables
	double localMean;
	double adcFactor;
	int ampGain;
	int testMark;
	bool waitUntilNextTransfer;

    // Functions
    RTVTContinuousViewerWidget( int timerInterval, int viewerChannel, QWidget *parent, QString name);
    void enableLineSmoothing( bool bEnable );
	void findStartPosition();

    void keyPressEvent(QKeyEvent *e );
    QSize sizeHint() const;

	void play();
	void stop();

signals:
    void iWasDoubleClicked(int channel);
	void iReachedEndOfData(int channel);

    protected:

        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        void mouseDoubleClickEvent(QMouseEvent *me);
        void mouseMoveEvent(QMouseEvent *event);
        void timeOut();

		void paintEvent(QPaintEvent *event);

    protected slots:
        void timeOutSlot();

    private:
        QTimer *glRedrawTimer;
};

#endif // RTVTCONTINUOUSVIEWERWIDGET_H
