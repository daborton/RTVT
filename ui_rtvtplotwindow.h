/********************************************************************************
** Form generated from reading UI file 'rtvtplotwindow.ui'
**
** Created: Wed Feb 15 16:26:02 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RTVTPLOTWINDOW_H
#define UI_RTVTPLOTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_RTVTPlotWindow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QListView *plotChannelListView;
    QwtPlot *plotQwtView;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *ampInformationLabel;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *RTVTPlotWindow)
    {
        if (RTVTPlotWindow->objectName().isEmpty())
            RTVTPlotWindow->setObjectName(QString::fromUtf8("RTVTPlotWindow"));
        RTVTPlotWindow->resize(776, 592);
        verticalLayout = new QVBoxLayout(RTVTPlotWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        plotChannelListView = new QListView(RTVTPlotWindow);
        plotChannelListView->setObjectName(QString::fromUtf8("plotChannelListView"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(plotChannelListView->sizePolicy().hasHeightForWidth());
        plotChannelListView->setSizePolicy(sizePolicy);
        plotChannelListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        plotChannelListView->setSelectionMode(QAbstractItemView::MultiSelection);

        horizontalLayout->addWidget(plotChannelListView);

        plotQwtView = new QwtPlot(RTVTPlotWindow);
        plotQwtView->setObjectName(QString::fromUtf8("plotQwtView"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(plotQwtView->sizePolicy().hasHeightForWidth());
        plotQwtView->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(plotQwtView);


        verticalLayout->addLayout(horizontalLayout);

        groupBox = new QGroupBox(RTVTPlotWindow);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(label);

        ampInformationLabel = new QLabel(groupBox);
        ampInformationLabel->setObjectName(QString::fromUtf8("ampInformationLabel"));

        horizontalLayout_2->addWidget(ampInformationLabel);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(label_2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(groupBox);


        retranslateUi(RTVTPlotWindow);

        QMetaObject::connectSlotsByName(RTVTPlotWindow);
    } // setupUi

    void retranslateUi(QWidget *RTVTPlotWindow)
    {
        RTVTPlotWindow->setWindowTitle(QApplication::translate("RTVTPlotWindow", "RTVT Plot Window", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("RTVTPlotWindow", "System information", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("RTVTPlotWindow", "Amplifier information:", 0, QApplication::UnicodeUTF8));
        ampInformationLabel->setText(QApplication::translate("RTVTPlotWindow", "None", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("RTVTPlotWindow", "Window type:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("RTVTPlotWindow", "Hanning", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RTVTPlotWindow: public Ui_RTVTPlotWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RTVTPLOTWINDOW_H
