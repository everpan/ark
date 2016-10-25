#include "ArkEditorTabWidget.h"

ArkEditorTabWidget::ArkEditorTabWidget(QWidget * parent) : QTabWidget(parent)
{
    setTabsClosable(true);
    setMovable(true);
    createMenu();
    createActions();
    createArkEditor();

    connect(this,SIGNAL(tabCloseRequested(int)),SLOT(tabClose(int)));
    checkActionsStatus();
}
ArkEditorTabWidget::~ArkEditorTabWidget(){

}
QMenu * ArkEditorTabWidget::fileMenu(){
    return _fileMenu;
}
QMenu * ArkEditorTabWidget::languageMenu(){
    return _langMenu;
}
void ArkEditorTabWidget::createMenu(){

    _fileMenu = new QMenu(tr("&File"),this);
    _langMenu = new QMenu(tr("&Language"),this);
}
void ArkEditorTabWidget::createActions(){
    _newAction = _fileMenu->addAction(QIcon(":/editor/new.png"),tr("&New"),
                                      this,SLOT(newFile()),QKeySequence::New);
    _openAction = _fileMenu->addAction(QIcon(":/editor/open.png"),tr("&Open"),
                                       this,SLOT(openFile()),QKeySequence::Open);
    _saveAction = _fileMenu->addAction(QIcon(":/editor/save.png"),tr("&Save"),
                                       this,SLOT(saveFile()),QKeySequence::Save);
    _saveAllAction = _fileMenu->addAction(QIcon(":/editor/sall.png"),tr("&Save All"),
                                          this,SLOT(saveAllFile()));
    //_menu->addSeparator();
    _fileMenu->addSection("Section Text");
    _runAction = _fileMenu->addAction(QIcon(":/editor/run.png"),tr("&Run"));
    _runAction->setEnabled(false);

    QAction * action;
    QActionGroup * alignmentGroup = new QActionGroup(this);
    _langMenu->addSeparator()->setText("Language");
    action = _langMenu->addAction("Bash");
    //action->setSeparator(true);
    action->setCheckable(true);
    alignmentGroup->addAction(action);
    action = _langMenu->addAction("Python");
    //action->setSeparator(true);
    action->setCheckable(true);
    alignmentGroup->addAction(action);
    action = _langMenu->addAction("SQL");
    //action->setSeparator(true);
    action->setCheckable(true);
    alignmentGroup->addAction(action);
    alignmentGroup->setExclusive(true);
    connect(alignmentGroup,SIGNAL(triggered(QAction*)),SLOT(setLanguage(QAction*)));
}
ArkEditor* ArkEditorTabWidget::createArkEditor(){
    ArkEditor  * editor = new ArkEditor(this);
    int minEmptyFileIndex = emptyFileMinIndex();
    addTab(editor,QIcon(":/editor/new.png"),QString("new %1").arg(minEmptyFileIndex));

    setCurrentWidget(editor);
    connect(editor,SIGNAL(changeFileName(QString)),SLOT(changeFileName(QString)));
    connect(editor,SIGNAL(modificationChanged(bool)),SLOT(modificationChanged(bool)));
    return editor;
}
QMap<QString,ArkEditor*> ArkEditorTabWidget::editors(){
    QMap<QString,ArkEditor*> editor_children;
    int countWidget = count();
    ArkEditor * editor = NULL;
    for(int i=0; i<countWidget; ++i){
        editor = qobject_cast<ArkEditor*>(widget(i));
        if(editor){
            const QString& filename = editor->fileName();
            if(filename.isEmpty()){
                editor_children[tabText(i)] = editor;
            }else{
                editor_children[editor->fileName()] = editor;
            }
        }
    }
    return editor_children;
}
void ArkEditorTabWidget::checkActionsStatus(){
    ArkEditor * editor = qobject_cast<ArkEditor*>(currentWidget());
    _saveAllAction->setEnabled(false);
    if(editor){
        if(editor->isModified()){
            _saveAction->setEnabled(true);
            _saveAllAction->setEnabled(true);
        }else{
            _saveAction->setEnabled(false);
        }
    }
    int countWidget = count();
    for(int i=0; i<countWidget; ++i){
        editor = qobject_cast<ArkEditor*>(widget(i));
        if(editor && editor->isModified()){
            //qDebug() << "set save all action enable.";
            _saveAllAction->setEnabled(true);
            break;
        }
    }

}
int ArkEditorTabWidget::emptyFileMinIndex(){
    int countWidget = count();
    ArkEditor * editor = NULL;
    std::set<int> tmp;
    for(int i=0; i<countWidget; ++i){
        editor = qobject_cast<ArkEditor*>(widget(i));
        if(editor && editor->fileName().isEmpty()){
            // new %1
            QString tabtxt = tabText(i);
            tabtxt.replace(QChar('*'),"");
            int pos = tabtxt.lastIndexOf(".");
            //if(pos == -1) pos = tabtxt.lastIndexOf(QChar('*'));
            int min = tabtxt.mid(4,pos).toInt();
            qDebug() << "toint:" << tabtxt.mid(4,pos) << min;
            tmp.insert(min);
        }
    }
    //qDebug() << tmp;
    int i = 1;
    std::set<int>::iterator it = tmp.begin();
    while(it != tmp.end()){
        qDebug() << i << *it << " hre.";
        if(i != *it) return i;
        ++it;
        ++i;
    }
    return i;
}
//private slots
void ArkEditorTabWidget::openFile(){
    QStringList flist = QFileDialog::getOpenFileNames(this,tr("Open Files"),"",
                                                      tr("SQL Files (*.sql *.hsql);;Bash(*.sh);;Python(*.py)"));
    //all file
    if(flist.size() == 0) return;
    ArkEditor * editor = NULL;
    QMap<QString,ArkEditor*> editor_children = editors();

    foreach(QString file,flist){
        QMap<QString,ArkEditor*>::iterator it = editor_children.find(file);
        if(it == editor_children.end()){
            editor = createArkEditor();
            editor->openFile(file);
            editor_children[file] = editor;
        }else{
            setCurrentWidget(editor_children[file]);
        }
    }
    checkActionsStatus();
}

void ArkEditorTabWidget::newFile(){
    createArkEditor();
    checkActionsStatus();
}
void ArkEditorTabWidget::saveFile(){
    ArkEditor * editor = qobject_cast<ArkEditor*>(currentWidget());
    if(editor){
        editor->saveFile();
    }
    checkActionsStatus();
}
void ArkEditorTabWidget::saveAllFile(){
    int countWidget = count();
    ArkEditor * editor = NULL;
    for(int i=0; i<countWidget; ++i){
        editor = qobject_cast<ArkEditor*>(widget(i));
        if(editor){
            editor->saveFile();
        }
    }
    checkActionsStatus();
}
void ArkEditorTabWidget::tabClose(int index){
    if(index > -1){
        QWidget * w = widget(index);

        ArkEditor * editor = qobject_cast<ArkEditor*>(w);
        if(editor){
            editor->saveFile();
        }
        removeTab(index);
        w->deleteLater();
    }
    checkActionsStatus();
}
void ArkEditorTabWidget::closeAllFile(){
    ArkEditor * editor = NULL;
    int i = count();
    for(; i>-1; --i){
        QWidget * w = widget(i);
        editor = qobject_cast<ArkEditor*>(w);
        if(editor){
            editor->saveFile();
        }
        removeTab(i);
        w->deleteLater();
    }
}
/**
 * @brief ArkEditorTabWidget::changeFileName
 * @param filename
 */
void ArkEditorTabWidget::changeFileName(const QString& filename){
    qDebug() << __FUNCDNAME__ << ":" << filename;
    ArkEditor * editor = qobject_cast<ArkEditor*>(sender());
    if(editor){
        QFileInfo finfo(filename);
        int index = indexOf(editor);
        if(index > -1){
            QString filename2 = finfo.fileName();
            if(filename2.isEmpty()) filename2 = tabText(index);
            if(editor->isModified()){
                filename2.append("*");
                //filename2 = "<font color=\"red\">" + filename2 + "</font>";
            }
            setTabText(index,filename2);
        }
    }
}

void ArkEditorTabWidget::modificationChanged(bool /*m*/){
    ArkEditor * editor = qobject_cast<ArkEditor*>(sender());
    if(editor){
        //模拟信号
        changeFileName(editor->fileName());
    }
}
void ArkEditorTabWidget::setLanguage(QAction *act){
    ArkEditor * editor = qobject_cast<ArkEditor*>(currentWidget());
    if(!editor) return;
    if(act->isChecked()){
        QString lang = act->text();
        qDebug() << "change to lang:" << lang;
        if(lang == "SQL"){
            editor->setLanguage(ArkEditor::SQL);
            //qDebug() << editor << " lang:SQL";
        }else if(lang == "Bash"){
            editor->setLanguage(ArkEditor::BASH);
            //qDebug() << editor << " lang:BASH";
        }else if(lang == "Python"){
            editor->setLanguage(ArkEditor::PYTHON);
            //qDebug() << editor << " lang:PYTHON";
        }
    }
}

//public slots
void ArkEditorTabWidget::preview(){
    //todo
}


