TEMPLATE = app

TARGET = turmite

CONFIG += qt c++11

QT += core gui widgets

SOURCES += \
    CAnt.cpp \
    GridWidget.cpp \
    main.cpp \
    subwindow.cpp

HEADERS += \
    CAnt.h \
    GridWidget.h \
    SquareCell.h \
    matrix.h \
    subwindow.h

msvc:{
    QMAKE_CXXFLAGS_RELEASE += /O2
}
gcc: {
    QMAKE_CXXFLAGS_RELEASE += -O2
}
clang:{
    QMAKE_CXXFLAGS_RELEASE += -O3
}
