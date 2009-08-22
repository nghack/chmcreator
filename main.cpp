#include <QtGui>
#include "mainwindow.h"
#include <QTextCodec>
#include "global.h"

QSettings settings("conf.ini",QSettings::IniFormat);

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    QApplication a(argc, argv);
    settings.setValue(APP_PATH,QCoreApplication::applicationDirPath ());
    MainWindow w(QCoreApplication::applicationDirPath ());
    w.show();
    return a.exec();
}
