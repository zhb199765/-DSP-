#-------------------------------------------------
#
# Project created by QtCreator 2019-05-03T09:11:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasyPR-master
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        include/easypr/thirdparty/LBP/helper.cpp \
        include/easypr/thirdparty/LBP/lbp.cpp \
        include/easypr/thirdparty/mser/mser2.cpp \
        include/easypr/thirdparty/svm/corrected_svm.cpp \
        include/easypr/thirdparty/textDetect/erfilter.cpp \
        include/easypr/thirdparty/xmlParser/xmlParser.cpp \
        main.cpp \
        mainwindow.cpp \
        src/core/chars_identify.cpp \
        src/core/chars_recognise.cpp \
        src/core/chars_segment.cpp \
        src/core/core_func.cpp \
        src/core/feature.cpp \
        src/core/params.cpp \
        src/core/plate_detect.cpp \
        src/core/plate_judge.cpp \
        src/core/plate_locate.cpp \
        src/core/plate_recognize.cpp \
        src/train/annCh_train.cpp \
        src/train/ann_train.cpp \
        src/train/create_data.cpp \
        src/train/svm_train.cpp \
        src/train/train.cpp \
        src/util/kv.cpp \
        src/util/program_options.cpp \
        src/util/util.cpp \

HEADERS += \
        include/easypr.h \
        include/easypr/api.hpp \
        include/easypr/config.h \
        include/easypr/core/character.hpp \
        include/easypr/core/chars_identify.h \
        include/easypr/core/chars_recognise.h \
        include/easypr/core/chars_segment.h \
        include/easypr/core/core_func.h \
        include/easypr/core/feature.h \
        include/easypr/core/params.h \
        include/easypr/core/plate.hpp \
        include/easypr/core/plate_detect.h \
        include/easypr/core/plate_judge.h \
        include/easypr/core/plate_locate.h \
        include/easypr/core/plate_recognize.h \
        include/easypr/thirdparty/LBP/helper.hpp \
        include/easypr/thirdparty/LBP/lbp.hpp \
        include/easypr/thirdparty/mser/mser2.hpp \
        include/easypr/thirdparty/svm/precomp.hpp \
        include/easypr/thirdparty/textDetect/erfilter.hpp \
        include/easypr/thirdparty/xmlParser/xmlParser.h \
        include/easypr/train/annCh_train.h \
        include/easypr/train/ann_train.h \
        include/easypr/train/create_data.h \
        include/easypr/train/svm_train.h \
        include/easypr/train/train.h \
        include/easypr/util/kv.h \
        include/easypr/util/program_options.h \
        include/easypr/util/switch.hpp \
        include/easypr/util/util.h \
        include/easypr/version.h \
        mainwindow.h \
        test/accuracy.hpp \
        test/chars.hpp \
        test/config.hpp \
        test/plate.hpp \
        test/result.hpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
INCLUDEPATH+= F:\opencv\build\include\opencv \
              F:\opencv\build\include\opencv2 \
              F:\opencv\build\include \

LIBS += -LF:\opencv\build\install\x86\mingw\lib\
-llibopencv_core320\
-llibopencv_highgui320\
-llibopencv_imgproc320\
-llibopencv_ml320\
-llibopencv_video320\
-llibopencv_features2d320\
-llibopencv_calib3d320\
-llibopencv_objdetect320\
-llibopencv_flann320\
-llibopencv_photo320\
-llibopencv_stitching320\
-llibopencv_superres320\
-llibopencv_videostab320\
-llibopencv_calib3d320\
-llibopencv_imgcodecs320\
-llibopencv_shape320\
-llibopencv_videoio320\
-llibopencv_videostab320
FORMS += \
        mainwindow.ui
    ui_mainwindow.h

