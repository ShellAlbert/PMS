/****************************************************************************
** Meta object code from reading C++ file 'ploginmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PMSManager/LoginManager/ploginmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ploginmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ZLoginPart_t {
    QByteArrayData data[6];
    char stringdata0[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZLoginPart_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZLoginPart_t qt_meta_stringdata_ZLoginPart = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ZLoginPart"
QT_MOC_LITERAL(1, 11, 14), // "ZSignalDoLogin"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 13), // "ZSignalDoExit"
QT_MOC_LITERAL(4, 41, 9), // "ZSlotOkay"
QT_MOC_LITERAL(5, 51, 11) // "ZSlotCancel"

    },
    "ZLoginPart\0ZSignalDoLogin\0\0ZSignalDoExit\0"
    "ZSlotOkay\0ZSlotCancel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZLoginPart[] = {

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
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ZLoginPart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZLoginPart *_t = static_cast<ZLoginPart *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSignalDoLogin(); break;
        case 1: _t->ZSignalDoExit(); break;
        case 2: _t->ZSlotOkay(); break;
        case 3: _t->ZSlotCancel(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ZLoginPart::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZLoginPart::ZSignalDoLogin)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ZLoginPart::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZLoginPart::ZSignalDoExit)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ZLoginPart::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_ZLoginPart.data,
      qt_meta_data_ZLoginPart,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZLoginPart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZLoginPart::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZLoginPart.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int ZLoginPart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
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
void ZLoginPart::ZSignalDoLogin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ZLoginPart::ZSignalDoExit()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_ZLoginFailPart_t {
    QByteArrayData data[3];
    char stringdata0[30];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZLoginFailPart_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZLoginFailPart_t qt_meta_stringdata_ZLoginFailPart = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ZLoginFailPart"
QT_MOC_LITERAL(1, 15, 13), // "ZSignalReturn"
QT_MOC_LITERAL(2, 29, 0) // ""

    },
    "ZLoginFailPart\0ZSignalReturn\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZLoginFailPart[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void ZLoginFailPart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZLoginFailPart *_t = static_cast<ZLoginFailPart *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSignalReturn(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ZLoginFailPart::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZLoginFailPart::ZSignalReturn)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ZLoginFailPart::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_ZLoginFailPart.data,
      qt_meta_data_ZLoginFailPart,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZLoginFailPart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZLoginFailPart::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZLoginFailPart.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int ZLoginFailPart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ZLoginFailPart::ZSignalReturn()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_PLoginManager_t {
    QByteArrayData data[7];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PLoginManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PLoginManager_t qt_meta_stringdata_PLoginManager = {
    {
QT_MOC_LITERAL(0, 0, 13), // "PLoginManager"
QT_MOC_LITERAL(1, 14, 12), // "ZSlotDoLogin"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11), // "ZSlotDoExit"
QT_MOC_LITERAL(4, 40, 20), // "ZSlotLoginOpFinished"
QT_MOC_LITERAL(5, 61, 7), // "retCode"
QT_MOC_LITERAL(6, 69, 18) // "ZSlotShowLoginPart"

    },
    "PLoginManager\0ZSlotDoLogin\0\0ZSlotDoExit\0"
    "ZSlotLoginOpFinished\0retCode\0"
    "ZSlotShowLoginPart"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PLoginManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    1,   36,    2, 0x0a /* Public */,
       6,    0,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,

       0        // eod
};

void PLoginManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PLoginManager *_t = static_cast<PLoginManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSlotDoLogin(); break;
        case 1: _t->ZSlotDoExit(); break;
        case 2: _t->ZSlotLoginOpFinished((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 3: _t->ZSlotShowLoginPart(); break;
        default: ;
        }
    }
}

const QMetaObject PLoginManager::staticMetaObject = {
    { &ZBaseInfoDia::staticMetaObject, qt_meta_stringdata_PLoginManager.data,
      qt_meta_data_PLoginManager,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PLoginManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PLoginManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PLoginManager.stringdata0))
        return static_cast<void*>(this);
    return ZBaseInfoDia::qt_metacast(_clname);
}

int PLoginManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ZBaseInfoDia::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
