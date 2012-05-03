/****************************************************************************
** Meta object code from reading C++ file 'rtvtwaveviewerglwidget.h'
**
** Created: Wed Feb 15 16:26:40 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "rtvtwaveviewerglwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rtvtwaveviewerglwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RTVTWaveViewerGLWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   24,   23,   23, 0x05,
      61,   55,   23,   23, 0x05,
     109,   98,   23,   23, 0x05,
     151,  137,   23,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
     187,   23,   23,   23, 0x09,
     201,   23,   23,   23, 0x09,
     223,   23,   23,   23, 0x09,
     244,   23,   23,   23, 0x09,
     276,   23,   23,   23, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_RTVTWaveViewerGLWidget[] = {
    "RTVTWaveViewerGLWidget\0\0channel\0"
    "iWasDoubleClicked(int)\0datum\0"
    "iHaveWaveformsToWrite(waveformDatum)\0"
    "theTrigger\0waveViewEditedTrigger(hoop)\0"
    "passedTrigger\0passTriggerToOtherWaveViewers(hoop)\0"
    "timeOutSlot()\0tiggerTimerTimedOut()\0"
    "runThreadedTiggers()\0"
    "triggersThreadFinishedRunning()\0"
    "tellTextToUpdate()\0"
};

const QMetaObject RTVTWaveViewerGLWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_RTVTWaveViewerGLWidget,
      qt_meta_data_RTVTWaveViewerGLWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RTVTWaveViewerGLWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RTVTWaveViewerGLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RTVTWaveViewerGLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RTVTWaveViewerGLWidget))
        return static_cast<void*>(const_cast< RTVTWaveViewerGLWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int RTVTWaveViewerGLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: iWasDoubleClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: iHaveWaveformsToWrite((*reinterpret_cast< waveformDatum(*)>(_a[1]))); break;
        case 2: waveViewEditedTrigger((*reinterpret_cast< hoop(*)>(_a[1]))); break;
        case 3: passTriggerToOtherWaveViewers((*reinterpret_cast< hoop(*)>(_a[1]))); break;
        case 4: timeOutSlot(); break;
        case 5: tiggerTimerTimedOut(); break;
        case 6: runThreadedTiggers(); break;
        case 7: triggersThreadFinishedRunning(); break;
        case 8: tellTextToUpdate(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void RTVTWaveViewerGLWidget::iWasDoubleClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RTVTWaveViewerGLWidget::iHaveWaveformsToWrite(waveformDatum _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RTVTWaveViewerGLWidget::waveViewEditedTrigger(hoop _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void RTVTWaveViewerGLWidget::passTriggerToOtherWaveViewers(hoop _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
