TEMPLATE = app

TARGET = turmite

CONFIG += qt c++11

QT += core gui widgets

SOURCES += \
    CAnt.cpp \
    GridWidget.cpp \
    InfoWindow.cpp \
    MainWindow.cpp \
    subwindow.cpp \
    main.cpp

HEADERS += \
    CAnt.h \
    GridWidget.h \
    InfoWindow.h \
    MainWindow.h \
    SquareCell.h \
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
