#ifndef RTVTPLOTWINDOW_H
#define RTVTPLOTWINDOW_H

#include <QWidget>
#include <QStringListModel>

// QWT for noise (and other) plots
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_scale_engine.h>

// QWT Utility functions
#include "External-Code/fftreal_wrapper.h"
#include "External-Code/utils.h"

namespace Ui {
    class RTVTPlotWindow;
}

class RTVTPlotWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RTVTPlotWindow(QWidget *parent = 0);
    ~RTVTPlotWindow();
    void addCurveWithDataFromChannel(QVector<qreal> frequency, QVector<qreal> amplitude, unsigned int channel);
    void addCurvesToList();
    QPen selectPen();

    QVector<QwtPlotCurve*>      curves;
    QStringListModel            *channelListStringModel;
    QStringList                 channelStringList;

    int                         startColorIndex;


    unsigned int            numberOfCurves;

public slots:
    void curveSelected(QModelIndex);

private:
    Ui::RTVTPlotWindow *ui;
};

#endif // RTVTPLOTWINDOW_H
