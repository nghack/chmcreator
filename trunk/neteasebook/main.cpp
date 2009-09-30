#include <QtCore>
#include "qneteasebookdownload.h"

int main(int argc, char *argv[])
{
    if(argc<2){
        qDebug()<<"Input Book Index URL.";
        return 0;
    }
    QCoreApplication app(argc, argv);

    QNeteaseBookDownload downloader(QString(argv[1]),".");
    downloader.setProxy("172.28.9.151",8080);
    downloader.download();
    app.connect(&downloader, SIGNAL(finished()), &app, SLOT(quit()));
    return app.exec();
}
