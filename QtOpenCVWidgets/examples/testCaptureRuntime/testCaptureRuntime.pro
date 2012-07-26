#-------------------------------------------------
#
# Project created by QtCreator 2012-06-22T12:51:27
#
#-------------------------------------------------

QT       += core gui

TARGET = testCaptureRuntime
CONFIG   += console debug
CONFIG   -= app_bundle

TEMPLATE = app


HEADERS += \
    mainwindow.h

SOURCES += main.cpp \
    mainwindow.cpp

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../../usr/lib/release/ -lQtOpenCVCapture
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../../usr/lib/debug/ -lQtOpenCVCapture
#else:symbian: LIBS += -lQtOpenCVCapture
#else:
unix: LIBS += -L/usr/lib/ -lQtOpenCVCapture

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../../usr/lib/release/ -lopencv_core
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../../usr/lib/debug/ -lopencv_core
#else:symbian: LIBS += -lopencv_core
#else:
unix: LIBS += -L/usr/lib/ -lopencv_core
unix: LIBS += -L/usr/lib/ -lopencv_highgui

INCLUDEPATH += /usr/include \
  /usr/include/opencv2/core \
  /usr/include/opencv2/highgui \
  $$PWD/../../runtime/capture/QtOpenCVCapture
DEPENDPATH += /usr/include \
  /usr/include/opencv2/core \
  /usr/include/opencv2/highgui \
  $$PWD/../../runtime/capture/QtOpenCVCapture

FORMS += \
    mainwindow.ui
