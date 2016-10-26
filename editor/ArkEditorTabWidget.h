#ifndef ARKEDITORTABWIDGET_H
#define ARKEDITORTABWIDGET_H

#include <QTabWidget>
#include <QAction>
#include <QMenu>
#include <QList>
#include <QFileDialog>
#include <QFileInfo>
#include <QMap>
//#include <QSet>
#include <set>
#include "ArkEditor.h"

class ArkEditorTabWidget : public QTabWidget
{
    Q_OBJECT
public:

    explicit ArkEditorTabWidget(QWidget * parent = 0);
    virtual ~ArkEditorTabWidget();
    QMenu * fileMenu();
    QMenu * languageMenu();
private:
    void createMenu();
    void createActions();
    ArkEditor * createArkEditor();
    //对于新建的多个文件，这里的返回可能不准确
    QMap<QString,ArkEditor*> editors();
    void checkActionsStatus();
    //获取newfile的文件名
    int emptyFileMinIndex();
private slots:
    void openFile();
    void newFile();
    void saveFile();
    void saveAllFile();
    void tabClose(int index);
    void currentTabChange(int);
    void closeAllFile();
    void changeFileName(const QString& filename);
    void modificationChanged(bool);
    void setLanguage(QAction * act);
public slots:
    //预览当前 sql ，一般替换和header 设置的添加
    void preview();
private:
    QMenu * _fileMenu,*_langMenu;
    QAction *_saveAction,*_openAction,*_saveAllAction,*_closeAction,*_newAction,*_runAction;
    QActionGroup * _languageGroup;
};

#endif // ARKEDITORTABWIDGET_H
