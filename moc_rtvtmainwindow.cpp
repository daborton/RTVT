/****************************************************************************
** Meta object code from reading C++ file 'rtvtmainwindow.h'
**
** Created: Wed Feb 15 16:26:37 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "rtvtmainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rtvtmainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RTVTMainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      37,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   15,   41,   15, 0x0a,
      68,   15,   15,   15, 0x0a,
      94,   15,   15,   15, 0x0a,
     122,   15,   15,   15, 0x0a,
     150,   15,   15,   15, 0x0a,
     176,   15,   15,   15, 0x0a,
     202,   15,   15,   15, 0x0a,
     230,   15,   15,   15, 0x0a,
     256,   15,   15,   15, 0x0a,
     274,   15,   15,   15, 0x0a,
     300,  292,   15,   15, 0x0a,
     326,  292,   15,   15, 0x0a,
     362,   15,   15,   15, 0x0a,
     375,   15,   15,   15, 0x0a,
     396,   15,   15,   15, 0x0a,
     445,  438,   15,   15, 0x0a,
     477,  470,   15,   15, 0x0a,
     499,   15,   15,   15, 0x0a,
     526,   15,   15,   15, 0x0a,
     567,  552,   15,   15, 0x0a,
     602,  596,   15,   15, 0x0a,
     638,   15,   15,   15, 0x0a,
     660,   15,   15,   15, 0x0a,
     685,   15,   15,   15, 0x0a,
     709,  705,   15,   15, 0x0a,
     735,   15,   15,   15, 0x0a,
     755,   15,   15,   15, 0x0a,
     798,  786,   15,   15, 0x0a,
     846,  830,   15,   15, 0x0a,
     878,   15,   15,   15, 0x0a,
     902,  896,   15,   15, 0x0a,
     926,   15,   15,   15, 0x0a,
     969,   15,   15,   15, 0x0a,
    1013,  999,   15,   15, 0x0a,
    1046, 1038,   15,   15, 0x0a,
    1073, 1067,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RTVTMainWindow[] = {
    "RTVTMainWindow\0\0appendToConsole(QString)\0"
    "QString\0openExistingData()\0"
    "chooseFileForSavingData()\0"
    "runThreadedDataBBTransfer()\0"
    "runThreadedDataSBTransfer()\0"
    "bbThreadFinishedRunning()\0"
    "sbThreadFinishedRunning()\0"
    "runThreadedDataABTransfer()\0"
    "abThreadFinishedRunning()\0tellViewsToDraw()\0"
    "tellAudioToPlay()\0channel\0"
    "viewWasDoubleClicked(int)\0"
    "continuousViewReachedEndOfData(int)\0"
    "updatePlay()\0resizeSelfAndViews()\0"
    "threadedChannelSeparation(unsigned char*)\0"
    "inPath\0setSaveDataPath(QString)\0inBool\0"
    "setSaveDataBool(bool)\0clearWaveformsOnChannels()\0"
    "resetTriggersOnChannels()\0state,fileName\0"
    "propogateSaveNEV(bool,char*)\0datum\0"
    "writeWaveformsToFile(waveformDatum)\0"
    "setSaveNEVState(bool)\0runThreadedAudioPlayer()\0"
    "addFilterFromFile()\0ind\0"
    "updateSelectedFilter(int)\0stopFilteringData()\0"
    "updateLocalWaveCheckValue(int)\0"
    "numChannels\0updateNumberOfChannelViews(int)\0"
    "numDataChannels\0updateNumberOfDataChannels(int)\0"
    "saveSNIFFRToMat()\0index\0updateAudioChannel(int)\0"
    "changeChannelDisplayToWavesAndContinuous()\0"
    "changeChannelDisplayToWaves()\0"
    "withRecording\0playFromController(bool)\0"
    "numWire\0setAddressingTo(int)\0yesNo\0"
    "tellWaveViewsToPropogateChangesWhenDone(bool)\0"
};

const QMetaObject RTVTMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RTVTMainWindow,
      qt_meta_data_RTVTMainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RTVTMainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RTVTMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RTVTMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RTVTMainWindow))
        return static_cast<void*>(const_cast< RTVTMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int RTVTMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: appendToConsole((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: { QString _r = openExistingData();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: chooseFileForSavingData(); break;
        case 3: runThreadedDataBBTransfer(); break;
        case 4: runThreadedDataSBTransfer(); break;
        case 5: bbThreadFinishedRunning(); break;
        case 6: sbThreadFinishedRunning(); break;
        case 7: runThreadedDataABTransfer(); break;
        case 8: abThreadFinishedRunning(); break;
        case 9: tellViewsToDraw(); break;
        case 10: tellAudioToPlay(); break;
        case 11: viewWasDoubleClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: continuousViewReachedEndOfData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: updatePlay(); break;
        case 14: resizeSelfAndViews(); break;
        case 15: threadedChannelSeparation((*reinterpret_cast< unsigned char*(*)>(_a[1]))); break;
        case 16: setSaveDataPath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: setSaveDataBool((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: clearWaveformsOnChannels(); break;
        case 19: resetTriggersOnChannels(); break;
        case 20: propogateSaveNEV((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2]))); break;
        case 21: writeWaveformsToFile((*reinterpret_cast< waveformDatum(*)>(_a[1]))); break;
        case 22: setSaveNEVState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: runThreadedAudioPlayer(); break;
        case 24: addFilterFromFile(); break;
        case 25: updateSelectedFilter((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: stopFilteringData(); break;
        case 27: updateLocalWaveCheckValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: updateNumberOfChannelViews((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: updateNumberOfDataChannels((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: saveSNIFFRToMat(); break;
        case 31: updateAudioChannel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: changeChannelDisplayToWavesAndContinuous(); break;
        case 33: changeChannelDisplayToWaves(); break;
        case 34: playFromController((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 35: setAddressingTo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: tellWaveViewsToPropogateChangesWhenDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 37;
    }
    return _id;
}

// SIGNAL 0
void RTVTMainWindow::appendToConsole(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
