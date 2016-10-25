#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ArkEditorTabWidget * ark_editor_tabwidget = new ArkEditorTabWidget(this);
    setCentralWidget(ark_editor_tabwidget);
    QMenuBar *menuBar = this->menuBar();
    menuBar->addMenu(ark_editor_tabwidget->fileMenu());
    menuBar->addMenu(ark_editor_tabwidget->languageMenu());
}

MainWindow::~MainWindow()
{
}
