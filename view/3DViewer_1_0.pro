QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../objParser.c \
    ../affine.c \
    glview.cpp \
    main.cpp \
    mainwindow.cpp \
    gifimage/dgif_lib.c \
    gifimage/egif_lib.c \
    gifimage/gifalloc.c \
    gifimage/gif_err.c \
    gifimage/gif_font.c \
    gifimage/gif_hash.c \
    gifimage/quantize.c \
    gifimage/qgifimage.cpp

HEADERS += \
    ../viewer.h \
    glview.h \
    mainwindow.h \
    gifimage/qgifimage.h \
    gifimage/qgifimage_p.h \
    gifimage/qgifglobal.h \
    gifimage/gif_hash.h \
    gifimage/gif_lib.h \
    gifimage/gif_lib_private.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
