#-------------------------------------------------
#
# Project created by QtCreator 2016-05-20T16:15:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stitching_v2-0
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imagestitching.cpp \
    videostitching.cpp \
    twocamsvideostitching.cpp \
    threecamsviderostitching.cpp \
    fourcamsvideostitching.cpp

HEADERS  += mainwindow.h \
    imagestitching.h \
    videostitching.h \
    twocamsvideostitching.h \
    threecamsviderostitching.h \
    fourcamsvideostitching.h

FORMS    += mainwindow.ui \
    imagestitching.ui \
    videostitching.ui \
    twocamsvideostitching.ui \
    threecamsviderostitching.ui \
    fourcamsvideostitching.ui

INCLUDEPATH+=D:\MyProgram\opencv\build\include\opencv\
                D:\MyProgram\opencv\build\include\opencv2\
                D:\MyProgram\opencv\build\include

LIBS+=D:\MyProgram\opencv\build\x86\vc10\lib\opencv_ml249d.lib
LIBS+=D:\MyProgram\opencv\build\x86\vc10\lib\opencv_calib3d249d.lib
LIBS+=D:\MyProgram\opencv\build\x86\vc10\lib\opencv_contrib249d.lib
LIBS+=D:\MyProgram\opencv\build\x86\vc10\lib\opencv_core249d.lib
LIBS+=D:\MyProgram\opencv\build\x86\vc10\lib\opencv_features2d249d.lib
LIBS+=D:\MyProgram\opencv\build\x86\vc10\lib\opencv_flann249d.lib
LIBS+=D:\MyProgram\opencv\build\x86\vc10\lib\opencv_gpu249d.lib
LIBS+=D:\MyProgram\opencv\build\x86\vc10\lib\opencv_highgui249d.lib
LIBS+=D:\MyProgram\opencv\build\x86\vc10\lib\opencv_imgproc249d.lib
LIBS+=D:\MyProgram\opencv\build\x86\vc10\lib\opencv_legacy249d.lib
LIBS+=D:\MyProgram\opencv\build\x86\vc10\lib\opencv_objdetect249d.lib
LIBS+=D:\MyProgram\opencv\build\x86\vc10\lib\opencv_ts249d.lib
LIBS+=D:\MyProgram\opencv\build\x86\vc10\lib\opencv_video249d.lib
LIBS+=D:\MyProgram\opencv\build\x86\vc10\lib\opencv_nonfree249d.lib
LIBS+=D:\MyProgram\opencv\build\x86\vc10\lib\opencv_ocl249d.lib
LIBS+=D:\MyProgram\opencv\build\x86\vc10\lib\opencv_photo249d.lib
LIBS+=D:\MyProgram\opencv\build\x86\vc10\lib\opencv_stitching249d.lib
LIBS+=D:\MyProgram\opencv\build\x86\vc10\lib\opencv_superres249d.lib
LIBS+=D:\MyProgram\opencv\build\x86\vc10\lib\opencv_videostab249d.lib
