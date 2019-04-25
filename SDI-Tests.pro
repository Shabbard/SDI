TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/Browser.cpp \
    src/SDI-tests.cpp \
    src/FileHandler.cpp \
    src/GUI.cpp \
    src/FIlm.cpp \
    src/FilmProject.cpp \
    src/Material.cpp

HEADERS += \
    headers/Browser.h \
    headers/Film.h \
    headers/FileHandler.h \
    headers/GUI.h \
    headers/Material.h \
    headers/FilmProject.h

INCLUDEPATH += headers/

TARGET = $$_PRO_FILE_PWD_/bin/SDI-Tests
