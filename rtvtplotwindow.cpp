#include "rtvtplotwindow.h"
#include "ui_rtvtplotwindow.h"

// QWT
#include "External-Code/fftreal_wrapper.h"

RTVTPlotWindow::RTVTPlotWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RTVTPlotWindow)
{
    ui->setupUi(this);

    connect(ui->plotChannelListView, SIGNAL(clicked(QModelIndex)), this, SLOT(curveSelected(QModelIndex)));
    // Setup curves
    numberOfCurves = 10;
    startColorIndex = 0;
    channelListStringModel = new QStringListModel();
    channelListStringModel->setStringList(channelStringList);
    ui->plotChannelListView->setModel(channelListStringModel);

	// Setup the plot view
	ui->plotQwtView->setCanvasBackground(QColor(Qt::darkBlue));
	ui->plotQwtView->setTitle("Frequency Response of Amplifier");
    ui->plotQwtView->setTitle("Amplitude");
    ui->plotQwtView->setAxisTitle(QwtPlot::yLeft,"dBm");
    ui->plotQwtView->setAxisTitle(QwtPlot::xBottom,"Frequency (Hz)");

	// grid 
    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->enableXMin(true);
    grid->setMajPen(QPen(Qt::white, 0, Qt::DotLine));
    grid->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));
	grid->attach(ui->plotQwtView);

	ui->plotQwtView->setAxisMaxMajor(QwtPlot::xBottom, 6);
    ui->plotQwtView->setAxisMaxMinor(QwtPlot::xBottom, 10);
    ui->plotQwtView->setAxisScaleEngine(QwtPlot::xBottom, new QwtLog10ScaleEngine);

    //QwtPlotGrid *gridy = new QwtPlotGrid();
    //gridy->attach(ui->plotQwtView);


    /*QwtLog10ScaleEngine * log10SE = new QwtLog10ScaleEngine();
    double x1=0.0, x2=4.3, stepSize=0.1;

    log10SE->autoScale(100, x1, x2, stepSize);

	QwtLinearScaleEngine * yAxisEngine = new  QwtLinearScaleEngine();
	double y1=-100.0, y2 = 10.0, yStep = 10.0;

	yAxisEngine->autoScale(10, y1, y2, yStep);*/

    //ui->plotQwtView->setAxisScaleEngine(QwtPlot::xBottom,log10SE);
	//ui->plotQwtView->setAxisScaleEngine(QwtPlot::yLeft,yAxisEngine);

	//ui->plotQwtView->setAxis

    ui->plotQwtView->replot();

}

RTVTPlotWindow::~RTVTPlotWindow()
{
    delete ui;
}

void RTVTPlotWindow::curveSelected(QModelIndex mi)
{
    Q_UNUSED(mi);

    QModelIndexList selectionIndexList = ui->plotChannelListView->selectionModel()->selectedIndexes();

//    foreach(QwtPlotItem *theItem, ui->plotQwtView->itemList())
//        if(qobject_cast<QObject *>(theItem)->metaObject()->className() == "QwtPlotCurve")
//            qobject_cast<QwtPlotCurve *>(theItem)->detach();

    ui->plotQwtView->detachItems(QwtPlotItem::Rtti_PlotCurve, false);

    foreach(QModelIndex selectedIndex, selectionIndexList)
        curves.at(selectedIndex.row())->attach(ui->plotQwtView);

    ui->plotQwtView->replot();
}

void RTVTPlotWindow::addCurveWithDataFromChannel(QVector<qreal> frequency, QVector<qreal> amplitude, unsigned int channel)
{
    QwtPlotCurve *curve = new QwtPlotCurve(QString("Channel " + QString::number(channel)));
    curve->setPen(selectPen());
    curve->setSamples(frequency, amplitude);
	curve->setAxes(QwtPlot::xBottom, QwtPlot::yLeft);
    curves << curve;

    channelStringList << curve->title().text();
    channelListStringModel->setStringList(channelStringList);
}

QPen RTVTPlotWindow::selectPen()
{
    unsigned short colors[]= {3,2,7,13,8,14,9,15,10,16,11,17,12,18,5,4,6,19,0,1};

    // Set different colors...
    QColor Color((Qt::GlobalColor) colors[startColorIndex]);
    startColorIndex++;
    if(startColorIndex == sizeof(colors))
    {
        startColorIndex = 0;
    }
    return QPen(Color);
}

void RTVTPlotWindow::addCurvesToList()
{

//    QStringList list;
//    foreach(QwtPlotCurve)
//    list << "a" << "b" << "c";
//    model->setStringList(list);
}






