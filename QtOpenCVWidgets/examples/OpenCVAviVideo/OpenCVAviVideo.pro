TEMPLATE = app
CONFIG += console
#CONFIG -= qt
CONFIG += core

SOURCES += main.cpp

#win32:CONFIG(release, debug|release): LIBS += -L/usr/lib/release/ -lopencv_highgui
#else:win32:CONFIG(debug, debug|release): LIBS += -L/usr/lib/debug/ -lopencv_highgui
#else:symbian: LIBS += -lopencv_highgui
#else:
unix: LIBS += -L/usr/lib/ -lopencv_highgui

INCLUDEPATH += /usr/include/opencv2/highgui
DEPENDPATH += /usr/include/opencv2/highgui

unix: LIBS += -L/usr/lib/ -lopencv_core

INCLUDEPATH += /usr/include/opencv2/core
DEPENDPATH += /usr/include/opencv2/core
