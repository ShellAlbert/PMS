/****************************************************************************
** Meta object code from reading C++ file 'ptaskmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PMSManager/TaskManager/ptaskmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ptaskmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PTaskList_t {
    QByteArrayData data[4];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PTaskList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PTaskList_t qt_meta_stringdata_PTaskList = {
    {
QT_MOC_LITERAL(0, 0, 9), // "PTaskList"
QT_MOC_LITERAL(1, 10, 20), // "ZSignalFilterChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 5) // "index"

    },
    "PTaskList\0ZSignalFilterChanged\0\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PTaskList[] = {

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
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void PTaskList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PTaskList *_t = static_cast<PTaskList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSignalFilterChanged((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PTaskList::*_t)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PTaskList::ZSignalFilterChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject PTaskList::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_PTaskList.data,
      qt_meta_data_PTaskList,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PTaskList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PTaskList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PTaskList.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int PTaskList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void PTaskList::ZSignalFilterChanged(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_PTaskManager_t {
    QByteArrayData data[31];
    char stringdata0[413];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PTaskManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PTaskManager_t qt_meta_stringdata_PTaskManager = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PTaskManager"
QT_MOC_LITERAL(1, 13, 17), // "ZSignalCloseEvent"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 6), // "widget"
QT_MOC_LITERAL(4, 39, 13), // "ZSignalLogMsg"
QT_MOC_LITERAL(5, 53, 6), // "logMsg"
QT_MOC_LITERAL(6, 60, 12), // "ZSignalAatch"
QT_MOC_LITERAL(7, 73, 10), // "moduleName"
QT_MOC_LITERAL(8, 84, 12), // "ZSignalDetch"
QT_MOC_LITERAL(9, 97, 12), // "ZSlotAddTask"
QT_MOC_LITERAL(10, 110, 13), // "ZSlotSaveTask"
QT_MOC_LITERAL(11, 124, 12), // "ZSlotMdyTask"
QT_MOC_LITERAL(12, 137, 12), // "ZSlotDelTask"
QT_MOC_LITERAL(13, 150, 15), // "ZSlotSubmitTask"
QT_MOC_LITERAL(14, 166, 17), // "ZSlotWithdrawTask"
QT_MOC_LITERAL(15, 184, 14), // "ZSlotCheckOkay"
QT_MOC_LITERAL(16, 199, 16), // "ZSlotCheckFailed"
QT_MOC_LITERAL(17, 216, 13), // "ZSlotArchieve"
QT_MOC_LITERAL(18, 230, 14), // "ZSlotPrintHtml"
QT_MOC_LITERAL(19, 245, 13), // "ZSlotPrintPdf"
QT_MOC_LITERAL(20, 259, 10), // "ZSlotPrint"
QT_MOC_LITERAL(21, 270, 9), // "ZSlotHelp"
QT_MOC_LITERAL(22, 280, 20), // "ZSlotTaskDataChanged"
QT_MOC_LITERAL(23, 301, 8), // "taskName"
QT_MOC_LITERAL(24, 310, 19), // "ZSlotCloseTabWidget"
QT_MOC_LITERAL(25, 330, 5), // "index"
QT_MOC_LITERAL(26, 336, 21), // "ZSlotDblClickOpenTask"
QT_MOC_LITERAL(27, 358, 20), // "ZSlotRefreshTaskList"
QT_MOC_LITERAL(28, 379, 14), // "ZSlotPopupMenu"
QT_MOC_LITERAL(29, 394, 2), // "pt"
QT_MOC_LITERAL(30, 397, 15) // "ZSlotAatchDetch"

    },
    "PTaskManager\0ZSignalCloseEvent\0\0widget\0"
    "ZSignalLogMsg\0logMsg\0ZSignalAatch\0"
    "moduleName\0ZSignalDetch\0ZSlotAddTask\0"
    "ZSlotSaveTask\0ZSlotMdyTask\0ZSlotDelTask\0"
    "ZSlotSubmitTask\0ZSlotWithdrawTask\0"
    "ZSlotCheckOkay\0ZSlotCheckFailed\0"
    "ZSlotArchieve\0ZSlotPrintHtml\0ZSlotPrintPdf\0"
    "ZSlotPrint\0ZSlotHelp\0ZSlotTaskDataChanged\0"
    "taskName\0ZSlotCloseTabWidget\0index\0"
    "ZSlotDblClickOpenTask\0ZSlotRefreshTaskList\0"
    "ZSlotPopupMenu\0pt\0ZSlotAatchDetch"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PTaskManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  129,    2, 0x06 /* Public */,
       4,    1,  132,    2, 0x06 /* Public */,
       6,    1,  135,    2, 0x06 /* Public */,
       8,    1,  138,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,  141,    2, 0x08 /* Private */,
      10,    0,  142,    2, 0x08 /* Private */,
      11,    0,  143,    2, 0x08 /* Private */,
      12,    0,  144,    2, 0x08 /* Private */,
      13,    0,  145,    2, 0x08 /* Private */,
      14,    0,  146,    2, 0x08 /* Private */,
      15,    0,  147,    2, 0x08 /* Private */,
      16,    0,  148,    2, 0x08 /* Private */,
      17,    0,  149,    2, 0x08 /* Private */,
      18,    0,  150,    2, 0x08 /* Private */,
      19,    0,  151,    2, 0x08 /* Private */,
      20,    0,  152,    2, 0x08 /* Private */,
      21,    0,  153,    2, 0x08 /* Private */,
      22,    1,  154,    2, 0x08 /* Private */,
      24,    1,  157,    2, 0x08 /* Private */,
      26,    1,  160,    2, 0x08 /* Private */,
      27,    1,  163,    2, 0x08 /* Private */,
      28,    1,  166,    2, 0x08 /* Private */,
      30,    0,  169,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::QModelIndex,   25,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::QPoint,   29,
    QMetaType::Void,

       0        // eod
};

void PTaskManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PTaskManager *_t = static_cast<PTaskManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSignalCloseEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->ZSignalLogMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ZSignalAatch((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->ZSignalDetch((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->ZSlotAddTask(); break;
        case 5: _t->ZSlotSaveTask(); break;
        case 6: _t->ZSlotMdyTask(); break;
        case 7: _t->ZSlotDelTask(); break;
        case 8: _t->ZSlotSubmitTask(); break;
        case 9: _t->ZSlotWithdrawTask(); break;
        case 10: _t->ZSlotCheckOkay(); break;
        case 11: _t->ZSlotCheckFailed(); break;
        case 12: _t->ZSlotArchieve(); break;
        case 13: _t->ZSlotPrintHtml(); break;
        case 14: _t->ZSlotPrintPdf(); break;
        case 15: _t->ZSlotPrint(); break;
        case 16: _t->ZSlotHelp(); break;
        case 17: _t->ZSlotTaskDataChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: _t->ZSlotCloseTabWidget((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 19: _t->ZSlotDblClickOpenTask((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 20: _t->ZSlotRefreshTaskList((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 21: _t->ZSlotPopupMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 22: _t->ZSlotAatchDetch(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PTaskManager::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PTaskManager::ZSignalCloseEvent)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PTaskManager::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PTaskManager::ZSignalLogMsg)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (PTaskManager::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PTaskManager::ZSignalAatch)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (PTaskManager::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PTaskManager::ZSignalDetch)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject PTaskManager::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_PTaskManager.data,
      qt_meta_data_PTaskManager,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PTaskManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PTaskManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PTaskManager.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ZAckNetFrmWidget"))
        return static_cast< ZAckNetFrmWidget*>(this);
    return QFrame::qt_metacast(_clname);
}

int PTaskManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void PTaskManager::ZSignalCloseEvent(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PTaskManager::ZSignalLogMsg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PTaskManager::ZSignalAatch(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PTaskManager::ZSignalDetch(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
