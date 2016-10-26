#include "MainWindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QSplashScreen>
#include <QTimer>

#include "arkbrowser/browsermainwindow.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    BrowserMainWindow w;
    QRect maxRect;
    {
        QDesktopWidget desktop;
        maxRect = desktop.availableGeometry();
        maxRect.adjust(50,50,-50,-50);
    }
    w.setGeometry(maxRect);

    qDebug() << QApplication::applicationDirPath() << QApplication::applicationFilePath();
    {
        QPixmap splashPixmap(QApplication::applicationDirPath() + "/comm/conf/pics/splash.png");
        QSplashScreen splash(splashPixmap);
        splash.show();

        enum{
            splashTime = 1500
        };
        QTimer timer;
        timer.start(splashTime);
        do{
            a.processEvents();
            splash.showMessage(QString("Loading Process: %1%").arg(timer.remainingTime()*100.0/splashTime),Qt::AlignBottom);
        }while(timer.remainingTime() > 1);

        splash.finish(&w);
    }
    w.show();
    a.processEvents();
    return a.exec();
}
