#include <QtGui>
#include "mainwindow.h"
#include <QTextCodec>
#include "global.h"

QSettings settings("conf.ini",QSettings::IniFormat);

int main(int argc, char *argv[])
{
    QTextCodec::codecForName("utf-8");

    QApplication a(argc, argv);
    settings.setValue(APP_PATH,QCoreApplication::applicationDirPath ());
    MainWindow w(QCoreApplication::applicationDirPath ());
    w.show();
    return a.exec();
}
