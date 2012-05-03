/****************************************************************************
** Meta object code from reading C++ file 'audiooutput.h'
**
** Created: Wed Feb 15 16:26:52 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "External-Code/audiooutput.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'audiooutput.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Generator[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_Generator[] = {
    "Generator\0"
};

const QMetaObject Generator::staticMetaObject = {
    { &QIODevice::staticMetaObject, qt_meta_stringdata_Generator,
      qt_meta_data_Generator, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Generator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Generator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Generator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Generator))
        return static_cast<void*>(const_cast< Generator*>(this));
    return QIODevice::qt_metacast(_clname);
}

int Generator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QIODevice::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_AudioTest[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   11,   10,   10, 0x0a,
      63,   10,   10,   10, 0x0a,
      85,   10,   10,   10, 0x08,
      96,   10,   10,   10, 0x08,
     115,   10,   10,   10, 0x08,
     134,  128,   10,   10, 0x08,
     162,   11,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AudioTest[] = {
    "AudioTest\0\0index\0currentIndexChanged(int)\0"
    "setCurrentIndex(int)\0toggleSuspendResume()\0"
    "notified()\0pullTimerExpired()\0"
    "toggleMode()\0state\0stateChanged(QAudio::State)\0"
    "deviceChanged(int)\0"
};

const QMetaObject AudioTest::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_AudioTest,
      qt_meta_data_AudioTest, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AudioTest::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AudioTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AudioTest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AudioTest))
        return static_cast<void*>(const_cast< AudioTest*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int AudioTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setCurrentIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: toggleSuspendResume(); break;
        case 3: notified(); break;
        case 4: pullTimerExpired(); break;
        case 5: toggleMode(); break;
        case 6: stateChanged((*reinterpret_cast< QAudio::State(*)>(_a[1]))); break;
        case 7: deviceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void AudioTest::currentIndexChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
