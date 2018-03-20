/****************************************************************************
** Meta object code from reading C++ file 'KDReportsPreviewDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PMSManager/KDReports/KDReportsPreviewDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KDReportsPreviewDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_KDReports__PreviewDialog_t {
    QByteArrayData data[14];
    char stringdata0[221];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KDReports__PreviewDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KDReports__PreviewDialog_t qt_meta_stringdata_KDReports__PreviewDialog = {
    {
QT_MOC_LITERAL(0, 0, 24), // "KDReports::PreviewDialog"
QT_MOC_LITERAL(1, 25, 15), // "pageSizeChanged"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 18), // "QPrinter::PageSize"
QT_MOC_LITERAL(4, 61, 8), // "pageSize"
QT_MOC_LITERAL(5, 70, 18), // "orientationChanged"
QT_MOC_LITERAL(6, 89, 21), // "QPrinter::Orientation"
QT_MOC_LITERAL(7, 111, 11), // "orientation"
QT_MOC_LITERAL(8, 123, 6), // "accept"
QT_MOC_LITERAL(9, 130, 6), // "reject"
QT_MOC_LITERAL(10, 137, 27), // "_kd_slotTableBreakingDialog"
QT_MOC_LITERAL(11, 165, 23), // "_kd_slotPrintWithDialog"
QT_MOC_LITERAL(12, 189, 18), // "_kd_slotQuickPrint"
QT_MOC_LITERAL(13, 208, 12) // "_kd_slotSave"

    },
    "KDReports::PreviewDialog\0pageSizeChanged\0"
    "\0QPrinter::PageSize\0pageSize\0"
    "orientationChanged\0QPrinter::Orientation\0"
    "orientation\0accept\0reject\0"
    "_kd_slotTableBreakingDialog\0"
    "_kd_slotPrintWithDialog\0_kd_slotQuickPrint\0"
    "_kd_slotSave"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KDReports__PreviewDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       5,    1,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,
      10,    0,   62,    2, 0x08 /* Private */,
      11,    0,   63,    2, 0x08 /* Private */,
      12,    0,   64,    2, 0x08 /* Private */,
      13,    0,   65,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void KDReports::PreviewDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PreviewDialog *_t = static_cast<PreviewDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pageSizeChanged((*reinterpret_cast< QPrinter::PageSize(*)>(_a[1]))); break;
        case 1: _t->orientationChanged((*reinterpret_cast< QPrinter::Orientation(*)>(_a[1]))); break;
        case 2: _t->accept(); break;
        case 3: _t->reject(); break;
        case 4: _t->d->_kd_slotTableBreakingDialog(); break;
        case 5: _t->d->_kd_slotPrintWithDialog(); break;
        case 6: _t->d->_kd_slotQuickPrint(); break;
        case 7: _t->d->_kd_slotSave(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PreviewDialog::*_t)(QPrinter::PageSize );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PreviewDialog::pageSizeChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PreviewDialog::*_t)(QPrinter::Orientation );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PreviewDialog::orientationChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject KDReports::PreviewDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_KDReports__PreviewDialog.data,
      qt_meta_data_KDReports__PreviewDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *KDReports::PreviewDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KDReports::PreviewDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KDReports__PreviewDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int KDReports::PreviewDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void KDReports::PreviewDialog::pageSizeChanged(QPrinter::PageSize _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KDReports::PreviewDialog::orientationChanged(QPrinter::Orientation _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
