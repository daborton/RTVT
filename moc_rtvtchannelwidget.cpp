/****************************************************************************
** Meta object code from reading C++ file 'rtvtchannelwidget.h'
**
** Created: Wed Feb 15 16:26:42 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "rtvtchannelwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rtvtchannelwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RTVTChannelWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,
      54,   43,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      90,   18,   18,   18, 0x0a,
     107,   18,   18,   18, 0x0a,
     138,  132,   18,   18, 0x0a,
     178,   43,   18,   18, 0x0a,
     206,   43,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RTVTChannelWidget[] = {
    "RTVTChannelWidget\0\0waveformsReadyToWrite()\0"
    "theTrigger\0sendTriggerToOtherWaveViewers(hoop)\0"
    "channelTimeout()\0viewRedrawTimerTimeout()\0"
    "datum\0childHasWaveformsToWrite(waveformDatum)\0"
    "childHasEditedTrigger(hoop)\0"
    "passTriggerUp(hoop)\0"
};

const QMetaObject RTVTChannelWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RTVTChannelWidget,
      qt_meta_data_RTVTChannelWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RTVTChannelWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RTVTChannelWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RTVTChannelWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RTVTChannelWidget))
        return static_cast<void*>(const_cast< RTVTChannelWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int RTVTChannelWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: waveformsReadyToWrite(); break;
        case 1: sendTriggerToOtherWaveViewers((*reinterpret_cast< hoop(*)>(_a[1]))); break;
        case 2: channelTimeout(); break;
        case 3: viewRedrawTimerTimeout(); break;
        case 4: childHasWaveformsToWrite((*reinterpret_cast< waveformDatum(*)>(_a[1]))); break;
        case 5: childHasEditedTrigger((*reinterpret_cast< hoop(*)>(_a[1]))); break;
        case 6: passTriggerUp((*reinterpret_cast< hoop(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void RTVTChannelWidget::waveformsReadyToWrite()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void RTVTChannelWidget::sendTriggerToOtherWaveViewers(hoop _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
