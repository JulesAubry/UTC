/****************************************************************************
** Meta object code from reading C++ file 'qcomputer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../UTComputer/qcomputer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcomputer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QComputer_t {
    QByteArrayData data[18];
    char stringdata0[288];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QComputer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QComputer_t qt_meta_stringdata_QComputer = {
    {
QT_MOC_LITERAL(0, 0, 9), // "QComputer"
QT_MOC_LITERAL(1, 10, 7), // "refresh"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 15), // "getNextCommande"
QT_MOC_LITERAL(4, 35, 22), // "stateChangedBipOptions"
QT_MOC_LITERAL(5, 58, 14), // "playBipOptions"
QT_MOC_LITERAL(6, 73, 25), // "stateChangedOptionClavier"
QT_MOC_LITERAL(7, 99, 15), // "buttonTriggered"
QT_MOC_LITERAL(8, 115, 12), // "addProgramme"
QT_MOC_LITERAL(9, 128, 15), // "deleteProgramme"
QT_MOC_LITERAL(10, 144, 16), // "updateProgrammes"
QT_MOC_LITERAL(11, 161, 19), // "editerProgrammeFunc"
QT_MOC_LITERAL(12, 181, 22), // "lancerEditionProgramme"
QT_MOC_LITERAL(13, 204, 11), // "addVariable"
QT_MOC_LITERAL(14, 216, 14), // "deleteVariable"
QT_MOC_LITERAL(15, 231, 15), // "updateVariables"
QT_MOC_LITERAL(16, 247, 18), // "editerVariableFunc"
QT_MOC_LITERAL(17, 266, 21) // "lancerEditionVariable"

    },
    "QComputer\0refresh\0\0getNextCommande\0"
    "stateChangedBipOptions\0playBipOptions\0"
    "stateChangedOptionClavier\0buttonTriggered\0"
    "addProgramme\0deleteProgramme\0"
    "updateProgrammes\0editerProgrammeFunc\0"
    "lancerEditionProgramme\0addVariable\0"
    "deleteVariable\0updateVariables\0"
    "editerVariableFunc\0lancerEditionVariable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QComputer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a /* Public */,
       3,    0,   95,    2, 0x0a /* Public */,
       4,    1,   96,    2, 0x0a /* Public */,
       5,    0,   99,    2, 0x0a /* Public */,
       6,    1,  100,    2, 0x0a /* Public */,
       7,    1,  103,    2, 0x0a /* Public */,
       8,    0,  106,    2, 0x0a /* Public */,
       9,    0,  107,    2, 0x0a /* Public */,
      10,    0,  108,    2, 0x0a /* Public */,
      11,    0,  109,    2, 0x0a /* Public */,
      12,    0,  110,    2, 0x0a /* Public */,
      13,    0,  111,    2, 0x0a /* Public */,
      14,    0,  112,    2, 0x0a /* Public */,
      15,    0,  113,    2, 0x0a /* Public */,
      16,    0,  114,    2, 0x0a /* Public */,
      17,    0,  115,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
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

       0        // eod
};

void QComputer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QComputer *_t = static_cast<QComputer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->refresh(); break;
        case 1: _t->getNextCommande(); break;
        case 2: _t->stateChangedBipOptions((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->playBipOptions(); break;
        case 4: _t->stateChangedOptionClavier((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->buttonTriggered((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->addProgramme(); break;
        case 7: _t->deleteProgramme(); break;
        case 8: _t->updateProgrammes(); break;
        case 9: _t->editerProgrammeFunc(); break;
        case 10: _t->lancerEditionProgramme(); break;
        case 11: _t->addVariable(); break;
        case 12: _t->deleteVariable(); break;
        case 13: _t->updateVariables(); break;
        case 14: _t->editerVariableFunc(); break;
        case 15: _t->lancerEditionVariable(); break;
        default: ;
        }
    }
}

const QMetaObject QComputer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QComputer.data,
      qt_meta_data_QComputer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QComputer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QComputer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QComputer.stringdata0))
        return static_cast<void*>(const_cast< QComputer*>(this));
    return QWidget::qt_metacast(_clname);
}

int QComputer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
