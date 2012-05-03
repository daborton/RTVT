/********************************************************************************
** Form generated from reading UI file 'rtvthudcontrollerview.ui'
**
** Created: Wed Feb 15 16:26:02 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RTVTHUDCONTROLLERVIEW_H
#define UI_RTVTHUDCONTROLLERVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RTVTHUDControllerView
{
public:
    QGridLayout *gridLayout;
    QGroupBox *channelSetupGroupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *numberOfChannelViewsBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *numberOfChannelsInDataBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *synchChannelNumberBox;
    QRadioButton *displayAsWavesButton;
    QRadioButton *displayAsWavesAndContinuousButton;
    QCheckBox *twoWireAddressButton;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *debugConsole;
    QGroupBox *filteringGroupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *selectFilterComboBox;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *RTVTHUDControllerView)
    {
        if (RTVTHUDControllerView->objectName().isEmpty())
            RTVTHUDControllerView->setObjectName(QString::fromUtf8("RTVTHUDControllerView"));
        RTVTHUDControllerView->resize(502, 419);
        gridLayout = new QGridLayout(RTVTHUDControllerView);
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 9, 0, 0);
        channelSetupGroupBox = new QGroupBox(RTVTHUDControllerView);
        channelSetupGroupBox->setObjectName(QString::fromUtf8("channelSetupGroupBox"));
        verticalLayout_2 = new QVBoxLayout(channelSetupGroupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(channelSetupGroupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(80, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        numberOfChannelViewsBox = new QLineEdit(channelSetupGroupBox);
        numberOfChannelViewsBox->setObjectName(QString::fromUtf8("numberOfChannelViewsBox"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(numberOfChannelViewsBox->sizePolicy().hasHeightForWidth());
        numberOfChannelViewsBox->setSizePolicy(sizePolicy);
        numberOfChannelViewsBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(numberOfChannelViewsBox);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(channelSetupGroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        numberOfChannelsInDataBox = new QLineEdit(channelSetupGroupBox);
        numberOfChannelsInDataBox->setObjectName(QString::fromUtf8("numberOfChannelsInDataBox"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(numberOfChannelsInDataBox->sizePolicy().hasHeightForWidth());
        numberOfChannelsInDataBox->setSizePolicy(sizePolicy1);
        numberOfChannelsInDataBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(numberOfChannelsInDataBox);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(channelSetupGroupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        synchChannelNumberBox = new QLineEdit(channelSetupGroupBox);
        synchChannelNumberBox->setObjectName(QString::fromUtf8("synchChannelNumberBox"));
        sizePolicy1.setHeightForWidth(synchChannelNumberBox->sizePolicy().hasHeightForWidth());
        synchChannelNumberBox->setSizePolicy(sizePolicy1);
        synchChannelNumberBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(synchChannelNumberBox);


        verticalLayout_2->addLayout(horizontalLayout_4);

        displayAsWavesButton = new QRadioButton(channelSetupGroupBox);
        displayAsWavesButton->setObjectName(QString::fromUtf8("displayAsWavesButton"));
        displayAsWavesButton->setChecked(true);

        verticalLayout_2->addWidget(displayAsWavesButton);

        displayAsWavesAndContinuousButton = new QRadioButton(channelSetupGroupBox);
        displayAsWavesAndContinuousButton->setObjectName(QString::fromUtf8("displayAsWavesAndContinuousButton"));

        verticalLayout_2->addWidget(displayAsWavesAndContinuousButton);

        twoWireAddressButton = new QCheckBox(channelSetupGroupBox);
        twoWireAddressButton->setObjectName(QString::fromUtf8("twoWireAddressButton"));
        twoWireAddressButton->setChecked(true);

        verticalLayout_2->addWidget(twoWireAddressButton);


        gridLayout->addWidget(channelSetupGroupBox, 0, 0, 1, 1);

        groupBox = new QGroupBox(RTVTHUDControllerView);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        debugConsole = new QTextEdit(groupBox);
        debugConsole->setObjectName(QString::fromUtf8("debugConsole"));

        verticalLayout_3->addWidget(debugConsole);


        gridLayout->addWidget(groupBox, 2, 0, 1, 1);

        filteringGroupBox = new QGroupBox(RTVTHUDControllerView);
        filteringGroupBox->setObjectName(QString::fromUtf8("filteringGroupBox"));
        verticalLayout = new QVBoxLayout(filteringGroupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(filteringGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        selectFilterComboBox = new QComboBox(filteringGroupBox);
        selectFilterComboBox->setObjectName(QString::fromUtf8("selectFilterComboBox"));
        sizePolicy1.setHeightForWidth(selectFilterComboBox->sizePolicy().hasHeightForWidth());
        selectFilterComboBox->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(selectFilterComboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addWidget(filteringGroupBox, 1, 0, 1, 1);


        retranslateUi(RTVTHUDControllerView);

        QMetaObject::connectSlotsByName(RTVTHUDControllerView);
    } // setupUi

    void retranslateUi(QWidget *RTVTHUDControllerView)
    {
        RTVTHUDControllerView->setWindowTitle(QApplication::translate("RTVTHUDControllerView", "RTVT Controller HUD", 0, QApplication::UnicodeUTF8));
        channelSetupGroupBox->setTitle(QApplication::translate("RTVTHUDControllerView", "Channel Setup", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("RTVTHUDControllerView", "Number of Channel Views", 0, QApplication::UnicodeUTF8));
        numberOfChannelViewsBox->setText(QApplication::translate("RTVTHUDControllerView", "100", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("RTVTHUDControllerView", "Number of Channels in Data", 0, QApplication::UnicodeUTF8));
        numberOfChannelsInDataBox->setText(QApplication::translate("RTVTHUDControllerView", "102", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("RTVTHUDControllerView", "Synch Channel Number", 0, QApplication::UnicodeUTF8));
        synchChannelNumberBox->setText(QApplication::translate("RTVTHUDControllerView", "102", 0, QApplication::UnicodeUTF8));
        displayAsWavesButton->setText(QApplication::translate("RTVTHUDControllerView", "Display views as wave array", 0, QApplication::UnicodeUTF8));
        displayAsWavesAndContinuousButton->setText(QApplication::translate("RTVTHUDControllerView", "Display views as waves with continuous data", 0, QApplication::UnicodeUTF8));
        twoWireAddressButton->setText(QApplication::translate("RTVTHUDControllerView", "Two-wire addressing", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("RTVTHUDControllerView", "Console Output", 0, QApplication::UnicodeUTF8));
        filteringGroupBox->setTitle(QApplication::translate("RTVTHUDControllerView", "Filtering", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("RTVTHUDControllerView", "Select Filter:", 0, QApplication::UnicodeUTF8));
        selectFilterComboBox->clear();
        selectFilterComboBox->insertItems(0, QStringList()
         << QApplication::translate("RTVTHUDControllerView", "No Filter", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("RTVTHUDControllerView", "Import a Filter...", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class RTVTHUDControllerView: public Ui_RTVTHUDControllerView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RTVTHUDCONTROLLERVIEW_H
