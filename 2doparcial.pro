QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += QCUSTOMPLOT_USE_LIBRARY  #linea especifica de esta libreria
DEFINES += MUPARSERLIB_EXPORTS #
QMAKE_CXXFLAGS += -Wa,-mbig-obj    #protege de incompatibilidades de actualizaciones de C++

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -LC:\qcp_lib    # += sumo una libreria -Ldireccion_del_.dll, entre comillas si hay espacios
LIBS += -lqcustomplotd2 #nombre archivo.dll
LIBS += -lmuParserDLL
INCLUDEPATH += C:\qcp_lib #direccion del .h
