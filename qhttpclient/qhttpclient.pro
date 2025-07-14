QT += core network
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11

TARGET = qhttpclient
INCLUDEPATH += . internal

#QMAKE_CXXFLAGS += -fPIC
#QMAKE_CFLAGS += -fPIC


DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    qhttpclient.h \
    qhttpclient.h \
    internal/curlengine.h \
    internal/curl/*.h

SOURCES += \
    qhttpclient.cpp \
    qhttpclient.cpp \
    internal/curlengine.cpp


#INCLUDEPATH += /usr/include

#LIBS += -lcurl



unix {
    target.path = /usr/lib
    INSTALLS += target
}


LIBS += -lpthread -lrt -lssl -lcrypto
LIBS += -L$$PWD/../../mob_jellies_prepaidv2/smartcardlib/lib/ -lcurl


INCLUDEPATH += $$PWD/../../mob_jellies_prepaidv2/smartcardlib/include
DEPENDPATH += $$PWD/../../mob_jellies_prepaidv2/smartcardlib/include
