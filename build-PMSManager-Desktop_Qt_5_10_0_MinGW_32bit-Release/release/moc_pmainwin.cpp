/****************************************************************************
** Meta object code from reading C++ file 'pmainwin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PMSManager/pmainwin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pmainwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ZShowUserInfoDia_t {
    QByteArrayData data[1];
    char stringdata0[17];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZShowUserInfoDia_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZShowUserInfoDia_t qt_meta_stringdata_ZShowUserInfoDia = {
    {
QT_MOC_LITERAL(0, 0, 16) // "ZShowUserInfoDia"

    },
    "ZShowUserInfoDia"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZShowUserInfoDia[] = {

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

void ZShowUserInfoDia::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ZShowUserInfoDia::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ZShowUserInfoDia.data,
      qt_meta_data_ZShowUserInfoDia,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZShowUserInfoDia::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZShowUserInfoDia::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZShowUserInfoDia.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ZShowUserInfoDia::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_ZTaskInfoWidget_t {
    QByteArrayData data[3];
    char stringdata0[33];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZTaskInfoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZTaskInfoWidget_t qt_meta_stringdata_ZTaskInfoWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ZTaskInfoWidget"
QT_MOC_LITERAL(1, 16, 15), // "ZSlotTimerFlush"
QT_MOC_LITERAL(2, 32, 0) // ""

    },
    "ZTaskInfoWidget\0ZSlotTimerFlush\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZTaskInfoWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ZTaskInfoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZTaskInfoWidget *_t = static_cast<ZTaskInfoWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSlotTimerFlush(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ZTaskInfoWidget::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_ZTaskInfoWidget.data,
      qt_meta_data_ZTaskInfoWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZTaskInfoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZTaskInfoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZTaskInfoWidget.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int ZTaskInfoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_ZUpdateNotifyDialog_t {
    QByteArrayData data[4];
    char stringdata0[43];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZUpdateNotifyDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZUpdateNotifyDialog_t qt_meta_stringdata_ZUpdateNotifyDialog = {
    {
QT_MOC_LITERAL(0, 0, 19), // "ZUpdateNotifyDialog"
QT_MOC_LITERAL(1, 20, 9), // "ZSlotOkay"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 11) // "ZSlotCancel"

    },
    "ZUpdateNotifyDialog\0ZSlotOkay\0\0"
    "ZSlotCancel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZUpdateNotifyDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x08 /* Private */,
       3,    0,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ZUpdateNotifyDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZUpdateNotifyDialog *_t = static_cast<ZUpdateNotifyDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSlotOkay(); break;
        case 1: _t->ZSlotCancel(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ZUpdateNotifyDialog::staticMetaObject = {
    { &ZBaseInfoDia::staticMetaObject, qt_meta_stringdata_ZUpdateNotifyDialog.data,
      qt_meta_data_ZUpdateNotifyDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZUpdateNotifyDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZUpdateNotifyDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZUpdateNotifyDialog.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ZAckNetFrmWidget"))
        return static_cast< ZAckNetFrmWidget*>(this);
    return ZBaseInfoDia::qt_metacast(_clname);
}

int ZUpdateNotifyDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ZBaseInfoDia::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_PMainWin_t {
    QByteArrayData data[31];
    char stringdata0[511];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PMainWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PMainWin_t qt_meta_stringdata_PMainWin = {
    {
QT_MOC_LITERAL(0, 0, 8), // "PMainWin"
QT_MOC_LITERAL(1, 9, 23), // "ZSlotCloseWaitingDialog"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 14), // "netFrmSerialNo"
QT_MOC_LITERAL(4, 49, 7), // "retCode"
QT_MOC_LITERAL(5, 57, 16), // "ZSlotShowTaskBar"
QT_MOC_LITERAL(6, 74, 5), // "bShow"
QT_MOC_LITERAL(7, 80, 15), // "ZSlotShowLogBar"
QT_MOC_LITERAL(8, 96, 16), // "ZSlotLatchModule"
QT_MOC_LITERAL(9, 113, 8), // "moduleNo"
QT_MOC_LITERAL(10, 122, 20), // "ZSlotSubWindowDetach"
QT_MOC_LITERAL(11, 143, 7), // "mdlName"
QT_MOC_LITERAL(12, 151, 19), // "ZSlotSubWindowAatch"
QT_MOC_LITERAL(13, 171, 24), // "ZSlotUpdateStatusBarTime"
QT_MOC_LITERAL(14, 196, 20), // "ZSlotShowUserManager"
QT_MOC_LITERAL(15, 217, 23), // "ZSlotShowTemplateEditor"
QT_MOC_LITERAL(16, 241, 20), // "ZSlotShowFileManager"
QT_MOC_LITERAL(17, 262, 22), // "ZSlotShowProcessEditor"
QT_MOC_LITERAL(18, 285, 20), // "ZSlotShowTaskManager"
QT_MOC_LITERAL(19, 306, 21), // "ZSlotShowFormDesigner"
QT_MOC_LITERAL(20, 328, 18), // "ZSlotShowSystemLog"
QT_MOC_LITERAL(21, 347, 20), // "ZSlotShowSystemSetup"
QT_MOC_LITERAL(22, 368, 19), // "ZSlotShowDataBackup"
QT_MOC_LITERAL(23, 388, 17), // "ZSlotShowSoftInfo"
QT_MOC_LITERAL(24, 406, 17), // "ZSlotShowUserInfo"
QT_MOC_LITERAL(25, 424, 15), // "ZSlotLockScreen"
QT_MOC_LITERAL(26, 440, 12), // "ZSlotExitSys"
QT_MOC_LITERAL(27, 453, 19), // "ZSlotCloseSubWidget"
QT_MOC_LITERAL(28, 473, 6), // "widget"
QT_MOC_LITERAL(29, 480, 13), // "ZSlotHearBeat"
QT_MOC_LITERAL(30, 494, 16) // "ZSlotDoExitClean"

    },
    "PMainWin\0ZSlotCloseWaitingDialog\0\0"
    "netFrmSerialNo\0retCode\0ZSlotShowTaskBar\0"
    "bShow\0ZSlotShowLogBar\0ZSlotLatchModule\0"
    "moduleNo\0ZSlotSubWindowDetach\0mdlName\0"
    "ZSlotSubWindowAatch\0ZSlotUpdateStatusBarTime\0"
    "ZSlotShowUserManager\0ZSlotShowTemplateEditor\0"
    "ZSlotShowFileManager\0ZSlotShowProcessEditor\0"
    "ZSlotShowTaskManager\0ZSlotShowFormDesigner\0"
    "ZSlotShowSystemLog\0ZSlotShowSystemSetup\0"
    "ZSlotShowDataBackup\0ZSlotShowSoftInfo\0"
    "ZSlotShowUserInfo\0ZSlotLockScreen\0"
    "ZSlotExitSys\0ZSlotCloseSubWidget\0"
    "widget\0ZSlotHearBeat\0ZSlotDoExitClean"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PMainWin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,  129,    2, 0x0a /* Public */,
       5,    1,  134,    2, 0x0a /* Public */,
       7,    1,  137,    2, 0x0a /* Public */,
       8,    1,  140,    2, 0x0a /* Public */,
      10,    1,  143,    2, 0x0a /* Public */,
      12,    1,  146,    2, 0x0a /* Public */,
      13,    0,  149,    2, 0x08 /* Private */,
      14,    0,  150,    2, 0x08 /* Private */,
      15,    0,  151,    2, 0x08 /* Private */,
      16,    0,  152,    2, 0x08 /* Private */,
      17,    0,  153,    2, 0x08 /* Private */,
      18,    0,  154,    2, 0x08 /* Private */,
      19,    0,  155,    2, 0x08 /* Private */,
      20,    0,  156,    2, 0x08 /* Private */,
      21,    0,  157,    2, 0x08 /* Private */,
      22,    0,  158,    2, 0x08 /* Private */,
      23,    0,  159,    2, 0x08 /* Private */,
      24,    0,  160,    2, 0x08 /* Private */,
      25,    0,  161,    2, 0x08 /* Private */,
      26,    0,  162,    2, 0x08 /* Private */,
      27,    1,  163,    2, 0x08 /* Private */,
      29,    0,  166,    2, 0x08 /* Private */,
      30,    0,  167,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,
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
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   28,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PMainWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PMainWin *_t = static_cast<PMainWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSlotCloseWaitingDialog((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 1: _t->ZSlotShowTaskBar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->ZSlotShowLogBar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->ZSlotLatchModule((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 4: _t->ZSlotSubWindowDetach((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->ZSlotSubWindowAatch((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->ZSlotUpdateStatusBarTime(); break;
        case 7: _t->ZSlotShowUserManager(); break;
        case 8: _t->ZSlotShowTemplateEditor(); break;
        case 9: _t->ZSlotShowFileManager(); break;
        case 10: _t->ZSlotShowProcessEditor(); break;
        case 11: _t->ZSlotShowTaskManager(); break;
        case 12: _t->ZSlotShowFormDesigner(); break;
        case 13: _t->ZSlotShowSystemLog(); break;
        case 14: _t->ZSlotShowSystemSetup(); break;
        case 15: _t->ZSlotShowDataBackup(); break;
        case 16: _t->ZSlotShowSoftInfo(); break;
        case 17: _t->ZSlotShowUserInfo(); break;
        case 18: _t->ZSlotLockScreen(); break;
        case 19: _t->ZSlotExitSys(); break;
        case 20: _t->ZSlotCloseSubWidget((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->ZSlotHearBeat(); break;
        case 22: _t->ZSlotDoExitClean(); break;
        default: ;
        }
    }
}

const QMetaObject PMainWin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PMainWin.data,
      qt_meta_data_PMainWin,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PMainWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PMainWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PMainWin.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ZAckNetFrmWidget"))
        return static_cast< ZAckNetFrmWidget*>(this);
    return QWidget::qt_metacast(_clname);
}

int PMainWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_PGuideWin_t {
    QByteArrayData data[8];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PGuideWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PGuideWin_t qt_meta_stringdata_PGuideWin = {
    {
QT_MOC_LITERAL(0, 0, 9), // "PGuideWin"
QT_MOC_LITERAL(1, 10, 18), // "ZSignalShowTaskBar"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 5), // "bShow"
QT_MOC_LITERAL(4, 36, 17), // "ZSignalShowLogBar"
QT_MOC_LITERAL(5, 54, 18), // "ZSignalLatchModule"
QT_MOC_LITERAL(6, 73, 8), // "moduleNo"
QT_MOC_LITERAL(7, 82, 16) // "ZSlotLatchModule"

    },
    "PGuideWin\0ZSignalShowTaskBar\0\0bShow\0"
    "ZSignalShowLogBar\0ZSignalLatchModule\0"
    "moduleNo\0ZSlotLatchModule"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PGuideWin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,
       5,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   43,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    6,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void PGuideWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PGuideWin *_t = static_cast<PGuideWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSignalShowTaskBar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->ZSignalShowLogBar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->ZSignalLatchModule((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 3: _t->ZSlotLatchModule(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PGuideWin::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PGuideWin::ZSignalShowTaskBar)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PGuideWin::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PGuideWin::ZSignalShowLogBar)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (PGuideWin::*_t)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PGuideWin::ZSignalLatchModule)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject PGuideWin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PGuideWin.data,
      qt_meta_data_PGuideWin,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PGuideWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PGuideWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PGuideWin.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PGuideWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void PGuideWin::ZSignalShowTaskBar(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PGuideWin::ZSignalShowLogBar(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PGuideWin::ZSignalLatchModule(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
