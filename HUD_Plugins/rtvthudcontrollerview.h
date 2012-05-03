#ifndef RTVTHUDCONTROLLERVIEW_H
#define RTVTHUDCONTROLLERVIEW_H

#include <QWidget>
#include <QMessageBox>
#include "../rtvtglobaldefinitions.h"

namespace Ui {
    class RTVTHUDControllerView;
}

class RTVTHUDControllerView : public QWidget {
    Q_OBJECT
public:
    RTVTHUDControllerView(QWidget *parent = 0);
    ~RTVTHUDControllerView();
	void appendToDebugConsole(QString debugLine);
	void addToFilterList(int ind, QString theName);
	void dataLoadingStarted();
	void dataLoadingStopped();
	
	int currentFilterIndex;
	int currentNumberOfChannelViews;
	int currentNumberOfDataChannels;
	
	public slots:
	void filterSelectionChanged(int ind);
	void numberOfChannelViewsChanged();
	void numberOfChannelsInDataChanged();
	void displayAsWavesAndContinuousButtonClicked();
	void displayAsWavesButtonClicked();
        void changeAddressing();
	
signals:
	void signalToAddFilterToController();
	void selectedFilterChanged(int);
	void changeNumberOfChannelViews(int);
	void changeNumberOfDataChannels(int);
	void signalNoFiltering();
	void changeChannelDisplayToWavesAndContinuous();
	void changeChannelDisplayToWaves();
        void changeMainWindowAmplifierAddressing(int numWire);
	
protected:
    void changeEvent(QEvent *e);

private:
    Ui::RTVTHUDControllerView *ui;
};

#endif // RTVTHUDCONTROLLERVIEW_H
