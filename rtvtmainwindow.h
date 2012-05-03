#ifndef RTVTMAINWINDOW_H
#define RTVTMAINWINDOW_H

// RTVTMainWindow is now a controller object for RTVT subsystem

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMutex>
#include <QtGui>
#include <QFuture>
#include <QFutureWatcher>
#include <QAudioOutput>

#include "rtvtchannelwidget.h"
#include "rtvtdataobject.h"

#ifdef USE_HS_USB
    #include "cpshsusbhardwareabstractionlayer.h"
#endif

// Timer
#include "RTVTTimer.h"

#include "universalStructures.h"

// For HUD Plugins
#include "multipagewidget.h"
#include "HUD_Plugins/rtvthudcontrollerview.h"
#include "HUD_Plugins/rtvthudwaveview.h"

#include "data_handling_plugins/bNEVwr.h"

#include "External-Code/audiooutput.h"

#include "rtvtglobaldefinitions.h"

// Filtering
#include "Filtering/FirKernels.h"

#define RTVT_DEBUG

class RTVTMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Variables
    RTVTDataObject *dataObject;
    int sbWriteEndPtr, sbDrawReadEndPtr, sbAudioReadEndPtr;
    QListWidget *dataListWidget;
    int playStep,readDataStep;
    QFuture<void> *bbFuture, *sbFuture, *abFuture;
    QFutureWatcher<void> *bbWatcher, *sbWatcher, *abWatcher;
    QTimer *bbTransferTimer, *sbTransferTimer, *playTimer;
    QList<RTVTChannelWidget*> channelWidgetList;
    int dataSource, dataPath;
    bool readAllData;
    QAudioOutput* audioOutput;
    bool startAudio, useAudio;
	bool sbThreadIsRunning;
    unsigned int audioChannel;
	int missedSynch;
    QBuffer *aBuffer;
    QTextBrowser *rtvtConsole;
    int	continuousViewerNeedsDataNumber;
    double dFilteredDataArray[DEFAULT_NUM_CHANNELS_IN_DATA][512000]; //was MAX_DATA_TO_FILTER
	QByteArray *byteArray;

    QFile saveDataFile;
    QTextStream streamToWrite;
    QDataStream out, binStreamToWrite;
    QString rtvtSaveDataPath;
    bool rtvtSavingData;
    int numberOfFileSaves;

    // Views
	int						numberOfChannelViews;
	int						channelViewType;
	bool					squareChannelGrid;

	// Data
        unsigned int						numberOfDataChannels;
	int						selectedWidgetNumber;
        unsigned int                        sampleFrameLength;
        unsigned int                        systemClockRate;
	QByteArray theDataArray;
    unsigned char *transferBuf;
	unsigned int singleFrameLoss;

    // HUD
    RTVTHUDControllerView	*rtvtControllerView;
    RTVTHUDWaveView			*rtvtWaveHUD;
    MultiPageWidget			*hud;
    QDockWidget				*hudDock;
	RTVTTriggerModel		*theWaveTableModel;
        unsigned int                    wireAddressing;

    // NEV Writer
    bNEVwr	*nevWriter;
    FILE	*nevFile;
    bool	saveNEVState;
	
    // Filtering
    FirKernels **firFilters;
    int selectedFilterIndex;
    int numberOfFiltersCreated;
    bool shouldFilter;

    // Audio
    AudioTest *audioPlayer;

    // Functions
    RTVTMainWindow();
    ~RTVTMainWindow();
    void initializeVariables();
    void centerMainWindow();
    void redrawChannelViews();

    void makeDataStoreToBackBufferTransfer();
    void makeBackToStorageBufferTransfer();
    void makeStorageToAudioBufferTransfer();
    void loadDataFromSource();
    void loadDataToTableOnChannels(int start, int end);
    unsigned int findFrameSynchInData(unsigned char *data);
    void resetAllBuffers();
    void threadedSaveRawData();

    void setupChannelGrid();
	void setNEVFile(bool state, char* fileName);

	void setSelectedWidget(int widgetNumber);

    // USB
    void setupHSUSB();

public slots:
    QString openExistingData();
    void chooseFileForSavingData();
    void runThreadedDataBBTransfer();
    void runThreadedDataSBTransfer();
    void bbThreadFinishedRunning();
    void sbThreadFinishedRunning();
    void runThreadedDataABTransfer();
    void abThreadFinishedRunning();
    void tellViewsToDraw();
    void tellAudioToPlay();
    void viewWasDoubleClicked(int channel);
    void continuousViewReachedEndOfData(int channel);
    void updatePlay();
    void resizeSelfAndViews();
    void threadedChannelSeparation(unsigned char *);
    void setSaveDataPath(QString inPath);
    void setSaveDataBool(bool inBool);
    void clearWaveformsOnChannels();
    void resetTriggersOnChannels();
    void propogateSaveNEV(bool state, char* fileName);
    void writeWaveformsToFile(waveformDatum datum);
    void setSaveNEVState(bool);
    void runThreadedAudioPlayer();
    void addFilterFromFile();
    void updateSelectedFilter(int ind);
    void stopFilteringData();
    void updateLocalWaveCheckValue(int);
    void updateNumberOfChannelViews(int numChannels);
    void updateNumberOfDataChannels(int numDataChannels);
    void saveSNIFFRToMat(void);
	void updateAudioChannel(int index);
	void changeChannelDisplayToWavesAndContinuous();
	void changeChannelDisplayToWaves();
        void playFromController(bool withRecording);
        void setAddressingTo(int numWire);
        void tellWaveViewsToPropogateChangesWhenDone(bool yesNo);

signals:
	void appendToConsole(QString);

private:
    QFile openDataFileHandle, saveDataFileHandle;
    mutable QMutex bbMutex;
    mutable QMutex sbMutex;
    void keyPressEvent(QKeyEvent *e);
protected:

	void resizeEvent (QResizeEvent * event);
	void moveEvent ( QMoveEvent * event );
	void mousePressEvent ( QMouseEvent * event );


};

#endif // RTVTMAINWINDOW_H
