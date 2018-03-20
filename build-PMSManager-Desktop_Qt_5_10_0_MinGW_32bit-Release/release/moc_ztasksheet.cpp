/****************************************************************************
** Meta object code from reading C++ file 'ztasksheet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PMSManager/TaskManager/ztasksheet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ztasksheet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ZTaskSheet_t {
    QByteArrayData data[11];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZTaskSheet_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZTaskSheet_t qt_meta_stringdata_ZTaskSheet = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ZTaskSheet"
QT_MOC_LITERAL(1, 11, 13), // "ZSignalLogMsg"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 6), // "logMsg"
QT_MOC_LITERAL(4, 33, 18), // "ZSignalDataChanged"
QT_MOC_LITERAL(5, 52, 8), // "taskName"
QT_MOC_LITERAL(6, 61, 16), // "ZSlotCellChanged"
QT_MOC_LITERAL(7, 78, 3), // "row"
QT_MOC_LITERAL(8, 82, 3), // "col"
QT_MOC_LITERAL(9, 86, 16), // "ZSlotCellClicked"
QT_MOC_LITERAL(10, 103, 17) // "QTableWidgetItem*"

    },
    "ZTaskSheet\0ZSignalLogMsg\0\0logMsg\0"
    "ZSignalDataChanged\0taskName\0"
    "ZSlotCellChanged\0row\0col\0ZSlotCellClicked\0"
    "QTableWidgetItem*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZTaskSheet[] = {

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
       6,    2,   40,    2, 0x08 /* Private */,
       9,    1,   45,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void, 0x80000000 | 10,    2,

       0        // eod
};

void ZTaskSheet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZTaskSheet *_t = static_cast<ZTaskSheet *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSignalLogMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->ZSignalDataChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ZSlotCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->ZSlotCellClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ZTaskSheet::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZTaskSheet::ZSignalLogMsg)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ZTaskSheet::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZTaskSheet::ZSignalDataChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ZTaskSheet::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_ZTaskSheet.data,
      qt_meta_data_ZTaskSheet,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZTaskSheet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZTaskSheet::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZTaskSheet.stringdata0))
        return static_cast<void*>(this);
    return QTableWidget::qt_metacast(_clname);
}

int ZTaskSheet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
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
void ZTaskSheet::ZSignalLogMsg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ZTaskSheet::ZSignalDataChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_ZCellDataCheckReportDialog_t {
    QByteArrayData data[3];
    char stringdata0[48];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZCellDataCheckReportDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZCellDataCheckReportDialog_t qt_meta_stringdata_ZCellDataCheckReportDialog = {
    {
QT_MOC_LITERAL(0, 0, 26), // "ZCellDataCheckReportDialog"
QT_MOC_LITERAL(1, 27, 19), // "ZSlotCopy2Clipboard"
QT_MOC_LITERAL(2, 47, 0) // ""

    },
    "ZCellDataCheckReportDialog\0"
    "ZSlotCopy2Clipboard\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZCellDataCheckReportDialog[] = {

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

void ZCellDataCheckReportDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZCellDataCheckReportDialog *_t = static_cast<ZCellDataCheckReportDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSlotCopy2Clipboard(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ZCellDataCheckReportDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ZCellDataCheckReportDialog.data,
      qt_meta_data_ZCellDataCheckReportDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZCellDataCheckReportDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZCellDataCheckReportDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZCellDataCheckReportDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ZCellDataCheckReportDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_ZTaskWidget_t {
    QByteArrayData data[12];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZTaskWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZTaskWidget_t qt_meta_stringdata_ZTaskWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ZTaskWidget"
QT_MOC_LITERAL(1, 12, 13), // "ZSignalLogMsg"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 6), // "logMsg"
QT_MOC_LITERAL(4, 34, 18), // "ZSignalDataChanged"
QT_MOC_LITERAL(5, 53, 8), // "taskName"
QT_MOC_LITERAL(6, 62, 18), // "ZSlotVarDblClicked"
QT_MOC_LITERAL(7, 81, 5), // "index"
QT_MOC_LITERAL(8, 87, 14), // "ZSlotPopupMenu"
QT_MOC_LITERAL(9, 102, 2), // "pt"
QT_MOC_LITERAL(10, 105, 18), // "ZSlotShowLineChart"
QT_MOC_LITERAL(11, 124, 17) // "ZSlotShowBarChart"

    },
    "ZTaskWidget\0ZSignalLogMsg\0\0logMsg\0"
    "ZSignalDataChanged\0taskName\0"
    "ZSlotVarDblClicked\0index\0ZSlotPopupMenu\0"
    "pt\0ZSlotShowLineChart\0ZSlotShowBarChart"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZTaskWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   50,    2, 0x08 /* Private */,
       8,    1,   53,    2, 0x08 /* Private */,
      10,    0,   56,    2, 0x08 /* Private */,
      11,    0,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void, QMetaType::QPoint,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ZTaskWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZTaskWidget *_t = static_cast<ZTaskWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSignalLogMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->ZSignalDataChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ZSlotVarDblClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 3: _t->ZSlotPopupMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 4: _t->ZSlotShowLineChart(); break;
        case 5: _t->ZSlotShowBarChart(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ZTaskWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZTaskWidget::ZSignalLogMsg)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ZTaskWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZTaskWidget::ZSignalDataChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ZTaskWidget::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_ZTaskWidget.data,
      qt_meta_data_ZTaskWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZTaskWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZTaskWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZTaskWidget.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int ZTaskWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ZTaskWidget::ZSignalLogMsg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ZTaskWidget::ZSignalDataChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_ZLineChartDialog_t {
    QByteArrayData data[1];
    char stringdata0[17];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZLineChartDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZLineChartDialog_t qt_meta_stringdata_ZLineChartDialog = {
    {
QT_MOC_LITERAL(0, 0, 16) // "ZLineChartDialog"

    },
    "ZLineChartDialog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZLineChartDialog[] = {

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

void ZLineChartDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ZLineChartDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ZLineChartDialog.data,
      qt_meta_data_ZLineChartDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZLineChartDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZLineChartDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZLineChartDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ZLineChartDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_ZBarChartDialog_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZBarChartDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZBarChartDialog_t qt_meta_stringdata_ZBarChartDialog = {
    {
QT_MOC_LITERAL(0, 0, 15) // "ZBarChartDialog"

    },
    "ZBarChartDialog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZBarChartDialog[] = {

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

void ZBarChartDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ZBarChartDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ZBarChartDialog.data,
      qt_meta_data_ZBarChartDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZBarChartDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZBarChartDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZBarChartDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ZBarChartDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
