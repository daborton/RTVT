#include "rtvthudcontrollerview.h"
#include "ui_rtvthudcontrollerview.h"

RTVTHUDControllerView::RTVTHUDControllerView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RTVTHUDControllerView)
{
    ui->setupUi(this);
	
	this->ui->selectFilterComboBox->insertSeparator(1);
	this->ui->selectFilterComboBox->insertSeparator(3);
	
	connect(this->ui->selectFilterComboBox, SIGNAL(activated(int)), this, SLOT(filterSelectionChanged(int)));
       connect(this->ui->numberOfChannelViewsBox, SIGNAL(returnPressed()), this, SLOT(numberOfChannelViewsChanged()));
	connect(this->ui->numberOfChannelsInDataBox, SIGNAL(editingFinished()), this, SLOT(numberOfChannelsInDataChanged()));
	connect(this->ui->displayAsWavesButton, SIGNAL(clicked(bool)), this, SLOT(displayAsWavesButtonClicked()));
	connect(this->ui->displayAsWavesAndContinuousButton, SIGNAL(clicked(bool)), this, SLOT(displayAsWavesAndContinuousButtonClicked()));
	connect(this->ui->displayAsWavesButton, SIGNAL(clicked(bool)), this, SLOT(displayAsWavesButtonClicked()));
        connect(this->ui->twoWireAddressButton, SIGNAL(stateChanged(int)), this, SLOT(changeAddressing()));

	currentFilterIndex = 0;

	this->currentNumberOfChannelViews = 1;

        this->ui->numberOfChannelsInDataBox->setText(QString::number(DEFAULT_NUM_CHANNELS_IN_DATA));
        this->ui->numberOfChannelViewsBox->setText(QString::number(DEFAULT_NUM_CHANNEL_VIEWS));
        this->ui->synchChannelNumberBox->setText(QString::number(DEFAULT_SYNCH_CHANNEL));
#ifdef USES_TWO_WIRE_ADDRESSING
		this->ui->twoWireAddressButton->setChecked(true);
#else
		this->ui->twoWireAddressButton->setChecked(false);
#endif
}

RTVTHUDControllerView::~RTVTHUDControllerView()
{
    delete ui;
}

void RTVTHUDControllerView::changeEvent(QEvent *e)
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

void RTVTHUDControllerView::appendToDebugConsole(QString debugLine)
{
	this->ui->debugConsole->append(debugLine);
}

void RTVTHUDControllerView::filterSelectionChanged(int ind)
{
	if(ind == 2)
		emit signalToAddFilterToController();
	else if(ind == 0)
		emit signalNoFiltering();
	else if(ind > 3)
	{
		emit selectedFilterChanged(ind - 4);
		this->currentFilterIndex = ind;
	}
		
}

void RTVTHUDControllerView::numberOfChannelViewsChanged()
{
        int value = this->ui->numberOfChannelViewsBox->text().toInt();

	emit changeNumberOfChannelViews(value);
	this->currentNumberOfChannelViews = value;
}

void RTVTHUDControllerView::numberOfChannelsInDataChanged()
{
        int value = this->ui->numberOfChannelsInDataBox->text().toInt();

	emit changeNumberOfDataChannels(value);
	this->currentNumberOfDataChannels = value;
}

void RTVTHUDControllerView::addToFilterList(int ind, QString theName)
{
	this->ui->selectFilterComboBox->insertItem((ind+4), theName);
	//this->ui->selectFilterComboBox->setCurrentIndex(ind+4);
	this->currentFilterIndex = ind;
}

void RTVTHUDControllerView::dataLoadingStarted()
{
	this->ui->numberOfChannelsInDataBox->setDisabled(true);
	this->ui->numberOfChannelViewsBox->setDisabled(true);
	this->ui->synchChannelNumberBox->setDisabled(true);
	this->ui->displayAsWavesAndContinuousButton->setDisabled(true);
	this->ui->displayAsWavesButton->setDisabled(true);
        this->ui->twoWireAddressButton->setDisabled(true);
}

void RTVTHUDControllerView::dataLoadingStopped()
{
	this->ui->numberOfChannelsInDataBox->setEnabled(true);
	this->ui->numberOfChannelViewsBox->setEnabled(true);
	this->ui->synchChannelNumberBox->setEnabled(true);
	this->ui->displayAsWavesAndContinuousButton->setEnabled(true);
	this->ui->displayAsWavesButton->setEnabled(true);
        this->ui->twoWireAddressButton->setEnabled(true);
}

void RTVTHUDControllerView::displayAsWavesAndContinuousButtonClicked()
{
	emit changeChannelDisplayToWavesAndContinuous();
}

void RTVTHUDControllerView::displayAsWavesButtonClicked()
{
	emit changeChannelDisplayToWaves();
}

void RTVTHUDControllerView::changeAddressing()
{
	if(this->ui->numberOfChannelsInDataBox->text().toInt() >=32)
	{
		if(this->ui->twoWireAddressButton->checkState() == Qt::Checked)
			emit changeMainWindowAmplifierAddressing(2);
		else
		{
			QMessageBox msgBox;
			 msgBox.setText("You cannot use two-wire addressing with less than 32 channels going through the controller - only supported in RChip or later");
			 msgBox.setStandardButtons(QMessageBox::Ok);
			 msgBox.setDefaultButton(QMessageBox::Ok);
			 int ret = msgBox.exec();

			 this->ui->twoWireAddressButton->setChecked(true);
		}
	}
	else
	{
		if(this->ui->twoWireAddressButton->checkState() == Qt::Unchecked)
			emit changeMainWindowAmplifierAddressing(4);
	}
}
