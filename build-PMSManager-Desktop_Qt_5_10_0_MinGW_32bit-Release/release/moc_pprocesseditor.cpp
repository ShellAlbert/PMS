/****************************************************************************
** Meta object code from reading C++ file 'pprocesseditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PMSManager/ProcessEditor/pprocesseditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pprocesseditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ZProcessManager_t {
    QByteArrayData data[6];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZProcessManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZProcessManager_t qt_meta_stringdata_ZProcessManager = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ZProcessManager"
QT_MOC_LITERAL(1, 16, 18), // "ZSignalOpenProcess"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 11), // "processName"
QT_MOC_LITERAL(4, 48, 20), // "ZSlotDblClickProcess"
QT_MOC_LITERAL(5, 69, 5) // "index"

    },
    "ZProcessManager\0ZSignalOpenProcess\0\0"
    "processName\0ZSlotDblClickProcess\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZProcessManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   27,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    5,

       0        // eod
};

void ZProcessManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZProcessManager *_t = static_cast<ZProcessManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSignalOpenProcess((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->ZSlotDblClickProcess((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ZProcessManager::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZProcessManager::ZSignalOpenProcess)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ZProcessManager::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_ZProcessManager.data,
      qt_meta_data_ZProcessManager,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZProcessManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZProcessManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZProcessManager.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int ZProcessManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ZProcessManager::ZSignalOpenProcess(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_ZProcessEditor_t {
    QByteArrayData data[10];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZProcessEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZProcessEditor_t qt_meta_stringdata_ZProcessEditor = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ZProcessEditor"
QT_MOC_LITERAL(1, 15, 13), // "ZSignalLogMsg"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 7), // "logInfo"
QT_MOC_LITERAL(4, 38, 18), // "ZSignalDataChanged"
QT_MOC_LITERAL(5, 57, 11), // "processName"
QT_MOC_LITERAL(6, 69, 16), // "ZSlotDataChanged"
QT_MOC_LITERAL(7, 86, 21), // "ZSlotRemoveStepEditor"
QT_MOC_LITERAL(8, 108, 12), // "PStepEditor*"
QT_MOC_LITERAL(9, 121, 4) // "edit"

    },
    "ZProcessEditor\0ZSignalLogMsg\0\0logInfo\0"
    "ZSignalDataChanged\0processName\0"
    "ZSlotDataChanged\0ZSlotRemoveStepEditor\0"
    "PStepEditor*\0edit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZProcessEditor[] = {

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
       4,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   40,    2, 0x0a /* Public */,
       7,    1,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void ZProcessEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZProcessEditor *_t = static_cast<ZProcessEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSignalLogMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->ZSignalDataChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ZSlotDataChanged(); break;
        case 3: _t->ZSlotRemoveStepEditor((*reinterpret_cast< PStepEditor*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PStepEditor* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ZProcessEditor::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZProcessEditor::ZSignalLogMsg)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ZProcessEditor::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZProcessEditor::ZSignalDataChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ZProcessEditor::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_ZProcessEditor.data,
      qt_meta_data_ZProcessEditor,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZProcessEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZProcessEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZProcessEditor.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int ZProcessEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ZProcessEditor::ZSignalLogMsg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ZProcessEditor::ZSignalDataChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_PProcessEditor_t {
    QByteArrayData data[19];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PProcessEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PProcessEditor_t qt_meta_stringdata_PProcessEditor = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PProcessEditor"
QT_MOC_LITERAL(1, 15, 17), // "ZSignalCloseEvent"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 6), // "widget"
QT_MOC_LITERAL(4, 41, 13), // "ZSignalLogMsg"
QT_MOC_LITERAL(5, 55, 6), // "logMsg"
QT_MOC_LITERAL(6, 62, 15), // "ZSlotAddProcess"
QT_MOC_LITERAL(7, 78, 16), // "ZSlotOpenProcess"
QT_MOC_LITERAL(8, 95, 16), // "ZSlotSaveProcess"
QT_MOC_LITERAL(9, 112, 18), // "ZSlotSaveAsProcess"
QT_MOC_LITERAL(10, 131, 15), // "ZSlotDelProcess"
QT_MOC_LITERAL(11, 147, 12), // "ZSlotAddStep"
QT_MOC_LITERAL(12, 160, 14), // "ZSlotRemoveTab"
QT_MOC_LITERAL(13, 175, 5), // "index"
QT_MOC_LITERAL(14, 181, 16), // "ZSlotDataChanged"
QT_MOC_LITERAL(15, 198, 11), // "processName"
QT_MOC_LITERAL(16, 210, 9), // "ZSlotHelp"
QT_MOC_LITERAL(17, 220, 14), // "ZSlotPopupMenu"
QT_MOC_LITERAL(18, 235, 2) // "pt"

    },
    "PProcessEditor\0ZSignalCloseEvent\0\0"
    "widget\0ZSignalLogMsg\0logMsg\0ZSlotAddProcess\0"
    "ZSlotOpenProcess\0ZSlotSaveProcess\0"
    "ZSlotSaveAsProcess\0ZSlotDelProcess\0"
    "ZSlotAddStep\0ZSlotRemoveTab\0index\0"
    "ZSlotDataChanged\0processName\0ZSlotHelp\0"
    "ZSlotPopupMenu\0pt"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PProcessEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   85,    2, 0x08 /* Private */,
       7,    0,   86,    2, 0x08 /* Private */,
       8,    0,   87,    2, 0x08 /* Private */,
       9,    0,   88,    2, 0x08 /* Private */,
      10,    0,   89,    2, 0x08 /* Private */,
      11,    0,   90,    2, 0x08 /* Private */,
      12,    1,   91,    2, 0x08 /* Private */,
      14,    1,   94,    2, 0x08 /* Private */,
       7,    1,   97,    2, 0x08 /* Private */,
      16,    0,  100,    2, 0x08 /* Private */,
      17,    1,  101,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   18,

       0        // eod
};

void PProcessEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PProcessEditor *_t = static_cast<PProcessEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSignalCloseEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->ZSignalLogMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ZSlotAddProcess(); break;
        case 3: _t->ZSlotOpenProcess(); break;
        case 4: _t->ZSlotSaveProcess(); break;
        case 5: _t->ZSlotSaveAsProcess(); break;
        case 6: _t->ZSlotDelProcess(); break;
        case 7: _t->ZSlotAddStep(); break;
        case 8: _t->ZSlotRemoveTab((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 9: _t->ZSlotDataChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->ZSlotOpenProcess((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->ZSlotHelp(); break;
        case 12: _t->ZSlotPopupMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PProcessEditor::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PProcessEditor::ZSignalCloseEvent)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PProcessEditor::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PProcessEditor::ZSignalLogMsg)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject PProcessEditor::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_PProcessEditor.data,
      qt_meta_data_PProcessEditor,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PProcessEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PProcessEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PProcessEditor.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ZAckNetFrmWidget"))
        return static_cast< ZAckNetFrmWidget*>(this);
    return QFrame::qt_metacast(_clname);
}

int PProcessEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void PProcessEditor::ZSignalCloseEvent(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PProcessEditor::ZSignalLogMsg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
