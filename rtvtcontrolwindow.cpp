#include "rtvtcontrolwindow.h"
#include "ui_rtvtcontrolwindow.h"

#ifdef USE_HS_USB
    CPSHSUSBHardwareAbstractionLayer *hsHAL;
#endif

FirKernels **sharedFilterArray;

// END

using namespace std;

RTVTControlWindow::RTVTControlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RTVTControlWindow)
{
    ui->setupUi(this);

	this->setGeometry(50,50,375,450);

    ui->samplesToCollectLabel->setText(QString::number(65536)); // 2^16 -- set in fftreal_wrapper.h
    ui->numAveragesText->setText(QString::number(4));

	Initialize();
}

void RTVTControlWindow::Initialize()
{
	/* Start the USB interface
	If we find the correct one, we will then start a timer to track the current
	values of all the attached processes in the configuration

	will need to keep some variables editable to adjust the system

	*/
	// Setup some save variables
	saveToDisk = 0;
	saveToDiskPath = QString("");

	// Set some default values
	this->halConnected = false;
	this->rtvtController = new RTVTMainWindow();
	//this->rtvtController->setParent(this);
	this->rtvtController->setGeometry(450,50,1100,900);

	/* setup HS USB device */

	#ifdef USE_HS_USB
	this->ui->statusHistoryField->append("Checking high-speed USB plugin...");
	hsHAL = new CPSHSUSBHardwareAbstractionLayer();
	this->ui->statusHistoryField->append("Found.");
	connect(this->ui->usesHSUSBRadioButton, SIGNAL(clicked()), this, SLOT(setupHSUSB()));
	#endif

	//// Iinitialize FIR
	sharedFilterArray = new FirKernels*[10]; //initialize array of 5 filters

	//localTriggerType = 0; //no trigger on startup

	for(int filterCount=0;filterCount<10;filterCount++)
	{
			sharedFilterArray[filterCount] = new FirKernels();
	}

	// Setup recursive save timers
	recursiveSaveTimer = new QTimer(this);
	connect(recursiveSaveTimer, SIGNAL(timeout()), this, SLOT(stopAndRestartRecursiveRecordings()));
	countdownTimer = new QTimer(this);
	connect(countdownTimer, SIGNAL(timeout()), this, SLOT(updateCountdownTimerField()));
	countInSeconds = 0;

	////
	// Events to occur after all loading
	// Connections
	connect(this->ui->actionShow_array_window, SIGNAL(triggered()), this, SLOT(openRTVTArrayPanel()));
	connect(this->ui->actionLoad_data_from_file, SIGNAL(triggered()), this, SLOT(rtvtOpenExistingData()));
	connect(this->ui->actionLoad_coefficients_file, SIGNAL(triggered()), this, SLOT(openFilterDataFile()));
	connect(this->ui->actionShow_HUD, SIGNAL(triggered()), this, SLOT(toggleHUDVisibility()));
	connect(this->ui->usesHSUSBRadioButton, SIGNAL(clicked(bool)), this, SLOT(setUsesUSB(bool)));
	connect(this->ui->usesDataFromFileRadioButton, SIGNAL(clicked(bool)), this, SLOT(setUsesFile(bool)));
	connect(this->ui->saveDataToDiskCheckBox, SIGNAL(clicked(bool)), this->rtvtController, SLOT(setSaveDataBool(bool)));
	connect(this->ui->setSavePathButton, SIGNAL(clicked()), this, SLOT(setSavePath()));
	connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(closeAndExitApplication()));
	connect(this->rtvtController, SIGNAL(appendToConsole(QString)),this, SLOT(appendToStatusField(QString)));
        connect(this->ui->actionSave_SNIFFR_to_dat, SIGNAL(triggered()), this->rtvtController, SLOT(saveSNIFFRToMat()));
        connect(this->ui->playWithoutRecordingButton, SIGNAL(clicked()), this, SLOT(stopStartClicked()));
        //connect(this->ui->playWithRecordingButton, SIGNAL(clicked()), this, SLOT(tellMainWindowToPlayAndRecord()));
        connect(this->ui->runNoiseTestButton, SIGNAL(clicked()), this, SLOT(runNoiseSpectrumTest()));
}
RTVTControlWindow::~RTVTControlWindow()
{
    delete ui;

    delete rtvtController;
#ifdef USE_HS_USB
    delete hsHAL;
#endif
    delete sharedFilterArray;

}

void RTVTControlWindow::closeAndExitApplication()
{
    // Close and delete anything that we need to - especially the db connections
    QApplication::quit();
}

void RTVTControlWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void RTVTControlWindow::setSavePath()
{
	QString path;
    
	path = QFileDialog::getSaveFileName(this, tr("Save Data File"),
                            tr(""),
                            tr("Data (*.snifr)"));
  
	this->ui->saveDataPathLabel->setText( path );
	this->saveToDiskPath = path;

	this->rtvtController->setSaveDataPath(this->saveToDiskPath);
}

void RTVTControlWindow::reloadStyleSheets()
{
	QFile file("qss/rtvthuddockstyle.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
	
	//this->rtvtController->rtvtWaveHUD->setStyleSheet(styleSheet);
	//this->rtvtController->hudDock->setStyleSheet(styleSheet);//"border-width: 1px; border-color: #535353; background-color: white;");
}


void RTVTControlWindow::setupHSUSB()
{
#ifdef USE_HS_USB
    int error;

    error = hsHAL->setupHSUSB();

	if(error==0)
	{
		this->ui->hsUSBConnectedLabel->setText("Connected");
		this->ui->statusHistoryField->append("HSUSB was Connected.");
                this->ui->fromDataFileLabel->setText("Not connected");
	}
	else
	{
		this->ui->hsUSBConnectedLabel->setText("Not connected");
		this->ui->statusHistoryField->append("HSUSB was not Connected.");
	}
#endif
}

void RTVTControlWindow::openRTVTArrayPanel()
{
	this->toggleRTVTChannelArrayVisibility();
	//this->toggleHUDVisibility();
}

void RTVTControlWindow::openFilterDataFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Filter Coefficients File"),
                                         QDir::currentPath(),
                                         tr("txt (*.txt)"));
	QByteArray ba = fileName.toLatin1();
	sharedFilterArray[0]->SetFilterData(ba.data());
}

void RTVTControlWindow::toggleHUDVisibility()
{
	if(this->rtvtController->hud->isHidden())
	{
		this->rtvtController->hud->show();
		this->ui->actionShow_HUD->setText("Hide HUD");
	}
	else
	{
		this->rtvtController->hud->hide();
		this->ui->actionShow_HUD->setText("Show HUD");
	}
}

void RTVTControlWindow::toggleRTVTChannelArrayVisibility()
{
	if(this->rtvtController->isHidden())
	{
		this->rtvtController->show();
		this->ui->actionShow_array_window->setText("Hide array window");
	}
	else
	{
		this->rtvtController->hide();
		this->ui->actionShow_array_window->setText("Show array window");
	}
}

void RTVTControlWindow::setUsesFile(bool state)
{
	if(state)
	{
                this->rtvtController->dataSource = FILE_DATA_TYPE;
		this->rtvtController->dataPath = FILE_DATA_PATH_TYPE;
                this->ui->fromDataFileLabel->setText("Connected");
                this->ui->hsUSBConnectedLabel->setText("Not connected");
	}
}

void RTVTControlWindow::setUsesUSB(bool state)
{
	if(state)
	{
		this->rtvtController->dataPath = NI_CEREBUS_DATA_PATH_TYPE;
		this->rtvtController->dataPath = HSUSB_DATA_PATH_TYPE;
	}

	//setupHSUSB();
}

void RTVTControlWindow::rtvtOpenExistingData()
{
	this->ui->statusHistoryField->append("Loading SNIFR data file...");
	QString openedFileName = this->rtvtController->openExistingData();
	this->ui->statusHistoryField->append("File found:");
	this->ui->statusHistoryField->append(openedFileName);
}

void RTVTControlWindow::appendToStatusField(QString inString)
{
	this->ui->statusHistoryField->append(inString);
}

//void RTVTControlWindow::tellMainWindowToPlayAndRecord()
//{
//    bool connectionIsMade = false;
//    bool fileIsSet = false;

//    // Check connection
//    if(this->rtvtController->dataPath == FILE_DATA_PATH_TYPE || this->rtvtController->dataPath == HSUSB_DATA_PATH_TYPE)
//        connectionIsMade = true;

//    // Check file status
//    if(this->rtvtController->rtvtSavingData)
//        fileIsSet = true;

//    if(connectionIsMade && fileIsSet)
//        this->rtvtController->playFromController(true);
//}

void RTVTControlWindow::tellMainWindowToPlay()
{
    bool connectionIsMade = false;
    // Check connection
    if(this->rtvtController->dataPath == FILE_DATA_PATH_TYPE || this->rtvtController->dataPath == HSUSB_DATA_PATH_TYPE)
        connectionIsMade = true;

    if(connectionIsMade)
    {
        this->rtvtController->playFromController(false);

        if(this->rtvtController->sbThreadIsRunning)
		{
            this->ui->playWithoutRecordingButton->setText("Stop playback");

			if(this->ui->recursiveSaveCheckbox->isChecked())
			{
				this->recursiveSaveTimer->start((this->ui->recursiveSaveSpinbox->value())*60*1000);
				this->countdownTimer->start(1000);
				this->countInSeconds = (this->ui->recursiveSaveSpinbox->value())*60 - 1;
			}

			this->ui->recursiveSaveCheckbox->setEnabled(false);
			this->ui->recursiveSaveSpinbox->setEnabled(false);
			this->ui->label_6->setEnabled(false);
			this->ui->countdownText->setEnabled(false);
		}
        else
		{
			this->ui->recursiveSaveCheckbox->setEnabled(true);
			this->ui->recursiveSaveSpinbox->setEnabled(true);
			this->ui->label_6->setEnabled(true);
			this->ui->countdownText->setEnabled(true);

			//this->countdownTimer->stop();
			//this->recursiveSaveTimer->stop();

            this->ui->playWithoutRecordingButton->setText("Start playback");

			if(this->ui->saveDataToDiskCheckBox->isChecked())
			{
				QString savePath = this->rtvtController->rtvtSaveDataPath;

				savePath = QString(savePath.replace(".snifr", QString("_" + QString::number((this->rtvtController->numberOfFileSaves-1)) + ".snifr")));
				this->ui->statusHistoryField->append("Saved data to: " + savePath);
				//this->ui->statusHistoryField->append(savePath);
				this->ui->statusHistoryField->append("-------------------------------------------------------------");
			}
		}

		 if(this->rtvtController->isHidden())
            this->toggleRTVTChannelArrayVisibility();
    }
}

void RTVTControlWindow::updateCountdownTimerField()
{
	countInSeconds--;
	this->ui->countdownText->setText(QString::number(countInSeconds));

	// do i need this to keep starting the thread? this->countdownTimer->start(1000);
}

void RTVTControlWindow::stopStartClicked()
{
	if(this->recursiveSaveTimer->isActive()) this->recursiveSaveTimer->stop();
	if(this->countdownTimer->isActive()) this->countdownTimer->stop();

	this->tellMainWindowToPlay();

}
void RTVTControlWindow::stopAndRestartRecursiveRecordings()
{
	// stop recording / save
	this->tellMainWindowToPlay();

	// Start up again
	this->tellMainWindowToPlay();
}

void RTVTControlWindow::runNoiseSpectrumTest()
{
#ifdef USE_QWT_PLOT

	Bode_MainWindow *noisePlotWindow = new Bode_MainWindow();

	int tempMaxNumberOfPlots = this->ui->numberOfChannelsToViewField->text().toInt();
	int tempNumberOfPlots;
	if(this->rtvtController->numberOfChannelViews < tempMaxNumberOfPlots)
		tempNumberOfPlots = this->rtvtController->numberOfChannelViews;
	else
		tempNumberOfPlots = tempMaxNumberOfPlots;
	
    for(unsigned int i=0;i<tempNumberOfPlots;i++)
    {
        QVector<qreal> amplitude;
        QVector<qreal> frequency;

        if(this->rtvtController->channelWidgetList.at(i)->calculateFFTWithLength(ui->numAveragesText->text().toInt(),amplitude,frequency))
            this->ui->statusHistoryField->append("Error processing data: recorded length too short");
        noisePlotWindow->addCurveWithDataFromChannel(frequency, amplitude, i);
    }


    noisePlotWindow->show();

    //this->rtvtController->channelWidgetList[0]->setupNoisePlot();
    //this->rtvtController->channelWidgetList[14]->setupNoisePlot();

    // Ideal process flow
    /*

     1. Create widget with a QwtPlot and a list view with N checkboxes for display of curves
     2. Create N QwtPlotCurves, one for each channel
     3. Scale the plot to fit curves

     */
#endif
}
