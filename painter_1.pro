QT       += core gui
QT       +=concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console
QMAKE_CXXFLAGS += -O0
#CONFIG ~= s/-O[0123s]//g
#CONFIG += -O0

QMAKE_CXXFLAGS += -O0
QMAKE_CXXFLAGS -= -O1
QMAKE_CXXFLAGS -= -O2
QMAKE_CXXFLAGS -= -O3
QMAKE_LFLAGS +="/STACK:6553600,409600"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
#    controler.cpp \
    #core.cpp \
    filter.cpp \
    main.cpp \
    point.cpp \
    tes2.cpp \
    widget.cpp

HEADERS += \
#    controler.h \
   # core.h \
    filter.h \
    point.h \
    tes2.h \
    widget.h

FORMS += \
#    controler.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH +=D:\OpenCV\opencv\build\include\opencv2
INCLUDEPATH +=D:\OpenCV\opencv\build\include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../OpenCV/opencv/build/x64/vc16/lib/ -lopencv_world480
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../OpenCV/opencv/build/x64/vc16/lib/ -lopencv_world480d

INCLUDEPATH += $$PWD/../../../OpenCV/opencv/build/x64/vc16
DEPENDPATH += $$PWD/../../../OpenCV/opencv/build/x64/vc16
