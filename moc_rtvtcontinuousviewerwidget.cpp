/****************************************************************************
** Meta object code from reading C++ file 'rtvtcontinuousviewerwidget.h'
**
** Created: Wed Feb 15 16:26:45 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "rtvtcontinuousviewerwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rtvtcontinuousviewerwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RTVTContinuousViewerWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      36,   28,   27,   27, 0x05,
      59,   28,   27,   27, 0x05,

 // slots: signature, parameters, type, tag, flags
      82,   27,   27,   27, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_RTVTContinuousViewerWidget[] = {
    "RTVTContinuousViewerWidget\0\0channel\0"
    "iWasDoubleClicked(int)\0iReachedEndOfData(int)\0"
    "timeOutSlot()\0"
};

const QMetaObject RTVTContinuousViewerWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RTVTContinuousViewerWidget,
      qt_meta_data_RTVTContinuousViewerWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RTVTContinuousViewerWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RTVTContinuousViewerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RTVTContinuousViewerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RTVTContinuousViewerWidget))
        return static_cast<void*>(const_cast< RTVTContinuousViewerWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int RTVTContinuousViewerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: iWasDoubleClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: iReachedEndOfData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: timeOutSlot(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void RTVTContinuousViewerWidget::iWasDoubleClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RTVTContinuousViewerWidget::iReachedEndOfData(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
