/****************************************************************************
** Meta object code from reading C++ file 'pfilemanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PMSManager/FileManager/pfilemanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pfilemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ZFileList_t {
    QByteArrayData data[1];
    char stringdata0[10];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZFileList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZFileList_t qt_meta_stringdata_ZFileList = {
    {
QT_MOC_LITERAL(0, 0, 9) // "ZFileList"

    },
    "ZFileList"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZFileList[] = {

 // content:
       7,       // revision
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

void ZFileList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ZFileList::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_ZFileList.data,
      qt_meta_data_ZFileList,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZFileList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZFileList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZFileList.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int ZFileList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_ZImageViewer_t {
    QByteArrayData data[6];
    char stringdata0[64];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZImageViewer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZImageViewer_t qt_meta_stringdata_ZImageViewer = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ZImageViewer"
QT_MOC_LITERAL(1, 13, 11), // "ZSlotZoomIn"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 12), // "ZSlotZoomOut"
QT_MOC_LITERAL(4, 39, 12), // "ZSlotZoomFit"
QT_MOC_LITERAL(5, 52, 11) // "ZSlotRotate"

    },
    "ZImageViewer\0ZSlotZoomIn\0\0ZSlotZoomOut\0"
    "ZSlotZoomFit\0ZSlotRotate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZImageViewer[] = {

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
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ZImageViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZImageViewer *_t = static_cast<ZImageViewer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSlotZoomIn(); break;
        case 1: _t->ZSlotZoomOut(); break;
        case 2: _t->ZSlotZoomFit(); break;
        case 3: _t->ZSlotRotate(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ZImageViewer::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_ZImageViewer.data,
      qt_meta_data_ZImageViewer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZImageViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZImageViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZImageViewer.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int ZImageViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_PFileManager_t {
    QByteArrayData data[18];
    char stringdata0[217];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PFileManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PFileManager_t qt_meta_stringdata_PFileManager = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PFileManager"
QT_MOC_LITERAL(1, 13, 17), // "ZSignalCloseEvent"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 6), // "widget"
QT_MOC_LITERAL(4, 39, 13), // "ZSignalLogMsg"
QT_MOC_LITERAL(5, 53, 6), // "logMsg"
QT_MOC_LITERAL(6, 60, 14), // "ZSlotNewFolder"
QT_MOC_LITERAL(7, 75, 14), // "ZSlotDelFolder"
QT_MOC_LITERAL(8, 90, 15), // "ZSlotUploadFile"
QT_MOC_LITERAL(9, 106, 14), // "ZSlotUploadPic"
QT_MOC_LITERAL(10, 121, 13), // "ZSlotOpenFile"
QT_MOC_LITERAL(11, 135, 12), // "ZSlotDelFile"
QT_MOC_LITERAL(12, 148, 14), // "ZSlotExpandAll"
QT_MOC_LITERAL(13, 163, 9), // "ZSlotHelp"
QT_MOC_LITERAL(14, 173, 19), // "ZSlotCloseTabWidget"
QT_MOC_LITERAL(15, 193, 5), // "index"
QT_MOC_LITERAL(16, 199, 14), // "ZSlotPopupMenu"
QT_MOC_LITERAL(17, 214, 2) // "pt"

    },
    "PFileManager\0ZSignalCloseEvent\0\0widget\0"
    "ZSignalLogMsg\0logMsg\0ZSlotNewFolder\0"
    "ZSlotDelFolder\0ZSlotUploadFile\0"
    "ZSlotUploadPic\0ZSlotOpenFile\0ZSlotDelFile\0"
    "ZSlotExpandAll\0ZSlotHelp\0ZSlotCloseTabWidget\0"
    "index\0ZSlotPopupMenu\0pt"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PFileManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   80,    2, 0x08 /* Private */,
       7,    0,   81,    2, 0x08 /* Private */,
       8,    0,   82,    2, 0x08 /* Private */,
       9,    0,   83,    2, 0x08 /* Private */,
      10,    0,   84,    2, 0x08 /* Private */,
      11,    0,   85,    2, 0x08 /* Private */,
      12,    0,   86,    2, 0x08 /* Private */,
      13,    0,   87,    2, 0x08 /* Private */,
      14,    1,   88,    2, 0x08 /* Private */,
      16,    1,   91,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::QPoint,   17,

       0        // eod
};

void PFileManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PFileManager *_t = static_cast<PFileManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSignalCloseEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->ZSignalLogMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ZSlotNewFolder(); break;
        case 3: _t->ZSlotDelFolder(); break;
        case 4: _t->ZSlotUploadFile(); break;
        case 5: _t->ZSlotUploadPic(); break;
        case 6: _t->ZSlotOpenFile(); break;
        case 7: _t->ZSlotDelFile(); break;
        case 8: _t->ZSlotExpandAll(); break;
        case 9: _t->ZSlotHelp(); break;
        case 10: _t->ZSlotCloseTabWidget((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 11: _t->ZSlotPopupMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PFileManager::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PFileManager::ZSignalCloseEvent)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PFileManager::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PFileManager::ZSignalLogMsg)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject PFileManager::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_PFileManager.data,
      qt_meta_data_PFileManager,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PFileManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PFileManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PFileManager.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ZAckNetFrmWidget"))
        return static_cast< ZAckNetFrmWidget*>(this);
    return QFrame::qt_metacast(_clname);
}

int PFileManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void PFileManager::ZSignalCloseEvent(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PFileManager::ZSignalLogMsg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
