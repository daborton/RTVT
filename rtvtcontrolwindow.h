#ifndef RTVTCONTROLWINDOW_H
#define RTVTCONTROLWINDOW_H

#include <QMainWindow>
#include "rtvtglobaldefinitions.h"
#include "Filtering/FirKernels.h"
#include "rtvtmainwindow.h"

#ifdef USE_QWT_PLOT
#include "rtvtplotwindow.h"
#include "External-Code/bodeplot/bode_mainwindow.h"
#endif

#ifdef USE_HS_USB
#include "cyapi.h"
#include "cpshsusbhardwareabstractionlayer.h"
#endif

namespace Ui {
    class RTVTControlWindow;
}

class RTVTControlWindow : public QMainWindow {
    Q_OBJECT
public:
    RTVTControlWindow(QWidget *parent = 0);
    ~RTVTControlWindow();

	void Initialize(void);

	RTVTMainWindow	*rtvtController; // RTVTMainWindow is now a controller object for RTVT subsystem
	bool halConnected;
	bool saveToDisk;
	QString saveToDiskPath;

	int	countInSeconds;
	QTimer *recursiveSaveTimer;
	QTimer *countdownTimer;

public slots:
	void closeAndExitApplication();
	void openFilterDataFile();
    void setSavePath();
    void toggleHUDVisibility();
    void toggleRTVTChannelArrayVisibility();
    void reloadStyleSheets();
    void setupHSUSB();
    void openRTVTArrayPanel();
	void setUsesUSB(bool state);
	void setUsesFile(bool state);
	void rtvtOpenExistingData();
	void appendToStatusField(QString);
        void tellMainWindowToPlay();
        void runNoiseSpectrumTest();
		void stopAndRestartRecursiveRecordings();
		void updateCountdownTimerField();
		void stopStartClicked();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::RTVTControlWindow *ui;
};

#endif // RTVTCONTROLWINDOW_H
