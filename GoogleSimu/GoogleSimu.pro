QT       += core gui
QT       += webenginewidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17

SOURCES += \
    BrowserView.cpp \
    Game.cpp \
    main.cpp \
    mainwindow.cpp \
    utils.cpp

HEADERS += \
    BrowserView.h \
    Game.h \
    mainwindow.h \
    utils.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    TODO

RESOURCES += \
    src.qrc


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../qpdflib/release/ -lqpdf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../qpdflib/debug/ -lqpdf
else:unix: LIBS += -L$$OUT_PWD/../qpdflib/ -lqpdf

INCLUDEPATH += $$PWD/../qpdflib
DEPENDPATH += $$PWD/../qpdflib
