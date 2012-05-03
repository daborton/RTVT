#include "rtvthudwaveview.h"
#include "ui_rtvthudwaveview.h"

#include <QFileDialog.h>

RTVTHUDWaveView::RTVTHUDWaveView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RTVTHUDWaveView)
{
    ui->setupUi(this);

	connect(ui->clearWaveformsButton, SIGNAL(clicked()), this, SLOT(clearWaveforms()));
	connect(ui->resetTriggersButton, SIGNAL(clicked()), this, SLOT(resetTriggers()));
	connect(ui->saveToNEVCheckbox, SIGNAL(clicked(bool)), this, SLOT(propogateNEVFile(bool)));
	connect(ui->saveNEVToggleButton, SIGNAL(clicked()), this, SLOT(propogateSaveNEVToggle()));
	connect(ui->setNEVFileButton, SIGNAL(clicked()), this, SLOT(setNEVFileLocation()));
	connect(ui->waveCheckSlider, SIGNAL(sliderMoved(int)), ui->waveCheckNumberLCD, SLOT(display(int)));
	connect(ui->waveCheckSlider, SIGNAL(sliderMoved(int)), this, SLOT(propogateSetWaveCheckLength(int)));
        connect(ui->adjustAllThresholdsCheckBox, SIGNAL(stateChanged(int)), this, SLOT(thresholdTogetherBoxClicked(int)));

	
	// setup the QTableView
	//itemDelegate = new CPSInstrumentDelegate(this->ui->tableView, availableInstrumentsStringList, attachableProcessesStringList);
	//this->ui->triggeredWaveformTableView->setItemDelegate(itemDelegate);
    this->ui->triggeredWaveformDataTable->setEditTriggers(QAbstractItemView::DoubleClicked
										 | QAbstractItemView::SelectedClicked);
    this->ui->triggeredWaveformDataTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->ui->triggeredWaveformDataTable->horizontalHeader()->setStretchLastSection(true);
}


RTVTHUDWaveView::~RTVTHUDWaveView()
{
    delete ui;
}

void RTVTHUDWaveView::setTableModel(RTVTTriggerModel *model)
{
	this->ui->triggeredWaveformDataTable->setModel(model);
	
	this->ui->triggeredWaveformDataTable->resizeColumnsToContents();
	this->ui->triggeredWaveformDataTable->resizeRowsToContents();
}

void RTVTHUDWaveView::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void RTVTHUDWaveView::clearWaveforms()
{
	emit clearWaveformButtonClicked();
}

void RTVTHUDWaveView::resetTriggers()
{
	emit resetWaveformTriggersButtonClicked();
}

void RTVTHUDWaveView::propogateNEVFile(bool inState)
{
	if(inState)
	{
		QByteArray tempByteArray = ui->nevFileNameLabel->text().toAscii();
		char * fileName = tempByteArray.data();
		//char* mode = "w";

		emit saveToNEVFileCheckboxClicked(inState,fileName); // should pass char array if saving is working

		//fstream os;
		//os.open("C:/Users/Public/testNEVFile.nev",fstream::out);
		//os << "Hellow my darling!";
		//os.close();
		//int tempi = 5;
	}
}

void RTVTHUDWaveView::propogateSetWaveCheckLength(int inValue)
{
	//check if it is a number
	emit updateWaveCheckValue(inValue);
}

void RTVTHUDWaveView::propogateSaveNEVToggle()
{
	if(ui->saveNEVToggleButton->isChecked())
	{
		ui->saveNEVToggleButton->setText("Turn Saving OFF");
		emit saveNEVToggleButtonState(true);
	}
	else
	{
		ui->saveNEVToggleButton->setText("Turn Saving ON");
		emit saveNEVToggleButtonState(false);
	}
}

void RTVTHUDWaveView::thresholdTogetherBoxClicked(int checkedState)
{
	Q_UNUSED(checkedState);
    if(this->ui->adjustAllThresholdsCheckBox->isChecked())
        emit controllerSaysMoveThresholdsTogether(true);
    else
        emit controllerSaysMoveThresholdsTogether(false);
}

void RTVTHUDWaveView::setNEVFileLocation()
{
	QString path;
    
	path = QFileDialog::getSaveFileName(this, tr("Set NEV File Location"),
                            tr("C:/Users/Public"),
                            tr("NEV (*.nev)"));
  
	this->ui->nevFileNameLabel->setText( path );
}
