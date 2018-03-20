/****************************************************************************
** Meta object code from reading C++ file 'zpdfviewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PMSManager/FileManager/zpdfviewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zpdfviewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ZPdfViewer_t {
    QByteArrayData data[13];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZPdfViewer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZPdfViewer_t qt_meta_stringdata_ZPdfViewer = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ZPdfViewer"
QT_MOC_LITERAL(1, 11, 14), // "ZSlotFirstPage"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 14), // "ZSlotPriorPage"
QT_MOC_LITERAL(4, 42, 13), // "ZSlotNextPage"
QT_MOC_LITERAL(5, 56, 13), // "ZSlotLastPage"
QT_MOC_LITERAL(6, 70, 12), // "ZSlotScaleUp"
QT_MOC_LITERAL(7, 83, 14), // "ZSlotScaleDown"
QT_MOC_LITERAL(8, 98, 13), // "ZSlotScaleFit"
QT_MOC_LITERAL(9, 112, 16), // "ZSlotLoadPdfPage"
QT_MOC_LITERAL(10, 129, 9), // "pageIndex"
QT_MOC_LITERAL(11, 139, 26), // "ZSlotScrollBarValueChanged"
QT_MOC_LITERAL(12, 166, 14) // "scrollBarValue"

    },
    "ZPdfViewer\0ZSlotFirstPage\0\0ZSlotPriorPage\0"
    "ZSlotNextPage\0ZSlotLastPage\0ZSlotScaleUp\0"
    "ZSlotScaleDown\0ZSlotScaleFit\0"
    "ZSlotLoadPdfPage\0pageIndex\0"
    "ZSlotScrollBarValueChanged\0scrollBarValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZPdfViewer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    1,   66,    2, 0x08 /* Private */,
      11,    1,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void ZPdfViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZPdfViewer *_t = static_cast<ZPdfViewer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSlotFirstPage(); break;
        case 1: _t->ZSlotPriorPage(); break;
        case 2: _t->ZSlotNextPage(); break;
        case 3: _t->ZSlotLastPage(); break;
        case 4: _t->ZSlotScaleUp(); break;
        case 5: _t->ZSlotScaleDown(); break;
        case 6: _t->ZSlotScaleFit(); break;
        case 7: _t->ZSlotLoadPdfPage((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 8: _t->ZSlotScrollBarValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ZPdfViewer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ZPdfViewer.data,
      qt_meta_data_ZPdfViewer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZPdfViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZPdfViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZPdfViewer.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ZPdfViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
