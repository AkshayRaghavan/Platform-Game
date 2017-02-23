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

CONFIG += c++14


SOURCES += main.cpp \
    src/computerinputcomponent.cpp \
    src/deadleft.cpp \
    src/deadright.cpp \
    src/diamond.cpp \
    src/gameobject.cpp \
    src/gamestate.cpp \
    src/gem.cpp \
    src/graphicscomponent.cpp \
    src/humaninputcomponent.cpp \
    src/inputcomponent.cpp \
    src/isjumping.cpp \
    src/isnotjumping.cpp \
    src/jumpingstate.cpp \
    src/keys.cpp \
    src/monsterphysicscomponent.cpp \
    src/movingleft.cpp \
    src/movingright.cpp \
    src/physicscomponent.cpp \
    src/playergraphicscomponent.cpp \
    src/playerphysicscomponent.cpp \
    src/readinput.cpp \
    src/state.cpp \
    src/stopleft.cpp \
    src/stopright.cpp \
    src/tile.cpp \
    src/inputhandler.cpp

HEADERS  += \
    include/computerinputcomponent.h \
    include/deadleft.h \
    include/deadright.h \
    include/diamond.h \
    include/enumerator.h \
    include/gameobject.h \
    include/gamestate.h \
    include/gem.h \
    include/graphicscomponent.h \
    include/humaninputcomponent.h \
    include/inputcomponent.h \
    include/isjumping.h \
    include/isnotjumping.h \
    include/jumpingleft.h \
    include/jumpingstate.h \
    include/keys.h \
    include/monsterphysicscomponent.h \
    include/movingleft.h \
    include/movingright.h \
    include/physicscomponent.h \
    include/playergraphicscomponent.h \
    include/playerphysicscomponent.h \
    include/readinput.h \
    include/state.h \
    include/stopleft.h \
    include/stopright.h \
    include/tile.h \
    include/inputhandler.h

FORMS    +=

INCLUDEPATH += $$PWD/include

RESOURCES += \
    res.qrc
