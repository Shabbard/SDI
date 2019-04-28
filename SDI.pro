TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/Browser.cpp \
    src/Controller.cpp \
    src/InputHandler.cpp \
    src/SDI-tests.cpp \
    src/FileHandler.cpp \
    src/FIlm.cpp \
    src/FilmProject.cpp \
    src/Material.cpp \
    src/SDI-tests.cpp \
    src/View.cpp \
    src/main.cpp


    
HEADERS += \
    headers/Browser.h \
    headers/Controller.h \
    headers/Film.h \
    headers/FileHandler.h \
    headers/InputHandler.h \
    headers/Material.h \
    headers/FilmProject.h \
    headers/View.h

INCLUDEPATH += headers/

TARGET = $$_PRO_FILE_PWD_/bin/main

LIBS += -lboost_unit_test_framework
LIBS += -lglib-2.0
