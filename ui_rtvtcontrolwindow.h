/********************************************************************************
** Form generated from reading UI file 'rtvtcontrolwindow.ui'
**
** Created: Wed Feb 15 16:26:02 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RTVTCONTROLWINDOW_H
#define UI_RTVTCONTROLWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RTVTControlWindow
{
public:
    QAction *actionExit;
    QAction *actionShow_array_window;
    QAction *actionShow_HUD;
    QAction *actionLoad_data_from_file;
    QAction *actionLoad_coefficients_file;
    QAction *actionSave_SNIFFR_to_dat;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *playWithoutRecordingButton;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label;
    QSpacerItem *horizontalSpacer_9;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_9;
    QCheckBox *recursiveSaveCheckbox;
    QSpacerItem *horizontalSpacer_8;
    QSpinBox *recursiveSaveSpinbox;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_7;
    QLabel *countdownText;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_4;
    QLabel *samplesToCollectLabel;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLineEdit *numAveragesText;
    QLabel *label_5;
    QLineEdit *numberOfChannelsToViewField;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *runNoiseTestButton;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QLabel *dataReadyIndicator;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout;
    QRadioButton *usesHSUSBRadioButton;
    QLabel *hsUSBConnectedLabel;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *usesDataFromFileRadioButton;
    QLabel *fromDataFileLabel;
    QGroupBox *configurationSettingsBox;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *saveDataToDiskCheckBox;
    QPushButton *setSavePathButton;
    QLabel *saveDataPathLabel;
    QSpacerItem *horizontalSpacer_5;
    QTextBrowser *statusHistoryField;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuViews;
    QMenu *menuData;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *RTVTControlWindow)
    {
        if (RTVTControlWindow->objectName().isEmpty())
            RTVTControlWindow->setObjectName(QString::fromUtf8("RTVTControlWindow"));
        RTVTControlWindow->resize(383, 533);
        actionExit = new QAction(RTVTControlWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionShow_array_window = new QAction(RTVTControlWindow);
        actionShow_array_window->setObjectName(QString::fromUtf8("actionShow_array_window"));
        actionShow_HUD = new QAction(RTVTControlWindow);
        actionShow_HUD->setObjectName(QString::fromUtf8("actionShow_HUD"));
        actionShow_HUD->setEnabled(true);
        actionLoad_data_from_file = new QAction(RTVTControlWindow);
        actionLoad_data_from_file->setObjectName(QString::fromUtf8("actionLoad_data_from_file"));
        actionLoad_coefficients_file = new QAction(RTVTControlWindow);
        actionLoad_coefficients_file->setObjectName(QString::fromUtf8("actionLoad_coefficients_file"));
        actionSave_SNIFFR_to_dat = new QAction(RTVTControlWindow);
        actionSave_SNIFFR_to_dat->setObjectName(QString::fromUtf8("actionSave_SNIFFR_to_dat"));
        centralwidget = new QWidget(RTVTControlWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 0);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 6, 12, 6);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        playWithoutRecordingButton = new QPushButton(groupBox);
        playWithoutRecordingButton->setObjectName(QString::fromUtf8("playWithoutRecordingButton"));

        horizontalLayout_3->addWidget(playWithoutRecordingButton);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);


        verticalLayout_2->addLayout(horizontalLayout_3);

        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_4 = new QVBoxLayout(groupBox_4);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        recursiveSaveCheckbox = new QCheckBox(groupBox_4);
        recursiveSaveCheckbox->setObjectName(QString::fromUtf8("recursiveSaveCheckbox"));

        horizontalLayout_9->addWidget(recursiveSaveCheckbox);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_8);

        recursiveSaveSpinbox = new QSpinBox(groupBox_4);
        recursiveSaveSpinbox->setObjectName(QString::fromUtf8("recursiveSaveSpinbox"));

        horizontalLayout_9->addWidget(recursiveSaveSpinbox);


        verticalLayout_4->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_8->addWidget(label_6);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);

        countdownText = new QLabel(groupBox_4);
        countdownText->setObjectName(QString::fromUtf8("countdownText"));
        countdownText->setMinimumSize(QSize(50, 0));
        countdownText->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_8->addWidget(countdownText);


        verticalLayout_4->addLayout(horizontalLayout_8);


        verticalLayout_2->addWidget(groupBox_4);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        horizontalLayout_7->addWidget(label_4);

        samplesToCollectLabel = new QLabel(groupBox_3);
        samplesToCollectLabel->setObjectName(QString::fromUtf8("samplesToCollectLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(samplesToCollectLabel->sizePolicy().hasHeightForWidth());
        samplesToCollectLabel->setSizePolicy(sizePolicy1);
        samplesToCollectLabel->setMinimumSize(QSize(50, 0));
        samplesToCollectLabel->setMaximumSize(QSize(16777215, 100));
        samplesToCollectLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(samplesToCollectLabel);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(label_3);

        numAveragesText = new QLineEdit(groupBox_3);
        numAveragesText->setObjectName(QString::fromUtf8("numAveragesText"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(numAveragesText->sizePolicy().hasHeightForWidth());
        numAveragesText->setSizePolicy(sizePolicy3);
        numAveragesText->setMaximumSize(QSize(20, 16777215));
        numAveragesText->setMaxLength(10);
        numAveragesText->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(numAveragesText);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(label_5);

        numberOfChannelsToViewField = new QLineEdit(groupBox_3);
        numberOfChannelsToViewField->setObjectName(QString::fromUtf8("numberOfChannelsToViewField"));
        sizePolicy3.setHeightForWidth(numberOfChannelsToViewField->sizePolicy().hasHeightForWidth());
        numberOfChannelsToViewField->setSizePolicy(sizePolicy3);
        numberOfChannelsToViewField->setMaximumSize(QSize(20, 16777215));
        numberOfChannelsToViewField->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(numberOfChannelsToViewField);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        runNoiseTestButton = new QPushButton(groupBox_3);
        runNoiseTestButton->setObjectName(QString::fromUtf8("runNoiseTestButton"));

        horizontalLayout_6->addWidget(runNoiseTestButton);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_6->addWidget(label_2);

        dataReadyIndicator = new QLabel(groupBox_3);
        dataReadyIndicator->setObjectName(QString::fromUtf8("dataReadyIndicator"));
        sizePolicy3.setHeightForWidth(dataReadyIndicator->sizePolicy().hasHeightForWidth());
        dataReadyIndicator->setSizePolicy(sizePolicy3);
        dataReadyIndicator->setMinimumSize(QSize(10, 10));
        dataReadyIndicator->setMaximumSize(QSize(10, 10));
        dataReadyIndicator->setAutoFillBackground(false);
        dataReadyIndicator->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));
        dataReadyIndicator->setTextFormat(Qt::PlainText);
        dataReadyIndicator->setScaledContents(true);
        dataReadyIndicator->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        horizontalLayout_6->addWidget(dataReadyIndicator);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_6);


        verticalLayout_2->addWidget(groupBox_3);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_8 = new QVBoxLayout(groupBox_2);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        usesHSUSBRadioButton = new QRadioButton(groupBox_2);
        usesHSUSBRadioButton->setObjectName(QString::fromUtf8("usesHSUSBRadioButton"));
        usesHSUSBRadioButton->setChecked(false);

        horizontalLayout->addWidget(usesHSUSBRadioButton);

        hsUSBConnectedLabel = new QLabel(groupBox_2);
        hsUSBConnectedLabel->setObjectName(QString::fromUtf8("hsUSBConnectedLabel"));
        hsUSBConnectedLabel->setLayoutDirection(Qt::RightToLeft);
        hsUSBConnectedLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(hsUSBConnectedLabel);


        verticalLayout_8->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        usesDataFromFileRadioButton = new QRadioButton(groupBox_2);
        usesDataFromFileRadioButton->setObjectName(QString::fromUtf8("usesDataFromFileRadioButton"));

        horizontalLayout_2->addWidget(usesDataFromFileRadioButton);

        fromDataFileLabel = new QLabel(groupBox_2);
        fromDataFileLabel->setObjectName(QString::fromUtf8("fromDataFileLabel"));
        fromDataFileLabel->setLayoutDirection(Qt::RightToLeft);
        fromDataFileLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(fromDataFileLabel);


        verticalLayout_8->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(groupBox_2);

        configurationSettingsBox = new QGroupBox(centralwidget);
        configurationSettingsBox->setObjectName(QString::fromUtf8("configurationSettingsBox"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(configurationSettingsBox->sizePolicy().hasHeightForWidth());
        configurationSettingsBox->setSizePolicy(sizePolicy4);
        verticalLayout_6 = new QVBoxLayout(configurationSettingsBox);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        saveDataToDiskCheckBox = new QCheckBox(configurationSettingsBox);
        saveDataToDiskCheckBox->setObjectName(QString::fromUtf8("saveDataToDiskCheckBox"));

        horizontalLayout_4->addWidget(saveDataToDiskCheckBox);

        setSavePathButton = new QPushButton(configurationSettingsBox);
        setSavePathButton->setObjectName(QString::fromUtf8("setSavePathButton"));

        horizontalLayout_4->addWidget(setSavePathButton);

        saveDataPathLabel = new QLabel(configurationSettingsBox);
        saveDataPathLabel->setObjectName(QString::fromUtf8("saveDataPathLabel"));
        saveDataPathLabel->setText(QString::fromUtf8("C:/Users/Public/test.dat"));
        saveDataPathLabel->setTextFormat(Qt::PlainText);
        saveDataPathLabel->setScaledContents(false);
        saveDataPathLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        horizontalLayout_4->addWidget(saveDataPathLabel);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        verticalLayout_6->addLayout(horizontalLayout_4);

        statusHistoryField = new QTextBrowser(configurationSettingsBox);
        statusHistoryField->setObjectName(QString::fromUtf8("statusHistoryField"));
        statusHistoryField->setFrameShape(QFrame::Box);
        statusHistoryField->setFrameShadow(QFrame::Plain);
        statusHistoryField->setReadOnly(false);

        verticalLayout_6->addWidget(statusHistoryField);


        verticalLayout->addWidget(configurationSettingsBox);

        RTVTControlWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RTVTControlWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 383, 18));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuViews = new QMenu(menubar);
        menuViews->setObjectName(QString::fromUtf8("menuViews"));
        menuData = new QMenu(menubar);
        menuData->setObjectName(QString::fromUtf8("menuData"));
        RTVTControlWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(RTVTControlWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        RTVTControlWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuData->menuAction());
        menubar->addAction(menuViews->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuViews->addAction(actionShow_array_window);
        menuViews->addAction(actionShow_HUD);
        menuViews->addSeparator();
        menuData->addAction(actionLoad_coefficients_file);
        menuData->addAction(actionLoad_data_from_file);
        menuData->addSeparator();
        menuData->addAction(actionSave_SNIFFR_to_dat);

        retranslateUi(RTVTControlWindow);

        QMetaObject::connectSlotsByName(RTVTControlWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RTVTControlWindow)
    {
        RTVTControlWindow->setWindowTitle(QApplication::translate("RTVTControlWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("RTVTControlWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionExit->setShortcut(QApplication::translate("RTVTControlWindow", "Alt+Shift+Q", 0, QApplication::UnicodeUTF8));
        actionShow_array_window->setText(QApplication::translate("RTVTControlWindow", "Show array window", 0, QApplication::UnicodeUTF8));
        actionShow_array_window->setShortcut(QApplication::translate("RTVTControlWindow", "Alt+Shift+A", 0, QApplication::UnicodeUTF8));
        actionShow_HUD->setText(QApplication::translate("RTVTControlWindow", "Show HUD", 0, QApplication::UnicodeUTF8));
        actionShow_HUD->setShortcut(QApplication::translate("RTVTControlWindow", "Alt+Shift+H", 0, QApplication::UnicodeUTF8));
        actionLoad_data_from_file->setText(QApplication::translate("RTVTControlWindow", "Load data from file", 0, QApplication::UnicodeUTF8));
        actionLoad_data_from_file->setShortcut(QApplication::translate("RTVTControlWindow", "Alt+Shift+L", 0, QApplication::UnicodeUTF8));
        actionLoad_coefficients_file->setText(QApplication::translate("RTVTControlWindow", "Load coefficients file", 0, QApplication::UnicodeUTF8));
        actionLoad_coefficients_file->setShortcut(QApplication::translate("RTVTControlWindow", "Alt+Shift+C", 0, QApplication::UnicodeUTF8));
        actionSave_SNIFFR_to_dat->setText(QApplication::translate("RTVTControlWindow", "Save SNIFFR to dat", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("RTVTControlWindow", "Playback Management", 0, QApplication::UnicodeUTF8));
        playWithoutRecordingButton->setText(QApplication::translate("RTVTControlWindow", "Start playback", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("RTVTControlWindow", "Click to start visualizing data from file or USB", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("RTVTControlWindow", "GroupBox", 0, QApplication::UnicodeUTF8));
        recursiveSaveCheckbox->setText(QApplication::translate("RTVTControlWindow", "Save data and restart every x minutes", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("RTVTControlWindow", "Seconds until next save", 0, QApplication::UnicodeUTF8));
        countdownText->setText(QApplication::translate("RTVTControlWindow", "0", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("RTVTControlWindow", "Noise calculation", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("RTVTControlWindow", "Samples to collect:", 0, QApplication::UnicodeUTF8));
        samplesToCollectLabel->setText(QApplication::translate("RTVTControlWindow", "Value", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("RTVTControlWindow", "Number of averages:", 0, QApplication::UnicodeUTF8));
        numAveragesText->setText(QApplication::translate("RTVTControlWindow", "4", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("RTVTControlWindow", "Number of channels:", 0, QApplication::UnicodeUTF8));
        numberOfChannelsToViewField->setText(QApplication::translate("RTVTControlWindow", "16", 0, QApplication::UnicodeUTF8));
        runNoiseTestButton->setText(QApplication::translate("RTVTControlWindow", "Run noise test", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("RTVTControlWindow", "Data is ready indicator:", 0, QApplication::UnicodeUTF8));
        dataReadyIndicator->setText(QString());
        groupBox_2->setTitle(QApplication::translate("RTVTControlWindow", "Data Source Configuration", 0, QApplication::UnicodeUTF8));
        usesHSUSBRadioButton->setText(QApplication::translate("RTVTControlWindow", "From High-Speed USB)", 0, QApplication::UnicodeUTF8));
        hsUSBConnectedLabel->setText(QApplication::translate("RTVTControlWindow", "Not connected", 0, QApplication::UnicodeUTF8));
        usesDataFromFileRadioButton->setText(QApplication::translate("RTVTControlWindow", "From file (SNIFR)", 0, QApplication::UnicodeUTF8));
        fromDataFileLabel->setText(QApplication::translate("RTVTControlWindow", "No file selected", 0, QApplication::UnicodeUTF8));
        configurationSettingsBox->setTitle(QApplication::translate("RTVTControlWindow", "File Storage Settings", 0, QApplication::UnicodeUTF8));
        saveDataToDiskCheckBox->setText(QApplication::translate("RTVTControlWindow", "Save Data to Disk", 0, QApplication::UnicodeUTF8));
        setSavePathButton->setText(QApplication::translate("RTVTControlWindow", "Choose Save Path", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("RTVTControlWindow", "File", 0, QApplication::UnicodeUTF8));
        menuViews->setTitle(QApplication::translate("RTVTControlWindow", "Views", 0, QApplication::UnicodeUTF8));
        menuData->setTitle(QApplication::translate("RTVTControlWindow", "Data", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RTVTControlWindow: public Ui_RTVTControlWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RTVTCONTROLWINDOW_H
