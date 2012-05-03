/********************************************************************************
** Form generated from reading UI file 'rtvthudwaveview.ui'
**
** Created: Wed Feb 15 16:26:02 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RTVTHUDWAVEVIEW_H
#define UI_RTVTHUDWAVEVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RTVTHUDWaveView
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *saveToNEVCheckbox;
    QSpacerItem *horizontalSpacer_6;
    QLabel *nevFileNameLabel;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *setNEVFileButton;
    QPushButton *saveNEVToggleButton;
    QSpacerItem *horizontalSpacer_8;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QTableView *triggeredWaveformDataTable;
    QHBoxLayout *horizontalLayout;
    QPushButton *addTriggerButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *removeTriggerButton;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *autoSetTriggersButton;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QLineEdit *rmsValueField;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *clearWaveformsButton;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *resetTriggersButton;
    QCheckBox *adjustAllThresholdsCheckBox;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSlider *waveCheckSlider;
    QLCDNumber *waveCheckNumberLCD;

    void setupUi(QWidget *RTVTHUDWaveView)
    {
        if (RTVTHUDWaveView->objectName().isEmpty())
            RTVTHUDWaveView->setObjectName(QString::fromUtf8("RTVTHUDWaveView"));
        RTVTHUDWaveView->resize(328, 567);
        verticalLayout = new QVBoxLayout(RTVTHUDWaveView);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 9, 0, 0);
        groupBox_3 = new QGroupBox(RTVTHUDWaveView);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setContentsMargins(6, 6, 6, 6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        saveToNEVCheckbox = new QCheckBox(groupBox_3);
        saveToNEVCheckbox->setObjectName(QString::fromUtf8("saveToNEVCheckbox"));

        horizontalLayout_6->addWidget(saveToNEVCheckbox);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        nevFileNameLabel = new QLabel(groupBox_3);
        nevFileNameLabel->setObjectName(QString::fromUtf8("nevFileNameLabel"));

        horizontalLayout_6->addWidget(nevFileNameLabel);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        setNEVFileButton = new QPushButton(groupBox_3);
        setNEVFileButton->setObjectName(QString::fromUtf8("setNEVFileButton"));

        horizontalLayout_8->addWidget(setNEVFileButton);

        saveNEVToggleButton = new QPushButton(groupBox_3);
        saveNEVToggleButton->setObjectName(QString::fromUtf8("saveNEVToggleButton"));
        saveNEVToggleButton->setCheckable(true);
        saveNEVToggleButton->setAutoDefault(false);
        saveNEVToggleButton->setDefault(false);
        saveNEVToggleButton->setFlat(false);

        horizontalLayout_8->addWidget(saveNEVToggleButton);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);


        verticalLayout_4->addLayout(horizontalLayout_8);


        verticalLayout->addWidget(groupBox_3);

        groupBox = new QGroupBox(RTVTHUDWaveView);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setContentsMargins(6, 6, 6, 6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        triggeredWaveformDataTable = new QTableView(groupBox);
        triggeredWaveformDataTable->setObjectName(QString::fromUtf8("triggeredWaveformDataTable"));
        QFont font;
        font.setFamily(QString::fromUtf8("Bell MT"));
        font.setPointSize(11);
        triggeredWaveformDataTable->setFont(font);
        triggeredWaveformDataTable->horizontalHeader()->setCascadingSectionResizes(true);
        triggeredWaveformDataTable->horizontalHeader()->setStretchLastSection(true);
        triggeredWaveformDataTable->verticalHeader()->setCascadingSectionResizes(true);

        verticalLayout_2->addWidget(triggeredWaveformDataTable);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 2, -1, -1);
        addTriggerButton = new QPushButton(groupBox);
        addTriggerButton->setObjectName(QString::fromUtf8("addTriggerButton"));

        horizontalLayout->addWidget(addTriggerButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        removeTriggerButton = new QPushButton(groupBox);
        removeTriggerButton->setObjectName(QString::fromUtf8("removeTriggerButton"));

        horizontalLayout->addWidget(removeTriggerButton);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        autoSetTriggersButton = new QPushButton(groupBox);
        autoSetTriggersButton->setObjectName(QString::fromUtf8("autoSetTriggersButton"));

        horizontalLayout_3->addWidget(autoSetTriggersButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        rmsValueField = new QLineEdit(groupBox);
        rmsValueField->setObjectName(QString::fromUtf8("rmsValueField"));
        rmsValueField->setMinimumSize(QSize(50, 0));
        rmsValueField->setMaximumSize(QSize(50, 16777215));
        rmsValueField->setBaseSize(QSize(50, 0));

        horizontalLayout_3->addWidget(rmsValueField);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        clearWaveformsButton = new QPushButton(groupBox);
        clearWaveformsButton->setObjectName(QString::fromUtf8("clearWaveformsButton"));

        horizontalLayout_5->addWidget(clearWaveformsButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        resetTriggersButton = new QPushButton(groupBox);
        resetTriggersButton->setObjectName(QString::fromUtf8("resetTriggersButton"));

        horizontalLayout_5->addWidget(resetTriggersButton);


        verticalLayout_2->addLayout(horizontalLayout_5);

        adjustAllThresholdsCheckBox = new QCheckBox(groupBox);
        adjustAllThresholdsCheckBox->setObjectName(QString::fromUtf8("adjustAllThresholdsCheckBox"));

        verticalLayout_2->addWidget(adjustAllThresholdsCheckBox);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setContentsMargins(6, 6, 6, 6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        waveCheckSlider = new QSlider(groupBox_2);
        waveCheckSlider->setObjectName(QString::fromUtf8("waveCheckSlider"));
        waveCheckSlider->setMaximum(100);
        waveCheckSlider->setValue(20);
        waveCheckSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(waveCheckSlider);

        waveCheckNumberLCD = new QLCDNumber(groupBox_2);
        waveCheckNumberLCD->setObjectName(QString::fromUtf8("waveCheckNumberLCD"));
        waveCheckNumberLCD->setNumDigits(3);
        waveCheckNumberLCD->setProperty("value", QVariant(20));
        waveCheckNumberLCD->setProperty("intValue", QVariant(20));

        horizontalLayout_2->addWidget(waveCheckNumberLCD);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addWidget(groupBox_2);


        verticalLayout->addWidget(groupBox);


        retranslateUi(RTVTHUDWaveView);
        QObject::connect(saveToNEVCheckbox, SIGNAL(clicked(bool)), nevFileNameLabel, SLOT(setEnabled(bool)));
        QObject::connect(saveToNEVCheckbox, SIGNAL(clicked(bool)), setNEVFileButton, SLOT(setEnabled(bool)));
        QObject::connect(saveToNEVCheckbox, SIGNAL(clicked(bool)), saveNEVToggleButton, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(RTVTHUDWaveView);
    } // setupUi

    void retranslateUi(QWidget *RTVTHUDWaveView)
    {
        RTVTHUDWaveView->setWindowTitle(QApplication::translate("RTVTHUDWaveView", "RTVT Wave Viewer Controls", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("RTVTHUDWaveView", "Waveform Data Collection", 0, QApplication::UnicodeUTF8));
        saveToNEVCheckbox->setText(QApplication::translate("RTVTHUDWaveView", "Save to NEV", 0, QApplication::UnicodeUTF8));
        nevFileNameLabel->setText(QApplication::translate("RTVTHUDWaveView", "testNEV.nev", 0, QApplication::UnicodeUTF8));
        setNEVFileButton->setText(QApplication::translate("RTVTHUDWaveView", "Set location", 0, QApplication::UnicodeUTF8));
        saveNEVToggleButton->setText(QApplication::translate("RTVTHUDWaveView", "Turn Saving ON", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("RTVTHUDWaveView", "Threshold and triggered waveform data table", 0, QApplication::UnicodeUTF8));
        addTriggerButton->setText(QApplication::translate("RTVTHUDWaveView", "Add Trigger", 0, QApplication::UnicodeUTF8));
        removeTriggerButton->setText(QApplication::translate("RTVTHUDWaveView", "Remove Trigger", 0, QApplication::UnicodeUTF8));
        autoSetTriggersButton->setText(QApplication::translate("RTVTHUDWaveView", "Automatically set triggers", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("RTVTHUDWaveView", "RMS:", 0, QApplication::UnicodeUTF8));
        clearWaveformsButton->setText(QApplication::translate("RTVTHUDWaveView", "Clear Waveforms", 0, QApplication::UnicodeUTF8));
        resetTriggersButton->setText(QApplication::translate("RTVTHUDWaveView", "Reset Triggers", 0, QApplication::UnicodeUTF8));
        adjustAllThresholdsCheckBox->setText(QApplication::translate("RTVTHUDWaveView", "Adjust thresholds with current channel", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("RTVTHUDWaveView", "Wave data processing settings", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("RTVTHUDWaveView", "Wave check length", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RTVTHUDWaveView: public Ui_RTVTHUDWaveView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RTVTHUDWAVEVIEW_H
