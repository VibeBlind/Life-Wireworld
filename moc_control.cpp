/****************************************************************************
** Meta object code from reading C++ file 'control.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "control.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'control.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ControlDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   15,   14,   14, 0x05,
      42,   15,   14,   14, 0x05,
      59,   14,   14,   14, 0x05,
      71,   14,   14,   14, 0x05,
      86,   14,   14,   14, 0x05,
      98,   14,   14,   14, 0x05,
     111,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     123,   14,   14,   14, 0x08,
     130,   14,   14,   14, 0x08,
     142,  138,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ControlDialog[] = {
    "ControlDialog\0\0change\0gridSizeChange(int)\0"
    "delayChange(int)\0quitPress()\0"
    "restartPress()\0playPress()\0pausePress()\0"
    "stepPress()\0play()\0pause()\0gen\0"
    "updateGen(int)\0"
};

void ControlDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ControlDialog *_t = static_cast<ControlDialog *>(_o);
        switch (_id) {
        case 0: _t->gridSizeChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->delayChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->quitPress(); break;
        case 3: _t->restartPress(); break;
        case 4: _t->playPress(); break;
        case 5: _t->pausePress(); break;
        case 6: _t->stepPress(); break;
        case 7: _t->play(); break;
        case 8: _t->pause(); break;
        case 9: _t->updateGen((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ControlDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ControlDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ControlDialog,
      qt_meta_data_ControlDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ControlDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ControlDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ControlDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ControlDialog))
        return static_cast<void*>(const_cast< ControlDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ControlDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void ControlDialog::gridSizeChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ControlDialog::delayChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ControlDialog::quitPress()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ControlDialog::restartPress()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void ControlDialog::playPress()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void ControlDialog::pausePress()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void ControlDialog::stepPress()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
