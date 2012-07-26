#-------------------------------------------------
#
# Project created by QtCreator 2012-06-21T10:08:46
#
#-------------------------------------------------

QT       += webkit

QT       -= gui

TARGET = QtOpenCVCapture
TEMPLATE = lib

DEFINES += QTOPENCV_LIB_EXPORT \
  TIMER_ON

CONFIG += debug_and_release

SOURCES += cqtopencvcaptureobject.cpp

HEADERS += cqtopencvcaptureobject.h \
    ../../../include/qtopencv_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE1A5FE8F
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = QtOpenCVCapture.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

unix: LIBS += -L/usr/lib/ -lopencv_core -lopencv_highgui

INCLUDEPATH += /usr/include/opencv2/core \
  /usr/include/opencv2/highgui
DEPENDPATH += /usr/include/opencv2/core \
  /usr/include/opencv2/highgui

#unix:!macx:!symbian: LIBS += -L/usr/local/lib/ -lGigEVisionSDK

#INCLUDEPATH += /usr/local/include/GigEVisionSDK/gige_cpp
#DEPENDPATH += /usr/local/include/GigEVisionSDK/gige_cpp

