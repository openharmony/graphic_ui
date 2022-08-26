CONFIG -= qt

TEMPLATE = lib
DEFINES += LIBJPEGTURBO_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DESTDIR = ../../libs
SOURCE_PATH = ../../../../../../../../third_party/libjpeg-turbo

SOURCES += \
      $${SOURCE_PATH}/jcapimin.c \
      $${SOURCE_PATH}/jcapistd.c \
      $${SOURCE_PATH}/jccoefct.c \
      $${SOURCE_PATH}/jccolor.c \
      $${SOURCE_PATH}/jcdctmgr.c \
      $${SOURCE_PATH}/jchuff.c \
      $${SOURCE_PATH}/jcicc.c \
      $${SOURCE_PATH}/jcinit.c \
      $${SOURCE_PATH}/jcmainct.c \
      $${SOURCE_PATH}/jcmarker.c \
      $${SOURCE_PATH}/jcmaster.c \
      $${SOURCE_PATH}/jcomapi.c \
      $${SOURCE_PATH}/jcparam.c \
      $${SOURCE_PATH}/jcphuff.c \
      $${SOURCE_PATH}/jcprepct.c \
      $${SOURCE_PATH}/jcsample.c \
      $${SOURCE_PATH}/jctrans.c \
      $${SOURCE_PATH}/jdapimin.c \
      $${SOURCE_PATH}/jdapistd.c \
      $${SOURCE_PATH}/jdatadst.c \
      $${SOURCE_PATH}/jdatasrc.c \
      $${SOURCE_PATH}/jdcoefct.c \
      $${SOURCE_PATH}/jdcolor.c \
      $${SOURCE_PATH}/jddctmgr.c \
      $${SOURCE_PATH}/jdhuff.c \
      $${SOURCE_PATH}/jdicc.c \
      $${SOURCE_PATH}/jdinput.c \
      $${SOURCE_PATH}/jdmainct.c \
      $${SOURCE_PATH}/jdmarker.c \
      $${SOURCE_PATH}/jdmaster.c \
      $${SOURCE_PATH}/jdmerge.c \
      $${SOURCE_PATH}/jdphuff.c \
      $${SOURCE_PATH}/jdpostct.c \
      $${SOURCE_PATH}/jdsample.c \
      $${SOURCE_PATH}/jdtrans.c \
      $${SOURCE_PATH}/jerror.c \
      $${SOURCE_PATH}/jfdctflt.c \
      $${SOURCE_PATH}/jfdctfst.c \
      $${SOURCE_PATH}/jfdctint.c \
      $${SOURCE_PATH}/jidctflt.c \
      $${SOURCE_PATH}/jidctfst.c \
      $${SOURCE_PATH}/jidctint.c \
      $${SOURCE_PATH}/jidctred.c \
      $${SOURCE_PATH}/jmemmgr.c \
      $${SOURCE_PATH}/jmemnobs.c \
      $${SOURCE_PATH}/jquant1.c \
      $${SOURCE_PATH}/jquant2.c \
      $${SOURCE_PATH}/jutils.c \
      $${SOURCE_PATH}/jsimd_none.c

INCLUDEPATH += \
    ../../../../../../../third_party/libjpeg-turbo
