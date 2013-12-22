#-------------------------------------------------
#
# Project created by QtCreator 2013-09-22T20:26:48
#
#-------------------------------------------------

QT       += core gui
QT       += webkit webkitwidgets network
QT       += widgets positioning

TARGET = GuiWebcam
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        player.cpp

HEADERS  += mainwindow.h \
        player.h

FORMS    += mainwindow.ui


INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib \
-lopencv_core \
-lopencv_imgproc \
-lopencv_highgui \
-lopencv_ml \
-lopencv_video \
-lopencv_features2d \
-lopencv_calib3d \
-lopencv_objdetect \
-lopencv_contrib \
-lopencv_legacy \
-lopencv_flann

OTHER_FILES += \
    Location.js



