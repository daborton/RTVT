#include "rtvtchannelwidget.h"
#include "rtvtmainwindow.h"

#include "External-Code/fftreal_wrapper.h"

#include <QKeyEvent>

RTVTChannelWidget::RTVTChannelWidget(QWidget *parent, int inAssignedChannel, int inWidgetNumber, int viewType)
{
	this->channelData = (unsigned char *) malloc (sizeof(unsigned char) * CHANNEL_BUFFER_LENGTH);
	this->filteredChannelData = (double *) malloc(sizeof(double) * CHANNEL_BUFFER_LENGTH);

	this->numberOfChannelsInData = DEFAULT_NUM_CHANNELS_IN_DATA;
	if(viewType)
		this->usesContinuousView = true;
	else
		this->usesContinuousView = false;

	this->assignedChannel = inAssignedChannel;
	this->assignedWidgetNumber = inWidgetNumber;
	this->nextWriteLocation = 0;
	this->nextFilterWriteLocation = 0;
	this->theMean = 0;
	this->isSelected = false;
        this->sampleFrameLength = SAMPLE_FRAME_LENGTH;
	
	this->isFiltering = false;

	this->channelTimer = new QTimer();
	this->viewRedrawTimer = new QTimer();
	connect(this->viewRedrawTimer, SIGNAL(timeout()), this, SLOT(viewRedrawTimerTimeout()));

	this->setBackgroundRole(QPalette::NoRole);
	this->setAttribute(Qt::WA_OpaquePaintEvent, true);
	this->setAutoFillBackground(false);
	this->setParent(parent);

	/*** Views ***/
	horizontalLayout = new QHBoxLayout();
	if(this->usesContinuousView)
		continuousViewer = new RTVTContinuousViewerWidget(50, assignedChannel, this, "cViewer"); 
	waveViewer = new RTVTWaveViewerGLWidget(50, assignedChannel, this, "wViewer"); 
	
	timerValueLabel = new QLabel("0");
	timerValueLabel->setText("<font color='white'>0</font>");
	connect(this->channelTimer, SIGNAL(timeout()), this, SLOT(channelTimeout()));
	//connect(this->channelTimer, SIGNAL(value()), this->timerValueLabel, SLOT(text()));

	horizontalLayout->setSpacing(0);
	horizontalLayout->setContentsMargins(0,0,0,0);
	horizontalLayout->addSpacing(11);
	horizontalLayout->addWidget(waveViewer);
	if(this->usesContinuousView)
	{
		horizontalLayout->addSpacing(2);
		horizontalLayout->addWidget(continuousViewer);
	}
	//horizontalLayout->addWidget(timerValueLabel);

	this->isPlaying = false;

	connect(this->waveViewer, SIGNAL(iHaveWaveformsToWrite(waveformDatum)), this, SLOT(childHasWaveformsToWrite(waveformDatum)));
	connect(this->waveViewer, SIGNAL(waveViewEditedTrigger(hoop)), this, SLOT(childHasEditedTrigger(hoop)));
        connect(this->waveViewer, SIGNAL(passTriggerToOtherWaveViewers(hoop)), this, SLOT(passTriggerUp(hoop)));

	this->setLayout(horizontalLayout);
}

RTVTChannelWidget::~RTVTChannelWidget()
{
	if(channelData !=0)
		//delete channelData;
	if(filteredChannelData != 0)
		//delete filteredChannelData;

    delete waveViewer;
    if(this->usesContinuousView)
        delete continuousViewer;
    delete channelTimer;
    delete viewRedrawTimer;
    delete horizontalLayout;
    delete timerValueLabel;

}

void RTVTChannelWidget::keyPressEvent( QKeyEvent *e )
{
    switch(e->key())
    {
    case Qt::Key_Escape:
            close();
            break;
    case Qt::Key_0:
            if(!waveViewer->lineSmoothingEnabled)
                waveViewer->enableLineSmoothing(true);
            else
                waveViewer->enableLineSmoothing(false);
			if(this->usesContinuousView)
			{
				if(!continuousViewer->lineSmoothingEnabled)
					continuousViewer->enableLineSmoothing(true);
				else
					continuousViewer->enableLineSmoothing(false);
			}
            break;
    case Qt::Key_T:
                waveViewer->keyPressEvent(e);
            break;
    case Qt::Key_M:
                waveViewer->keyPressEvent(e);
            break;
    case Qt::Key_Y:
            if(!waveViewer->setYScaleMode)
                waveViewer->setYScaleMode = true;
            else
                waveViewer->setYScaleMode = false;
			if(this->usesContinuousView)
			{
				if(!continuousViewer->setYScaleMode)
					continuousViewer->setYScaleMode = true;
				else
					continuousViewer->setYScaleMode = false;
			}
            break;
	case Qt::Key_D:
		waveViewer->timeWindowInS += waveViewer->timeWindowInS/10;
		break;
	case Qt::Key_S:
		waveViewer->yPeakToPeak += waveViewer->yPeakToPeak/10;
		break;
	case Qt::Key_A:
		waveViewer->timeWindowInS -= waveViewer->timeWindowInS/10;
		break;
	case Qt::Key_W:
		waveViewer->yPeakToPeak -= waveViewer->yPeakToPeak/10;
		break;
	case Qt::Key_G:
		waveViewer->keyPressEvent(e);
		break;
	case Qt::Key_Up:
		if(this->usesContinuousView)
			continuousViewer->baseline += 10;
		break;
	case Qt::Key_Down:
		if(this->usesContinuousView)
			continuousViewer->baseline -= 10;
		break;
	case Qt::Key_Left:
		if(this->usesContinuousView)
		{
			if(continuousViewer->timeWindowInS > 1.0)
				continuousViewer->timeWindowInS -= 0.5;
			else
				continuousViewer->timeWindowInS = 1.0;
		}
		break;
	case Qt::Key_Right:
		if(this->usesContinuousView)
		{
			if(continuousViewer->timeWindowInS < 20.5)
				continuousViewer->timeWindowInS += 0.5;
			else
				continuousViewer->timeWindowInS = 20.0;
		}
		break;
	case Qt::Key_Z:
		if(this->usesContinuousView)
			continuousViewer->yPeakToPeak += continuousViewer->yPeakToPeak/10;
		break;
	case Qt::Key_X:
		if(this->usesContinuousView)
			continuousViewer->yPeakToPeak -= continuousViewer->yPeakToPeak/10;
		break;
	case Qt::Key_I:
		if(this->usesContinuousView)
		{
			if(continuousViewer->showInformation)
				continuousViewer->showInformation = false;
			else
				continuousViewer->showInformation = true;
		}
		break;
    default:
            break;
    }
}

void RTVTChannelWidget::play()
{
	this->channelTimer->setInterval(100);
	this->channelMSCount = 0;
	this->channelTimer->start(100);

	this->viewRedrawTimer->setInterval(3000);
	
	this->timerValueLabel->setText("0");

	this->isPlaying = true;
	this->waveViewer->isPlaying = true;	
	this->waveViewer->drawingFromData = true;
	this->waveViewer->play();

	if(this->usesContinuousView)
	{
		this->continuousViewer->isPlaying = true;
		this->continuousViewer->drawingFromData = true;
		this->continuousViewer->play();
	}
}

void RTVTChannelWidget::stop()
{
	this->waveViewer->stop();


	QString text = QString::number(this->channelMSCount);

	QString fonttemplate = tr("<font color='white'>%1</font>");

	this->channelTimer->stop();

	this->timerValueLabel->setText(fonttemplate.arg(text));
	this->isPlaying = false;
	this->waveViewer->isPlaying = false;

	if(this->usesContinuousView)
	{
		this->continuousViewer->stop();
		this->continuousViewer->isPlaying = false;
	}
}

void RTVTChannelWidget::resetReadPointer()
{
	this->waveViewer->readFromChannelDataPtr = 0;
	this->waveViewer->readFromChannelFilterDataPtr = 0;
	this->waveViewer->findStartPosition();

	if(this->usesContinuousView)
	{
		this->continuousViewer->readFromChannelFilterDataPtr = 0;
		this->continuousViewer->readFromChannelDataPtr = 0;
		this->continuousViewer->findStartPosition();
		this->continuousViewer->baseline = 4600;
	}
	// Why do i have these baselines?
	this->waveViewer->baseline = 4450;
	
}

void RTVTChannelWidget::setDrawFromData(bool isDrawing)
{
	this->waveViewer->drawingFromData = isDrawing;
	if(this->usesContinuousView)
		this->continuousViewer->drawingFromData = isDrawing;
}

void RTVTChannelWidget::updateNextWriteLocationWithAddition(unsigned int bytesWritten)
{
	if(this->nextWriteLocation > (CHANNEL_BUFFER_LENGTH - bytesWritten))
	{
		this->nextWriteLocation = 0;

		//reset continuous here too? Should all the viewers reference the same ptr? probably...
		this->waveViewer->readFromChannelDataPtr = 0;
		if(this->usesContinuousView)
		{
			this->continuousViewer->readFromChannelDataPtr = 0;
			this->continuousViewer->readFromChannelFilterDataPtr = 0;
		}
		
	}
	else
	{
		this->nextWriteLocation += bytesWritten;

		// Make sure we continue parsing data
		this->waveViewer->waitUntilNextTransfer = false;
		if(this->usesContinuousView)
			this->continuousViewer->waitUntilNextTransfer = false;
	}
}

void RTVTChannelWidget::updateNextFilterWriteLocationWithAddition(unsigned int lengthWritten)
{
	if(this->nextFilterWriteLocation > (CHANNEL_BUFFER_LENGTH/2 - lengthWritten))
	{
		this->nextFilterWriteLocation = 0;
		
		//reset continuous here too? Should all the viewers reference the same ptr? probably...
		this->waveViewer->readFromChannelFilterDataPtr = 0;
		if(this->usesContinuousView)
			this->continuousViewer->readFromChannelFilterDataPtr = 0;
		
	}
	else
	{
		this->nextFilterWriteLocation += lengthWritten;

		// Make sure we continue parsing data
		this->waveViewer->waitUntilNextTransfer = false;
		if(this->usesContinuousView)
			this->continuousViewer->waitUntilNextTransfer = false;
	}
}

void RTVTChannelWidget::updateMean(double inMean)
{
	theMean = ((float)inMean + theMean)/2;
	
	//this->waveViewer->localMean = theMean;
	//this->continuousViewer->localMean = theMean;
}

unsigned int RTVTChannelWidget::getNextFilterWriteLocation()
{
	if(this->nextFilterWriteLocation > (CHANNEL_BUFFER_LENGTH/2 - BACK_BUFFER_LENGTH/2/numberOfChannelsInData))
	{
		return 0;
	}
	else
		return this->nextFilterWriteLocation;
}

unsigned int RTVTChannelWidget::getNextWriteLocation()
{
	if(this->nextWriteLocation > (CHANNEL_BUFFER_LENGTH - BACK_BUFFER_LENGTH/numberOfChannelsInData))
	{
		return 0;
	}
	else
		return this->nextWriteLocation;
}

int RTVTChannelWidget::calculateFFTWithLength(unsigned int numberOfAverages, QVector<qreal>& amplitude, QVector<qreal>& frequency)
{
#ifdef USE_QWT_PLOT
    m_fft = new FFTRealWrapper();
    int intSampleRate = SYSTEM_CLOCK_RATE/SAMPLE_FRAME_LENGTH/this->numberOfChannelsInData;
    int bytesPerSample = 2; //sizeof(unsigned char)*
    unsigned int numberOfSamples = SpectrumLengthSamples;

    // Divide into X sections
    unsigned int nSections = numberOfAverages;
    unsigned int lengthRecorded = this->nextWriteLocation/bytesPerSample;

    // Check if we have enough data
    if(lengthRecorded/nSections < numberOfSamples)
    {
        amplitude.fill(0.0,numberOfSamples);
        frequency.fill(0.0,numberOfSamples);
        return 1;
    }

    // Else continue to calculate and return vectors

    for(unsigned int s=0;s<nSections;s++)
    {
        QVector<float> inputToFFT(numberOfSamples, 0.0);
        QVector<float> outputFromFFT(numberOfSamples, 0.0);

        // init window
        m_window = QVector<float>(numberOfSamples, 0.0);

        this->calculateWindow();
        //Q_ASSERT(lengthRecorded == m_numSamples * bytesPerSample);

        // Initialize data array
        const unsigned char *ptr = this->channelData;
        const unsigned int dataOffset = s*numberOfSamples;
        ptr += dataOffset;

        for (unsigned int i=0; i<numberOfSamples; ++i) {
            const qint16 pcmSample = *reinterpret_cast<const qint16*>(ptr);
            // Scale down to range [-1.0, 1.0]
            const float realSample = pcmToReal(pcmSample);
            const float windowedSample = realSample * m_window[i];
            inputToFFT[i] = windowedSample;
            ptr += bytesPerSample;
        }

        // Calculate the FFT
        m_fft->calculateFFT(outputFromFFT.data(), inputToFFT.data());

        //QVector<qreal>  frequencyV(SpectrumLengthSamples,0.0);
        //QVector<qreal>  amplitudeV(SpectrumLengthSamples,0.0);

        for (unsigned int i=2; i<=numberOfSamples/2; ++i) {
            const qreal real = outputFromFFT[i];
            qreal imag = 0.0;
            if (i>0 && i<numberOfSamples/2)
                imag = outputFromFFT[numberOfSamples/2 + i];

            const qreal magnitude = sqrt(real*real + imag*imag);

            if(s==0)
            {
                amplitude << 10*log(magnitude); // should this be 20?
                frequency << qreal(i * intSampleRate) / (numberOfSamples);
            }
            else
            {
                amplitude[i-2] = (amplitude[i-2] + 10*log(magnitude))/2;
                //frequency[i-2] = (frequency[i-2] + qreal(i * intSampleRate) / (numberOfSamples))/2;
            }
        }
    }

#endif
    return 0;
}

void RTVTChannelWidget::calculateWindow()
{
    int m_windowFunction = 1;
    int m_numSamples = SpectrumLengthSamples;

    for (int i=0; i<m_numSamples; ++i) {
        DataType x = 0.0;

        switch (m_windowFunction) {
        case 0:
            x = 1.0;
            break;
        case 1:
            x = 0.5 * (1 - qCos((2 * M_PI * i) / (m_numSamples - 1)));
            break;
        default:
            Q_ASSERT(false);
        }

        m_window[i] = x;
    }
}

void RTVTChannelWidget::updateChannelViews()
{
	this->waveViewer->viewNeedsRedraw = true;
	//this->waveViewer->update();

	if(this->usesContinuousView)
		this->continuousViewer->viewNeedsRedraw = true;
	//this->continuousViewer->update();
}

void RTVTChannelWidget::channelTimeout()
{
	this->channelMSCount++;
	this->channelTimer->start(100);
}

void RTVTChannelWidget::viewRedrawTimerTimeout()
{
	if(this->usesContinuousView)
		this->continuousViewer->viewNeedsRedraw = true;
	this->viewRedrawTimer->start();
}

void RTVTChannelWidget::resizeEvent (QResizeEvent *)
{
	// Set needs redraw
	if(this->usesContinuousView)
		this->continuousViewer->viewNeedsRedraw = true;
	this->update();
}

void RTVTChannelWidget::childHasWaveformsToWrite(waveformDatum datum)
{
	// Pass to parent to write with singular writer
	//QGridLayout *test = (QGridLayout *)this->parent();
	//RTVTMainWindow *test2 = (RTVTMainWindow *)test->parent();

	// Maybe want to have a specific pointer to the mainwindow instead of parent tree...
	//waveformDatum testDatum;
	((RTVTMainWindow*)(this->parent()->parent()))->writeWaveformsToFile(datum);
}

void RTVTChannelWidget::paintEvent(QPaintEvent * event )
{
	Q_UNUSED(event);
	QPainter painter(this);
	QFont f = QFont("Helvetica [Cronyx]",7,1,false);
	QFontMetrics fm(f);
	QPen pen;

	// Clear the old drawing
	QRectF clearRect = QRect(0, 0, 11, height());
	painter.fillRect(clearRect,QColor(0,0,0));

	if(this->isSelected)
	{
		// Draw selected channel region
		QRectF frameRect = QRect(0, 0, 11, height()-5);
		painter.fillRect(frameRect,QColor(0,255,0));

		pen = QPen(QBrush(QColor(0,0,0),Qt::SolidPattern),0.2,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
	}
	else
	{
		// Draw selected channel region
		QRectF frameRect = QRect(0, 0, 11, height()-5);
		painter.fillRect(frameRect,QColor(100,100,100));

		pen = QPen(QBrush(QColor(255,255,255),Qt::SolidPattern),0.2,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
	}

	painter.setPen(pen);

	// Display assigned channel number and widget number
	QString widgetNumberString = QString::number(this->assignedWidgetNumber);
	painter.setFont(f);
	painter.drawText(3,fm.height(), widgetNumberString.at(0));
	if(widgetNumberString.length() >1)
		painter.drawText(3,fm.height()*2, widgetNumberString.at(1));
	if(widgetNumberString.length() >2)
		painter.drawText(3,fm.height()*3, widgetNumberString.at(2));

	QString channelNumberString = QString::number(this->assignedChannel);
	painter.setFont(f);
	
	if(channelNumberString.length() > 1)
	{
		if(channelNumberString.length() > 2)
		{
			painter.drawText(3,height()-fm.height()*3, channelNumberString.at(0));
			painter.drawText(3,height()-fm.height()*2, channelNumberString.at(1));
			painter.drawText(3,height()-fm.height(), channelNumberString.at(2));
		}
		else
		{
			painter.drawText(3,height()-fm.height()*2, channelNumberString.at(0));
			painter.drawText(3,height()-fm.height(), channelNumberString.at(1));
		}
	}
	else
		painter.drawText(3,height()-fm.height(), channelNumberString.at(0));

}

void RTVTChannelWidget::childHasEditedTrigger(hoop theTrigger)
{	
	QList<hoop> currentListOfTriggers = ((RTVTMainWindow*)(this->parent()->parent()))->theWaveTableModel->getTriggerList();
	for (int i=0; i<currentListOfTriggers.count(); i++) 
	{
		if((currentListOfTriggers.value(i).channel == theTrigger.channel) && (currentListOfTriggers.value(i).triggerNumber == theTrigger.triggerNumber)) // Found match
		{
			currentListOfTriggers.replace(i, theTrigger);
			break;
		}
	}
	((RTVTMainWindow*)(this->parent()->parent()))->theWaveTableModel->setTriggerList(currentListOfTriggers);
	//((RTVTMainWindow*)(this->parent()->parent()))->rtvtWaveHUD->triggeredWaveformDataTable->update()
}

void RTVTChannelWidget::setNumberOfChannelsInData(int numChannels)
{
	this->numberOfChannelsInData = numChannels;
}

void RTVTChannelWidget::passTriggerUp(hoop theTrigger)
{
    foreach (RTVTChannelWidget *cw, ((RTVTMainWindow*)(this->parent()->parent()))->channelWidgetList)
	{
		// Just copy over the needed parts of the trigger to avoid cross-display
        cw->waveViewer->triggers[this->waveViewer->selectedTrigger].top = theTrigger.top;
		cw->waveViewer->triggers[this->waveViewer->selectedTrigger].bottom = theTrigger.bottom;
		cw->waveViewer->triggers[this->waveViewer->selectedTrigger].sampleNumberToTest = theTrigger.sampleNumberToTest;
		//cw->waveViewer->triggers[this->waveViewer->selectedTrigger].tickOfSampleCrossing = theTrigger.tickOfSampleCrossing;
	}
}

void RTVTChannelWidget::setChannelSelected(bool status)
{
	this->isSelected = status;
	update();
}

void RTVTChannelWidget::setAddressScheme( unsigned int inWireAddressing)
{
    if(inWireAddressing == 2)
    {
        this->sampleFrameLength = TWO_WIRE_SAMPLE_FRAME_LENGTH;
        this->waveViewer->sampleRate = SYSTEM_CLOCK_RATE/TWO_WIRE_SAMPLE_FRAME_LENGTH/this->numberOfChannelsInData;
        if(this->usesContinuousView)
            this->continuousViewer->sampleRate = SYSTEM_CLOCK_RATE/TWO_WIRE_SAMPLE_FRAME_LENGTH/this->numberOfChannelsInData;
    }
    else if(inWireAddressing == 4)
    {
        this->sampleFrameLength = FOUR_WIRE_SAMPLE_FRAME_LENGTH;
        this->waveViewer->sampleRate = SYSTEM_CLOCK_RATE/FOUR_WIRE_SAMPLE_FRAME_LENGTH/this->numberOfChannelsInData;
        if(this->usesContinuousView)
            this->continuousViewer->sampleRate = SYSTEM_CLOCK_RATE/FOUR_WIRE_SAMPLE_FRAME_LENGTH/this->numberOfChannelsInData;
    }
}

void RTVTChannelWidget::mousePressEvent(QMouseEvent *event)
{
	if(this->isSelected)
		event->ignore();
	else
	{
		((RTVTMainWindow*)(this->parent()->parent()))->setSelectedWidget(this->assignedWidgetNumber);
		event->ignore();
	}
}
