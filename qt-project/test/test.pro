QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
            ../app/datamodels.cpp \
            tst_testmodel.cpp


HEADERS +=  \
        ../app/datamodels.h

INCLUDEPATH += \
        ../app


