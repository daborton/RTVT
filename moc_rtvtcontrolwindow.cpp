/****************************************************************************
** Meta object code from reading C++ file 'rtvtcontrolwindow.h'
**
** Created: Wed Feb 15 16:26:56 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "rtvtcontrolwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rtvtcontrolwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RTVTControlWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x0a,
      45,   18,   18,   18, 0x0a,
      66,   18,   18,   18, 0x0a,
      80,   18,   18,   18, 0x0a,
     102,   18,   18,   18, 0x0a,
     137,   18,   18,   18, 0x0a,
     157,   18,   18,   18, 0x0a,
     170,   18,   18,   18, 0x0a,
     197,  191,   18,   18, 0x0a,
     214,  191,   18,   18, 0x0a,
     232,   18,   18,   18, 0x0a,
     255,   18,   18,   18, 0x0a,
     284,   18,   18,   18, 0x0a,
     307,   18,   18,   18, 0x0a,
     330,   18,   18,   18, 0x0a,
     366,   18,   18,   18, 0x0a,
     394,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RTVTControlWindow[] = {
    "RTVTControlWindow\0\0closeAndExitApplication()\0"
    "openFilterDataFile()\0setSavePath()\0"
    "toggleHUDVisibility()\0"
    "toggleRTVTChannelArrayVisibility()\0"
    "reloadStyleSheets()\0setupHSUSB()\0"
    "openRTVTArrayPanel()\0state\0setUsesUSB(bool)\0"
    "setUsesFile(bool)\0rtvtOpenExistingData()\0"
    "appendToStatusField(QString)\0"
    "tellMainWindowToPlay()\0runNoiseSpectrumTest()\0"
    "stopAndRestartRecursiveRecordings()\0"
    "updateCountdownTimerField()\0"
    "stopStartClicked()\0"
};

const QMetaObject RTVTControlWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RTVTControlWindow,
      qt_meta_data_RTVTControlWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RTVTControlWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RTVTControlWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RTVTControlWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RTVTControlWindow))
        return static_cast<void*>(const_cast< RTVTControlWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int RTVTControlWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: closeAndExitApplication(); break;
        case 1: openFilterDataFile(); break;
        case 2: setSavePath(); break;
        case 3: toggleHUDVisibility(); break;
        case 4: toggleRTVTChannelArrayVisibility(); break;
        case 5: reloadStyleSheets(); break;
        case 6: setupHSUSB(); break;
        case 7: openRTVTArrayPanel(); break;
        case 8: setUsesUSB((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: setUsesFile((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: rtvtOpenExistingData(); break;
        case 11: appendToStatusField((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: tellMainWindowToPlay(); break;
        case 13: runNoiseSpectrumTest(); break;
        case 14: stopAndRestartRecursiveRecordings(); break;
        case 15: updateCountdownTimerField(); break;
        case 16: stopStartClicked(); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
