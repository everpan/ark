#include "MainWindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QRect maxRect;
    {
        QDesktopWidget desktop;
        maxRect = desktop.availableGeometry();
        maxRect.adjust(50,50,-50,-50);
    }
    qDebug() << QApplication::applicationDirPath() << QApplication::applicationFilePath();
    MainWindow w;
    w.setGeometry(maxRect);
    w.show();
    return a.exec();
}
