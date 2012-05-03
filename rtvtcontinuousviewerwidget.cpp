#include "rtvtcontinuousviewerwidget.h"
#include "rtvtchannelwidget.h"

#include <qtimer.h>
#include <QKeyEvent>
#include <QtGui>
#include <iostream>
#include <QThread>
#include <math.h>

RTVTContinuousViewerWidget::RTVTContinuousViewerWidget(int timerInterval, int viewerChannel, QWidget *parent, QString name)
{
    // Draw widget boarder for reference
    this->setStyleSheet("border-width: 1px; border-color: #000000;");

	this->setParent(parent);

	//this->setMinimumSize(150, 100);
    this->lineSmoothingEnabled = true;
    this->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);

	//parent->setBackgroundRole(QPalette::NoRole);
	//this->setAttribute(Qt::WA_OpaquePaintEvent, true);

    //// initialize some variables
    // Viewport setup and calibration
    fov = double(45.0);
    zFromCamera = double(-10.0);
    interSampleLength = double(0.0);

    // Input data structure - should be placed in channel object
    sampleRate = SYSTEM_CLOCK_RATE/SAMPLE_FRAME_LENGTH/DEFAULT_NUM_CHANNELS_IN_DATA;
    timeWindowInS = 6.0;
    numberOfSamples = (int)(sampleRate*timeWindowInS);

    this->drawingFromData = false;
    this->viewNeedsRedraw = true;
    this->assignedViewerChannel = viewerChannel;
    this->yPeakToPeak = 0.003; // 300 uV
    this->yDragOrigin = 0;
    this->xDragOrigin = 0;
    this->smooth = false;
    this->setThresholdMode = false;
    this->setYScaleMode = false;
    this->thresholdPP = 0.0;
	this->readFromDrawBufferFramePtr = 0;
	this->xScaleFactor = 1.0;
	this->readStartPositionForChannel = 0;
	this->isPlaying = false;
	this->askedToClear = false;
	this->readByteOffset = 0;
	this->drawPixelOffset = 0;
	this->drawWindowWidth = 0;
	this->storedYValueForNextFrame = 0.0;
	this->storedXValueForNextFrame = 0;
	this->readFromChannelDataPtr = 0;
	this->readFromChannelFilterDataPtr = 0;
	this->baseline = 4600;
	this->yScaleFactor = 1.0;
	this->secondCounter = 0;
	this->localMean = 0.0;
	this->meanCounter = 0;
	this->showInformation = true;
        this->adcFactor = ADC_RANGE/4096;
	this->ampGain = 200;
	this->testMark = 0;
	this->waitUntilNextTransfer = false;

	//this->meanSource = (double) malloc (sizeof(double) * MEAN_WINDOW);

    if( timerInterval == 0 )
            glRedrawTimer = 0;
    else
    {
            glRedrawTimer = new QTimer( this );
            connect( glRedrawTimer, SIGNAL(timeout()), this, SLOT(timeOutSlot()) );
            //glRedrawTimer->start( timerInterval );
    }

    //connect(this,SIGNAL(iWasDoubleClicked(int)),this->parentWidget()->parentWidget(),SLOT(viewWasDoubleClicked(int)));
	connect(this,SIGNAL(iReachedEndOfData(int)),this->parentWidget()->parentWidget(),SLOT(continuousViewReachedEndOfData(int)));
}

QSize RTVTContinuousViewerWidget::sizeHint() const
{
    return QSize(900,200);
}

void RTVTContinuousViewerWidget::enableLineSmoothing(bool enable)
{
	this->lineSmoothingEnabled = enable;
}

void RTVTContinuousViewerWidget::keyPressEvent( QKeyEvent *e )
{
//    std::cout << "Key Pressed..." << std::endl;
    switch(e->key())
    {
    case Qt::Key_Escape:
            close();
            break;
    case Qt::Key_0:
            if(!this->lineSmoothingEnabled)
				this->lineSmoothingEnabled = true;
            else
				this->lineSmoothingEnabled = false;
            break;
    case Qt::Key_T:
            if(!this->setThresholdMode)
                this->setThresholdMode = true;
            else
                this->setThresholdMode = false;
            break;
    case Qt::Key_Y:
            if(!this->setYScaleMode)
                this->setYScaleMode = true;
            else
                this->setYScaleMode = false;
            break;
	case Qt::Key_Period:
		this->timeWindowInS += 0.5;
		break;
	case Qt::Key_Comma:
		this->timeWindowInS -= 0.5;
		break;
    default:
            break;
    }
}

void RTVTContinuousViewerWidget::mousePressEvent(QMouseEvent *event)
{
    // Set the original drag position
    this->yDragOrigin = event->pos().y();
    this->xDragOrigin = event->pos().x();

    //this->lineSmoothingEnabled = !this->lineSmoothingEnabled;
    //std::cout << "Enabled Changed" << std::endl;
}

void RTVTContinuousViewerWidget::mouseDoubleClickEvent(QMouseEvent *)
{
	this->viewNeedsRedraw = true;
    //emit iWasDoubleClicked(this->assignedViewerChannel);
}

void RTVTContinuousViewerWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(this->setYScaleMode)
    {
        double yScaleDragPosition = (double)event->pos().y();
        this->yPeakToPeak = (double)(yScaleDragPosition/this->yDragOrigin)*1024.0;
        //this->lineSmoothingEnabled = !this->lineSmoothingEnabled;
        std::cout << "Dragging...::" << yScaleDragPosition << "::" << this->yDragOrigin << "::" << this->yPeakToPeak << std::endl;
    }
    else if(this->setThresholdMode)
    {
        double thresholdDragPosition = (double)event->pos().y();
        this->thresholdPP = (double)(thresholdDragPosition/this->yDragOrigin)*1024.0;
        this->thresholdOrigin = this->xDragOrigin;
        std::cout << "Dragging...::" << thresholdDragPosition << "::" << this->yDragOrigin << "::" << this->thresholdPP << std::endl;
    }

    //update();
}

void RTVTContinuousViewerWidget::mouseReleaseEvent(QMouseEvent *)
{
    if(this->setThresholdMode)
        this->thresholdOrigin = this->xDragOrigin;
}

void RTVTContinuousViewerWidget::timeOut()
{
    this->update();
}

void RTVTContinuousViewerWidget::timeOutSlot()
{
    timeOut();
}

void RTVTContinuousViewerWidget::paintEvent(QPaintEvent * /* event */)
{
    // Calculate and store the space
    this->aspectRatio = (double)height()/(double)width();
    this->vpWidth = -tan(fov/2)*(this->zFromCamera)/aspectRatio;
    this->vpHeight = -tan(fov/2)*(this->zFromCamera);
	this->numberOfSamples = (int)(this->sampleRate*this->timeWindowInS);
	// Let's make the interSamplelength always 1 pixel since we are almost always drawing more than one sample / pixel
    //this->interSampleLength = ((double)width() - (double)LEFT_PAD_PERCENT*width()/100 - (double)RIGHT_PAD_PERCENT*width()/100)/this->numberOfSamples;
	this->interSampleLength = 1.0;
	
    // Setup some variables for drawing properly
    double yScaleFactorToVPSpace = (height())/this->yPeakToPeak;
	
	QRect boundingRect = QRect(1, 1, width()-1, height() - 1);
	QPen pen, tickPen;
    QPainter painter(this);
	QPainterPath path;
	
	tickPen = QPen(QBrush(QColor("Blue"),Qt::SolidPattern),0.5,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
	
	if(viewNeedsRedraw)
	{
		painter.setPen(palette().dark().color());
		painter.fillRect(QRect(0, 0, width(), height()),QBrush(Qt::SolidPattern));
		this->viewNeedsRedraw = false;
		
		if (this->lineSmoothingEnabled)
			painter.setRenderHint(QPainter::Antialiasing, false);
		
		pen = QPen(QBrush(QColor("blue"),Qt::SolidPattern),0.5,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
		painter.setPen(pen);
		painter.drawLine((double)LEFT_PAD_PERCENT*width()/100,height()/2,width()-(double)RIGHT_PAD_PERCENT*width()/100,height()/2);
		painter.drawLine((double)LEFT_PAD_PERCENT*width()/100,(double)TOP_PAD_PERCENT*height()/100,(double)LEFT_PAD_PERCENT*width()/100,height() - (double)TOP_PAD_PERCENT*height()/100);
		painter.drawLine(width() - (double)RIGHT_PAD_PERCENT*width()/100,(double)TOP_PAD_PERCENT*height()/100,width() - (double)RIGHT_PAD_PERCENT*width()/100,height() - (double)TOP_PAD_PERCENT*height()/100);
		
		// Draw a test line
		painter.drawLine(width()/2, 1*height()/4, width()/2, 3*height()/4);
		
	}
	
    // If we are pulling from data, draw the data - could check other conditionals here
    if(drawingFromData)
    {

		if(((RTVTChannelWidget *)this->parent())->isFiltering)
			this->readByteOffset = this->readFromChannelFilterDataPtr; //(this->readFromDrawBufferFramePtr)*DRAW_FRAME_LENGTH;
		else
			this->readByteOffset = this->readFromChannelDataPtr;

		// Check if we are reading past DRAW_BUFFER
		// If in filter buffer
		if(((RTVTChannelWidget *)this->parent())->isFiltering)
		{
			if(this->readByteOffset >= ((RTVTChannelWidget *)this->parent())->nextFilterWriteLocation)
			{
				testMark++;
				waitUntilNextTransfer = true;
				return;
			}
		}
		else
		{
			if(this->readByteOffset >= ((RTVTChannelWidget *)this->parent())->nextWriteLocation)
			{
				testMark++;
				waitUntilNextTransfer = true;
				return;
			}
		}

		// How many pixels are in the screen to draw on? Then lets draw the correct x scale
		// boundingRect is the drawing space here
		unsigned int pxWidth = (boundingRect.width() - (double)LEFT_PAD_PERCENT/100*width() - (double)RIGHT_PAD_PERCENT/100*width());
		// How many samples are in this width? // this->numberOfSamples
		unsigned int samplesPerPixel = floor((float)(this->numberOfSamples/pxWidth)); // means 1 pixel = stride number of samples
		if((samplesPerPixel % 2) > 0) // Not even
			samplesPerPixel--;
		
		// Figure out if we need to move drawPtr back to beginning of window
		if((drawPixelOffset) >= (pxWidth)) // Since this is # of samples in one channel 2bytes/sample
			drawPixelOffset = 0;		// Reset to beginning of buffer
		
        int i = 0;
		int decimationStride; // is in samples
		//if(((RTVTChannelWidget *)this->parent())->isFiltering)
		//	decimationStride = samplesPerPixel;
		//else
		decimationStride = samplesPerPixel;
		int startSampleLocation = 0;
        double yPoint = 0;
		double xPoint = (double)LEFT_PAD_PERCENT/100*width() + drawPixelOffset; //(double)LEFT_PAD_PERCENT/100*width() + (drawPixelOffset)/2*this->interSampleLength; // Set the drawPtr to correct location in view
		
		// Check the readDataPtr to see if we need to move back to beginning of buffer
		// Also set the readPtr location for beginning to read from buffer
		// Set the first draw point to be last value or 0

		if((drawPixelOffset*samplesPerPixel) >= DRAW_FRAME_LENGTH/2)
			path.moveTo((xPoint - 1.0),this->storedYValueForNextFrame);
		else
		{
			if(this->readByteOffset > 0)
				path.moveTo((double)LEFT_PAD_PERCENT/100*width(),this->storedYValueForNextFrame);
			else
				path.moveTo((double)LEFT_PAD_PERCENT/100*width(),(double)height()/2);
		}

		startSampleLocation = readByteOffset; //+(startCounter+(assignedViewerChannel))*2);
		
		// Set Pen and draw wave path for drawFrame in view
		pen = QPen(QBrush(QColor("gray"),Qt::SolidPattern),0.5,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
		painter.setPen(pen);
		
        for(i=startSampleLocation;i<(startSampleLocation+DRAW_FRAME_LENGTH/2);)
        {			
			double value = 0.0;
			if(((RTVTChannelWidget *)this->parent())->isFiltering)
			{
				value = ((RTVTChannelWidget *)this->parent())->filteredChannelData[i]*this->adcFactor/this->ampGain;
				if(abs(value) > 10000)
					value = ((RTVTChannelWidget *)this->parent())->filteredChannelData[i - decimationStride]*this->adcFactor/this->ampGain;
			}
			else
			{
				value = (((RTVTChannelWidget *)this->parent())->channelData[i+1]*256 + ((RTVTChannelWidget *)this->parent())->channelData[i])*this->adcFactor/this->ampGain;
				if(abs(value) > 10000)
					value = (((RTVTChannelWidget *)this->parent())->channelData[(i-decimationStride)+1]*256 + ((RTVTChannelWidget *)this->parent())->channelData[(i-decimationStride)])*this->adcFactor/this->ampGain;
			}
			
			if(this->secondCounter >= this->sampleRate)
			{
				QPainterPath tickPath;
				
				this->secondCounter = 0;
				tickPath.moveTo(xPoint, height());
				tickPath.lineTo(xPoint, height()-5);
				
				painter.setPen(tickPen);
				painter.drawPath(tickPath);
				painter.setPen(pen);
				//path.moveTo(xPoint, this->storedYValueForNextFrame);
			}
			else
				this->secondCounter += (decimationStride);
			
			if(this->meanCounter >= (int)this->sampleRate/(100)) // 1.6ms @ 40k * 10 windows
			{
				this->localMean += value;
				this->localMean = this->localMean/2;
				this->meanCounter = 0;
			}
			else
				this->meanCounter += (decimationStride);

			
			// Draw some lines and text for the mean +/- max/min by pressing the "i" key for information
			//int value = (this->channelData[i+1]*256 + this->channelData[i])/10;
			yPoint = (double)height()/2 +(value - this->localMean)*yScaleFactorToVPSpace;    //(double)height()/2 + 
			path.lineTo(xPoint, yPoint);
			xPoint = xPoint + this->interSampleLength;

			if(((RTVTChannelWidget *)this->parent())->isFiltering)
				i+=decimationStride; // since we need to skip ahead in samples
			else
				i+=decimationStride; // since we need to skip ahead in samples
        }
		
		// Store the last value of the frame for the start point of next frame
		this->storedYValueForNextFrame = yPoint;
		this->storedXValueForNextFrame = xPoint;
		
		// clear area where we are drawing to remove old data
		QRectF clearRect = QRectF(path.boundingRect().x()+1, 0, path.boundingRect().width()*2,height());
		painter.fillRect(clearRect,QColor(0,0,0));
		QRectF pointerRect = QRectF(path.boundingRect().x()+path.boundingRect().width()+1, 1, path.boundingRect().width()/4,height()-1);
		painter.fillRect(pointerRect,QColor(0,255,0));

		// now draw the wave
		painter.setPen(pen);
		painter.drawPath(path);
		
		if(this->showInformation)
		{
			painter.setPen(palette().dark().color());
			painter.fillRect(QRect(0, 0, (double)LEFT_PAD_PERCENT/100*width(), height()),QBrush(Qt::SolidPattern)); // Left text area
			painter.fillRect(QRect(width()-(double)RIGHT_PAD_PERCENT/100*width(), 0, width(), height()),QBrush(Qt::SolidPattern)); // right text area
			
			QFont f = QFont("Helvetica [Cronyx]",7,1,false);
			QFontMetrics fm(f);
			
			pen = QPen(QBrush(QColor("white"),Qt::SolidPattern),0.2,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
			painter.setPen(pen);
			
			// Display stats
			QString timeString = QString("T:");
			timeString.append(QString::number(this->timeWindowInS,'f',4));
			
			QString sampleString = QString("S:");
			sampleString.append(QString::number(this->numberOfSamples));
			
			painter.setFont(f);
			painter.drawText(width()-(double)RIGHT_PAD_PERCENT/100*width() + 5,fm.height(), timeString);
			painter.drawText(width()-(double)RIGHT_PAD_PERCENT/100*width() + 5,height(), sampleString);
			
			painter.drawText((double)LEFT_PAD_PERCENT/100*width() - 40,fm.height(), QString::number(this->yPeakToPeak/2*this->ampGain,'f',3));
			painter.drawText((double)LEFT_PAD_PERCENT/100*width() - 40,height()/2+fm.height()/2, QString::number(this->localMean*this->ampGain,'f',3));
			painter.drawText((double)LEFT_PAD_PERCENT/100*width() - 40,height(), QString::number(this->yPeakToPeak/2*this->ampGain,'f',3));
			
			pen = QPen(QBrush(QColor("blue"),Qt::SolidPattern),0.3,Qt::DashLine,Qt::RoundCap,Qt::RoundJoin);
			painter.setPen(pen);
			painter.drawLine((double)LEFT_PAD_PERCENT*width()/100,height()/2,width()-(double)RIGHT_PAD_PERCENT*width()/100,height()/2);
			painter.drawLine((double)LEFT_PAD_PERCENT*width()/100,0,(double)LEFT_PAD_PERCENT*width()/100,height());
			painter.drawLine(width() - (double)RIGHT_PAD_PERCENT*width()/100,0,width() - (double)RIGHT_PAD_PERCENT*width()/100,height());
		}
		
		// Now that we have read and displayed, increment the ptr for next round
		if(this->isPlaying)
		{
			if(((RTVTChannelWidget *)this->parent())->isFiltering)
			{
				this->readFromChannelFilterDataPtr += (DRAW_FRAME_LENGTH/2); //this->readFromDrawBufferFramePtr++;
				this->drawPixelOffset += ceil(((double)(DRAW_FRAME_LENGTH/2)/samplesPerPixel));
			}
			else
			{
				this->readFromChannelDataPtr += DRAW_FRAME_LENGTH;
				this->drawPixelOffset += ceil(((double)(DRAW_FRAME_LENGTH/2)/samplesPerPixel));
			}
		}
    }
	
	painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    //painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

void RTVTContinuousViewerWidget::play()
{
	this->glRedrawTimer->start(30);
}

void RTVTContinuousViewerWidget::stop()
{
	this->glRedrawTimer->stop();
	this->drawingFromData = false;

}

// Utilities

void RTVTContinuousViewerWidget::findStartPosition()
{
	// Find frame synch
    for(int f=0;f<15;f++)
    {
        // Convert to hex for comparrison
       char sTmp1[30],sTmp2[30];
       char out[128];

       sprintf(sTmp1,"0x%x",(int)((RTVTChannelWidget *)this->parent())->channelData[(f*2)]);// Why is this ff for synch and not cd????
       sprintf(sTmp2,"0x%x",(int)((RTVTChannelWidget *)this->parent())->channelData[(f*2)+1]);
       out[f*5]=sTmp1[2];
       out[f*5+1]=sTmp1[3];
       out[f*5+2]=sTmp2[2];
       out[f*5+3]=sTmp2[3];
       out[f*5+4]=' ';

       if(((unsigned char)((RTVTChannelWidget *)this->parent())->channelData[f*2] == 0x21) && ((unsigned char)((RTVTChannelWidget *)this->parent())->channelData[f*2+1] == 0xCD))//if((sTmp1[2] == '2') && (sTmp1[3] == '1') && (sTmp2[2] == 'c') && (sTmp2[3] == 'd'))
       {
           //std::cout << "Found frame synch..." << std::endl;
           this->readStartPositionForChannel = f;
           f = 15;
       }
    }
}
