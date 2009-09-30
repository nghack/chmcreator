#ifndef QNETEASEBOOKDOWNLOAD_H
#define QNETEASEBOOKDOWNLOAD_H

#include <QObject>
#include <QtCore>
#include <QtNetwork>

const QString INDEX_URL_TEMPLATE = "/book/home/%1/%2.html";
const QString CONTENT_URL_TEMPLATE = "/book/section/%1/%2%3_b.html";
const QString CHAPTER_LOCAL_FILE_TEMPLATE = "%1%2_b.html";
class QNeteaseBookDownload : public QObject
{
    Q_OBJECT
public:
    QNeteaseBookDownload(QString bookId,QString bookRoot);
    void setProxy(QString hostname,int port);
    void download();
signals:
    void finished();
public slots:
    void saveFile(bool);
private:
    int status;
    QString bookRoot;
    QString bookIndexURL;

    QString bookCatalog;
    QString bookID;
    int block;
    QString urlTemplate;
    QHttp* http;
    void downloadChapter();
};

#endif // QNETEASEBOOKDOWNLOAD_H
