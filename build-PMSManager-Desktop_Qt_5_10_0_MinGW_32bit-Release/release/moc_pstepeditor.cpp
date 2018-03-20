/****************************************************************************
** Meta object code from reading C++ file 'pstepeditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PMSManager/ProcessEditor/pstepeditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pstepeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PStepEditor_t {
    QByteArrayData data[13];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PStepEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PStepEditor_t qt_meta_stringdata_PStepEditor = {
    {
QT_MOC_LITERAL(0, 0, 11), // "PStepEditor"
QT_MOC_LITERAL(1, 12, 14), // "ZSignalCloseMe"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 12), // "PStepEditor*"
QT_MOC_LITERAL(4, 41, 2), // "me"
QT_MOC_LITERAL(5, 44, 18), // "ZSignalDataChanged"
QT_MOC_LITERAL(6, 63, 12), // "ZSlotCloseMe"
QT_MOC_LITERAL(7, 76, 20), // "ZSlotAddLinkTemplate"
QT_MOC_LITERAL(8, 97, 20), // "ZSlotDelLinkTemplate"
QT_MOC_LITERAL(9, 118, 16), // "ZSlotAddLinkFile"
QT_MOC_LITERAL(10, 135, 16), // "ZSlotDelLinkFile"
QT_MOC_LITERAL(11, 152, 16), // "ZSlotAddLinkRole"
QT_MOC_LITERAL(12, 169, 16) // "ZSlotDelLinkRole"

    },
    "PStepEditor\0ZSignalCloseMe\0\0PStepEditor*\0"
    "me\0ZSignalDataChanged\0ZSlotCloseMe\0"
    "ZSlotAddLinkTemplate\0ZSlotDelLinkTemplate\0"
    "ZSlotAddLinkFile\0ZSlotDelLinkFile\0"
    "ZSlotAddLinkRole\0ZSlotDelLinkRole"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PStepEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       5,    0,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,
      11,    0,   68,    2, 0x08 /* Private */,
      12,    0,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PStepEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PStepEditor *_t = static_cast<PStepEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZSignalCloseMe((*reinterpret_cast< PStepEditor*(*)>(_a[1]))); break;
        case 1: _t->ZSignalDataChanged(); break;
        case 2: _t->ZSlotCloseMe(); break;
        case 3: _t->ZSlotAddLinkTemplate(); break;
        case 4: _t->ZSlotDelLinkTemplate(); break;
        case 5: _t->ZSlotAddLinkFile(); break;
        case 6: _t->ZSlotDelLinkFile(); break;
        case 7: _t->ZSlotAddLinkRole(); break;
        case 8: _t->ZSlotDelLinkRole(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PStepEditor* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PStepEditor::*_t)(PStepEditor * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PStepEditor::ZSignalCloseMe)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PStepEditor::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PStepEditor::ZSignalDataChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject PStepEditor::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_PStepEditor.data,
      qt_meta_data_PStepEditor,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PStepEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PStepEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PStepEditor.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int PStepEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void PStepEditor::ZSignalCloseMe(PStepEditor * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PStepEditor::ZSignalDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
