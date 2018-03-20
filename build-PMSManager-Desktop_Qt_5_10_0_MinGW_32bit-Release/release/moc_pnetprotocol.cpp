/****************************************************************************
** Meta object code from reading C++ file 'pnetprotocol.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PMSManager/NetProtocol/pnetprotocol.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pnetprotocol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PNetProtocol_t {
    QByteArrayData data[8];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PNetProtocol_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PNetProtocol_t qt_meta_stringdata_PNetProtocol = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PNetProtocol"
QT_MOC_LITERAL(1, 13, 15), // "ZSignalTxNetFrm"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 8), // "serialNo"
QT_MOC_LITERAL(4, 39, 11), // "ZSignalExit"
QT_MOC_LITERAL(5, 51, 10), // "ZSlotStart"
QT_MOC_LITERAL(6, 62, 13), // "ZSlotReadData"
QT_MOC_LITERAL(7, 76, 14) // "ZSlotWriteData"

    },
    "PNetProtocol\0ZSignalTxNetFrm\0\0serialNo\0"
    "ZSignalExit\0ZSlotStart\0ZSlotReadData\0"
    "ZSlotWriteData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PNetProtocol[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    0,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   43,    2, 0x0a /* Public */,
       6,    0,   44,    2, 0x0a /* Public */,
       7,    0,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PNetProtocol::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PNetProtocol *_t = static_cast<PNetProtocol *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSignalTxNetFrm((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 1: _t->ZSignalExit(); break;
        case 2: _t->ZSlotStart(); break;
        case 3: _t->ZSlotReadData(); break;
        case 4: _t->ZSlotWriteData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PNetProtocol::*_t)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PNetProtocol::ZSignalTxNetFrm)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PNetProtocol::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PNetProtocol::ZSignalExit)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject PNetProtocol::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PNetProtocol.data,
      qt_meta_data_PNetProtocol,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PNetProtocol::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PNetProtocol::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PNetProtocol.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PNetProtocol::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void PNetProtocol::ZSignalTxNetFrm(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PNetProtocol::ZSignalExit()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_PNetProTimeout_t {
    QByteArrayData data[7];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PNetProTimeout_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PNetProTimeout_t qt_meta_stringdata_PNetProTimeout = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PNetProTimeout"
QT_MOC_LITERAL(1, 15, 22), // "ZSignalTxNetFrmTimeout"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 8), // "serialNo"
QT_MOC_LITERAL(4, 48, 11), // "ZSignalExit"
QT_MOC_LITERAL(5, 60, 10), // "ZSlotStart"
QT_MOC_LITERAL(6, 71, 21) // "ZSlotScanWaitAckQueue"

    },
    "PNetProTimeout\0ZSignalTxNetFrmTimeout\0"
    "\0serialNo\0ZSignalExit\0ZSlotStart\0"
    "ZSlotScanWaitAckQueue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PNetProTimeout[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    0,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   38,    2, 0x0a /* Public */,
       6,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PNetProTimeout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PNetProTimeout *_t = static_cast<PNetProTimeout *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSignalTxNetFrmTimeout((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 1: _t->ZSignalExit(); break;
        case 2: _t->ZSlotStart(); break;
        case 3: _t->ZSlotScanWaitAckQueue(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PNetProTimeout::*_t)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PNetProTimeout::ZSignalTxNetFrmTimeout)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PNetProTimeout::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PNetProTimeout::ZSignalExit)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject PNetProTimeout::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PNetProTimeout.data,
      qt_meta_data_PNetProTimeout,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PNetProTimeout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PNetProTimeout::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PNetProTimeout.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PNetProTimeout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void PNetProTimeout::ZSignalTxNetFrmTimeout(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PNetProTimeout::ZSignalExit()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_PNetProcessor_t {
    QByteArrayData data[7];
    char stringdata0[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PNetProcessor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PNetProcessor_t qt_meta_stringdata_PNetProcessor = {
    {
QT_MOC_LITERAL(0, 0, 13), // "PNetProcessor"
QT_MOC_LITERAL(1, 14, 21), // "ZSignalTxNetFrmFinish"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 8), // "serialNo"
QT_MOC_LITERAL(4, 46, 7), // "retCode"
QT_MOC_LITERAL(5, 54, 13), // "ZSlotTxNetFrm"
QT_MOC_LITERAL(6, 68, 20) // "ZSlotTxNetFrmTimeout"

    },
    "PNetProcessor\0ZSignalTxNetFrmFinish\0"
    "\0serialNo\0retCode\0ZSlotTxNetFrm\0"
    "ZSlotTxNetFrmTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PNetProcessor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   34,    2, 0x08 /* Private */,
       6,    1,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void PNetProcessor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PNetProcessor *_t = static_cast<PNetProcessor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSignalTxNetFrmFinish((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 1: _t->ZSlotTxNetFrm((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 2: _t->ZSlotTxNetFrmTimeout((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PNetProcessor::*_t)(qint32 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PNetProcessor::ZSignalTxNetFrmFinish)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject PNetProcessor::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PNetProcessor.data,
      qt_meta_data_PNetProcessor,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PNetProcessor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PNetProcessor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PNetProcessor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PNetProcessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void PNetProcessor::ZSignalTxNetFrmFinish(qint32 _t1, qint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
