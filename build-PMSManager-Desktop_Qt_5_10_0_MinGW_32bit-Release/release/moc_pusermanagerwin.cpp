/****************************************************************************
** Meta object code from reading C++ file 'pusermanagerwin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PMSManager/UserManager/pusermanagerwin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pusermanagerwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PUserManagerWin_t {
    QByteArrayData data[27];
    char stringdata0[332];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PUserManagerWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PUserManagerWin_t qt_meta_stringdata_PUserManagerWin = {
    {
QT_MOC_LITERAL(0, 0, 15), // "PUserManagerWin"
QT_MOC_LITERAL(1, 16, 17), // "ZSignalCloseEvent"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 6), // "widget"
QT_MOC_LITERAL(4, 42, 13), // "ZSignalLogMsg"
QT_MOC_LITERAL(5, 56, 6), // "logMsg"
QT_MOC_LITERAL(6, 63, 12), // "ZSignalAatch"
QT_MOC_LITERAL(7, 76, 10), // "moduleName"
QT_MOC_LITERAL(8, 87, 12), // "ZSignalDetch"
QT_MOC_LITERAL(9, 100, 11), // "ZSlotAddGrp"
QT_MOC_LITERAL(10, 112, 11), // "ZSlotMdyGrp"
QT_MOC_LITERAL(11, 124, 11), // "ZSlotDelGrp"
QT_MOC_LITERAL(12, 136, 12), // "ZSlotAddUser"
QT_MOC_LITERAL(13, 149, 12), // "ZSlotMdyUser"
QT_MOC_LITERAL(14, 162, 12), // "ZSlotDelUser"
QT_MOC_LITERAL(15, 175, 11), // "ZSlotExpand"
QT_MOC_LITERAL(16, 187, 14), // "ZSlotImportXML"
QT_MOC_LITERAL(17, 202, 16), // "ZSlotImportExcel"
QT_MOC_LITERAL(18, 219, 14), // "ZSlotExportXML"
QT_MOC_LITERAL(19, 234, 16), // "ZSlotExportExcel"
QT_MOC_LITERAL(20, 251, 10), // "ZSlotPrint"
QT_MOC_LITERAL(21, 262, 9), // "ZSlotHelp"
QT_MOC_LITERAL(22, 272, 19), // "ZSlotTreeDblClicked"
QT_MOC_LITERAL(23, 292, 5), // "index"
QT_MOC_LITERAL(24, 298, 14), // "ZSlotPopupMenu"
QT_MOC_LITERAL(25, 313, 2), // "pt"
QT_MOC_LITERAL(26, 316, 15) // "ZSlotAatchDetch"

    },
    "PUserManagerWin\0ZSignalCloseEvent\0\0"
    "widget\0ZSignalLogMsg\0logMsg\0ZSignalAatch\0"
    "moduleName\0ZSignalDetch\0ZSlotAddGrp\0"
    "ZSlotMdyGrp\0ZSlotDelGrp\0ZSlotAddUser\0"
    "ZSlotMdyUser\0ZSlotDelUser\0ZSlotExpand\0"
    "ZSlotImportXML\0ZSlotImportExcel\0"
    "ZSlotExportXML\0ZSlotExportExcel\0"
    "ZSlotPrint\0ZSlotHelp\0ZSlotTreeDblClicked\0"
    "index\0ZSlotPopupMenu\0pt\0ZSlotAatchDetch"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PUserManagerWin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  114,    2, 0x06 /* Public */,
       4,    1,  117,    2, 0x06 /* Public */,
       6,    1,  120,    2, 0x06 /* Public */,
       8,    1,  123,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,  126,    2, 0x08 /* Private */,
      10,    0,  127,    2, 0x08 /* Private */,
      11,    0,  128,    2, 0x08 /* Private */,
      12,    0,  129,    2, 0x08 /* Private */,
      13,    0,  130,    2, 0x08 /* Private */,
      14,    0,  131,    2, 0x08 /* Private */,
      15,    0,  132,    2, 0x08 /* Private */,
      16,    0,  133,    2, 0x08 /* Private */,
      17,    0,  134,    2, 0x08 /* Private */,
      18,    0,  135,    2, 0x08 /* Private */,
      19,    0,  136,    2, 0x08 /* Private */,
      20,    0,  137,    2, 0x08 /* Private */,
      21,    0,  138,    2, 0x08 /* Private */,
      22,    1,  139,    2, 0x08 /* Private */,
      24,    1,  142,    2, 0x08 /* Private */,
      26,    0,  145,    2, 0x08 /* Private */,

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
    QMetaType::Void, QMetaType::QModelIndex,   23,
    QMetaType::Void, QMetaType::QPoint,   25,
    QMetaType::Void,

       0        // eod
};

void PUserManagerWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PUserManagerWin *_t = static_cast<PUserManagerWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSignalCloseEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->ZSignalLogMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ZSignalAatch((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->ZSignalDetch((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->ZSlotAddGrp(); break;
        case 5: _t->ZSlotMdyGrp(); break;
        case 6: _t->ZSlotDelGrp(); break;
        case 7: _t->ZSlotAddUser(); break;
        case 8: _t->ZSlotMdyUser(); break;
        case 9: _t->ZSlotDelUser(); break;
        case 10: _t->ZSlotExpand(); break;
        case 11: _t->ZSlotImportXML(); break;
        case 12: _t->ZSlotImportExcel(); break;
        case 13: _t->ZSlotExportXML(); break;
        case 14: _t->ZSlotExportExcel(); break;
        case 15: _t->ZSlotPrint(); break;
        case 16: _t->ZSlotHelp(); break;
        case 17: _t->ZSlotTreeDblClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 18: _t->ZSlotPopupMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 19: _t->ZSlotAatchDetch(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PUserManagerWin::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PUserManagerWin::ZSignalCloseEvent)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PUserManagerWin::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PUserManagerWin::ZSignalLogMsg)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (PUserManagerWin::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PUserManagerWin::ZSignalAatch)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (PUserManagerWin::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PUserManagerWin::ZSignalDetch)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject PUserManagerWin::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_PUserManagerWin.data,
      qt_meta_data_PUserManagerWin,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PUserManagerWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PUserManagerWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PUserManagerWin.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ZAckNetFrmWidget"))
        return static_cast< ZAckNetFrmWidget*>(this);
    return QFrame::qt_metacast(_clname);
}

int PUserManagerWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void PUserManagerWin::ZSignalCloseEvent(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PUserManagerWin::ZSignalLogMsg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PUserManagerWin::ZSignalAatch(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PUserManagerWin::ZSignalDetch(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
