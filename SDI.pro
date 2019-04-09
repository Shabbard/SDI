TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/Browser.cpp \
    src/Film.cpp \
    src/main.cpp \
    src/SDI-tests.cpp

HEADERS += \
    headers/Browser.h \
    headers/Film.h

INCLUDEPATH += headers/

TARGET = $$_PRO_FILE_PWD_/bin/main
