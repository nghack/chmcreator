#include <QtGui>
#include "mainwindow.h"
#include <QTextCodec>
#include "global.h"

QSettings settings("conf.ini",QSettings::IniFormat);
QTextCodec* codec = QTextCodec::codecForName("UTF-8");
QString toUTF8(QByteArray array){
    codec->toUnicode(array);
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    settings.setValue(APP_PATH,QCoreApplication::applicationDirPath ());
    MainWindow w(QCoreApplication::applicationDirPath ());
    w.show();
    return a.exec();
}
