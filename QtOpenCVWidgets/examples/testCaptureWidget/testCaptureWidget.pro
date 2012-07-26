#-------------------------------------------------
#
# Project created by QtCreator 2012-06-22T14:02:29
#
#-------------------------------------------------

QT       += core gui

TARGET = testCaptureWidget
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    ../../widgets/QtOpenCVCaptureWidget/cqtopencvcapturewidget.h


FORMS    += mainwindow.ui

unix: LIBS += -L/usr/lib/ -lQtOpenCVCaptureWidget

INCLUDEPATH += /usr/include \
  $$PWD../../widgets/QtOpenCVCaptureWidget
DEPENDPATH += /usr/include \
  $$PWD../../widgets/QtOpenCVCaptureWidget

unix: LIBS += -L/usr/lib/ -lopencv_core -lopencv_highgui

INCLUDEPATH += /usr/include/opencv2/core \
  /usr/include/opencv2/highgui
DEPENDPATH += /usr/include/opencv2/core \
  /usr/include/opencv2/highgui
