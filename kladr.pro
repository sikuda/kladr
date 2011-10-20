CONFIG += static
DEFINES += STATIC
TEMPLATE = app
TARGET = kladr
QT += core \
    gui \
    sql
HEADERS += \
    winkladr.h \
    address.h
SOURCES += \
    winkladr.cpp \
    main.cpp \
    address.cpp
FORMS += \
    Address.ui \
    winkladr.ui
