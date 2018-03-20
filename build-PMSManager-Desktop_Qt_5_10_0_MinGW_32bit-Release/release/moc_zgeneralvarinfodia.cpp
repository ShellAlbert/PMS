/****************************************************************************
** Meta object code from reading C++ file 'zgeneralvarinfodia.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PMSManager/TemplateEditor/zgeneralvarinfodia.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zgeneralvarinfodia.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ZGeneralVarInfoDia_t {
    QByteArrayData data[6];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZGeneralVarInfoDia_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZGeneralVarInfoDia_t qt_meta_stringdata_ZGeneralVarInfoDia = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ZGeneralVarInfoDia"
QT_MOC_LITERAL(1, 19, 20), // "ZSlotDataTypeChanged"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 4), // "type"
QT_MOC_LITERAL(4, 46, 9), // "ZSlotOkay"
QT_MOC_LITERAL(5, 56, 11) // "ZSlotCancel"

    },
    "ZGeneralVarInfoDia\0ZSlotDataTypeChanged\0"
    "\0type\0ZSlotOkay\0ZSlotCancel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZGeneralVarInfoDia[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x08 /* Private */,
       4,    0,   32,    2, 0x08 /* Private */,
       5,    0,   33,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ZGeneralVarInfoDia::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZGeneralVarInfoDia *_t = static_cast<ZGeneralVarInfoDia *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSlotDataTypeChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->ZSlotOkay(); break;
        case 2: _t->ZSlotCancel(); break;
        default: ;
        }
    }
}

const QMetaObject ZGeneralVarInfoDia::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ZGeneralVarInfoDia.data,
      qt_meta_data_ZGeneralVarInfoDia,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ZGeneralVarInfoDia::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZGeneralVarInfoDia::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZGeneralVarInfoDia.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ZGeneralVarInfoDia::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
