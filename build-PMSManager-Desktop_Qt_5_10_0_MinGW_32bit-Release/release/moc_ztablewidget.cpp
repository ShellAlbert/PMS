/****************************************************************************
** Meta object code from reading C++ file 'ztablewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PMSManager/FormDesigner/ztablewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ztablewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ZTableDialog_t {
    QByteArrayData data[1];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZTableDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZTableDialog_t qt_meta_stringdata_ZTableDialog = {
    {
QT_MOC_LITERAL(0, 0, 12) // "ZTableDialog"

    },
    "ZTableDialog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZTableDialog[] = {

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

void ZTableDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ZTableDialog::staticMetaObject = {
    { &ZBaseInfoDia::staticMetaObject, qt_meta_stringdata_ZTableDialog.data,
      qt_meta_data_ZTableDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZTableDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZTableDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZTableDialog.stringdata0))
        return static_cast<void*>(this);
    return ZBaseInfoDia::qt_metacast(_clname);
}

int ZTableDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ZBaseInfoDia::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_ZTableWidget_t {
    QByteArrayData data[1];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZTableWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZTableWidget_t qt_meta_stringdata_ZTableWidget = {
    {
QT_MOC_LITERAL(0, 0, 12) // "ZTableWidget"

    },
    "ZTableWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZTableWidget[] = {

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

void ZTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ZTableWidget::staticMetaObject = {
    { &ZBaseWidget::staticMetaObject, qt_meta_stringdata_ZTableWidget.data,
      qt_meta_data_ZTableWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZTableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZTableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZTableWidget.stringdata0))
        return static_cast<void*>(this);
    return ZBaseWidget::qt_metacast(_clname);
}

int ZTableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ZBaseWidget::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
