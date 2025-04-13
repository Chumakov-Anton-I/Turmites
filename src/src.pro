TEMPLATE = app

TARGET = turmite

CONFIG += qt c++11

QT += core gui widgets

SOURCES += \
    CAnt.cpp \
    GridWidget.cpp \
    InfoWindow.cpp \
    MainWindow.cpp \
    #RuleBuilder.cpp \
    TabAnt.cpp \
    engine.cpp \
    subwindow.cpp \
    main.cpp
    #turmitewgt.cpp

HEADERS += \
    CAnt.h \
    GridWidget.h \
    InfoWindow.h \
    MainWindow.h \
    #RuleBuilder.h \
    RuleValidator.h \
    SquareCell.h \
    TabAnt.h \
    engine.h \
    subwindow.h
    #turmitewgt.h

msvc:{
    QMAKE_CXXFLAGS_RELEASE += /O2
}
gcc: {
    QMAKE_CXXFLAGS_RELEASE += -O2
}
clang:{
    QMAKE_CXXFLAGS_RELEASE += -O3
}

RESOURCES += \
    app.qrc
