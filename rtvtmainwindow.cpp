#include "rtvtmainwindow.h"
#include <QKeyEvent>
#include <iostream>
#include <QtConcurrentRun>
#include <QThread>
#include <QApplication>
#include <QDebug>
#include <QtOpenGL>
#include <math.h>

//#define RTVT_DEBUG
//#define USE_AUDIO
#define DATA_PATH_TYPE HSUSB_DATA_PATH_TYPE

#ifdef EXTERNAL_MEMCPY
	#include "External-Code/memcpy.h"
#endif

unsigned char *drawingByteBuffer;
//unsigned char *workingByteBuffer;
//unsigned char *workingChannelBuffer;
unsigned char *storageByteBuffer;
unsigned char *audioByteBuffer;

// Timer
RTVTTimer *theTime;

#ifdef USE_HS_USB
    extern unsigned char					*backByteBuffer; // from CPSHSUSB
    extern CPSHSUSBHardwareAbstractionLayer	*hsHAL;
#else
    unsigned char	*backByteBuffer;
#endif

static long length = BACK_BUFFER_LENGTH; // this is the Xfer length, not bb length - needs to be bblength/2


RTVTMainWindow::RTVTMainWindow()
{
    // Init procedure for non-view variables
    this->initializeVariables();

    theTime = new RTVTTimer();

    // Set the frame in the center of the screen and fix it
    this->setGeometry(450,50,1100,900);
	this->layout()->setContentsMargins(0,0,0,0);
	this->setStatusBar(0);
    //this->setMinimumSize(1200,700);
    //this->setMaximumSize(1200,700);

    // Make the BG black
    //this->setStyleSheet("background-color: black;");

    // Make unified bar
    //this->setUnifiedTitleAndToolBarOnMac(true);

    this->setFocusPolicy(Qt::StrongFocus);

    QAudioFormat format;
    format.setFrequency(SYSTEM_CLOCK_RATE/SAMPLE_FRAME_LENGTH/DEFAULT_NUM_CHANNELS_IN_DATA);
    format.setChannels(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    this->audioOutput = new QAudioOutput(format,this);

    this->startAudio = false;
    this->useAudio = false;

    //this->redrawChannelViews();
	// Start with waves as default view
    this->changeChannelDisplayToWaves();
	
#ifdef USE_AUDIO
	// Channels are created - we can create and set the audio system
	audioPlayer = new AudioTest();
	//audioPlayer->setChannelPtr(this->channelWidgetList[0]);
	connect(audioPlayer, SIGNAL(currentIndexChanged(int)), this, SLOT(updateAudioChannel(int)));
	
	QStringList items;
	for(int ac = 0;ac<this->numberOfDataChannels;ac++)
	{
		items << QString::number(ac+1);
	}
	this->audioPlayer->channelComboBox->clear();
	this->audioPlayer->channelComboBox->addItems(items);

	this->audioPlayer->setGeometry(100,100,200,150);
    audioPlayer->show();
#endif
	
	// Filtering
	this->firFilters = new FirKernels*[MAX_NUMBER_OF_FILTERS];
        for(int filterCount=0;filterCount<MAX_NUMBER_OF_FILTERS;filterCount++)
	{
		this->firFilters[filterCount] = new FirKernels();
	}
	this->numberOfFiltersCreated = 0;
	
    //// Placeholder widgets
    // Top
#ifdef RTVT_DEBUG
	/*QDockWidget *phDockTop = new QDockWidget("Top widget area placeholder",this);
    phDockTop->setGeometry(0,0,300,800);
    phDockTop->setStyleSheet("border-width: 1px; border-color: #535353; background-color: white;");
	this->rtvtConsole = new QTextBrowser(this);
	this->rtvtConsole->append("Browser created and setup for appending data.");
	this->rtvtConsole->setGeometry(0,0,300,myCentralWidget->height());
	QScrollBar *vbar = new QScrollBar(Qt::Vertical, this);
	this->rtvtConsole->setVerticalScrollBar(vbar);
	this->rtvtConsole->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
	this->rtvtConsole->setReadOnly(false);
	phDockTop->layout()->addWidget(this->rtvtConsole);
    this->addDockWidget(Qt::LeftDockWidgetArea,phDockTop);*/
#endif
	

    // Bottom
    //QDockWidget *phDockBottom = new QDockWidget("Bottom widget area placeholder",this);
    //phDockBottom->setGeometry(0,0,1200,200);
    //phDockBottom->setStyleSheet("border-width: 1px; border-color: #535353; background-color: white;");
    //dataListWidget = new QListWidget(phDockBottom);
    //dataListWidget->setGeometry(0,0,1200,200);
    //dataListWidget->setFocusPolicy(Qt::NoFocus);
    //phDockBottom->layout()->addWidget(dataListWidget);
    //this->addDockWidget(Qt::BottomDockWidgetArea, phDockBottom);

    // Center the window
    this->centerMainWindow();

    //// BB Thread
    // create a QFuture and a QFutureWatcher
    bbFuture = new QFuture<void>;
    bbWatcher = new QFutureWatcher<void>;

    // Set a timer for buffer transfers
    bbTransferTimer = new QTimer(this);
    connect(bbTransferTimer, SIGNAL(timeout()), this, SLOT(runThreadedDataBBTransfer()));
    // display a message box when the calculation has finished
    connect(bbWatcher, SIGNAL(finished()), this, SLOT(bbThreadFinishedRunning()));

    ///// SB Thread
    // create a QFuture and a QFutureWatcher
    sbFuture = new QFuture<void>;
    sbWatcher = new QFutureWatcher<void>;

    // Set a timer for buffer transfers
    sbTransferTimer = new QTimer(this);
    connect(sbTransferTimer, SIGNAL(timeout()), this, SLOT(runThreadedDataSBTransfer()));
    // display a message box when the calculation has finished
    connect(sbWatcher, SIGNAL(finished()), this, SLOT(sbThreadFinishedRunning()));

    // Set a timer for buffer transfers
    playTimer = new QTimer(this);
    connect(playTimer, SIGNAL(timeout()), this, SLOT(updatePlay()));

	// /**** Create the HUD ****/
	// Create the RTVT Controller page - load from form
	rtvtControllerView = new RTVTHUDControllerView();
	rtvtWaveHUD = new RTVTHUDWaveView();
	
	// Setup the table in the Wave view and make datamodel
	QList<hoop> currentTriggerList;
	foreach (RTVTChannelWidget *cw, this->channelWidgetList)
	{
		for(int t=0;t<cw->waveViewer->numberOfActiveTriggers;t++)
			currentTriggerList << cw->waveViewer->triggers[t];
	}	
	theWaveTableModel = new RTVTTriggerModel(currentTriggerList, this); // Make a model
    rtvtWaveHUD->setTableModel(theWaveTableModel); // Set the model in the view
	
	connect(this->rtvtWaveHUD, SIGNAL(clearWaveformButtonClicked()), this, SLOT(clearWaveformsOnChannels()));
	connect(this->rtvtWaveHUD, SIGNAL(resetWaveformTriggersButtonClicked()), this, SLOT(resetTriggersOnChannels()));
	connect(this->rtvtWaveHUD, SIGNAL(saveToNEVFileCheckboxClicked(bool, char*)), this, SLOT(propogateSaveNEV(bool, char*)));
	connect(this->rtvtWaveHUD, SIGNAL(saveNEVToggleButtonState(bool)), this, SLOT(setSaveNEVState(bool)));
	connect(this->rtvtWaveHUD, SIGNAL(updateWaveCheckValue(int)), this, SLOT(updateLocalWaveCheckValue(int)));
       connect(this->rtvtWaveHUD, SIGNAL(controllerSaysMoveThresholdsTogether(bool)), this, SLOT(tellWaveViewsToPropogateChangesWhenDone(bool)));
	
	connect(this->rtvtControllerView, SIGNAL(signalToAddFilterToController()), this, SLOT(addFilterFromFile()));
	connect(this->rtvtControllerView, SIGNAL(selectedFilterChanged(int)), this, SLOT(updateSelectedFilter(int)));
	connect(this->rtvtControllerView, SIGNAL(signalNoFiltering()), this, SLOT(stopFilteringData()));
	connect(this->rtvtControllerView, SIGNAL(changeNumberOfChannelViews(int)), this, SLOT(updateNumberOfChannelViews(int)));
	connect(this->rtvtControllerView, SIGNAL(changeNumberOfDataChannels(int)), this, SLOT(updateNumberOfDataChannels(int)));
	connect(this->rtvtControllerView, SIGNAL(changeChannelDisplayToWavesAndContinuous()), this, SLOT(changeChannelDisplayToWavesAndContinuous()));
	connect(this->rtvtControllerView, SIGNAL(changeChannelDisplayToWaves()), this, SLOT(changeChannelDisplayToWaves()));
        connect(this->rtvtControllerView, SIGNAL(changeMainWindowAmplifierAddressing(int)), this, SLOT(setAddressingTo(int)));

	/*** Add first filter - always the null filter and average (11 samples) so we have them around
	***/
	this->selectedFilterIndex = -1;
	
	// Null Filter
	QString fileName = "C:/Users/OptoBOSS/Desktop/Programming/RTVT_2011/Filtering/null_filter.txt";
	QByteArray ba = fileName.toLatin1();
	this->firFilters[this->numberOfFiltersCreated]->SetFilterData(ba.data());
	this->numberOfFiltersCreated++;
	QFileInfo nullPathInfo(fileName);
	QString theNullName(nullPathInfo.fileName());
	this->rtvtControllerView->addToFilterList(this->numberOfFiltersCreated, theNullName);

	// Average filter
        fileName = "Filtering/average.txt";
	ba = fileName.toLatin1();
	this->firFilters[this->numberOfFiltersCreated]->SetFilterData(ba.data());
	this->numberOfFiltersCreated++;
	QFileInfo averagePathInfo(fileName);
	QString theAverageName(averagePathInfo.fileName());
	this->rtvtControllerView->addToFilterList(this->numberOfFiltersCreated, theAverageName);
	/***
	***/

	//QWidget *HUDWindow = new QWidget(this);
	//HUDWindow->setGeometry(100,100,400,800);

	hud = new MultiPageWidget(0);
	hud->setGeometry(50,550,375,450);
	hud->setContentsMargins(0,0,0,0);
	hud->insertPage(0,rtvtControllerView);
	hud->insertPage(1,rtvtWaveHUD);
	//hud->setStyle(new QWindowsStyle);
	hud->setCurrentIndex(0);

	// Load qss file for styling
	QFile file("qss/rtvthuddockstyle.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

	//hudDock = new QDockWidget("HUD Dock");
	//hudDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	
	// to hide the title bar completely must replace the default widget with a generic one
	//QWidget* titleWidget = new QWidget(this); /* where this a QMainWindow object */
	//hudDock->setTitleBarWidget( titleWidget );
    
	//hudDock->setStyleSheet(styleSheet);//"border-width: 1px; border-color: #535353; background-color: white;");
    //dataListWidget = new QListWidget(phDockBottom);
    //dataListWidget->setGeometry(0,0,1200,200);
    //hudDock->setFocusPolicy(Qt::NoFocus);
    //hudDock->setWidget(hud);
	//this->addDockWidget(Qt::LeftDockWidgetArea, hudDock);
	
	hud->hide();

	//this->connect(this->centralWidget(), SIGNAL(resize()), this, SLOT(resizeSelfAndViews()));

}

RTVTMainWindow::~RTVTMainWindow()
{
#ifndef USE_HS_USB
        free(backByteBuffer);
#endif
    free(drawingByteBuffer);
    free(storageByteBuffer);
    //free(workingByteBuffer);
    //free(workingChannelBuffer);
    //free(transferBuf);

    delete byteArray;
    delete dataObject;
    delete theTime;
    delete audioOutput;
#ifdef USE_AUDIO
    delete audioPlayer;
#endif
    delete firFilters;
    delete bbFuture;
    delete bbWatcher;
    delete bbTransferTimer;
    delete sbFuture;
    delete sbWatcher;
    delete sbTransferTimer;
    delete playTimer;
    delete rtvtControllerView;
    delete rtvtWaveHUD;
    delete theWaveTableModel;
    delete hud;




}

void RTVTMainWindow::initializeVariables()
{
        this->numberOfChannelViews = DEFAULT_NUM_CHANNEL_VIEWS;
        cout<<this->numberOfChannelViews <<endl;
	this->numberOfDataChannels = DEFAULT_NUM_CHANNELS_IN_DATA;

    this->playStep = 0;
    this->readDataStep = 0;
    this->dataPath = -1; //FILE_DATA_PATH_TYPE;
	this->dataSource = TEST_VECTOR_DATA_TYPE;
    this->readAllData = true;
    this->audioChannel = 1;
	this->continuousViewerNeedsDataNumber = 0;
	this->sbThreadIsRunning = false;
	this->missedSynch = 0;
	this->selectedWidgetNumber = 0;
	this->singleFrameLoss = 0;

	this->squareChannelGrid = false;

	this->byteArray = new QByteArray();

	this->rtvtSaveDataPath = "C:/Users/Public/test.dat";
	this->rtvtSavingData = false;
	this->numberOfFileSaves = 0;
    this->wireAddressing = DEFAULT_WIRE_ADDRESSING;

    this->dataObject = new RTVTDataObject();
	this->saveNEVState = false;
	
	this->shouldFilter = false;
        this->sampleFrameLength = SAMPLE_FRAME_LENGTH;

    sbWriteEndPtr = 0;
    sbDrawReadEndPtr = 0;
    sbAudioReadEndPtr = 0;

	backByteBuffer = (unsigned char *) malloc (sizeof(unsigned char) * length);
    drawingByteBuffer = (unsigned char *) malloc (sizeof(unsigned char) * DRAW_BUFFER_LENGTH);
    storageByteBuffer = (unsigned char *) malloc (sizeof(unsigned char) * STORAGE_BUFFER_LENGTH);
    //workingByteBuffer = (unsigned char *) malloc (sizeof(unsigned char) * BACK_BUFFER_LENGTH);
    //workingChannelBuffer = (unsigned char *) malloc (sizeof(unsigned char) * BACK_BUFFER_LENGTH / numberOfDataChannels);

	theDataArray.clear();
	transferBuf=(unsigned char *) malloc (sizeof(unsigned char) * BACK_BUFFER_LENGTH);
    //this->aBuffer = new QBuffer(&audioByteBuffer,this);
    //this->aBuffer->open(QIODevice::ReadOnly);
}

void RTVTMainWindow::setupChannelGrid()
{
    // Create grid for wave viewers
}

void RTVTMainWindow::centerMainWindow()
{
    QRect myAvailableGeometry = QDesktopWidget().availableGeometry();
    QRect myCurrentGeometry = this->frameGeometry();
    this->setGeometry(myAvailableGeometry.width() / 2 - myCurrentGeometry.width() / 2,
                            myAvailableGeometry.height() / 2 - myCurrentGeometry.height() / 2,
                            myCurrentGeometry.width(),
                            myCurrentGeometry.height());
}

void RTVTMainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_L:
        if(this->sbThreadIsRunning)//this->sbTransferTimer->isActive())
        {
                this->sbThreadIsRunning = false; //this->sbTransferTimer->stop();
                this->saveDataFile.close();

				emit appendToConsole("Data loading stopped.");
				this->rtvtControllerView->dataLoadingStopped();
        }
        else
        {
                //this->sbTransferTimer->setInterval(300);
                //const char *filepath = (const char*)this->rtvtSaveDataPath.data();
                //this->saveDataFile.setFileName(this->rtvtSaveDataPath);
                //if (!this->saveDataFile.open(QIODevice::WriteOnly))
                //{int t = 1;}

            // update the save path to new file name +1
#ifdef USE_AUDIO
            QString savePath = this->rtvtSaveDataPath;

            savePath = QString(savePath.replace(".snifr", QString("_" + QString::number(this->numberOfFileSaves) + ".snifr")));

            this->saveDataFile.setFileName(savePath);
                this->numberOfFileSaves++;
                if(!this->saveDataFile.open(QIODevice::WriteOnly))
                        qDebug()<<"Error opening the file";
                this->binStreamToWrite.setDevice(&this->saveDataFile);
                //this->streamToWrite.setDevice(&this->saveDataFile);

                //saveDataFile.open( QFile::WriteOnly );
#endif

                this->sbTransferTimer->setSingleShot(true);
                this->sbThreadIsRunning = true;
                this->sbTransferTimer->start();

				emit appendToConsole("Data loading started.");
				this->rtvtControllerView->dataLoadingStarted();
        }
            break;
        case Qt::Key_R:
            this->resetAllBuffers();
            break;
        case Qt::Key_N:
            //this->channelWidgetList[0]->setupNoisePlot();
            break;
        case Qt::Key_P:
			if(this->channelWidgetList.at(0)->isPlaying)
			{
				for(int i=0;i<this->channelWidgetList.count();i++)
					this->channelWidgetList.at(i)->stop();
				/*if(this->saveNEVState)
					this->nevWriter->end();*/
			}
            else
			{
				//memcpy (drawingByteBuffer, &storageByteBuffer[0], DRAW_BUFFER_LENGTH);
				//this->sbDrawReadEndPtr += DRAW_BUFFER_LENGTH;
				for(int i=0;i<this->channelWidgetList.count();i++)
					this->channelWidgetList.at(i)->play();
                this->updatePlay();

				//if(this->saveNEVState)
				//	this->nevWriter->start();
			}
            break;
        case Qt::Key_3:
                this->setupChannelGrid();
                break;
        case Qt::Key_U:
                if(!this->useAudio)
                {
                    this->startAudio = true;
                    this->useAudio = true;
                }
                else
                {
                    this->audioOutput->stop();
                    this->useAudio = false;
                }
                break;
        case Qt::Key_0:
                foreach (RTVTChannelWidget *cw, this->channelWidgetList)
                    cw->keyPressEvent(e);
            break;
        case Qt::Key_T:
                foreach (RTVTChannelWidget *cw, this->channelWidgetList)
                    cw->keyPressEvent(e);
            break;
        case Qt::Key_M:
                foreach (RTVTChannelWidget *cw, this->channelWidgetList)
                    cw->keyPressEvent(e);
            break;
        case Qt::Key_Y:
                foreach (RTVTChannelWidget *cw, this->channelWidgetList)
                    cw->keyPressEvent(e);
            break;
		case Qt::Key_D:
			foreach (RTVTChannelWidget *cw, this->channelWidgetList)
                    cw->keyPressEvent(e);
			break;
		case Qt::Key_S:
			foreach (RTVTChannelWidget *cw, this->channelWidgetList)
                    cw->keyPressEvent(e);
			break;
		case Qt::Key_W:
			foreach (RTVTChannelWidget *cw, this->channelWidgetList)
                    cw->keyPressEvent(e);
			break;
		case Qt::Key_A:
			foreach (RTVTChannelWidget *cw, this->channelWidgetList)
                    cw->keyPressEvent(e);
			//this->audioPlayer->startPlayingAudio();
			break;
		case Qt::Key_O:
			this->audioPlayer->show();
			//this->audioPlayer->startPlayingAudio();
			break;
		case Qt::Key_Up:
			if(this->channelWidgetList[this->selectedWidgetNumber]->assignedChannel == this->numberOfDataChannels)
				this->channelWidgetList[this->selectedWidgetNumber]->assignedChannel = 1;
			else
				this->channelWidgetList[this->selectedWidgetNumber]->assignedChannel += 1;

			this->channelWidgetList[this->selectedWidgetNumber]->update();
#ifdef USE_AUDIO
			this->audioPlayer->setCurrentIndex(this->channelWidgetList[this->selectedWidgetNumber]->assignedChannel-1);
#endif
			//foreach (RTVTChannelWidget *cw, this->channelWidgetList)
                    //cw->keyPressEvent(e);
			break;
		case Qt::Key_Down:
			if(this->channelWidgetList[this->selectedWidgetNumber]->assignedChannel == 1)
                                this->channelWidgetList[this->selectedWidgetNumber]->assignedChannel = this->numberOfDataChannels;
			else
				this->channelWidgetList[this->selectedWidgetNumber]->assignedChannel -= 1;

			this->channelWidgetList[this->selectedWidgetNumber]->update();
#ifdef USE_AUDIO
			this->audioPlayer->setCurrentIndex(this->channelWidgetList[this->selectedWidgetNumber]->assignedChannel-1);
#endif
			//foreach (RTVTChannelWidget *cw, this->channelWidgetList)
                    //cw->keyPressEvent(e);
			break;
		case Qt::Key_Left:
			foreach (RTVTChannelWidget *cw, this->channelWidgetList)
                    cw->keyPressEvent(e);
			break;
		case Qt::Key_Right:
			foreach (RTVTChannelWidget *cw, this->channelWidgetList)
                    cw->keyPressEvent(e);
			break;
		case Qt::Key_Z:
			foreach (RTVTChannelWidget *cw, this->channelWidgetList)
				cw->keyPressEvent(e);
			break;
		case Qt::Key_X:
			foreach (RTVTChannelWidget *cw, this->channelWidgetList)
                cw->keyPressEvent(e);
			break;
		case Qt::Key_I:
			foreach (RTVTChannelWidget *cw, this->channelWidgetList)
                cw->keyPressEvent(e);
			break;
        case Qt::Key_C:
            this->clearWaveformsOnChannels();
            break;
		case Qt::Key_G:
			foreach (RTVTChannelWidget *cw, this->channelWidgetList)
				cw->keyPressEvent(e);
			break;
        default:
                e->ignore();
    }

    e->ignore();
}

QString RTVTMainWindow::openExistingData()
{
    // Open dialog
    QFileDialog::Options options;
    QString selectedFilter;

    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("Open Existing Data File:"),
                                "",
                                tr("SNIFR Files (*.snifr);;All Files (*);;Data Files (*.dat);;CSV Files (*.csv)"),
                                &selectedFilter,
                                options);
    if (!fileName.isEmpty())
    {
        this->openDataFileHandle.setFileName(fileName);
        if (!this->openDataFileHandle.open(QIODevice::ReadOnly)) {
            std::cerr << "Cannot open file for reading: "<< qPrintable(this->openDataFileHandle.errorString()) << std::endl;
            return QString("Error opening file");
        }

        this->playStep = 0;
        this->readDataStep = 0;
        std::cout << "Done opening file: " << qPrintable(fileName) << std::endl;
		return fileName;
    }
    else
    {}

	return QString("No error, no file...");

}

void RTVTMainWindow::chooseFileForSavingData()
{
    // Open dialog
    QFileDialog::Options options;
    QString selectedFilter;

    QString fileName = QFileDialog::getSaveFileName(this,
                                tr("Choose a file to save data:"),
                                "",
                                tr("All Files (*)"),
                                &selectedFilter,
                                options);
    if (!fileName.isEmpty())
    {
        this->saveDataFileHandle.setFileName(fileName);
        if (!this->saveDataFileHandle.open(QIODevice::WriteOnly)) {
            std::cerr << "Cannot open file for writing: "<< qPrintable(this->saveDataFileHandle.errorString()) << std::endl;
            return;
        }

        std::cout << "Done opening file for data out stream: " << qPrintable(fileName) << std::endl;
    }
    else
    {}

}

void RTVTMainWindow::setAddressingTo(int numWire)
{
    this->wireAddressing = numWire;
    if(numWire==2)
    {
        this->sampleFrameLength = 12;
        this->systemClockRate = 24000000;
    }
    else
    {
        this->sampleFrameLength = 24;
        this->systemClockRate = 13560000;
    }

    for(int i=0;i<this->channelWidgetList.count();i++)
    {
         this->channelWidgetList.at(i)->setAddressScheme(numWire);
         //this->channelWidgetList.at(i)->setSystemClockRate(this->systemClockRate);
    }

    this->redrawChannelViews();
}

void RTVTMainWindow::playFromController(bool withRecording)
{
    Q_UNUSED(withRecording);

    // Start the loading
    if(this->sbThreadIsRunning)//this->sbTransferTimer->isActive())
    {
        this->sbThreadIsRunning = false; //this->sbTransferTimer->stop();

        if(this->rtvtSavingData)
            this->saveDataFile.close();
#ifdef USE_AUDIO
        this->audioPlayer->toggleSuspendResume();
#endif
		emit appendToConsole("Data loading stopped at: " + (QTime::currentTime()).toString());
        this->rtvtControllerView->dataLoadingStopped();
    }
    else
    {

        if(this->rtvtSavingData)
        {
            QString savePath = this->rtvtSaveDataPath;

            savePath = QString(savePath.replace(".snifr", QString("_" + QString::number(this->numberOfFileSaves) + ".snifr")));

            this->saveDataFile.setFileName(savePath);
            this->numberOfFileSaves++;
            if(!this->saveDataFile.open(QIODevice::WriteOnly))
                    qDebug()<<"Error opening the file";
            this->binStreamToWrite.setDevice(&this->saveDataFile);
        }

        this->sbTransferTimer->setSingleShot(true);
        this->sbThreadIsRunning = true;
        this->sbTransferTimer->start();

		emit appendToConsole("-------------------------------------------------------------");
		emit appendToConsole("Data loading started at: " + (QTime::currentTime()).toString());
        this->rtvtControllerView->dataLoadingStarted();
    }

    // Start the playing
    if(this->channelWidgetList.at(0)->isPlaying)
        for(int i=0;i<this->channelWidgetList.count();i++)
             this->channelWidgetList.at(i)->stop();
    else
        for(int i=0;i<this->channelWidgetList.count();i++)
            this->channelWidgetList.at(i)->play();

    // Start the thresholding
    //QKeyEvent e = QKeyEvent(QEvent::KeyPress,Qt::Key,Qt::NoModifier);
    QKeyEvent e = QKeyEvent(QEvent::KeyPress,Qt::Key_T,Qt::NoModifier);
    this->keyPressEvent(&e);
}

void RTVTMainWindow::updatePlay()
{
	// Check if we need to update the drawing buffer from storage
//	if((playStep*DRAW_FRAME_LENGTH) > (DRAW_BUFFER_LENGTH-DRAW_FRAME_LENGTH))
	//{
		// Check if we still have data to pull from storage buffer - if not, repeat
		/*
		if(this->sbDrawReadEndPtr > (this->sbWriteEndPtr - DRAW_BUFFER_LENGTH))
			this->sbDrawReadEndPtr = 0;

		memcpy (drawingByteBuffer, &storageByteBuffer[this->sbDrawReadEndPtr], DRAW_BUFFER_LENGTH);
		
		if(this->sbDrawReadEndPtr >= (STORAGE_BUFFER_LENGTH - DRAW_BUFFER_LENGTH))
			this->sbDrawReadEndPtr = 0;
		else
			this->sbDrawReadEndPtr += DRAW_BUFFER_LENGTH;

		// Reset the read ptr for views
		int c = this->channelWidgetList.count();

		for(int i=0;i<this->channelWidgetList.count();i++)
		{
			this->channelWidgetList.at(i)->resetReadPointer();
			this->channelWidgetList.at(i)->setDrawFromData(true);
		}

		this->playStep = 0;

#ifdef RTVT_DEBUG
	this->rtvtControllerView->ui->debugConsole->append(":: Made storageBuffer-drawBuffer transfer ::");
#endif

	//}

	//this->playStep++;
	*/
}

void RTVTMainWindow::makeDataStoreToBackBufferTransfer()
{
    if(this->dataPath == FILE_DATA_PATH_TYPE)
    {
        if(!this->openDataFileHandle.isReadable())
            return;

        int tempPos = this->openDataFileHandle.pos();
        this->openDataFileHandle.seek(tempPos + BACK_BUFFER_LENGTH);

        if(!this->openDataFileHandle.atEnd()) 
		{
			
			this->openDataFileHandle.seek(tempPos);
		}
        else {
			qDebug("@ end of file");
            this->openDataFileHandle.seek(0);
        }

		// Lock to transfer
		bbMutex.lock();
			theDataArray = this->openDataFileHandle.read(BACK_BUFFER_LENGTH);
			transferBuf = (unsigned char*)theDataArray.data();
			memcpy(&backByteBuffer[0], transferBuf, BACK_BUFFER_LENGTH);
		bbMutex.unlock();
        // Unlocked
		
    }
#ifdef USE_HS_USB
	else if(this->dataPath == HSUSB_DATA_PATH_TYPE)
	{
            // Check for space in storage buffer
            if(this->sbWriteEndPtr > (STORAGE_BUFFER_LENGTH-BACK_BUFFER_LENGTH))
                    this->sbWriteEndPtr = 0;

            hsHAL->makeUSBTransfer();
	}
#endif
}

void RTVTMainWindow::makeBackToStorageBufferTransfer()
{
        // Should make the working buffer here so it can be used by each thread as it wants...
        unsigned char *workingByteBuffer;
        workingByteBuffer = (unsigned char *) malloc (sizeof(unsigned char) * BACK_BUFFER_LENGTH);

	this->makeDataStoreToBackBufferTransfer(); // Fill the back buffer
	
	// No matter what, update the pointer
	if(this->sbWriteEndPtr > (STORAGE_BUFFER_LENGTH - (BACK_BUFFER_LENGTH)))
        this->sbWriteEndPtr = 0; // Write over at the beginning of the buffer
	
#ifdef USE_HS_USB
	if(this->dataPath == HSUSB_DATA_PATH_TYPE)
	{
	// Always add the new data to the end of the storage buffer and increment ptr
	memcpy(&storageByteBuffer[this->sbWriteEndPtr],&backByteBuffer[hsHAL->bbNextReadPtr],(BACK_BUFFER_LENGTH));

	/*** Break into channels and place in channel data buffer ***/
	// Copy into workign buffer
	memcpy(workingByteBuffer,&backByteBuffer[hsHAL->bbNextReadPtr],BACK_BUFFER_LENGTH);
	
	}
	else if(this->dataPath == FILE_DATA_PATH_TYPE)
	{
		memcpy(&storageByteBuffer[this->sbWriteEndPtr],&backByteBuffer[0],(BACK_BUFFER_LENGTH));
		memcpy(workingByteBuffer,&backByteBuffer[0],BACK_BUFFER_LENGTH);
	}
#else
	memcpy(&storageByteBuffer[this->sbWriteEndPtr],&backByteBuffer[0],(BACK_BUFFER_LENGTH));
        memcpy(workingByteBuffer,&backByteBuffer[0],BACK_BUFFER_LENGTH);
#endif
	
	// No matter what, update the pointer
	this->sbWriteEndPtr += BACK_BUFFER_LENGTH;
	
	
	// Should need to spin this to a thread... running slowly
	if(this->rtvtSavingData)
	{
		//extern void threadedSaveRawData();
                QFuture<void> future = QtConcurrent::run(this,&RTVTMainWindow::threadedSaveRawData);

            // Try not threaded for now
            //this->threadedSaveRawData();
	}

	// Spin thread to burn through the data / separating to channels, etc.

        QFuture<void> future = QtConcurrent::run(this,&RTVTMainWindow::threadedChannelSeparation, workingByteBuffer);
        //future.waitForFinished();
        //this->threadedChannelSeparation();
	
	#ifdef RTVT_DEBUG
	//this->rtvtControllerView->appendToDebugConsole(":: Made Working to Channel transfer ::");
#endif
	/*QTimer *silkThreadTimer = new QTimer(this);
    connect(silkThreadTimer, SIGNAL(timeout()), this, SLOT(threadedChannelSeparation()));
    silkThreadTimer->start();*/

}

void RTVTMainWindow::threadedSaveRawData()
{
	// Binary save
	this->binStreamToWrite.writeRawData((char*)backByteBuffer, BACK_BUFFER_LENGTH);

	//Text Save
	/*for(int w=0;w<BACK_BUFFER_LENGTH/2;w++)
			this->streamToWrite<<(backByteBuffer[w*2+1]*256+backByteBuffer[w*2]);*/
}

void RTVTMainWindow::saveSNIFFRToMat()
{
    QFile saveFileHandle;
    QFileDialog::Options options;
    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(this,
                                tr("Choose save file name:"),
                                "",
                                tr("Data Files (*.dat)"),
                                &selectedFilter,
                                options);
    if (!fileName.isEmpty())
    {
        saveFileHandle.setFileName(fileName);
        if (!saveFileHandle.open(QIODevice::WriteOnly)) {
            std::cerr << "Cannot open file for writing: "<< qPrintable(this->openDataFileHandle.errorString()) << std::endl;
        }

        std::cout << "Opened file to write: " << qPrintable(fileName) << std::endl;
    }
    else
    {}

    this->openDataFileHandle.seek(0);

    QTextStream out(&saveFileHandle);
    unsigned int i = 0;
    QByteArray theDataArray;
    unsigned char *buf;
    buf=(unsigned char *) malloc (sizeof(unsigned char) * BACK_BUFFER_LENGTH);
    int frameSynchIndex = -1;
    unsigned int counter = 0;
    int values[102];				// need to fix this - does not need to be a number in MAC OS X

    theDataArray = this->openDataFileHandle.readAll();
    unsigned int lengthOfFile = theDataArray.length();
    buf = (unsigned char*)theDataArray.data();

    // Find start point in the data after frame synch
    frameSynchIndex = this->findFrameSynchInData(buf);
    i = frameSynchIndex*2+2;

	// Start a progress bar dialog since this task takes all of thread
	QProgressDialog progress("Converting SNIFFR to DAT...", "Abort save", 0, (lengthOfFile-frameSynchIndex*2-102*2), this); // fix here for both 16 and 101 channels ystems
    progress.setWindowModality(Qt::WindowModal);

    // Always starting at channel 0, so find synch, go up two bytes, and begin reading

    // Burn through all the data and write to file - start at framesynchindex + 1 for channel 0
    for(unsigned int k = 0;k<(lengthOfFile-frameSynchIndex*2-this->numberOfDataChannels*2);k=k+204)
    {
		progress.setValue(k);
		if (progress.wasCanceled())
             break;
        //fill the values array
        unsigned int chCounter=0;

        for(chCounter=0;chCounter<this->numberOfDataChannels;chCounter++)
            values[chCounter] = ((buf[i+k+chCounter*2+1] & 0x0F)*256 + buf[i+k+chCounter*2]);

        for(chCounter=0;chCounter<this->numberOfDataChannels;chCounter++)
            out << (qint16)values[chCounter] << QString(" ");
        out << endl;

        /*out << (qint16)values[0] << QString(" ") << (qint16)values[1] << QString(" ") << (qint16)values[2] << QString(" ")
                << (qint16)values[3] << QString(" ") << (qint16)values[4] << QString(" ") << (qint16)values[5] << QString(" ")
                << (qint16)values[6] << QString(" ") << (qint16)values[7] << QString(" ") << (qint16)values[8] << QString(" ")
                << (qint16)values[9] << QString(" ") << (qint16)values[10] << QString(" ") << (qint16)values[11] << QString(" ")
                << (qint16)values[12] << QString(" ") << (qint16)values[13] << QString(" ") << (qint16)values[14] << QString(" ")
                << (qint16)values[15] << endl;
                */
    }

        progress.setValue((lengthOfFile-frameSynchIndex*2-this->numberOfDataChannels*2));

    counter++;


    saveFileHandle.close();

}

void RTVTMainWindow::threadedChannelSeparation(unsigned char *workingInBuffer)
{
	// Find start point in the data after frame synch
	int startingLocation = 0;
	int workingChannel = 0;
	unsigned int startChannel = 0;
        unsigned int evenOddShift = 0;
        unsigned int frameSynchIndex = this->findFrameSynchInData(workingInBuffer);

        // Should make the working buffer here so it can be used by each thread as it wants...
        unsigned char *workingChannelBufferTemp;
        workingChannelBufferTemp = (unsigned char *) malloc (sizeof(unsigned char) * BACK_BUFFER_LENGTH);

        /*if(frameSynchIndex < (this->numberOfDataChannels)) // Meaning that frame synch is not the first data in the buffer
	{
                startChannel = (this->numberOfDataChannels) - frameSynchIndex; // find channel to start working on first
		startingLocation = 0;//(15 - frameSynchIndex)*2; // align the data to fit the channel
	}
	else // start from this point forward
	{
                startChannel = this->numberOfDataChannels;
                startingLocation = frameSynchIndex*2;
	}
        */

        // Find the channel that the 0 and 1 index represent
        // check if FSI is > number of channels - meaning we missed a synch and want to start at new frame
        if(frameSynchIndex > numberOfDataChannels)
            startChannel = numberOfDataChannels;
        else
        {
            // if odd, we need to adjust since only half the startLocation is part of the startChannel sample
            int test1 = frameSynchIndex/2;
            double test2 = ceil((((double)frameSynchIndex+1)/2));
            if(test1 == test2)
            {
                // add shift to startingLocation and set start channel to 1 higher
                startChannel = numberOfDataChannels - (frameSynchIndex+1)/2 +1;
                evenOddShift = 1;
            }
            else //if even
                startChannel = numberOfDataChannels - (frameSynchIndex)/2;
        }


	// Substract from synch the channels before to get to starting channel of data
	// Always starting at channel 0, so find synch, go up two bytes, and begin reading

	// Burn through all the data and separate into channels
	workingChannel = startChannel;
	for(int z = 0; z<numberOfChannelViews;z++) // changing to numberOfDataChannels
	{
		// Need to find the channel to copy to - check assigned channel of view #1 and so on
		unsigned int activeChannel = this->channelWidgetList.at(z)->assignedChannel;
                /*if(activeChannel <= startChannel)
			startingLocation = (frameSynchIndex + activeChannel)*2;
		else 
                        startingLocation = ((activeChannel) - (startChannel))*2;
                */

                // Check if we are going to read from before or after the frameSynch
                if (activeChannel == numberOfDataChannels)
                    startingLocation = frameSynchIndex;
                else if(activeChannel < startChannel)
                    startingLocation = frameSynchIndex + activeChannel*2 + evenOddShift;
                else if(activeChannel > (startChannel))
                    startingLocation = (activeChannel - startChannel)*2 + evenOddShift; // was this: frameSynchIndex - (activeChannel - startChannel)*2 + evenOddShift; // were getting data displayed across channels


		// Check to see where we should begin writin // should optimize this to not have if all the time
		unsigned int bytesWritten = 0;
		for(int i=startingLocation;i<BACK_BUFFER_LENGTH;)
		{
                        if(activeChannel == DEFAULT_SYNCH_CHANNEL)
                            if(!(((unsigned char)workingInBuffer[i] == 0x21)&&((unsigned char)workingInBuffer[i+1]== 0xCD)))
							{
                                                                if((((unsigned char)workingInBuffer[i+numberOfDataChannels*2] == 0x21)&&((unsigned char)workingInBuffer[i+1+numberOfDataChannels*2]== 0xCD)))
									this->singleFrameLoss++;
								//else
									//this->missedSynch++;
									/*char sTmp1[4],sTmp2[4];

								sprintf(sTmp1,"0x%x",workingByteBuffer[i]);// Why is this ff for synch and not cd????
								sprintf(sTmp2,"0x%x",workingByteBuffer[i+1]);
								*/
								
							}

			// Add data from single channel to working buffer 
			// Bring down to 12 bit value
                        workingChannelBufferTemp[bytesWritten + 1] = workingInBuffer[i+1] & 0x0F;
                        workingChannelBufferTemp[bytesWritten] = workingInBuffer[i];

			//memcpy(&workingChannelBuffer[bytesWritten], &workingByteBuffer[i],2*sizeof(unsigned char));
			i += numberOfDataChannels * 2;
			bytesWritten += 2;
		}

		// Transfer from working buffer to channel
		unsigned int startWriteLocation = this->channelWidgetList.at(z)->getNextWriteLocation();
                memcpy(&this->channelWidgetList.at(z)->channelData[startWriteLocation], &workingChannelBufferTemp[0],(bytesWritten));//BACK_BUFFER_LENGTH / numberOfDataChannels);

#ifdef USE_AUDIO
		// copy to audio buffer if not filtering
                if(activeChannel == this->audioChannel && !this->shouldFilter)
                        this->audioPlayer->m_generator->writeData((const char*)&workingChannelBufferTemp[0],static_cast<qint64>(BACK_BUFFER_LENGTH / numberOfDataChannels));
#endif
		// Set the new ptr to the last location written
		this->channelWidgetList.at(z)->updateNextWriteLocationWithAddition(bytesWritten);
		
// For filtering
		
		if(this->shouldFilter)
		{
			//unsigned char *p_siSrcAddr;	// Local scope pointers to source/destination 
			double dMax, dMin, dMean, dMeanScale;;	// Local storage and work variable for data being filtered
			double* dFiltSource = new double[BACK_BUFFER_LENGTH/numberOfDataChannels/2]; //(4000doubles)
			double* dFilteredDataArray = new double[BACK_BUFFER_LENGTH/numberOfDataChannels/2];
			
			// Calculate length to pass filter all data in half buffer
			int iLenToPassFilter = this->firFilters[this->selectedFilterIndex]->GetFilterLen() + BACK_BUFFER_LENGTH/numberOfDataChannels/2;
			
			// Transfer from working buffer to channel
			unsigned int filterStartWriteLocation = this->channelWidgetList.at(z)->getNextFilterWriteLocation();
			
			// Do a recast and filter - may run slow at first - could change later to make double here and ONLY here
			dMeanScale = (double)(2.4/4096/BACK_BUFFER_LENGTH/numberOfDataChannels/2);
			dMean = 0.0;
			// This is reducing data by 2 since 2 bytes per sample
                        for (unsigned int j = 0; j < BACK_BUFFER_LENGTH/numberOfDataChannels/2; j+=1)
			{ //  copy and recast input data
				//dFiltSource[j] = (((double)this->channelWidgetList.at(z)->channelData[j*2+1])*256.0)+(double)(this->channelWidgetList.at(z)->channelData[j*2]);
                                dFiltSource[j] = (((double)workingChannelBufferTemp[j*2+1])*256.0)+((double)workingChannelBufferTemp[j*2]);
				dMean += dFiltSource[j];
			}
			
			dMean = dMean*dMeanScale;
			
			this->firFilters[this->selectedFilterIndex]->ApplyFilter(iLenToPassFilter, &dFiltSource[0], &dFilteredDataArray[0], &dMax, &dMin); // Here is the actual filtering
			
			memcpy(&this->channelWidgetList.at(z)->filteredChannelData[filterStartWriteLocation], &dFilteredDataArray[0],(BACK_BUFFER_LENGTH/numberOfDataChannels/2)*sizeof(double));
			
			this->channelWidgetList.at(z)->updateNextFilterWriteLocationWithAddition(BACK_BUFFER_LENGTH/numberOfDataChannels/2);
			//this->channelWidgetList.at(z)->updateMean(dMean);
			
			if(activeChannel == this->audioChannel)
				this->audioPlayer->m_generator->writeData((const char*)&dFilteredDataArray[0],static_cast<qint64>((BACK_BUFFER_LENGTH/2/numberOfDataChannels)*sizeof(double)));

			delete dFiltSource;
			delete dFilteredDataArray;
		}
		
#ifdef USE_AUDIO
		// Transfer to audio buffer - if turned on
		// Transfer the active audio channel to audiobuffer... 
                //this->audioPlayer->audioBuffer->write((const char*)&this->channelWidgetList[0]->channelData[this->channelWidgetList[0]->nextWriteLocation - BACK_BUFFER_LENGTH/numberOfDataChannels], BACK_BUFFER_LENGTH/numberOfDataChannels);
		
		
                //if((this->audioPlayer->isPlaying) && (this->audioPlayer->selectedChannel == z))
                //	memcpy(&this->audioPlayer->gen->buffer[0],&workingChannelBuffer[0],BACK_BUFFER_LENGTH / numberOfDataChannels);
#endif

		// Update the active channel
		/*if(workingChannel == (numberOfDataChannels - 1))
			workingChannel = 0;
		else
			workingChannel++;*/

		//startingLocation += 2;
		
		
	}

       delete workingInBuffer;
       delete workingChannelBufferTemp;

}

unsigned int RTVTMainWindow::findFrameSynchInData(unsigned char *data)
{
	// Find frame synch
	// Need to have a synch finder when synch not found... 16 in a frame let's say 10 frames
        int framesToCheck = 2;
        unsigned int currentFrame = 0;

	int byteOffset = 0; // had a byte offset of 2048

    for(unsigned int byteIndex=byteOffset;byteIndex<(byteOffset+(numberOfDataChannels*2*framesToCheck));byteIndex++)
	{
                char sTmp1[30],sTmp2[30];

		
		//unsigned char v1, v2;

                sprintf(sTmp1,"0x%x",(int)data[byteIndex]);// Why is this ff for synch and not cd????
                sprintf(sTmp2,"0x%x",(int)data[byteIndex+1]);
		
		/** 
			Below is no longer true once we shifted the clock line to match better the data
			x21 xCF for real BIC data
			x21 xCD for test data
		**/
                //if(byteIndex>numberOfDataChannels){};

                // Check next frame synch, make sure we are aligned
                if(((unsigned char)data[byteIndex] == 0x21)&&((unsigned char)data[byteIndex+1]== 0xCD))
                {
                    bool lostSynch = false;

                    for(unsigned int synchsToCheck = 1; synchsToCheck<10; synchsToCheck++)
                    {
                        if(!(((unsigned char)data[byteIndex+numberOfDataChannels*2*synchsToCheck] == 0x21)&&((unsigned char)data[byteIndex+1+numberOfDataChannels*2*synchsToCheck]== 0xCD)))
                        {
                            cout << "Lost frame @ " << synchsToCheck << endl;
                            lostSynch = true;
							this->missedSynch++;
                        }
                    }

                    if(!lostSynch)
                        return byteIndex;
                    else
                        cout << "Lost @ byte index: " << byteIndex << endl;
                }


                //currentFrame++;

                // For debugging
		/*if(this->dataSource == TEST_VECTOR_DATA_TYPE)
                {
                v1 = (unsigned char)data[byteIndex*2];
                v2 = (unsigned char)data[byteIndex*2+1];
                if(v1 == 0x21)
                {
                        int x = 1;
                }
                if(v2 == 0xcd)
                {
                        int y = 1;
                }

                //}
                //else if(this->dataSource == BIC_DATA_TYPE)
                //{
                //	if((data[byteIndex*2] == 0x21)&&(data[byteIndex*2+1]== 0xCF))//if((sTmp1[2] == '2') && (sTmp1[3] == '1') && (sTmp2[2] == 'c') && (sTmp2[3] == 'd'))
                //		return byteIndex;
                //}

                */

		// changed from 21cd to 21cc for Rhip low-voltage value - we could check for this and report...

	}

	this->missedSynch++;
	return 0;
}

void RTVTMainWindow::makeStorageToAudioBufferTransfer()
{
 //   int startCounter = 0;
 //   char *tempAudioBuff;
 //   sbMutex.lock();

 //   if(this->sbAudioReadEndPtr >= sizeof(storageByteBuffer) - AUDIO_BUFFER_LENGTH))
 //       this->sbAudioReadEndPtr = 0;

	//tempAudioBuff = (unsigned char*)malloc (sizeof(char) * AUDIO_BEFFER_LENGTH);
 //   tempAudioBuff = memcpy(storageByteBuffer.mid(sbAudioReadEndPtr,AUDIO_BUFFER_LENGTH);
 //   sbAudioReadEndPtr += AUDIO_BUFFER_LENGTH;

 //   sbMutex.unlock();

 //   // Find frame synch
 //   for(int f=0;f<15;f++)
 //   {
 //       // Convert to hex for comparrison
 //      char sTmp1[30],sTmp2[30];
 //      char out[128];
 //      sprintf(sTmp1,"0x%x",(quint8)tempAudioBuff.data()[(f*2)]);
 //      sprintf(sTmp2,"0x%x",(quint8)tempAudioBuff.data()[(f*2)+1]);
 //      out[f*5]=sTmp1[2];
 //      out[f*5+1]=sTmp1[3];
 //      out[f*5+2]=sTmp2[2];
 //      out[f*5+3]=sTmp2[3];
 //      out[f*5+4]=' ';

 //      if((sTmp1[2] == '2') && (sTmp1[3] == '1') && (sTmp2[2] == 'c') && (sTmp2[3] == 'd'))
 //      {
 //          startCounter = f;
 //          f = 15;
 //      }
 //   }

 //   // Collect from this channel pointer on to end of window
 //   int i = 0;
 //   for(i=(startCounter+(this->audioChannel))*2;i<tempAudioBuff.length();i=i+16*2)
 //       audioByteBuffer.append(tempAudioBuff.mid(i,2));


}

void RTVTMainWindow::addFilterFromFile()
{
	if(this->numberOfFiltersCreated != MAX_NUMBER_OF_FILTERS)
	{
		QString fileName = QFileDialog::getOpenFileName(this, tr("Open Filter Coefficients File"),
														QDir::currentPath(),
														tr("txt (*.txt)"));
		QByteArray ba = fileName.toLatin1();
		
		this->firFilters[this->numberOfFiltersCreated]->SetFilterData(ba.data());
		this->numberOfFiltersCreated++;
		
		QFileInfo pathInfo(fileName);
		
		QString theName(pathInfo.fileName());
		
		this->rtvtControllerView->addToFilterList(this->numberOfFiltersCreated, theName);
	}
}

void RTVTMainWindow::updateSelectedFilter(int ind)
{
	this->selectedFilterIndex = ind;
	this->shouldFilter = true;
	foreach (RTVTChannelWidget *cw, this->channelWidgetList)
		cw->isFiltering = true;
}

void RTVTMainWindow::stopFilteringData()
{
	this->shouldFilter = false;
	foreach (RTVTChannelWidget *cw, this->channelWidgetList)
		cw->isFiltering = false;
}

void RTVTMainWindow::loadDataFromSource()
{
    // Set a timer to transfer and display...
    //std::cout << qPrintable(QString("Progressing using %1 thread(s)...").arg(QThread::idealThreadCount())) << std::endl;
    if(this->dataPath == FILE_DATA_PATH_TYPE && this->readAllData)
    {
        this->openDataFileHandle.seek(0);

        while(!this->openDataFileHandle.atEnd())
        {
            // Untimed here to keep the synchonisity

            this->makeDataStoreToBackBufferTransfer();
            this->makeBackToStorageBufferTransfer();
            readDataStep++;
        }

        this->playStep = 0;

        std::cout << "At end of file:: Read Data: " << readDataStep << " :: Back Buffer Length: " << BACK_BUFFER_LENGTH << std::endl;
        //std::cout << "Done reading all data from file." << std::endl;
    }
	else if(this->dataPath == HSUSB_DATA_PATH_TYPE)
	{
		//sbMutex.lock();
		this->makeDataStoreToBackBufferTransfer();
        this->makeBackToStorageBufferTransfer();
        //sbMutex.unlock();
		//readDataStep++;

		//this->playStep = 0;

		/*for(int i=0;i<this->waveWidgetList.count();i++)
			this->waveWidgetList.at(i)->readFromDrawBufferFramePtr = 1;*/
	}
}

void RTVTMainWindow::viewWasDoubleClicked(int channel)
{
    this->audioChannel = channel;
    std::cout << "Audio channel is now: " << this->audioChannel << std::endl;
}

void RTVTMainWindow::continuousViewReachedEndOfData(int channel)
{
	this->continuousViewerNeedsDataNumber += channel;
    if(this->continuousViewerNeedsDataNumber == numberOfChannelViews)
	{
		this->updatePlay();
		this->continuousViewerNeedsDataNumber = 0;
	}
}

void RTVTMainWindow::tellViewsToDraw()
{
 //   //std::cout << "Draw data pressed..." << std::endl;

	//if(this->dataPath == HSUSB_DATA_PATH_TYPE)
	//	this->playStep++;
 //   else if(readDataStep>playStep || (this->readAllData)) {this->playStep++;}

 //   this->sbFuture->waitForFinished();

 //   //this->dataObject->addToChannelArray(storageByteBuffer.mid((playStep-1)*DRAW_BUFFER_LENGTH, DRAW_BUFFER_LENGTH));

 //   if(this->sbDrawReadEndPtr >= (STORAGE_BUFFER_LENGTH - DRAW_BUFFER_LENGTH))
	//{
 //       this->sbDrawReadEndPtr = 0;
	//	playStep = 0;
	//}
 //   else
 //       this->sbDrawReadEndPtr = (playStep-1)*DRAW_BUFFER_LENGTH;

 //   for(int i=0;i<this->waveWidgetList.count();i++)
 //   {
 //       //this->waveWidgetList.at(i)->drawBuffer = storageByteBuffer.mid(this->sbDrawReadEndPtr, DRAW_BUFFER_LENGTH);
 //       this->waveWidgetList.at(i)->drawingFromData = true;
 //       this->waveWidgetList.at(i)->needsRedraw = true;
 //       this->waveWidgetList.at(i)->update();
	//	this->waveWidgetList.at(i)->readFromDrawBufferFramePtr++;
 //   }

 //   this->tellAudioToPlay();
}

void RTVTMainWindow::tellAudioToPlay()
{
    //std::cout << "At Play step: " << (playStep-1) << ":: and Draw Buffer*playStep: " << (playStep-1)*DRAW_BUFFER_LENGTH/(16*2) << ":: Should end at: " << BACK_BUFFER_LENGTH/(16*2) << std::endl;

    //if(this->sbDrawReadEndPtr>=this->sbAudioReadEndPtr)
    //    this->makeStorageToAudioBufferTransfer();

    //if(this->useAudio)
    //{
    //    if(this->startAudio)
    //    {

    //        std::cout << "Audio Buffer Length: " << audioByteBuffer.length() << std::endl;

    //        this->aBuffer->setData(audioByteBuffer);
    //        //this->aBuffer->seek(); //(playStep-1)*DRAW_BUFFER_LENGTH/(16*2)
    //        this->audioOutput->start(this->aBuffer);

    //        this->startAudio = false;
    //    }
    //}
    //else
    //    this->audioOutput->stop();
}

void RTVTMainWindow::loadDataToTableOnChannels(int start, int)
{
    QStringList theListToDisplay((QList<QString>)this->dataObject->returnDoubleListOfLengthForChannel(DRAW_BUFFER_LENGTH,start));

    this->dataListWidget->clear();
    this->dataListWidget->insertItems(0,theListToDisplay);
}

void RTVTMainWindow::runThreadedDataBBTransfer()
{
	this->makeDataStoreToBackBufferTransfer();

    //*bbFuture = QtConcurrent::run(this,&RTVTMainWindow::makeDataStoreToBackBufferTransfer);
    //bbWatcher->setFuture(*bbFuture);
}

void RTVTMainWindow::bbThreadFinishedRunning()
{
    //std::cout << "BB Thread finished running." << std::endl;

    this->bbTransferTimer->stop();

    this->sbTransferTimer->start(200);
}

void RTVTMainWindow::runThreadedDataSBTransfer()
{
	//this->makeBackToStorageBufferTransfer();
    *sbFuture = QtConcurrent::run(this,&RTVTMainWindow::makeBackToStorageBufferTransfer);
    sbWatcher->setFuture(*sbFuture);
}

void RTVTMainWindow::sbThreadFinishedRunning()
{
    //std::cout << "SB Thread finished running." << std::endl;

    //this->sbTransferTimer->stop();

#ifdef RTVT_DEBUG
        this->rtvtControllerView->appendToDebugConsole(":::: Made datastore-backByteBuffer-storageBuffer-workingBuffer-channelBuffers transfers ::::");
		this->rtvtControllerView->appendToDebugConsole(QString(":::: Number synchs misses:%1 ::::").arg(this->missedSynch));
		this->rtvtControllerView->appendToDebugConsole(QString(":::: Number of single-frame synchs lost: %1 ::::").arg(this->singleFrameLoss));
        cout << "# missed synchs: " << this->missedSynch << endl;
		cout << "# of single frame synchs missed: " << this->singleFrameLoss << endl;
		this->singleFrameLoss = 0;
#endif

	if(this->sbThreadIsRunning)
		this->sbTransferTimer->start(200);
}

void RTVTMainWindow::runThreadedDataABTransfer()
{
    *abFuture = QtConcurrent::run(this,&RTVTMainWindow::makeStorageToAudioBufferTransfer);
    abWatcher->setFuture(*abFuture);
}

void RTVTMainWindow::abThreadFinishedRunning()
{
    //std::cout << "AB Thread finished running." << std::endl;

    //this->abTransferTimer->stop();
}

void RTVTMainWindow::resetAllBuffers()
{
	// Stop the transfers
	if(this->sbTransferTimer->isActive())
        this->sbTransferTimer->stop();
	
	// Stop the playing
	for(int i=0;i<this->channelWidgetList.count();i++)
		this->channelWidgetList.at(i)->stop();

	// Reset read/write ptrs
	this->sbWriteEndPtr = 0;
	for(int i=0;i<this->channelWidgetList.count();i++)
		this->channelWidgetList.at(i)->resetReadPointer();

	// Reactivate timers
	this->sbTransferTimer->start(200);
	for(int i=0;i<this->channelWidgetList.count();i++)
		this->channelWidgetList.at(i)->play();
	this->updatePlay();

	// Done
}

void RTVTMainWindow::resizeSelfAndViews()
{
	/*this->centralWidget()->update();

	for(int i=0;i<this->channelWidgetList.count();i++)
		this->channelWidgetList.at(i)->updateChannelViews();
		*/
}

void RTVTMainWindow::resizeEvent (QResizeEvent * e)
{
	//e->ignore();
	Q_UNUSED(e);
	this->update();
	this->centralWidget()->repaint();
	/*
	for(int i=0;i<this->channelWidgetList.count();i++)
		this->channelWidgetList.at(i)->updateChannelViews();
		*/
}

void RTVTMainWindow::setSaveDataPath(QString inPath)
{
	this->rtvtSaveDataPath = inPath;
	this->numberOfFileSaves = 0;
}

void RTVTMainWindow::setSaveDataBool(bool inBool)
{
	this->rtvtSavingData = inBool;
}

// These functions should be going straight to the wave views, not through the main window controller. 
void RTVTMainWindow::clearWaveformsOnChannels()
{
	foreach (RTVTChannelWidget *cw, this->channelWidgetList)
        cw->waveViewer->clearWaveforms();
}

void RTVTMainWindow::resetTriggersOnChannels()
{
	foreach (RTVTChannelWidget *cw, this->channelWidgetList)
        cw->waveViewer->resetTriggers();
}

void RTVTMainWindow::propogateSaveNEV(bool state, char* fileName)
{
	//foreach (RTVTChannelWidget *cw, this->channelWidgetList)
        //cw->waveViewer->setNEVFile(state, theFile);

	this->setNEVFile(state, fileName);
}

void RTVTMainWindow::writeWaveformsToFile(waveformDatum datum)
{
	if(this->saveNEVState)
	{
		//unsigned int s = sizeof(datum.tickStamps);
		for(unsigned int i=0;i<sizeof(datum.tickStamps)/sizeof(int);i++)
		{
			
			// Convert wave samples to shorts and write
                    short tempWave[64];
                    for(unsigned int w=0;w<(DATA_RATE*0.0016);w++)
                            tempWave[w] = (short)(datum.waveSamples[i][w]*1000000);

                    this->nevWriter->wr(datum.tickStamps[i],datum.channelNumber,datum.unitNumber,&tempWave);
		}
	}

	//free(&datum);
}

void RTVTMainWindow::setNEVFile(bool state, char *fileName)
{
	// Old save location "C:/Users/Public/testNEVFile.nev"
	// or
	// Use input
	if(state)
	{
		this->nevWriter = new bNEVwr(fileName,2,"BIC Array 16","Sample Comments");
		for(unsigned short ch=0;ch<numberOfDataChannels;ch++)
		{
			this->nevWriter->setupCh(ch,3);
		}
	}
}

void RTVTMainWindow::setSaveNEVState(bool state)
{
	this->saveNEVState = state;
	if(state)
		this->nevWriter->start();
	else
		this->nevWriter->end();
}

void RTVTMainWindow::updateLocalWaveCheckValue(int inValue)
{
	foreach (RTVTChannelWidget *cw, this->channelWidgetList)
        cw->waveViewer->updateWaveCheckValue(inValue);
}

void RTVTMainWindow::runThreadedAudioPlayer()
{
	
}

void RTVTMainWindow::updateNumberOfChannelViews(int numChannels)
{
	this->numberOfChannelViews = numChannels;
	this->redrawChannelViews();
}

void RTVTMainWindow::updateNumberOfDataChannels(int numDataChannels)
{
        this->numberOfDataChannels = numDataChannels;
#ifdef USES_AUDIO
        this->audioPlayer->dataFrequency = SYSTEM_CLOCK_RATE/numDataChannels;
#endif

	foreach (RTVTChannelWidget *cw, this->channelWidgetList)
            cw->setNumberOfChannelsInData(numDataChannels);
}

void RTVTMainWindow::changeChannelDisplayToWavesAndContinuous()
{
	this->channelViewType = WAVE_AND_CONTINUOUS_VIEW_TYPE;
	this->squareChannelGrid = false;
	this->redrawChannelViews();
}

void RTVTMainWindow::changeChannelDisplayToWaves()
{
	this->channelViewType = WAVE_VIEW_TYPE;
	this->squareChannelGrid = true;
	this->redrawChannelViews();
}

void RTVTMainWindow::updateAudioChannel(int index)
{
	this->audioChannel = index;
}

void RTVTMainWindow::setSelectedWidget(int widgetNumber)
{
	this->selectedWidgetNumber = widgetNumber;

	foreach (RTVTChannelWidget *cw, this->channelWidgetList)
		if(cw->assignedWidgetNumber == widgetNumber)
			cw->setChannelSelected(true);
		else
			cw->setChannelSelected(false);
}

void RTVTMainWindow::tellWaveViewsToPropogateChangesWhenDone(bool yesNo)
{
    foreach (RTVTChannelWidget *cw, this->channelWidgetList)
    {
        if(yesNo)
            cw->waveViewer->propogatesChangesInThreshold = true;
        else
            cw->waveViewer->propogatesChangesInThreshold = false;
    }
}

void RTVTMainWindow::redrawChannelViews()
{
    // QMainWindow should delete the pointer to old central widget once this one replaces it
	//foreach (RTVTChannelWidget *cw, this->channelWidgetList)
	//	this->channelWidgetList->removeItemWidget cw;

	for(int i=0;i<this->channelWidgetList.length();i++)
		this->channelWidgetList.removeAt(i);

    this->channelWidgetList.clear();
    QWidget *myCentralWidget = new QWidget();
    QGridLayout *channelGrid = new QGridLayout;
    channelGrid->setSpacing(0);
	channelGrid->setContentsMargins(0,0,0,0);
    int channelColumn = 0;
    int channelRow = 0;
	double temp = sqrt((double)numberOfChannelViews);
	int viewsPerRow = 1;

	if(this->squareChannelGrid)
		viewsPerRow = floor(temp);

    for(int channelToAdd = 1; channelToAdd<=numberOfChannelViews; channelToAdd++)
    {
        int	tempChannel = channelToAdd;
        if(this->wireAddressing == TWO_WIRE_ADDRESSING)
        {

			if(channelToAdd < (this->numberOfDataChannels-1)/2+1) //51
                tempChannel = (channelToAdd*2)-1;
            else
                tempChannel = ((channelToAdd-(this->numberOfDataChannels-1)/2)*2); //50
        }
        else
            tempChannel = channelToAdd;

        RTVTChannelWidget *channelViewer = new RTVTChannelWidget(this,tempChannel,(channelToAdd-1), this->channelViewType);

        if (channelToAdd>(viewsPerRow*(channelRow+1)))
        {
            channelColumn = 0;
            channelRow++;
        }

        channelGrid->addWidget(channelViewer,channelRow,channelColumn);
        channelWidgetList.append(channelViewer);

        channelColumn++;
    }

    myCentralWidget->setLayout(channelGrid);
    this->setCentralWidget(myCentralWidget);
}

void RTVTMainWindow::moveEvent ( QMoveEvent * theEvent )
{
	Q_UNUSED(theEvent);
	/*foreach (RTVTChannelWidget *cw, this->channelWidgetList)
	{
		cw->continuousViewer->repaint();
		cw->waveViewer->repaint();
	}*/
}

void RTVTMainWindow::mousePressEvent ( QMouseEvent * theEvent )
{
	Q_UNUSED(theEvent);
	/*foreach (RTVTChannelWidget *cw, this->channelWidgetList)
	{
		cw->continuousViewer->repaint();
		cw->waveViewer->repaint();
	}*/
}
