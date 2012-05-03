#ifndef RTVTWAVEVIEWERGLWIDGET_H
#define RTVTWAVEVIEWERGLWIDGET_H

#include <QGLWidget>
#include <QFuture>
#include <QFutureWatcher>

// Data I/O
#include <iostream>
#include "universalStructures.h"

#include "rtvtglobaldefinitions.h"

#define MAX_NUMBER_TRIGGERS					3

#define BASE_TRIGGER_CONTROL_TYPE			0
#define X_TRIGGER_CONTROL_TYPE				1
#define Y_TOP_TRIGGER_CONTROL_TYPE			2
#define Y_BOTTOM_TRIGGER_CONTROL_TYPE		3

#define MEAN_WINDOW							6400

class QTimer;

struct hoop
{
	short channel;
	short triggerNumber;
    float top;
    float bottom;
	short sampleNumberToTest;
	unsigned int tickOfSampleCrossing[NUMBER_OF_WAVES_PER_TRIGGER];
	float waveSample[NUMBER_OF_WAVES_PER_TRIGGER][DEFAULT_NUMBER_OF_SAMPLES_PER_WAVE]; // From 0 at beginning of window
	short nextWaveNumber;
	short numberOfWaves;
	
	float r,g,b;
	QRect controlPointBoundingRect;
};

Q_DECLARE_METATYPE(hoop)
  
class RTVTWaveViewerGLWidget : public QGLWidget
{
    Q_OBJECT

    public:
    // Variables
        bool lineSmoothingEnabled;
		GLfloat aspectRatio, vpWidth, vpHeight, fov, zFromCamera, interSampleLength;
	GLfloat	BASE_TRIGGER_CONTROL_POINT_X1, BASE_TRIGGER_CONTROL_POINT_Y1, TRIGGER_CONTROL_POINT_X1, TRIGGER_CONTROL_POINT_Y1;
        float timeWindowInS;
        int sampleRate, numberOfSamples;
        bool drawingFromData;
        bool needsRedraw;
        bool smooth;
		bool isPlaying;
        int assignedViewerChannel;
        float yPeakToPeak;
        float yDragOrigin, xDragOrigin, thresholdOrigin;
		float xScaleFactor;
        bool setThresholdMode, setYScaleMode;
        float thresholdPP;
        unsigned int readFromDrawBufferFramePtr;
        unsigned int readFromChannelDataPtr;
		unsigned int nextFilterWriteLocation;
        unsigned int readByteOffset;
        unsigned int readStartPositionForChannel;
		unsigned int readFromChannelFilterDataPtr;
		bool drawThresholds;
	
        float triggerThreshold;
        int baseline;
        bool viewNeedsRedraw;
        int thresholdReadPtr;
        //char *thresholdWorkingBuffer;
        QFuture<void>	*triggersFuture;
        QFutureWatcher<void> *triggersWatcher;
        int testMark;
        float adcFactor;
        bool waitUntilNextTransfer;
        float localMean;
		float drawingMean;
        int meanCounter;
		unsigned int meanCheckPoint;
        int ampGain;
		unsigned int numberOfWaveLengthsToCheck;
		bool mouseIsDown;

        QTimer *triggerTimer;

        hoop triggers[MAX_NUMBER_TRIGGERS];
        QPoint cursorClickLocation;
        int selectedTrigger;
        int numberOfActiveTriggers;
        int selectedTriggerType;
        bool propogatesChangesInThreshold;
		int numberOfSamplesPerWave;
		int numberOfSamplesBeforeTrigger;
		unsigned int numberOfSamplesAfterTrigger;
		unsigned int waveByteLength;

        bool shouldUpdateTextDisplay;
        QTimer *textUpdateTimer;

    // Functions
        RTVTWaveViewerGLWidget( int timerInterval, int viewerChannel, QWidget *parent, QString name);
        ~RTVTWaveViewerGLWidget();
        void enableLineSmoothing( bool bEnable );
        void findStartPosition();
        void applyConstraints();
        void applySimpleThreshold();
        void applySimpleThresholdOnFilteredData();
        void play();
        void stop();

        void clearWaveforms();
        void resetTriggers();

        void updateWaveCheckValue(int inValue);

        void keyPressEvent(QKeyEvent *e );
        QSize sizeHint() const;

signals:
        void iWasDoubleClicked(int channel);
		void iHaveWaveformsToWrite(waveformDatum datum);
		void waveViewEditedTrigger(hoop theTrigger);
               void passTriggerToOtherWaveViewers(hoop passedTrigger);

    protected:
        void initializeGL();
        void resizeGL(int width, int height );
        void paintGL();


        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        void mouseDoubleClickEvent(QMouseEvent *me);
        void mouseMoveEvent(QMouseEvent *event);
        void timeOut();

    protected slots:
        void timeOutSlot();
		void tiggerTimerTimedOut();
		void runThreadedTiggers();
		void triggersThreadFinishedRunning();
                void tellTextToUpdate();

    private:
        QTimer *glRedrawTimer;


};

#endif // RTVTWAVEVIEWERGLWIDGET_H
