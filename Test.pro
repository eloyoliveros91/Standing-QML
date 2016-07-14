QT += qml quick widgets quickcontrols2

CONFIG += c++11

SOURCES += main.cpp \
    contest.cpp \
    team.cpp \


RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    contest.h \
    team.h
