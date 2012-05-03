/****************************************************************************
** Meta object code from reading C++ file 'rtvthudcontrollerview.h'
**
** Created: Wed Feb 15 16:26:49 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "HUD_Plugins/rtvthudcontrollerview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rtvthudcontrollerview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RTVTHUDControllerView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x05,
      55,   22,   22,   22, 0x05,
      82,   22,   22,   22, 0x05,
     114,   22,   22,   22, 0x05,
     146,   22,   22,   22, 0x05,
     166,   22,   22,   22, 0x05,
     209,   22,   22,   22, 0x05,
     247,  239,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
     292,  288,   22,   22, 0x0a,
     320,   22,   22,   22, 0x0a,
     350,   22,   22,   22, 0x0a,
     382,   22,   22,   22, 0x0a,
     425,   22,   22,   22, 0x0a,
     455,   22,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RTVTHUDControllerView[] = {
    "RTVTHUDControllerView\0\0"
    "signalToAddFilterToController()\0"
    "selectedFilterChanged(int)\0"
    "changeNumberOfChannelViews(int)\0"
    "changeNumberOfDataChannels(int)\0"
    "signalNoFiltering()\0"
    "changeChannelDisplayToWavesAndContinuous()\0"
    "changeChannelDisplayToWaves()\0numWire\0"
    "changeMainWindowAmplifierAddressing(int)\0"
    "ind\0filterSelectionChanged(int)\0"
    "numberOfChannelViewsChanged()\0"
    "numberOfChannelsInDataChanged()\0"
    "displayAsWavesAndContinuousButtonClicked()\0"
    "displayAsWavesButtonClicked()\0"
    "changeAddressing()\0"
};

const QMetaObject RTVTHUDControllerView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RTVTHUDControllerView,
      qt_meta_data_RTVTHUDControllerView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RTVTHUDControllerView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RTVTHUDControllerView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RTVTHUDControllerView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RTVTHUDControllerView))
        return static_cast<void*>(const_cast< RTVTHUDControllerView*>(this));
    return QWidget::qt_metacast(_clname);
}

int RTVTHUDControllerView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signalToAddFilterToController(); break;
        case 1: selectedFilterChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: changeNumberOfChannelViews((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: changeNumberOfDataChannels((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: signalNoFiltering(); break;
        case 5: changeChannelDisplayToWavesAndContinuous(); break;
        case 6: changeChannelDisplayToWaves(); break;
        case 7: changeMainWindowAmplifierAddressing((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: filterSelectionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: numberOfChannelViewsChanged(); break;
        case 10: numberOfChannelsInDataChanged(); break;
        case 11: displayAsWavesAndContinuousButtonClicked(); break;
        case 12: displayAsWavesButtonClicked(); break;
        case 13: changeAddressing(); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void RTVTHUDControllerView::signalToAddFilterToController()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void RTVTHUDControllerView::selectedFilterChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RTVTHUDControllerView::changeNumberOfChannelViews(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void RTVTHUDControllerView::changeNumberOfDataChannels(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void RTVTHUDControllerView::signalNoFiltering()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void RTVTHUDControllerView::changeChannelDisplayToWavesAndContinuous()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void RTVTHUDControllerView::changeChannelDisplayToWaves()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void RTVTHUDControllerView::changeMainWindowAmplifierAddressing(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
