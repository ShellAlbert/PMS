/****************************************************************************
** Meta object code from reading C++ file 'pformdesigner.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PMSManager/FormDesigner/pformdesigner.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pformdesigner.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ZFormList_t {
    QByteArrayData data[1];
    char stringdata0[10];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZFormList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZFormList_t qt_meta_stringdata_ZFormList = {
    {
QT_MOC_LITERAL(0, 0, 9) // "ZFormList"

    },
    "ZFormList"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZFormList[] = {

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

void ZFormList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ZFormList::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_ZFormList.data,
      qt_meta_data_ZFormList,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZFormList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZFormList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZFormList.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int ZFormList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_ZGraphicsView_t {
    QByteArrayData data[8];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZGraphicsView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZGraphicsView_t qt_meta_stringdata_ZGraphicsView = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ZGraphicsView"
QT_MOC_LITERAL(1, 14, 18), // "ZSignalDataChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 11), // "ZSignalZoom"
QT_MOC_LITERAL(4, 46, 4), // "zoom"
QT_MOC_LITERAL(5, 51, 13), // "ZSlotEditable"
QT_MOC_LITERAL(6, 65, 8), // "editable"
QT_MOC_LITERAL(7, 74, 9) // "ZSlotZoom"

    },
    "ZGraphicsView\0ZSignalDataChanged\0\0"
    "ZSignalZoom\0zoom\0ZSlotEditable\0editable\0"
    "ZSlotZoom"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZGraphicsView[] = {

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
       3,    1,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   38,    2, 0x0a /* Public */,
       7,    1,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    4,

       0        // eod
};

void ZGraphicsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZGraphicsView *_t = static_cast<ZGraphicsView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSignalDataChanged(); break;
        case 1: _t->ZSignalZoom((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->ZSlotEditable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->ZSlotZoom((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ZGraphicsView::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZGraphicsView::ZSignalDataChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ZGraphicsView::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZGraphicsView::ZSignalZoom)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ZGraphicsView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_ZGraphicsView.data,
      qt_meta_data_ZGraphicsView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZGraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZGraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZGraphicsView.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int ZGraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
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
void ZGraphicsView::ZSignalDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ZGraphicsView::ZSignalZoom(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_ZFormWidget_t {
    QByteArrayData data[3];
    char stringdata0[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZFormWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZFormWidget_t qt_meta_stringdata_ZFormWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ZFormWidget"
QT_MOC_LITERAL(1, 12, 18), // "ZSignalDataChanged"
QT_MOC_LITERAL(2, 31, 0) // ""

    },
    "ZFormWidget\0ZSignalDataChanged\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZFormWidget[] = {

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

void ZFormWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZFormWidget *_t = static_cast<ZFormWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSignalDataChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ZFormWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ZFormWidget::ZSignalDataChanged)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ZFormWidget::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_ZFormWidget.data,
      qt_meta_data_ZFormWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZFormWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZFormWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZFormWidget.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int ZFormWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ZFormWidget::ZSignalDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_PFormDesigner_t {
    QByteArrayData data[30];
    char stringdata0[393];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PFormDesigner_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PFormDesigner_t qt_meta_stringdata_PFormDesigner = {
    {
QT_MOC_LITERAL(0, 0, 13), // "PFormDesigner"
QT_MOC_LITERAL(1, 14, 17), // "ZSignalCloseEvent"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 6), // "widget"
QT_MOC_LITERAL(4, 40, 13), // "ZSignalLogMsg"
QT_MOC_LITERAL(5, 54, 6), // "logMsg"
QT_MOC_LITERAL(6, 61, 12), // "ZSlotNewForm"
QT_MOC_LITERAL(7, 74, 13), // "ZSlotOpenForm"
QT_MOC_LITERAL(8, 88, 13), // "ZSlotSaveForm"
QT_MOC_LITERAL(9, 102, 12), // "ZSlotDelForm"
QT_MOC_LITERAL(10, 115, 12), // "ZSlotAddLine"
QT_MOC_LITERAL(11, 128, 17), // "ZSlotAddRectangle"
QT_MOC_LITERAL(12, 146, 16), // "ZSlotAddCheckBox"
QT_MOC_LITERAL(13, 163, 15), // "ZSlotAddSpinBox"
QT_MOC_LITERAL(14, 179, 20), // "ZSlotAddDateTimeEdit"
QT_MOC_LITERAL(15, 200, 13), // "ZSlotAddTable"
QT_MOC_LITERAL(16, 214, 12), // "ZSlotAddText"
QT_MOC_LITERAL(17, 227, 14), // "ZSlotSelectAll"
QT_MOC_LITERAL(18, 242, 16), // "ZSlotDeSelectAll"
QT_MOC_LITERAL(19, 259, 13), // "ZSlotBarGraph"
QT_MOC_LITERAL(20, 273, 13), // "ZSlotPieGraph"
QT_MOC_LITERAL(21, 287, 10), // "ZSlotPrint"
QT_MOC_LITERAL(22, 298, 14), // "ZSlotPrintView"
QT_MOC_LITERAL(23, 313, 14), // "ZSlotDoPrinter"
QT_MOC_LITERAL(24, 328, 9), // "QPrinter*"
QT_MOC_LITERAL(25, 338, 7), // "printer"
QT_MOC_LITERAL(26, 346, 9), // "ZSlotHelp"
QT_MOC_LITERAL(27, 356, 16), // "ZSlotFormChanged"
QT_MOC_LITERAL(28, 373, 13), // "ZSlotCloseTab"
QT_MOC_LITERAL(29, 387, 5) // "index"

    },
    "PFormDesigner\0ZSignalCloseEvent\0\0"
    "widget\0ZSignalLogMsg\0logMsg\0ZSlotNewForm\0"
    "ZSlotOpenForm\0ZSlotSaveForm\0ZSlotDelForm\0"
    "ZSlotAddLine\0ZSlotAddRectangle\0"
    "ZSlotAddCheckBox\0ZSlotAddSpinBox\0"
    "ZSlotAddDateTimeEdit\0ZSlotAddTable\0"
    "ZSlotAddText\0ZSlotSelectAll\0"
    "ZSlotDeSelectAll\0ZSlotBarGraph\0"
    "ZSlotPieGraph\0ZSlotPrint\0ZSlotPrintView\0"
    "ZSlotDoPrinter\0QPrinter*\0printer\0"
    "ZSlotHelp\0ZSlotFormChanged\0ZSlotCloseTab\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PFormDesigner[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  134,    2, 0x06 /* Public */,
       4,    1,  137,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  140,    2, 0x08 /* Private */,
       7,    0,  141,    2, 0x08 /* Private */,
       8,    0,  142,    2, 0x08 /* Private */,
       9,    0,  143,    2, 0x08 /* Private */,
      10,    0,  144,    2, 0x08 /* Private */,
      11,    0,  145,    2, 0x08 /* Private */,
      12,    0,  146,    2, 0x08 /* Private */,
      13,    0,  147,    2, 0x08 /* Private */,
      14,    0,  148,    2, 0x08 /* Private */,
      15,    0,  149,    2, 0x08 /* Private */,
      16,    0,  150,    2, 0x08 /* Private */,
      17,    0,  151,    2, 0x08 /* Private */,
      18,    0,  152,    2, 0x08 /* Private */,
      19,    0,  153,    2, 0x08 /* Private */,
      20,    0,  154,    2, 0x08 /* Private */,
      21,    0,  155,    2, 0x08 /* Private */,
      22,    0,  156,    2, 0x08 /* Private */,
      23,    1,  157,    2, 0x08 /* Private */,
      26,    0,  160,    2, 0x08 /* Private */,
      27,    0,  161,    2, 0x08 /* Private */,
      28,    1,  162,    2, 0x08 /* Private */,
       7,    1,  165,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::QModelIndex,   29,

       0        // eod
};

void PFormDesigner::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PFormDesigner *_t = static_cast<PFormDesigner *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSignalCloseEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->ZSignalLogMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ZSlotNewForm(); break;
        case 3: _t->ZSlotOpenForm(); break;
        case 4: _t->ZSlotSaveForm(); break;
        case 5: _t->ZSlotDelForm(); break;
        case 6: _t->ZSlotAddLine(); break;
        case 7: _t->ZSlotAddRectangle(); break;
        case 8: _t->ZSlotAddCheckBox(); break;
        case 9: _t->ZSlotAddSpinBox(); break;
        case 10: _t->ZSlotAddDateTimeEdit(); break;
        case 11: _t->ZSlotAddTable(); break;
        case 12: _t->ZSlotAddText(); break;
        case 13: _t->ZSlotSelectAll(); break;
        case 14: _t->ZSlotDeSelectAll(); break;
        case 15: _t->ZSlotBarGraph(); break;
        case 16: _t->ZSlotPieGraph(); break;
        case 17: _t->ZSlotPrint(); break;
        case 18: _t->ZSlotPrintView(); break;
        case 19: _t->ZSlotDoPrinter((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        case 20: _t->ZSlotHelp(); break;
        case 21: _t->ZSlotFormChanged(); break;
        case 22: _t->ZSlotCloseTab((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 23: _t->ZSlotOpenForm((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PFormDesigner::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PFormDesigner::ZSignalCloseEvent)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PFormDesigner::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PFormDesigner::ZSignalLogMsg)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject PFormDesigner::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_PFormDesigner.data,
      qt_meta_data_PFormDesigner,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PFormDesigner::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PFormDesigner::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PFormDesigner.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ZAckNetFrmWidget"))
        return static_cast< ZAckNetFrmWidget*>(this);
    return QFrame::qt_metacast(_clname);
}

int PFormDesigner::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 24;
    }
    return _id;
}

// SIGNAL 0
void PFormDesigner::ZSignalCloseEvent(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PFormDesigner::ZSignalLogMsg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
