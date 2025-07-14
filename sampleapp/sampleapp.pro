QT += core gui
TEMPLATE = app
TARGET = sample_app

INCLUDEPATH += ../qhttpclient
CONFIG += c++11

HEADERS +=
SOURCES += \
    main.cpp

LIBS += -lpthread -lrt -lssl -lcrypto
LIBS += -L$$PWD/../build-debug/qhttpclient/ -lqhttpclient
LIBS += -L$$PWD/../../mob_jellies_prepaidv2/smartcardlib/lib/ -lcurl
