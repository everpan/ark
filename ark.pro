#-------------------------------------------------
#
# Project created by QtCreator 2016-10-24T14:03:54
#
#-------------------------------------------------

QT       += core gui webenginewidgets uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



CONFIG += qscintilla2
CONFIG += release

TARGET = ark
TEMPLATE = app

INCLUDEPATH += arkbrowser


SOURCES += main.cpp\
        MainWindow.cpp \
    editor/ArkEditor.cpp \
    editor/ArkEditorTabWidget.cpp \
    arkbrowser/autosaver.cpp \
    arkbrowser/bookmarks.cpp \
    arkbrowser/browserapplication.cpp \
    arkbrowser/browsermainwindow.cpp \
    arkbrowser/chasewidget.cpp \
    arkbrowser/cookiejar.cpp \
    arkbrowser/downloadmanager.cpp \
    arkbrowser/edittableview.cpp \
    arkbrowser/edittreeview.cpp \
    arkbrowser/featurepermissionbar.cpp \
    arkbrowser/fullscreennotification.cpp \
    arkbrowser/history.cpp \
    arkbrowser/modelmenu.cpp \
    arkbrowser/printtopdfdialog.cpp \
    arkbrowser/savepagedialog.cpp \
    arkbrowser/searchlineedit.cpp \
    arkbrowser/settings.cpp \
    arkbrowser/squeezelabel.cpp \
    arkbrowser/tabwidget.cpp \
    arkbrowser/toolbarsearch.cpp \
    arkbrowser/urllineedit.cpp \
    arkbrowser/webview.cpp \
    arkbrowser/xbel.cpp \
    comm/ArkLeftPannel.cpp

HEADERS  += MainWindow.h \
    editor/ArkEditor.h \
    editor/ArkEditorTabWidget.h \
    arkbrowser/autosaver.h \
    arkbrowser/bookmarks.h \
    arkbrowser/browserapplication.h \
    arkbrowser/browsermainwindow.h \
    arkbrowser/chasewidget.h \
    arkbrowser/cookiejar.h \
    arkbrowser/downloadmanager.h \
    arkbrowser/edittableview.h \
    arkbrowser/edittreeview.h \
    arkbrowser/featurepermissionbar.h \
    arkbrowser/fullscreennotification.h \
    arkbrowser/history.h \
    arkbrowser/modelmenu.h \
    arkbrowser/printtopdfdialog.h \
    arkbrowser/savepagedialog.h \
    arkbrowser/searchlineedit.h \
    arkbrowser/settings.h \
    arkbrowser/squeezelabel.h \
    arkbrowser/tabwidget.h \
    arkbrowser/toolbarsearch.h \
    arkbrowser/urllineedit.h \
    arkbrowser/webview.h \
    arkbrowser/xbel.h \
    comm/ArkLeftPannel.h
#win32 utf8
win32:QMAKE_CXXFLAGS += /utf-8

FORMS    += \
    arkbrowser/addbookmarkdialog.ui \
    arkbrowser/bookmarks.ui \
    arkbrowser/cookies.ui \
    arkbrowser/cookiesexceptions.ui \
    arkbrowser/downloaditem.ui \
    arkbrowser/downloads.ui \
    arkbrowser/history.ui \
    arkbrowser/passworddialog.ui \
    arkbrowser/printtopdfdialog.ui \
    arkbrowser/proxy.ui \
    arkbrowser/savepagedialog.ui \
    arkbrowser/settings.ui

RESOURCES += \
    res/datafactory/datafactory.qrc \
    res/editor/editor.qrc

SUBDIRS += \
    arkbrowser/arkbrowser.pro

DISTFILES += \
    arkbrowser/Info_mac.plist \
    arkbrowser/demobrowser.ico \
    arkbrowser/demobrowser.icns \
    arkbrowser/demobrowser.rc
