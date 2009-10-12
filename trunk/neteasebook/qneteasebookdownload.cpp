#include "qneteasebookdownload.h"

QNeteaseBookDownload::QNeteaseBookDownload(QString bookIndexURL,QString bookRoot)
{
    this->bookRoot = bookRoot;
    this->bookIndexURL = bookIndexURL;

    QString temp = bookIndexURL.right(26);

    bookCatalog = temp.left(12);
    qDebug()<<"Catalog is:"<<bookCatalog;
    bookID = temp.right(13).left(8);
    qDebug()<<"Book ID is:"<<bookID;

    http = new QHttp(this);
    http->setHost("data.book.163.com");
    connect(http,SIGNAL(done(bool)),this,SLOT(saveFile(bool)));

    QDir dir(bookRoot);
    dir.setCurrent(bookRoot);

    if(!dir.exists(bookID)){
        dir.mkdir(bookID);
    }

    block = 0;

    status = 0;
}
void QNeteaseBookDownload::setProxy(QString hostname,int port){
    http->setProxy(hostname,port,"","");
    qDebug()<<"setProxy:"<<hostname<<":"<<port;
}

void QNeteaseBookDownload::saveFile(bool isError){
    qDebug()<<"Requesting:Finished!"<<http->lastResponse().statusCode();
    if(isError||http->lastResponse().statusCode()==404){
        qDebug()<<"ERROR!"<<http->errorString();
        emit finished();
        return;
    }

    downloadChapter();
    block++;
}
void QNeteaseBookDownload::download()
{
    QString indexURL = QString(INDEX_URL_TEMPLATE).arg(bookCatalog).arg(bookID);
    qDebug()<<"Start downloading:"<<indexURL;
    http->get(QUrl::toPercentEncoding(indexURL),new QFile(bookRoot+"/"+bookID+"/index.html",this));
}
void QNeteaseBookDownload::downloadChapter(){
    QString chapterTemplate = QString(CONTENT_URL_TEMPLATE).arg(bookID).arg(bookID).arg(block);
    http->get(QUrl::toPercentEncoding(chapterTemplate),new QFile(bookRoot+"/"+bookID+"/"+QString(CHAPTER_LOCAL_FILE_TEMPLATE).arg(bookID).arg(block),this));
    qDebug()<<"Requesting:"<<chapterTemplate;
}
