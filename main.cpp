#include <QtGui>
#include "mainwindow.h"
#include <QTextCodec>
#include "global.h"

QSettings settings("conf.ini",QSettings::IniFormat);
QTextCodec* codec = QTextCodec::codecForName("UTF-8");
QString toUTF8(QByteArray array){
    return codec->toUnicode(array);
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    settings.setValue(APP_PATH,QCoreApplication::applicationDirPath ());
    /*if(settings.value(PROJECT_WORKSPACE).isNull()){
        QString path = QInputDialog::getText(0,"","");
        if(path==QString::null){
            return a.exec();
        }
        settings.setValue(PROJECT_WORKSPACE,path);
    }*/
    MainWindow w(QCoreApplication::applicationDirPath ());
    w.show();
    return a.exec();
}
