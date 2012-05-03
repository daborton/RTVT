#ifndef RTVTCHANNELWIDGET_H
#define RTVTCHANNELWIDGET_H

#include <QWidget>
#include <QtGui>

//#include "rtvtmainwindow.h" // for some parent calls

#include "rtvtcontinuousviewerwidget.h"
#include "rtvtwaveviewerglwidget.h"

// QWT for noise (and other) plots
#ifdef IS_WINDOWS_PC
#ifdef USE_QWT_PLOT
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_scale_engine.h>
#endif
#endif
#ifdef IS_MACOSX
#ifdef USE_QWT_PLOT
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_plot_grid.h>
#include <qwt/qwt_scale_engine.h>
#endif
#endif
#include "External-Code/fftreal_wrapper.h"
#include "External-Code/utils.h"

#include "universalStructures.h"

class FFTRealWrapper;

// Number of audio samples used to calculate the frequency spectrum
const int    SpectrumLengthSamples  = PowerOfTwo<FFTLengthPowerOfTwo>::Result;

// Number of bands in the frequency spectrum
const int    SpectrumNumBands       = 10;

// Lower bound of first band in the spectrum
const qreal  SpectrumLowFreq        = 0.0; // Hz

// Upper band of last band in the spectrum
const qreal  SpectrumHighFreq       = 1000.0; // Hz

class RTVTChannelWidget : public QWidget
{
Q_OBJECT;
public:
    RTVTChannelWidget(QWidget *parent, int assignedChannel, int assignedWidget, int viewType);
    ~RTVTChannelWidget();
    void play();
    void stop();
    void resetReadPointer();
    void setDrawFromData(bool isDrawing);
    void updateNextWriteLocationWithAddition(unsigned int bytesWritten);
	void updateNextFilterWriteLocationWithAddition(unsigned int bytesWritten);
	unsigned int getNextFilterWriteLocation();
    unsigned int getNextWriteLocation();
    void updateChannelViews();
    int calculateFFTWithLength(unsigned int numberOfAverages, QVector<qreal>& amplitude, QVector<qreal>& frequency);


    typedef float DataType;

    unsigned char					*channelData;
    double							*filteredChannelData;

    float							theMean;

    QHBoxLayout						*horizontalLayout;

    RTVTWaveViewerGLWidget			*waveViewer;
    RTVTContinuousViewerWidget		*continuousViewer;

    FFTRealWrapper*                          m_fft;
    QVector<float>                        m_window;

    bool							isPlaying;
	bool							usesContinuousView;
    unsigned int					nextWriteLocation;
	unsigned int					nextFilterWriteLocation;
	unsigned int					numberOfChannelsInData;
	bool							isSelected;

    QTimer							*channelTimer;
    QTimer							*viewRedrawTimer;
    QLabel							*timerValueLabel;
    unsigned int					channelMSCount;
    unsigned int					assignedChannel;
	unsigned int					assignedWidgetNumber;
	
	bool							isFiltering;
        unsigned int                                sampleFrameLength;

    void keyPressEvent(QKeyEvent *e );
	void updateMean(double inMean);
	void setNumberOfChannelsInData(int numChannels);
	void setChannelSelected(bool status);
       void calculateWindow();
       void setAddressScheme( unsigned int inWireAddressing );

public slots:
	void channelTimeout();
	void viewRedrawTimerTimeout();
	void childHasWaveformsToWrite(waveformDatum datum);
	void childHasEditedTrigger(hoop theTrigger);
        void passTriggerUp(hoop theTrigger);
	
signals:
	void waveformsReadyToWrite(void);
        void sendTriggerToOtherWaveViewers(hoop theTrigger);

protected:
	void resizeEvent (QResizeEvent * event);
	void paintEvent(QPaintEvent * event );
	void mousePressEvent(QMouseEvent *event);
};

#endif // RTVTCHANNELWIDGET_H
