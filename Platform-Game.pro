#-------------------------------------------------
#
# Project created by QtCreator 2017-02-20T00:59:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Platform-Game
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    src/graphicscomponent.cpp \
    src/playergraphicscomponent.cpp \
    src/gameobject.cpp \
    src/jumpingstate.cpp \
    src/inputcomponent.cpp \
    src/keys.cpp \
    src/state.cpp \
    src/physicscomponent.cpp \
    src/playerphysicscomponent.cpp \
    src/tile.cpp

HEADERS  += \
    include/graphicscomponent.h \
    include/playergraphicscomponent.h \
    include/gameobject.h \
    include/keys.h \
    include/state.h \
    include/jumpingstate.h \
    include/enumerator.h \
    include/inputcomponent.h \
    include/physicscomponent.h \
    include/playerphysicscomponent.h \
    include/tile.h

FORMS    +=

INCLUDEPATH += $$PWD/include
