TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "C:/gtest/googletest/googletest/include"
LIBS += -L"C:/gtest/googletest/build/lib" \
        -lgtest -lgtest_main \
        -lpthread

QMAKE_CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=1
LIBS += -static-libgcc -static-libstdc++

SOURCES += \
        main.cpp \
        testvector.cpp

HEADERS += \
    iterator.h \
    vector.h
