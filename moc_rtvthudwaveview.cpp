/****************************************************************************
** Meta object code from reading C++ file 'rtvthudwaveview.h'
**
** Created: Wed Feb 15 16:26:47 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "HUD_Plugins/rtvthudwaveview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rtvthudwaveview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RTVTHUDWaveView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      46,   16,   16,   16, 0x05,
      85,   83,   16,   16, 0x05,
     132,  126,   16,   16, 0x05,
     171,  163,   16,   16, 0x05,
     203,  197,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
     246,   16,   16,   16, 0x0a,
     263,   16,   16,   16, 0x0a,
     279,   16,   16,   16, 0x0a,
     302,   16,   16,   16, 0x0a,
     327,   16,   16,   16, 0x0a,
     348,   16,   16,   16, 0x0a,
     381,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RTVTHUDWaveView[] = {
    "RTVTHUDWaveView\0\0clearWaveformButtonClicked()\0"
    "resetWaveformTriggersButtonClicked()\0"
    ",\0saveToNEVFileCheckboxClicked(bool,char*)\0"
    "state\0saveNEVToggleButtonState(bool)\0"
    "inValue\0updateWaveCheckValue(int)\0"
    "yesNo\0controllerSaysMoveThresholdsTogether(bool)\0"
    "clearWaveforms()\0resetTriggers()\0"
    "propogateNEVFile(bool)\0propogateSaveNEVToggle()\0"
    "setNEVFileLocation()\0"
    "propogateSetWaveCheckLength(int)\0"
    "thresholdTogetherBoxClicked(int)\0"
};

const QMetaObject RTVTHUDWaveView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RTVTHUDWaveView,
      qt_meta_data_RTVTHUDWaveView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RTVTHUDWaveView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RTVTHUDWaveView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RTVTHUDWaveView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RTVTHUDWaveView))
        return static_cast<void*>(const_cast< RTVTHUDWaveView*>(this));
    return QWidget::qt_metacast(_clname);
}

int RTVTHUDWaveView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clearWaveformButtonClicked(); break;
        case 1: resetWaveformTriggersButtonClicked(); break;
        case 2: saveToNEVFileCheckboxClicked((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2]))); break;
        case 3: saveNEVToggleButtonState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: updateWaveCheckValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: controllerSaysMoveThresholdsTogether((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: clearWaveforms(); break;
        case 7: resetTriggers(); break;
        case 8: propogateNEVFile((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: propogateSaveNEVToggle(); break;
        case 10: setNEVFileLocation(); break;
        case 11: propogateSetWaveCheckLength((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: thresholdTogetherBoxClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void RTVTHUDWaveView::clearWaveformButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void RTVTHUDWaveView::resetWaveformTriggersButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void RTVTHUDWaveView::saveToNEVFileCheckboxClicked(bool _t1, char * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void RTVTHUDWaveView::saveNEVToggleButtonState(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void RTVTHUDWaveView::updateWaveCheckValue(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void RTVTHUDWaveView::controllerSaysMoveThresholdsTogether(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
