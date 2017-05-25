#-------------------------------------------------
#
# Project created by QtCreator 2016-05-25T17:24:31
#
#-------------------------------------------------

QT       += core gui
QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = UTComputer
TEMPLATE = app


SOURCES += main.cpp\
    computer.cpp \
    litteral.cpp \
    qcomputer.cpp \
    controleur.cpp \
    strategie.cpp \
    operator.cpp \
    entier.cpp \
    librairie.cpp \
    reel.cpp \
    rationnel.cpp \
    complexe.cpp \
    programme.cpp \
    expression.cpp \
    atome.cpp

HEADERS  += \
    computer.h \
    qcomputer.h \
    litteral.h \
    operator.h \
    strategie.h \
    controleur.h \
    regex.h \
    utcomputerexception.h \
    entier.h \
    librairie.h \
    reel.h \
    rationnel.h \
    complexe.h \
    programme.h \
    expression.h \
    memento.h \
    atome.h

FORMS    += mainwindow.ui

RESOURCES += \
    beep.qrc
