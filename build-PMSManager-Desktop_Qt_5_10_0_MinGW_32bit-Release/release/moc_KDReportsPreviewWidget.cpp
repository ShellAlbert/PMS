/****************************************************************************
** Meta object code from reading C++ file 'KDReportsPreviewWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PMSManager/KDReports/KDReportsPreviewWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KDReportsPreviewWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_KDReports__PreviewWidget_t {
    QByteArrayData data[20];
    char stringdata0[373];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KDReports__PreviewWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KDReports__PreviewWidget_t qt_meta_stringdata_KDReports__PreviewWidget = {
    {
QT_MOC_LITERAL(0, 0, 24), // "KDReports::PreviewWidget"
QT_MOC_LITERAL(1, 25, 15), // "pageSizeChanged"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 18), // "QPrinter::PageSize"
QT_MOC_LITERAL(4, 61, 8), // "pageSize"
QT_MOC_LITERAL(5, 70, 18), // "orientationChanged"
QT_MOC_LITERAL(6, 89, 21), // "QPrinter::Orientation"
QT_MOC_LITERAL(7, 111, 11), // "orientation"
QT_MOC_LITERAL(8, 123, 20), // "tableSettingsClicked"
QT_MOC_LITERAL(9, 144, 26), // "_kd_slotCurrentPageChanged"
QT_MOC_LITERAL(10, 171, 17), // "_kd_slotFirstPage"
QT_MOC_LITERAL(11, 189, 16), // "_kd_slotPrevPage"
QT_MOC_LITERAL(12, 206, 16), // "_kd_slotNextPage"
QT_MOC_LITERAL(13, 223, 16), // "_kd_slotLastPage"
QT_MOC_LITERAL(14, 240, 26), // "_kd_slotPaperSizeActivated"
QT_MOC_LITERAL(15, 267, 33), // "_kd_slotPaperOrientationActiv..."
QT_MOC_LITERAL(16, 301, 14), // "_kd_slotZoomIn"
QT_MOC_LITERAL(17, 316, 15), // "_kd_slotZoomOut"
QT_MOC_LITERAL(18, 332, 19), // "_kd_slotZoomChanged"
QT_MOC_LITERAL(19, 352, 20) // "_kd_previewNextItems"

    },
    "KDReports::PreviewWidget\0pageSizeChanged\0"
    "\0QPrinter::PageSize\0pageSize\0"
    "orientationChanged\0QPrinter::Orientation\0"
    "orientation\0tableSettingsClicked\0"
    "_kd_slotCurrentPageChanged\0_kd_slotFirstPage\0"
    "_kd_slotPrevPage\0_kd_slotNextPage\0"
    "_kd_slotLastPage\0_kd_slotPaperSizeActivated\0"
    "_kd_slotPaperOrientationActivated\0"
    "_kd_slotZoomIn\0_kd_slotZoomOut\0"
    "_kd_slotZoomChanged\0_kd_previewNextItems"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KDReports__PreviewWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       5,    1,   87,    2, 0x06 /* Public */,
       8,    0,   90,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    1,   96,    2, 0x08 /* Private */,
      15,    1,   99,    2, 0x08 /* Private */,
      16,    0,  102,    2, 0x08 /* Private */,
      17,    0,  103,    2, 0x08 /* Private */,
      18,    0,  104,    2, 0x08 /* Private */,
      19,    0,  105,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void KDReports::PreviewWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PreviewWidget *_t = static_cast<PreviewWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pageSizeChanged((*reinterpret_cast< QPrinter::PageSize(*)>(_a[1]))); break;
        case 1: _t->orientationChanged((*reinterpret_cast< QPrinter::Orientation(*)>(_a[1]))); break;
        case 2: _t->tableSettingsClicked(); break;
        case 3: _t->d->_kd_slotCurrentPageChanged(); break;
        case 4: _t->d->_kd_slotFirstPage(); break;
        case 5: _t->d->_kd_slotPrevPage(); break;
        case 6: _t->d->_kd_slotNextPage(); break;
        case 7: _t->d->_kd_slotLastPage(); break;
        case 8: _t->d->_kd_slotPaperSizeActivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->d->_kd_slotPaperOrientationActivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->d->_kd_slotZoomIn(); break;
        case 11: _t->d->_kd_slotZoomOut(); break;
        case 12: _t->d->_kd_slotZoomChanged(); break;
        case 13: _t->d->_kd_previewNextItems(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PreviewWidget::*_t)(QPrinter::PageSize );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PreviewWidget::pageSizeChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PreviewWidget::*_t)(QPrinter::Orientation );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PreviewWidget::orientationChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (PreviewWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PreviewWidget::tableSettingsClicked)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject KDReports::PreviewWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_KDReports__PreviewWidget.data,
      qt_meta_data_KDReports__PreviewWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *KDReports::PreviewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KDReports::PreviewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KDReports__PreviewWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int KDReports::PreviewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void KDReports::PreviewWidget::pageSizeChanged(QPrinter::PageSize _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KDReports::PreviewWidget::orientationChanged(QPrinter::Orientation _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void KDReports::PreviewWidget::tableSettingsClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
