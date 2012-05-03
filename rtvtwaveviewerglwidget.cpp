#include "rtvtwaveviewerglwidget.h"
#include "rtvtchannelwidget.h"
#include "RTVTTimer.h"

#include <qtimer.h>
#include <QKeyEvent>
#include <QtOpenGL>
#include <QtGui>
#include <iostream>

extern RTVTTimer *theTime;

#define WAVE_BYTE_LENGTH 128
//#define MAX_WAVE_PER_TRIGGER 500
#define ADC_FACTOR (ADC_RANGE/4096)

#define DRAW_GL_TEXT    0
#define AMP_TO_UV		1000		// Multiplier for amp display values to be in uV

RTVTWaveViewerGLWidget::RTVTWaveViewerGLWidget(int timerInterval, int viewerChannel, QWidget *parent, QString name)
        : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	Q_UNUSED(name);
    // Draw widget boarder for reference
    this->setStyleSheet("border-width: 1px; border-color: #000000;");
    //this->setMinimumSize(150, 100);
    this->lineSmoothingEnabled = false;
    this->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);

	this->setParent(parent);

    //// initialize some variables
    // Viewport setup and calibration
    fov = GLfloat(45.0);
    zFromCamera = GLfloat(-10.0);
    interSampleLength = GLfloat(0.0);

    // Initialize the QVariant MetaType for waveformDatum
    int id = qRegisterMetaType<waveformDatum>();
	// Initialize the QVariant MetaType for waveformDatum
    int id2 = qRegisterMetaType<hoop>();

    // Input data structure
    sampleRate = SYSTEM_CLOCK_RATE/SAMPLE_FRAME_LENGTH/DEFAULT_NUM_CHANNELS_IN_DATA;
    timeWindowInS = 0.0016f;
    numberOfSamples = (int)(sampleRate*timeWindowInS);

    this->drawingFromData = false;
    this->needsRedraw = false;
    this->assignedViewerChannel = viewerChannel;
    this->yPeakToPeak = 0.003f; // 300 uV
    this->yDragOrigin = 0;
    this->xDragOrigin = 0;
    this->smooth = false;
    this->setThresholdMode = false;
    this->setYScaleMode = false;
    this->thresholdPP = 0.0;
    this->readFromDrawBufferFramePtr = 0;
    this->readFromChannelDataPtr = 0;
	this->readFromChannelFilterDataPtr = 0;
    this->xScaleFactor = 1.0;
    this->readStartPositionForChannel = 0;
    this->isPlaying = false;
    this->baseline = 4096; // 4096 = 2.4 v once channel number is removed.
    this->readByteOffset = 0;
    this->viewNeedsRedraw = true;
    this->thresholdReadPtr = 0;
    this->testMark = 0;
    this->adcFactor = (float)2.4/4096;
    this->ampGain = 200;
    this->waitUntilNextTransfer = false;
    this->selectedTrigger = -1;
    this->numberOfActiveTriggers = 2;
    this->selectedTriggerType = 0;
    this->localMean = 0;
	this->drawingMean = 0;
    this->meanCounter = 0;					// how many samples before next mean check 
	this->meanCheckPoint = 400;				// number of samples to go before checking
    this->numberOfWaveLengthsToCheck = 20;
	this->mouseIsDown = false;
    this->shouldUpdateTextDisplay = false;                   // Just the initial drawing - no need to draw right away
    this->propogatesChangesInThreshold = false;
	this->numberOfSamplesPerWave = (int)ceil(SYSTEM_CLOCK_RATE/DEFAULT_NUM_CHANNELS_IN_DATA/SAMPLE_FRAME_LENGTH*this->timeWindowInS);
	this->numberOfSamplesBeforeTrigger = (int)ceil((float)(numberOfSamplesPerWave/3)); // copy 1/3 number samples before triggered point
	this->numberOfSamplesAfterTrigger = (int)(numberOfSamplesPerWave-numberOfSamplesBeforeTrigger); // copy 
	this->waveByteLength = numberOfSamplesPerWave*2;
	this->drawThresholds = true;

    // Setup a trigger hoop for initial testing
	this->BASE_TRIGGER_CONTROL_POINT_X1 = 0.5;
	this->BASE_TRIGGER_CONTROL_POINT_Y1	= (GLfloat)0.1;
	this->TRIGGER_CONTROL_POINT_X1		= (GLfloat)0.1;
	this->TRIGGER_CONTROL_POINT_Y1		= 0.5;
	
    this->triggers[0].bottom = -0.00005f;
    this->triggers[0].top = 0.00005f;
    this->triggers[0].nextWaveNumber = 0;
    this->triggers[0].numberOfWaves = 0;
    this->triggers[0].r = 0.6f;
    this->triggers[0].g = 0.6f;
    this->triggers[0].b = 0.6f;
	this->triggers[0].channel = this->assignedViewerChannel;
	this->triggers[0].triggerNumber = 0;
	this->triggers[0].sampleNumberToTest = 1;				// needed a placehold for this variable since not used in this trigger

    this->triggers[1].bottom = -0.00020f;
    this->triggers[1].top = 0.00020f;
    this->triggers[1].nextWaveNumber = 0;
    this->triggers[1].numberOfWaves = 0;
    this->triggers[1].r = 1.0f;
    this->triggers[1].g = 1.0f;
    this->triggers[1].b = 0.1f;
	this->triggers[1].sampleNumberToTest = this->numberOfSamples/3;
	this->triggers[1].channel = this->assignedViewerChannel;
	this->triggers[1].triggerNumber = 1;

	/*
    this->triggers[2].bottom = -0.00020;
    this->triggers[2].top = 0.00020;
    this->triggers[2].nextWaveNumber = 0;
    this->triggers[2].numberOfWaves = 0;
    this->triggers[2].r = 0.1;
    this->triggers[2].g = 1.0;
    this->triggers[2].b = 0.1;
    this->triggers[2].sampleNumberToTest = 48;
	this->triggers[2].channel = this->assignedViewerChannel;
	this->triggers[2].triggerNumber = 2;
	*/

    // set a timer for text updates because they take a LONG time in GL world
    this->textUpdateTimer = new QTimer(this);
    connect(textUpdateTimer, SIGNAL(timeout()), this, SLOT(tellTextToUpdate()) );

    this->triggerThreshold = 0.001f;

    ///// Triggers Thread
    // create a QFuture and a QFutureWatcher
    triggersFuture = new QFuture<void>;
    triggersWatcher = new QFutureWatcher<void>;

	// Set a timer for trigger checks
	triggerTimer = new QTimer(this);
	connect(triggerTimer, SIGNAL(timeout()), this, SLOT(runThreadedTiggers()) );
    // display a message box when the calculation has finished
    connect(triggersWatcher, SIGNAL(finished()), this, SLOT(triggersThreadFinishedRunning()));

	//QString temp = QString("testNEV_" + this->assignedViewerChannel + ".nev");
	//char fileName;
	//int err = temp.toWCharArray(&fileName);
	//this->nevWriter = bNEVwr("testNEV.nev",2,"Single E","Sample Comments");
	//this->nevWriter.setupCh(1,2);
	//this->nevWriter.setupCh(107,3);

    if( timerInterval == 0 )
        glRedrawTimer = 0;
    else
    {
        glRedrawTimer = new QTimer( this );
        connect( glRedrawTimer, SIGNAL(timeout()), this, SLOT(timeOutSlot()) );
    }

    //connect(this,SIGNAL(iWasDoubleClicked(int)),this->parentWidget(),SLOT(viewWasDoubleClicked(int)));
}

RTVTWaveViewerGLWidget::~RTVTWaveViewerGLWidget()
{
    delete textUpdateTimer;
    delete triggersFuture;
    delete triggersWatcher;
    delete triggerTimer;
    delete glRedrawTimer;
}

QSize RTVTWaveViewerGLWidget::sizeHint() const
{
    return QSize(75,50);
}

void RTVTWaveViewerGLWidget::keyPressEvent( QKeyEvent *e )
{
//    std::cout << "Key Pressed..." << std::endl;
    switch(e->key())
    {
    case Qt::Key_Escape:
            close();
            break;
    /*case Qt::Key_0:
            if(!this->lineSmoothingEnabled)
                this->enableLineSmoothing(true);
            else
                this->enableLineSmoothing(false);
            break;*/
    case Qt::Key_T:
            if(!this->setThresholdMode)
			{
                this->setThresholdMode = true;
				//this->triggerTimer->setInterval(300);
				this->triggerTimer->start(30);
			}
            else
			{
				this->triggerTimer->stop();
                this->setThresholdMode = false;
			}
            break;
    case Qt::Key_M:
            if(this->textUpdateTimer->isActive())
                this->textUpdateTimer->stop();
            else
                this->textUpdateTimer->start(30);

            break;
    case Qt::Key_Y:
            if(!this->setYScaleMode)
                this->setYScaleMode = true;
            else
                this->setYScaleMode = false;
            break;
	case Qt::Key_Period:
		this->timeWindowInS += 0.0001f;
		break;
	case Qt::Key_Comma:
		this->timeWindowInS -= 0.0001f;
		break;
	case Qt::Key_G:
		this->drawThresholds = !this->drawThresholds;
		break;
    default:
            break;
    }
}

void RTVTWaveViewerGLWidget::mousePressEvent(QMouseEvent *event)
{
	GLfloat yScaleFactorToVPSpace = this->vpHeight/this->yPeakToPeak;
	
	// For testing the hit rects
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	GLint realY,realX;
	GLdouble wx, wy, wz;

	this->mouseIsDown = true;

    // Set the original drag position
    this->yDragOrigin = event->pos().y();
    this->xDragOrigin = event->pos().x();

	// /**** Find out where we clicked - i.e. what object we are on ***/
	// Get the cursor and convert to model coordinates
	cursorClickLocation = event->pos();

	// Convert to model coordinates
	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

	realY = viewport[3] - (GLint) cursorClickLocation.y() - 1;
	realX = viewport[2] - (GLint) cursorClickLocation.x() - 1;
	gluUnProject((GLdouble) realX, (GLdouble) realY, 0.0, mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
	wx = -wx*100;
	wy = wy*100;

	// Make the cursor rect with margin
	QRectF cursorRect((wx-.1),(wy+.1),0.2,-0.2);

	// Iterate through the trigger control points
	for(int t=0;t<this->numberOfActiveTriggers;t++)
	{
		if (t==0)
		{
			QPointF one(-vpWidth/2 - this->BASE_TRIGGER_CONTROL_POINT_X1, this->triggers[0].top*yScaleFactorToVPSpace + this->BASE_TRIGGER_CONTROL_POINT_Y1);
			QPointF two(-vpWidth/2, this->triggers[0].top*yScaleFactorToVPSpace - this->BASE_TRIGGER_CONTROL_POINT_Y1);

			/*QRectF baseTriggerControlRect((-vpWidth/2 - TRIGGER_CONTROL_POINT_X1*this->interSampleLength), this->triggers[0].top*yScaleFactorToVPSpace,
				TRIGGER_CONTROL_POINT_X1*this->interSampleLength*2, TRIGGER_CONTROL_POINT_Y1*yScaleFactorToVPSpace*2);*/
			QRectF baseTriggerControlRect(one,two);

			if(cursorRect.intersects(baseTriggerControlRect)) { this->selectedTrigger = t; this->selectedTriggerType = BASE_TRIGGER_CONTROL_TYPE; break;}
		}
		else
		{
			// Make control rect
			/*QRectF triggerXControlRect(this->triggers[t].sampleNumberToTest*this->interSampleLength - TRIGGER_CONTROL_POINT_X1*this->interSampleLength, -vpHeight/2, 
				TRIGGER_CONTROL_POINT_X1*this->interSampleLength*2 ,TRIGGER_CONTROL_POINT_Y1*yScaleFactorToVPSpace*2);*/
			QPointF one((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) - this->TRIGGER_CONTROL_POINT_X1, -vpHeight/2 - this->TRIGGER_CONTROL_POINT_Y1);
			QPointF two((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) + this->TRIGGER_CONTROL_POINT_X1, -vpHeight/2);

			QPointF oneYT((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) - this->TRIGGER_CONTROL_POINT_X1*2, this->triggers[t].top*yScaleFactorToVPSpace + this->TRIGGER_CONTROL_POINT_Y1);
			QPointF twoYT((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) + this->TRIGGER_CONTROL_POINT_X1*2, this->triggers[t].top*yScaleFactorToVPSpace);
			QPointF oneYB((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) - this->TRIGGER_CONTROL_POINT_X1*2, this->triggers[t].bottom*yScaleFactorToVPSpace - this->TRIGGER_CONTROL_POINT_Y1);
			QPointF twoYB((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) + this->TRIGGER_CONTROL_POINT_X1*2, this->triggers[t].bottom*yScaleFactorToVPSpace);

			QRectF triggerXControlRect(one,two);
			
			QRectF triggerYTopControlRect(oneYT,twoYT);
			
			/*this->triggers[t].sampleNumberToTest*this->interSampleLength - TRIGGER_CONTROL_POINT_X1*this->interSampleLength/2,
				this->triggers[t].top*yScaleFactorToVPSpace + TRIGGER_CONTROL_POINT_Y1*yScaleFactorToVPSpace/2,
				TRIGGER_CONTROL_POINT_X1*this->interSampleLength ,TRIGGER_CONTROL_POINT_Y1*yScaleFactorToVPSpace);*/

			QRectF triggerYBottomControlRect(oneYB,twoYB);
				
			/*this->triggers[t].sampleNumberToTest*this->interSampleLength - TRIGGER_CONTROL_POINT_X1*this->interSampleLength/2,
			this->triggers[t].bottom*yScaleFactorToVPSpace + TRIGGER_CONTROL_POINT_Y1*yScaleFactorToVPSpace/2,
			TRIGGER_CONTROL_POINT_X1*this->interSampleLength ,TRIGGER_CONTROL_POINT_Y1*yScaleFactorToVPSpace);*/

			if(cursorRect.intersects(triggerXControlRect)) { this->selectedTrigger = t; this->selectedTriggerType = X_TRIGGER_CONTROL_TYPE; break;}
			else if(cursorRect.intersects(triggerYTopControlRect)) { this->selectedTrigger = t; this->selectedTriggerType = Y_TOP_TRIGGER_CONTROL_TYPE; break;}
			else if(cursorRect.intersects(triggerYBottomControlRect)) { this->selectedTrigger = t; this->selectedTriggerType = Y_BOTTOM_TRIGGER_CONTROL_TYPE; break;}
		}

		// If we got to the end without hitting anything
		this->selectedTrigger = -1;
		//((RTVTChannelWidget*)this->parent())->setChannelSelected(true);
	}

	updateGL();

    //this->lineSmoothingEnabled = !this->lineSmoothingEnabled;
    //std::cout << "Enabled Changed" << std::endl;
}

void RTVTWaveViewerGLWidget::mouseDoubleClickEvent(QMouseEvent *)
{
    emit iWasDoubleClicked(this->assignedViewerChannel);
}

void RTVTWaveViewerGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(this->setYScaleMode)
    {
        float yScaleDragPosition = (float)event->pos().y();
        //this->yPeakToPeak = (float)(yScaleDragPosition/this->yDragOrigin);
        //this->lineSmoothingEnabled = !this->lineSmoothingEnabled;
        std::cout << "Dragging...::" << yScaleDragPosition << "::" << this->yDragOrigin << "::" << this->yPeakToPeak << std::endl;
    }
	else if(this->setThresholdMode && this->selectedTrigger != -1)
    {
        float thresholdDragPosition = (float)event->pos().y();
        this->thresholdPP = (float)(thresholdDragPosition/this->yDragOrigin)*1024.0;
        this->thresholdOrigin = this->xDragOrigin;

		// Get the cursor and convert to model coordinates
		cursorClickLocation = event->pos();
		GLint viewport[4];
		GLdouble mvmatrix[16], projmatrix[16];
		GLint realY, realX;
		GLdouble wx, wy, wz;

		// Convert to model coordinates
		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
		glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

		realY = viewport[3] - (GLint) cursorClickLocation.y() - 1;
		realX = viewport[2] - (GLint) cursorClickLocation.x() - 1;
		gluUnProject((GLdouble) realX, (GLdouble) realY, 0.0, mvmatrix, projmatrix, viewport, &wx, &wy, &wz);

		wx = -wx*100;
		wy = wy*100;
		
		if(this->selectedTriggerType==BASE_TRIGGER_CONTROL_TYPE)
			this->triggers[selectedTrigger].top = (wy)*(this->yPeakToPeak/this->vpHeight); // *100 for scale / 2 for moving wave to middle of window
		if(this->selectedTriggerType==Y_TOP_TRIGGER_CONTROL_TYPE)
			this->triggers[selectedTrigger].top = (wy)*(this->yPeakToPeak/this->vpHeight); // *100 for scale / 2 for moving wave to middle of window
        else if(this->selectedTriggerType==Y_BOTTOM_TRIGGER_CONTROL_TYPE)
			this->triggers[selectedTrigger].bottom = (wy)*(this->yPeakToPeak/this->vpHeight);
		else if(this->selectedTriggerType==X_TRIGGER_CONTROL_TYPE)
		{
			//if(wx >= 0) { 
			this->triggers[selectedTrigger].sampleNumberToTest = (int)(wx/this->interSampleLength) + this->numberOfSamplesPerWave/2;//}
			//else { this->triggers[selectedTrigger].sampleNumberToTest = ((int)(wx/this->interSampleLength) + 32) ;}
		}
		
		//emit waveViewEditedTrigger(this->triggers[selectedTrigger]);

		//std::cout << "Dragging...::" << thresholdDragPosition << "::" << this->yDragOrigin << "::" << this->thresholdPP << std::endl;
    }

	//wait(200);
    updateGL();
}

void RTVTWaveViewerGLWidget::mouseReleaseEvent(QMouseEvent *)
{
	if(this->setThresholdMode && this->selectedTrigger != -1)
    {
        this->thresholdOrigin = this->xDragOrigin;
		((RTVTChannelWidget*)this->parent())->childHasEditedTrigger(this->triggers[this->selectedTrigger]);

        if(this->setThresholdMode && this->selectedTrigger != -1 && this->propogatesChangesInThreshold)
        {
            emit passTriggerToOtherWaveViewers(this->triggers[this->selectedTrigger]);
        }
    }

	this->mouseIsDown = false;

	
}

void RTVTWaveViewerGLWidget::timeOut()
{
    updateGL();
}


void RTVTWaveViewerGLWidget::timeOutSlot()
{
    timeOut();
}

void RTVTWaveViewerGLWidget::initializeGL()
{
    glShadeModel(GL_SMOOTH);

    
	char* vendor = (char *) glGetString(GL_VENDOR);
	qDebug("  OpenGL Vendor:     %s\n",vendor);
	
	char* renderer = (char *) glGetString(GL_RENDERER);
	qDebug("  OpenGL Renderer:   %s\n",renderer);
	
	char* version = (char *) glGetString(GL_VERSION);
	qDebug("  OpenGL Version:    %s\n",version);
	
	char* exts = (char *) glGetString(GL_EXTENSIONS);
	qDebug("  OpenGL Extensions: \n%s\n",exts);
    

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void RTVTWaveViewerGLWidget::resizeGL( int width, int height )
{
	this->viewNeedsRedraw = true; // will need to redraw after adjustments

    //* Shold maybe fix the aspect ratio

    //std::cout << "Width: " << width << " Height: " << height << std::endl;
    height = height?height:1;

    glViewport( 0, 0, (GLint)width, (GLint)height );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(this->fov,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void RTVTWaveViewerGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Translate viewport to be in view of camera (-10f from center of camera)
    glTranslatef(0.0f,0.0f,this->zFromCamera);

    // Calculate and store the space
    this->aspectRatio = (GLfloat)this->height()/(GLfloat)this->width();
    this->vpWidth = -tan(fov/2)*(this->zFromCamera)/aspectRatio;
    this->vpHeight = -tan(fov/2)*(this->zFromCamera);
	this->numberOfSamples = (int)(this->sampleRate*this->timeWindowInS);
    this->interSampleLength = this->vpWidth/this->numberOfSamples;

    // Setup some variables for drawing properly
    GLfloat yScaleFactorToVPSpace = this->vpHeight/this->yPeakToPeak;

    // Draw Axis
    GLint factor = 2;        // Stippling factor
    GLushort pattern = 0x5555;    // Stipple pattern

	//glDisable(GL_BLEND);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(factor,pattern);
	glBegin(GL_LINES);
		glVertex2f(-vpWidth/2, 0.0f);
		glVertex2f(vpWidth/2, 0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(-vpWidth/2, -vpHeight/2);
		glVertex2f(-vpWidth/2, vpHeight/2);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(vpWidth/2, -vpHeight/2);
		glVertex2f(vpWidth/2, vpHeight/2);
	glEnd();

	// grid
	glDisable(GL_LINE_STIPPLE);
	glColor4f(0.0f,0.1f,1.1f,0.2f);
	for(int g=0;g<=8;g++)
	{
		glBegin(GL_LINES);
			glVertex2f(-vpWidth/2, (vpHeight/2)-(vpHeight/8)*g);
			glVertex2f(vpWidth/2, (vpHeight/2)-(vpHeight/8)*g);
		glEnd();
	}
	for(int g=0;g<=8;g++)
	{
		glBegin(GL_LINES);
			glVertex2f(vpWidth/2 -(vpWidth/8)*g, -vpHeight/2);
			glVertex2f(vpWidth/2 -(vpWidth/8)*g, vpHeight/2);
		glEnd();
	}
	
	// Draw threshold
	if(this->setYScaleMode)
		glColor3f(0.1f,1.0f,0.1f);

	// Render text
	glColor3f(1.0f,1.0f,1.0f);
	QFont font;
	font.setPointSize(7);
	QFontMetrics fm( font );

	// Mixed precision here - need to fix

	//DEBUG
        if(this->shouldUpdateTextDisplay)
        {
			// multiplying by 1000 to show numbers in uV
            if(((RTVTChannelWidget *)this->parent())->isFiltering)
            {
                    renderText((float)-vpWidth/2,(float)vpHeight/2+((float)fm.height()/20*5/8),0.0,QString::number(this->readFromChannelFilterDataPtr),font);
                    renderText((float)0.0,(float)vpHeight/2+((float)fm.height()/20*5/8),0.0,QString::number(((RTVTChannelWidget *)this->parent())->nextFilterWriteLocation),font);
            }
            else
            {
                    renderText((float)-vpWidth/2,(float)vpHeight/2+((float)fm.height()/20*5/8),0.0,QString::number(this->readFromChannelDataPtr/sizeof(unsigned char)),font);
                    renderText((float)0.0,(float)vpHeight/2+((float)fm.height()/20*5/8),0.0,QString::number(((RTVTChannelWidget *)this->parent())->nextWriteLocation/sizeof(unsigned char)),font);
            }

            renderText((float)-vpWidth/2 - (vpWidth/32)*5,(float)vpHeight/2 - ((float)fm.height()/20*5/8),0.0,QString::number(this->yPeakToPeak/2*this->ampGain*AMP_TO_UV*CONTROLLER_MULTIPLIER,'f',1),font);
            renderText((float)-vpWidth/2 - (vpWidth/32)*5,(float)0.0,0,QString::number(this->localMean*this->ampGain*AMP_TO_UV,'f',3),font);
            renderText((float)-vpWidth/2 - (vpWidth/32)*6,-(float)vpHeight/2,0.0,QString::number(-(this->yPeakToPeak/2*this->ampGain)*AMP_TO_UV*CONTROLLER_MULTIPLIER,'f',1),font);
            renderText((float)vpWidth/2 + (vpWidth/32),0,0,QString::number(timeWindowInS*1000,'f',2),font);
            renderText((float)vpWidth/2 + (vpWidth/32),(float)this->triggers[0].top*yScaleFactorToVPSpace,0.0,QString::number((this->triggers[0].top*this->ampGain)*AMP_TO_UV*CONTROLLER_MULTIPLIER,'f',1),font);
            renderText((float)-vpWidth/2 - (vpWidth/32)*5,(float)-vpHeight/2 + fm.height()/2 - vpHeight/8,0,QString::number((this->yPeakToPeak/8)*this->ampGain*AMP_TO_UV*CONTROLLER_MULTIPLIER,'f',1),font);
            this->shouldUpdateTextDisplay = false;
        }
	glDisable(GL_LINE_STIPPLE);
	this->viewNeedsRedraw = false;

    // Draw text from the drawBuffer
    if(drawingFromData)
    {
        // Draw from this channel pointer on to end of window
        GLfloat xPoint = -(float)vpWidth/2;
		float waveMean = 0.0;

		GLfloat vertices[DEFAULT_NUMBER_OF_SAMPLES_PER_WAVE*2];
        glColor3f(1.0f,1.0f,1.0f);

		// Loop through triggers and draw waveforms
		for(int t=0;t<this->numberOfActiveTriggers;t++)
		{
			// Set color of waveform base on trigger
			glColor3f((this->triggers[t].r),(this->triggers[t].g),(this->triggers[t].b));
			
			// Loop through waves in trigger
			for(int w=0;w<this->triggers[t].numberOfWaves;w++)
			{
				// Attempting to use optimized draw procedure... 
				xPoint = -(float)vpWidth/2;  // Reset x location
				// Get mean of wave
				/*waveMean = 0.0;
				for(int z=0;z<NUMBER_OF_SAMPLES_PER_WAVE*2;z+=2)
					waveMean += this->triggers[t].waveSample[w][z/2];
				waveMean = waveMean / NUMBER_OF_SAMPLES_PER_WAVE*2;*/

				for(int s=0;s<this->numberOfSamplesPerWave*2;s+=2)
				{
					vertices[s] = xPoint;
					vertices[s+1] = (this->triggers[t].waveSample[w][s/2] - this->triggers[t].waveSample[w][0])*yScaleFactorToVPSpace;//- this->triggers[t].waveSample[w][0])*yScaleFactorToVPSpace; //- this->drawingMean // this->triggers[t].waveSample[w][16]
					xPoint = xPoint + this->interSampleLength;
				}
					
				// activate and specify pointer to vertex array
				glEnableClientState(GL_VERTEX_ARRAY);
				glVertexPointer(2, GL_FLOAT, 0, vertices);
				
				// draw a waveform
				glDrawArrays(GL_LINE_STRIP, 0, this->numberOfSamplesPerWave);
				
				// deactivate vertex arrays after drawing
				glDisableClientState(GL_VERTEX_ARRAY);
			}
		}
    }

	// Draw the thresholds on top of the waves
	if(this->drawThresholds)
	{
		// Draw threshold 0 which is always a line threshold

		// Draw line for threshold
		if(this->mouseIsDown && this->selectedTrigger == 0)
		{
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset( 1.0f, 1.0f );
		}
		//glColor3f((this->triggers[0].r),(this->triggers[0].g),(this->triggers[0].b));
		glColor3f(1.0f,0.0f,0.0f);
		glBegin(GL_LINES);
			glVertex2f(-vpWidth/2, this->triggers[0].top*yScaleFactorToVPSpace);
			glVertex2f(vpWidth/2, this->triggers[0].top*yScaleFactorToVPSpace);
		glEnd();

		// Draw control point
		glBegin(GL_POLYGON);
			glVertex2f(-vpWidth/2 - BASE_TRIGGER_CONTROL_POINT_X1, this->triggers[0].top*yScaleFactorToVPSpace + BASE_TRIGGER_CONTROL_POINT_Y1);
			glVertex2f(-vpWidth/2 - BASE_TRIGGER_CONTROL_POINT_X1*1/3, this->triggers[0].top*yScaleFactorToVPSpace + BASE_TRIGGER_CONTROL_POINT_Y1);
			glVertex2f(-vpWidth/2, this->triggers[0].top*yScaleFactorToVPSpace);
			glVertex2f(-vpWidth/2 - BASE_TRIGGER_CONTROL_POINT_X1*1/3, this->triggers[0].top*yScaleFactorToVPSpace - BASE_TRIGGER_CONTROL_POINT_Y1);
			glVertex2f(-vpWidth/2 - BASE_TRIGGER_CONTROL_POINT_X1, this->triggers[0].top*yScaleFactorToVPSpace - BASE_TRIGGER_CONTROL_POINT_Y1);
		glEnd();

		if(this->mouseIsDown && this->selectedTrigger == 0)
		{
			glDisable(GL_POLYGON_OFFSET_FILL);

			// Draw the borders
			glColor3f(1.0f,1.0f,1.0f);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			
			glBegin(GL_LINES);
				glVertex2f(-vpWidth/2, this->triggers[0].top*yScaleFactorToVPSpace);
				glVertex2f(vpWidth/2, this->triggers[0].top*yScaleFactorToVPSpace);
			glEnd();

			// Draw control point
			glBegin(GL_POLYGON);
				glVertex2f(-vpWidth/2 - BASE_TRIGGER_CONTROL_POINT_X1, this->triggers[0].top*yScaleFactorToVPSpace + BASE_TRIGGER_CONTROL_POINT_Y1);
				glVertex2f(-vpWidth/2 - BASE_TRIGGER_CONTROL_POINT_X1*1/3, this->triggers[0].top*yScaleFactorToVPSpace + BASE_TRIGGER_CONTROL_POINT_Y1);
				glVertex2f(-vpWidth/2, this->triggers[0].top*yScaleFactorToVPSpace);
				glVertex2f(-vpWidth/2 - BASE_TRIGGER_CONTROL_POINT_X1*1/3, this->triggers[0].top*yScaleFactorToVPSpace - BASE_TRIGGER_CONTROL_POINT_Y1);
				glVertex2f(-vpWidth/2 - BASE_TRIGGER_CONTROL_POINT_X1, this->triggers[0].top*yScaleFactorToVPSpace - BASE_TRIGGER_CONTROL_POINT_Y1);
			glEnd();
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			// End Boarder
		}
		

		for (int t=1;t<this->numberOfActiveTriggers;t++)
		{
			glColor3f((this->triggers[t].r),(this->triggers[t].g),(this->triggers[t].b));
			
			if(this->mouseIsDown && this->selectedTrigger == t)
			{
				glEnable(GL_POLYGON_OFFSET_FILL);
				glPolygonOffset( 1.0f, 1.0f );
			}

			// Draw sample number control point
			glBegin(GL_POLYGON);
				glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) - TRIGGER_CONTROL_POINT_X1, -vpHeight/2 - TRIGGER_CONTROL_POINT_Y1);
				glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) - TRIGGER_CONTROL_POINT_X1, -vpHeight/2 - TRIGGER_CONTROL_POINT_Y1*1/3);
				glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2), -vpHeight/2);
				glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) + TRIGGER_CONTROL_POINT_X1, -vpHeight/2 - TRIGGER_CONTROL_POINT_Y1*1/3);
				glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) + TRIGGER_CONTROL_POINT_X1, -vpHeight/2 - TRIGGER_CONTROL_POINT_Y1);
			glEnd();

			// Draw top control point
			glBegin(GL_POLYGON);
				glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) - TRIGGER_CONTROL_POINT_X1*2, this->triggers[t].top*yScaleFactorToVPSpace + TRIGGER_CONTROL_POINT_Y1);
				glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) + TRIGGER_CONTROL_POINT_X1*2, this->triggers[t].top*yScaleFactorToVPSpace + TRIGGER_CONTROL_POINT_Y1);
				glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2), this->triggers[t].top*yScaleFactorToVPSpace);
			glEnd();

			// Draw bottom control point
			glBegin(GL_POLYGON);
				glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) - TRIGGER_CONTROL_POINT_X1*2, this->triggers[t].bottom*yScaleFactorToVPSpace - TRIGGER_CONTROL_POINT_Y1);
				glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) + TRIGGER_CONTROL_POINT_X1*2, this->triggers[t].bottom*yScaleFactorToVPSpace - TRIGGER_CONTROL_POINT_Y1);
				glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2), this->triggers[t].bottom*yScaleFactorToVPSpace);
			glEnd();

			if(this->mouseIsDown && this->selectedTrigger == t)
			{
				glDisable(GL_POLYGON_OFFSET_FILL);

				// Draw the borders
				glColor3f(1.0f,1.0f,1.0f);
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				
				// Draw sample number control point
				glBegin(GL_POLYGON);
					glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) - TRIGGER_CONTROL_POINT_X1, -vpHeight/2 - TRIGGER_CONTROL_POINT_Y1);
					glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) - TRIGGER_CONTROL_POINT_X1, -vpHeight/2 - TRIGGER_CONTROL_POINT_Y1*1/3);
					glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2), -vpHeight/2);
					glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) + TRIGGER_CONTROL_POINT_X1, -vpHeight/2 - TRIGGER_CONTROL_POINT_Y1*1/3);
					glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) + TRIGGER_CONTROL_POINT_X1, -vpHeight/2 - TRIGGER_CONTROL_POINT_Y1);
				glEnd();

				// Draw top control point
				glBegin(GL_POLYGON);
					glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) - TRIGGER_CONTROL_POINT_X1*2, this->triggers[t].top*yScaleFactorToVPSpace + TRIGGER_CONTROL_POINT_Y1);
					glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) + TRIGGER_CONTROL_POINT_X1*2, this->triggers[t].top*yScaleFactorToVPSpace + TRIGGER_CONTROL_POINT_Y1);
					glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2), this->triggers[t].top*yScaleFactorToVPSpace);
				glEnd();

				// Draw bottom control point
				glBegin(GL_POLYGON);
					glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) - TRIGGER_CONTROL_POINT_X1*2, this->triggers[t].bottom*yScaleFactorToVPSpace - TRIGGER_CONTROL_POINT_Y1);
					glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2) + TRIGGER_CONTROL_POINT_X1*2, this->triggers[t].bottom*yScaleFactorToVPSpace - TRIGGER_CONTROL_POINT_Y1);
					glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2), this->triggers[t].bottom*yScaleFactorToVPSpace);
				glEnd();
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				// End Boarder
			}

			// Draw line in-between y control points
			glBegin(GL_LINES);
				glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2),this->triggers[t].bottom*yScaleFactorToVPSpace);
				glVertex2f((this->triggers[t].sampleNumberToTest*this->interSampleLength - vpWidth/2),this->triggers[t].top*yScaleFactorToVPSpace);
			glEnd();

			// For testing the hit rects
			// Get the cursor and convert to model coordinates
			//glColor3f(1.0f,1.0f,1.0f);
			//GLint viewport[4];
			//GLdouble mvmatrix[16], projmatrix[16];
			//GLint realY,realX;
			//GLdouble wx, wy, wz;

			//// Convert to model coordinates
			//glGetIntegerv(GL_VIEWPORT, viewport);
			//glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
			//glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

			//realY = viewport[3] - (GLint) cursorClickLocation.y() - 1;
			//realX = viewport[2] - (GLint) cursorClickLocation.x() - 1;
			//gluUnProject((GLdouble) realX, (GLdouble) realY, 0.0, mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
			//wx = -wx*100;
			//wy = wy*100;

			//glBegin(GL_POLYGON);
			//	glVertex2f(wx-.1,wy-.1);
			//	glVertex2f(wx-.1,wy+.1);
			//	glVertex2f(wx+.1,wy+.1);
			//	glVertex2f(wx+.1,wy-.1);
			//glEnd();
		}

		// Below here should not be called by paint... should call paint!
		/*if(!(this->waitUntilNextTransfer))
		{
			if(this->assignedViewerChannel != SYNCH_CHANNEL)
			{
				if(((RTVTChannelWidget *)this->parent())->isFiltering)
					this->applySimpleThresholdOnFilteredData();
				else 
					this->applySimpleThreshold();
			}
			else //increment the synch channel just as much as the others
				this->readFromChannelDataPtr += WAVE_BYTE_LENGTH*numberOfWaveLengthsToCheck;
		}	
		*/
	}
	else
		glColor3f(0.6f,0.6f,0.6f);
}

// Function to enable smoothing
void RTVTWaveViewerGLWidget::enableLineSmoothing( bool bEnable )
{
    if( bEnable )
    {
        // Smooth out lines
        glEnable( GL_LINE_SMOOTH );
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

        // Enable Blending
        glEnable(GL_BLEND);

        // Specifies pixel arithmetic
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        this->smooth = true;
        std::cout << "::Smoothing enabled" << std::endl;

    }
    else // if the options are disabled
    {
        glDisable(GL_LINE_SMOOTH); // Smooth out lines
        glDisable(GL_BLEND);

        this->smooth = false;

        std::cout << "::Smoothing disabled" << std::endl;
    }

    this->lineSmoothingEnabled = bEnable;
}

// Utilities

void RTVTWaveViewerGLWidget::findStartPosition()
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

       if(((unsigned char)((RTVTChannelWidget *)this->parent())->channelData[f*2] == 0x21)&& ((unsigned char)((RTVTChannelWidget *)this->parent())->channelData[f*2+1] == 0xCD))//if((sTmp1[2] == '2') && (sTmp1[3] == '1') && (sTmp2[2] == 'c') && (sTmp2[3] == 'd'))
       {
           //std::cout << "Found frame synch..." << std::endl;
           this->readStartPositionForChannel = f;
           f = 15;
       }
    }
}

void RTVTWaveViewerGLWidget::tiggerTimerTimedOut()
{
	if(((RTVTChannelWidget *)this->parent())->isFiltering)
		this->applySimpleThresholdOnFilteredData();
	else 
		this->applySimpleThreshold();
}

void RTVTWaveViewerGLWidget::applySimpleThreshold()
{
	//unsigned int test = (((RTVTChannelWidget *)this->parent())->nextWriteLocation - WAVE_BYTE_LENGTH*10);

	if(this->readFromChannelDataPtr > (CHANNEL_BUFFER_LENGTH-waveByteLength*numberOfWaveLengthsToCheck)) {}
		//this->readFromChannelDataPtr = 0;
	if(this->readFromChannelDataPtr > (((RTVTChannelWidget *)this->parent())->nextWriteLocation - waveByteLength*numberOfWaveLengthsToCheck))
	{
		testMark++;
		waitUntilNextTransfer = true;
		return;
	}
	
	//int workingBufferLength = BACK_BUFFER_LENGTH/NUMBER_OF_CHANNELS_IN_DATA;
	unsigned int i = 0;
	//if(((RTVTChannelWidget *)this->parent())->nextWriteLocation == 0)
	//	return; // need to wait for some data in the buffer
	//if(this->thresholdReadPtr < (((RTVTChannelWidget *)this->parent())->nextWriteLocation - workingBufferLength))
	//	this->thresholdReadPtr = ((RTVTChannelWidget *)this->parent())->nextWriteLocation - workingBufferLength;
	//if(this->thresholdReadPtr > (((RTVTChannelWidget *)this->parent())->nextWriteLocation - WAVE_BYTE_LENGTH*10))
	//	this->thresholdReadPtr = ((RTVTChannelWidget *)this->parent())->nextWriteLocation;	
	//for(i=this->thresholdReadPtr;i<(this->thresholdReadPtr+WAVE_BYTE_LENGTH*10);)

	// Shouldn't need this check here = wastes time
	//float dMean = 0.0;
	//for (unsigned int j = this->readFromChannelDataPtr ; j <(this->readFromChannelDataPtr+WAVE_BYTE_LENGTH*numberOfWaveLengthsToCheck); j+=2)  
	//	dMean += (((RTVTChannelWidget *)this->parent())->channelData[j+1]*256 + ((RTVTChannelWidget *)this->parent())->channelData[j])*this->adcFactor/this->ampGain; //+= dRecastXfr;	// Accumulate mean

	//dMean = (dMean/(WAVE_BYTE_LENGTH*numberOfWaveLengthsToCheck))*2; // *3 works for the test vectors...
	//this->localMean = dMean;
	////this->localMean = this->localMean/2;
	//this->drawingMean = this->localMean;

    for(i=this->readFromChannelDataPtr;i<(this->readFromChannelDataPtr+waveByteLength*numberOfWaveLengthsToCheck);)
    {
		// if 0 shift over 32 - issue with -32 index...
		if(i==0)
			i = this->numberOfSamplesBeforeTrigger*2;

		// Have a simple threshold to stop over checking for spikes - i.e. if we are getting more than 100 in
		// should be value in V
		float value = ((((float)((RTVTChannelWidget *)this->parent())->channelData[i+1]*256.0)+(float)((RTVTChannelWidget *)this->parent())->channelData[i]))*this->adcFactor/this->ampGain; // the *2 is for bit shift //*this->ampGain;//(((((RTVTChannelWidget *)this->parent())->channelData[i+1]*256)+((RTVTChannelWidget *)this->parent())->channelData[i]))/10;
		
		// Now that we have the value, should we check / add to the mean?
		if(this->meanCheckPoint == this->meanCounter) // YES
		{
			this->localMean += value;
			this->localMean = this->localMean/2;
			this->drawingMean = this->localMean;
			this->meanCounter = 0;
		}
		else
			this->meanCounter++;

		// Have we passed the first threshold???
		bool baseTriggerWasHit = false;
		if(this->triggers[0].top > 0) 
		{ 
			if((value - this->localMean) > this->triggers[0].top) 
			{ 
				baseTriggerWasHit = true;
			}
		}
		else // baseline trigger is below zero on view - need to check below
		{ 
			if((value - this->localMean) <= (this->triggers[0].top)) { baseTriggerWasHit = true;}
		}

		if(baseTriggerWasHit) // ***** NEEDS TO BE FIXED AS VALUE SHOULD BE -PEAK TO +PEAK
		{
			// YES, we have passed the baseline threshold (trigger[0])
			// Let's copy the wave to the waveSample
			float sampleValue = 0.0;
			
			// Get and store the time
			this->triggers[0].tickOfSampleCrossing[this->triggers[0].nextWaveNumber] = theTime->calculateElapsedTime();

			// Fill the wave samples into the storage array - crossing threshold centered at 1/3 samples into wave
			for(int z=-this->numberOfSamplesBeforeTrigger*2; z<(this->numberOfSamplesPerWave-this->numberOfSamplesBeforeTrigger)*2 ; z+=2)
			{
				sampleValue = ((((unsigned char)((RTVTChannelWidget *)this->parent())->channelData[(i+z)+1]*256)+(unsigned char)((RTVTChannelWidget *)this->parent())->channelData[(i+z)]))*this->adcFactor/this->ampGain;
				
				// Remove the mean
				//sampleValue -= this->localMean;
				this->triggers[0].waveSample[this->triggers[0].nextWaveNumber][(z+this->numberOfSamplesBeforeTrigger*2)/2] = sampleValue - this->localMean;
			}
			if(this->triggers[0].nextWaveNumber >= NUMBER_OF_WAVES_PER_TRIGGER - 1)
			{
				// We need to send out waves for writing
				// Copy and send up to heap
				waveformDatum datum;
				datum.channelNumber = (unsigned short)this->assignedViewerChannel;
				datum.unitNumber = 0;
				memcpy(&datum.waveSamples, &this->triggers[0].waveSample, sizeof(this->triggers[0].waveSample));
				memcpy(&datum.tickStamps, &this->triggers[0].tickOfSampleCrossing, sizeof(this->triggers[0].tickOfSampleCrossing));

				// Send it up - need to destroy later
				((RTVTChannelWidget*)this->parent())->childHasWaveformsToWrite(datum);
				//emit iHaveWaveformsToWrite(datum);

				this->triggers[0].nextWaveNumber = 0;
				this->triggers[0].numberOfWaves = 0;
				
			}
			else
			{
				if(this->triggers[0].numberOfWaves >= NUMBER_OF_WAVES_PER_TRIGGER)
					this->triggers[0].nextWaveNumber++;
				else
				{
					this->triggers[0].numberOfWaves++;
					this->triggers[0].nextWaveNumber++;
				}
				
			}
			
			// Update anything outside of this object
			//emit waveViewEditedTrigger(this->triggers[0]);
			//((RTVTChannelWidget*)this->parent())->childHasEditedTrigger(this->triggers[0]);

			// Write the wave to NEV
			//this->nevWriter.wr(QDateTime::currentDateTime().toUTC().toTime_t(),this->assignedViewerChannel,0,(short(*)[64])this->triggers[0].waveSample[this->triggers[0].nextWaveNumber-1]);
			
			// Are there any other triggers to be used? let's iterate and find out
			for (int t=1;t<this->numberOfActiveTriggers;t++)
			{
				// YES, there is another trigger to check
				float tempTopValue = 0.0;
				float tempBottomValue = 0.0;

				// Set the top check
				if(this->triggers[t].top > 0) { tempTopValue = this->triggers[t].top;} //+ this->localMean
				else { tempTopValue = this->triggers[t].top;}

				// Set the bottom check
				if(this->triggers[t].bottom > 0) { tempBottomValue = this->triggers[t].bottom;} //+ this->localMean
				else { tempBottomValue = this->triggers[t].bottom;}

				// Check the trigger hoops (only one right now)
				if((this->triggers[0].waveSample[this->triggers[0].nextWaveNumber-1][this->triggers[t].sampleNumberToTest] > tempBottomValue) &&
					(this->triggers[0].waveSample[this->triggers[0].nextWaveNumber-1][this->triggers[t].sampleNumberToTest] < tempTopValue))
				{
					// YES, the waveSample at our request is in the hoop
					
					// Save the time
					this->triggers[t].tickOfSampleCrossing[this->triggers[t].nextWaveNumber] = theTime->calculateElapsedTime();
					
					// Save the waveForm again in the hooped trigger for display later
					for(int i=0;i<this->numberOfSamplesPerWave;i++)
						this->triggers[t].waveSample[this->triggers[t].nextWaveNumber][i] = this->triggers[0].waveSample[this->triggers[0].nextWaveNumber-1][i];
					
					// Now adjust the sample number
					if(this->triggers[t].nextWaveNumber >= NUMBER_OF_WAVES_PER_TRIGGER - 1) 
					{
						// We need to send out waves for writing
						// Copy and send up to heap
						waveformDatum datum;
						datum.channelNumber = (unsigned short)this->assignedViewerChannel;
						datum.unitNumber = t;
						//unsigned int test1 = sizeof(datum.waveSamples);
						//unsigned int test2 = sizeof(this->triggers[t].waveSample);
						memcpy(&datum.waveSamples, &this->triggers[t].waveSample, sizeof(this->triggers[t].waveSample));
						memcpy(&datum.tickStamps, &this->triggers[t].tickOfSampleCrossing, sizeof(this->triggers[t].tickOfSampleCrossing));

						// Send it up - need to destroy later
						((RTVTChannelWidget*)this->parent())->childHasWaveformsToWrite(datum);
						//emit iHaveWaveformsToWrite(datum);

						// Reset iPointer to beginning - will write over old waves now
						this->triggers[t].nextWaveNumber = 0;
						this->triggers[t].numberOfWaves = 0;
						
					}
					else
					{
						if(this->triggers[t].numberOfWaves >= NUMBER_OF_WAVES_PER_TRIGGER)
							this->triggers[t].nextWaveNumber++;
						else
						{
							this->triggers[t].numberOfWaves++;
							this->triggers[t].nextWaveNumber++;
						}
					}
					
					//emit waveViewEditedTrigger(this->triggers[t]);
					//((RTVTChannelWidget*)this->parent())->childHasEditedTrigger(this->triggers[t]);
				}
			}
			i+= this->numberOfSamplesPerWave*2-2;//126; // Skip over 1.6 ms -- SHOULD WE BE DOING THIS?
		}

        i=i+2; // + 2 move over one sample (channelData is per/channel data - prealigned 
    }
	this->readFromChannelDataPtr += waveByteLength*numberOfWaveLengthsToCheck;//WAVE_BYTE_LENGTH*10;
}

void RTVTWaveViewerGLWidget::applySimpleThresholdOnFilteredData()
{
	if(this->readFromChannelFilterDataPtr > (CHANNEL_BUFFER_LENGTH/2-waveByteLength/2*numberOfWaveLengthsToCheck)) {}
	//unsigned int tempWL = ((RTVTChannelWidget *)this->parent())->nextFilterWriteLocation;
	if(this->readFromChannelFilterDataPtr >= (((RTVTChannelWidget *)this->parent())->nextFilterWriteLocation - waveByteLength/2*numberOfWaveLengthsToCheck))
	{
		testMark++;
		waitUntilNextTransfer = true;
		return;
	}
	
	unsigned int i = 0;

	//float accumulator = 0.0;
	//float sample  = 0.0;
	//for (unsigned int j = this->readFromChannelFilterDataPtr ; j < ((this->readFromChannelFilterDataPtr+WAVE_BYTE_LENGTH/2*numberOfWaveLengthsToCheck -1)); j+=1)  
	//{
	//	// this is a workaround... need to change this (dmean craps out when filtered data has a glitch?)
	//	sample = (float)(((RTVTChannelWidget *)this->parent())->filteredChannelData[j]);
	//	if( sample < 0.0) 
	//	{
	//		int testmark = 1;
	//	}
	//	else
	//	{
	//		accumulator += sample;	// Accumulate mean
	//		i++;
	//	}
	//}

	//if(i==0)
	//	i++;
	//accumulator = (accumulator/i)*(this->adcFactor)/this->ampGain; // *3 works for the test vectors...
	//this->localMean += accumulator;
	//this->localMean = this->localMean/2;
	//this->drawingMean = this->localMean;
	
    for(i=this->readFromChannelFilterDataPtr;i<(this->readFromChannelFilterDataPtr+waveByteLength/2*numberOfWaveLengthsToCheck);)
    {
		// if 0 shift over 16 - issue with -16 index...
		if(i==0)
			i = 16;

		// should be value in V
		float value = (float)(((RTVTChannelWidget *)this->parent())->filteredChannelData[i])*this->adcFactor/this->ampGain;
		
		// Unfiltered value for testing
		//float UFvalue = ((((unsigned char)((RTVTChannelWidget *)this->parent())->channelData[i*2+1]*256)+(unsigned char)((RTVTChannelWidget *)this->parent())->channelData[i*2]))*this->adcFactor/this->ampGain;//*this->ampGain;//(((((RTVTChannelWidget *)this->parent())->channelData[i+1]*256)+((RTVTChannelWidget *)this->parent())->channelData[i]))/10;
		
		// Now that we have the value, should we check / add to the mean?
		if(this->meanCheckPoint == this->meanCounter) // YES
		{
			if((float)abs(this->localMean)>1000.0)
				this->localMean = value;

			this->localMean += value;
			this->localMean = this->localMean/2;
			this->drawingMean = this->localMean;
			this->meanCounter = 0;
		}
		else
			this->meanCounter++;

		// Have we passed the first threshold???
		bool baseTriggerWasHit = false;
		if(this->triggers[0].top > 0) 
		{ 
			if((value - this->localMean) > this->triggers[0].top) 
			{ 
				baseTriggerWasHit = true;
			}
		}
		else // baseline trigger is below zero on view - need to check below
		{ 
			if((value - this->localMean) <= (this->triggers[0].top)) { baseTriggerWasHit = true;}
		}
		
		if(baseTriggerWasHit && i>=16) // ***** NEEDS TO BE FIXED AS VALUE SHOULD BE -PEAK TO +PEAK
		{
			// YES, we have passed the baseline threshold (trigger[0])
			// Let's copy the wave to the waveSample
			float sampleValue = 0.0;
			
			// Get and store the time
			this->triggers[0].tickOfSampleCrossing[this->triggers[0].nextWaveNumber] = theTime->calculateElapsedTime();
			
			// Fill the wave samples into the storage array - crossing threshold centered at 16 samples into wave
			for(int z=-16; z<48 ; z+=1)
			{
				sampleValue = (float)(((RTVTChannelWidget *)this->parent())->filteredChannelData[i+z])*this->adcFactor/this->ampGain;
				
				// Remove the mean
				//sampleValue -= this->localMean;
				this->triggers[0].waveSample[this->triggers[0].nextWaveNumber][(z+16)] = sampleValue;
			}
			if(this->triggers[0].nextWaveNumber >= NUMBER_OF_WAVES_PER_TRIGGER - 1)
			{
				// We need to send out waves for writing
				// Copy and send up to heap
				waveformDatum datum;
				datum.channelNumber = (unsigned short)this->assignedViewerChannel;
				datum.unitNumber = 0;
				memcpy(&datum.waveSamples, &this->triggers[0].waveSample, sizeof(this->triggers[0].waveSample));
				memcpy(&datum.tickStamps, &this->triggers[0].tickOfSampleCrossing, sizeof(this->triggers[0].tickOfSampleCrossing));
				
				// Send it up - need to destroy later
				//((RTVTChannelWidget*)this->parent())->childHasWaveformsToWrite(datum);
				//emit iHaveWaveformsToWrite(datum);
				
				this->triggers[0].nextWaveNumber = 0;
				this->triggers[0].numberOfWaves = 0;
				
			}
			else
			{
				if(this->triggers[0].numberOfWaves >= NUMBER_OF_WAVES_PER_TRIGGER)
					this->triggers[0].nextWaveNumber++;
				else
				{
					this->triggers[0].numberOfWaves++;
					this->triggers[0].nextWaveNumber++;
				}
				
			}
			
			// Update anything outside of this object
			//emit waveViewEditedTrigger(this->triggers[0]);
			
			// Write the wave to NEV
			//this->nevWriter.wr(QDateTime::currentDateTime().toUTC().toTime_t(),this->assignedViewerChannel,0,(short(*)[64])this->triggers[0].waveSample[this->triggers[0].nextWaveNumber-1]);
			
			// Are there any other triggers to be used? let's iterate and find out
			for (int t=1;t<this->numberOfActiveTriggers;t++)
			{
				// YES, there is another trigger to check
				float tempTopValue = 0.0;
				float tempBottomValue = 0.0;
				
				// Set the top check
				if(this->triggers[t].top > 0) { tempTopValue = this->triggers[t].top + this->localMean;}
				else { tempTopValue = this->localMean + this->triggers[t].top;}
				
				// Set the bottom check
				if(this->triggers[t].bottom > 0) { tempBottomValue = this->triggers[t].bottom + this->localMean;}
				else { tempBottomValue = this->localMean + this->triggers[t].bottom;}
				
				// Check the trigger hoops (only one right now)
				if((this->triggers[0].waveSample[this->triggers[0].nextWaveNumber-1][this->triggers[t].sampleNumberToTest] > tempBottomValue) &&
				   (this->triggers[0].waveSample[this->triggers[0].nextWaveNumber-1][this->triggers[t].sampleNumberToTest] < tempTopValue))
				{
					// YES, the waveSample at our request is in the hoop
					
					// Save the time
					this->triggers[t].tickOfSampleCrossing[this->triggers[t].nextWaveNumber] = theTime->calculateElapsedTime();
					
					// Save the waveForm again in the hooped trigger for display later
					for(int i=0;i<64;i++)
						this->triggers[t].waveSample[this->triggers[t].nextWaveNumber][i] = this->triggers[0].waveSample[this->triggers[0].nextWaveNumber-1][i];
					
					// Now adjust the sample number
					if(this->triggers[t].nextWaveNumber >= NUMBER_OF_WAVES_PER_TRIGGER - 1) 
					{
						// We need to send out waves for writing
						// Copy and send up to heap
						waveformDatum datum;
						datum.channelNumber = (unsigned short)this->assignedViewerChannel;
						datum.unitNumber = t;
						memcpy(&datum.waveSamples, &this->triggers[t].waveSample, sizeof(this->triggers[t].waveSample));
						memcpy(&datum.tickStamps, &this->triggers[t].tickOfSampleCrossing, sizeof(this->triggers[t].tickOfSampleCrossing));
						
						// Send it up - need to destroy later
						//((RTVTChannelWidget*)this->parent())->childHasWaveformsToWrite(datum);
						//emit iHaveWaveformsToWrite(datum);
						
						// Reset iPointer to beginning - will write over old waves now
						this->triggers[t].nextWaveNumber = 0;
						this->triggers[t].numberOfWaves = 0;
						
					}
					else
					{
						if(this->triggers[t].numberOfWaves >= NUMBER_OF_WAVES_PER_TRIGGER)
							this->triggers[t].nextWaveNumber++;
						else
						{
							this->triggers[t].numberOfWaves++;
							this->triggers[t].nextWaveNumber++;
						}
					}
					
					//emit waveViewEditedTrigger(this->triggers[t]);
				}
			}
			i+=64; // Skip over 1.6 ms -- SHOULD WE BE DOING THIS?
		}
		
        i=i+1; // + 1 move over one sample (channelData is per/channel data - prealigned 
    }
	this->readFromChannelFilterDataPtr += waveByteLength/2*numberOfWaveLengthsToCheck;//WAVE_BYTE_LENGTH*10;
}

void RTVTWaveViewerGLWidget::applyConstraints()
{
	/*
	// trigger event by scanning the filtered data array for channel iChanNum from 
	// [iStartFrom] looking for either a dV in some dT set by parameters from 
	// private variables or a threshold level and slope as determined by the 
	// value of the iTrigEnblFlag.  If iStartFrom < filter length, then start point calculated 
	// from window length/filter length.
	// Return -1 for no trigger, and index of midpoint between max and min for
	// trigger.
	
	int iIndx, iMaxT, iMinT, iMaxDeltaT, j, iIndxStart, iIndxStop, iDisplayWindowLength;
	int iReturnIndx, iNewMaxMinT;
	float dMax, dMin, dVsig, dVsigLag, dThresh;

	int indexOfCrossing;
	
	// The starting point for a trigger event search must avoid the bad data at
	// the beginning of the data buffer and guarantee that it is possible to display
	// a result at mid-window.  See notes under Run() at point where 
	// new data transferred from NI buffer to my main buffer with channel assignment.

	iIndxStart = 0; //Fir[selectedFilterIndex]->GetFilterLen() + 5;

	if (iStartFrom > iIndxStart) iIndxStart = iStartFrom;
	iIndxStop = DRAW_BUFFER_LENGTH - DRAW_FRAME_LENGTH; //iEndOfFilteredData - iDisplayWindowLength;

	if (1) // For now just the hoop
	{
		// Initialize
		dMax = -2.4;
		dMin = +2.4;
		indexOfCrossing = 0; // INDEX of crossing the threshold

		// Scan entire block of channel data
		for (iIndx = iIndxStart; iIndx < iIndxStop; iIndx++)  
		{
			if ((iMaxT < 0) || (iMinT < 0))  {	// one or other times is out of joint
				dMax = -2.4;
				dMin = +2.4;
				for (j = 0; j < iMaxDeltaT; j++)  
				{	// Fill in private variable for max delta T
					dVsig = dFilteredDataArray[iChanNum][iIndx + j];
					if (dVsig > dMax) {dMax = dVsig; iMaxT = j;}
					if (dVsig < dMin) {dMin = dVsig; iMinT = j;}
				}
				goto ApplyTest1;
			}

			// Fit in latest point for advance that does not invalidate max or min
			// If whole interval not searched then this iNewMaxMinT 
			// index is the only potential candidate for a new max or min.
			dVsig = dFilteredDataArray[iChanNum][iIndx + iMaxDeltaT - 1];	
			if (dVsig > dMax) {dMax = dVsig; iMaxT = iNewMaxMinT;}
			if (dVsig < dMin) {dMin = dVsig; iMinT = iNewMaxMinT;}
			// Now have indices and values of max and min in interval [iIndx, iIndx + iMaxDeltaT).
ApplyTest1:
			dVsig = dMax - dMin;	// Delta V to use as test
			iReturnIndx = iIndx + ((iMaxT + iMinT) >> 1);	// Return value if trigger event
			
			// Handle possitive and negative thresholds
			if (dTrigDeltaVArray[iChanNum] > 0)
			{
				if (dVsig > dTrigDeltaVArray[iChanNum]) 
				{
					if ((iTrigRampMode == 0) && (iMaxT > iMinT)) return(iReturnIndx);
					if ((iTrigRampMode == 1) && (iMinT > iMaxT)) return(iReturnIndx);
					if (iTrigRampMode == 2) return(iReturnIndx);
					}
			}
			else // case threshold < 0
			{
				if (dVsig < dTrigDeltaVArray[iChanNum]) 
				{
					if ((iTrigRampMode == 0) && (iMaxT > iMinT)) return(iReturnIndx);
					if ((iTrigRampMode == 1) && (iMinT > iMaxT)) return(iReturnIndx);
					if (iTrigRampMode == 2) return(iReturnIndx);
				}
			}
		}
		
	}
	return(-1);	// No event
	*/
}

void RTVTWaveViewerGLWidget::play()
{
	this->glRedrawTimer->start(30);
	//this->triggerTimer->start(125);
}

void RTVTWaveViewerGLWidget::stop()
{
	this->glRedrawTimer->stop();
	//this->triggerTimer->stop();
}

void RTVTWaveViewerGLWidget::runThreadedTiggers()
{
	if(((RTVTChannelWidget *)this->parent())->isFiltering)
		*triggersFuture = QtConcurrent::run(this,&RTVTWaveViewerGLWidget::applySimpleThresholdOnFilteredData);
	else 
		*triggersFuture = QtConcurrent::run(this,&RTVTWaveViewerGLWidget::applySimpleThreshold);
	
    triggersWatcher->setFuture(*triggersFuture);
}

void RTVTWaveViewerGLWidget::triggersThreadFinishedRunning()
{
    //std::cout << "SB Thread finished running." << std::endl;

    //this->sbTransferTimer->stop();
	if(this->setThresholdMode)
		this->triggerTimer->start(30);
}

void RTVTWaveViewerGLWidget::clearWaveforms()
{
	for(int h=0;h<this->numberOfActiveTriggers;h++)
	{
		memset(this->triggers[h].waveSample, 0, NUMBER_OF_WAVES_PER_TRIGGER*DEFAULT_NUMBER_OF_SAMPLES_PER_WAVE*sizeof(short));
		this->triggers[h].numberOfWaves = 0;
		this->triggers[h].nextWaveNumber = 0;
	}
}

void RTVTWaveViewerGLWidget::resetTriggers()
{
	for(int h=1;h<this->numberOfActiveTriggers;h++)
	{
		this->triggers[h].top = 0.020f;
		this->triggers[h].bottom = -0.020f;
		this->triggers[h].sampleNumberToTest = 24+h*2;
	}
}

void RTVTWaveViewerGLWidget::updateWaveCheckValue(int inValue)
{
	this->numberOfWaveLengthsToCheck = inValue;
}

void RTVTWaveViewerGLWidget::tellTextToUpdate()
{
    this->shouldUpdateTextDisplay = true;
}
