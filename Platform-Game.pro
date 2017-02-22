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
    src/movingleft.cpp \
    src/movingright.cpp \
    src/keys.cpp \
    src/humaninputcomponent.cpp \
    src/gameobject.cpp \
    src/stopleft.cpp \
    src/stopright.cpp \
    src/isjumping.cpp \
    src/jumpingstate.cpp \
    src/isnotjumping.cpp \
    src/deadleft.cpp \
    src/deadright.cpp \
    src/inputcomponent.cpp \
    src/graphicscomponent.cpp \
    src/playergraphicscomponent.cpp \
    src/computerinputcomponent.cpp \
    src/state.cpp \
    src/gamestate.cpp

HEADERS  += \
    include/movingleft.h \
    include/movingright.h \
    include/keys.h \
    include/inputcomponent.h \
    include/humaninputcomponent.h \
    include/state.h \
    include/gameobject.h \
    include/stopleft.h \
    include/stopright.h \
    include/jumpingstate.h \
    include/isjumping.h \
    include/isnotjumping.h \
    include/deadleft.h \
    include/deadright.h \
    include/enumerator.h \
    include/graphicscomponent.h \
    include/playergraphicscomponent.h \
    include/computerinputcomponent.h \
    include/gamestate.h

FORMS    +=

INCLUDEPATH += $$PWD/include
