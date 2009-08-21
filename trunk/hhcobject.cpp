#include "hhcobject.h"

HHCObject::HHCObject(QString title,QString fileName)
{
    this->title = title;
    this->fileName = fileName;

    QMessageBox::about(0,"",fileName);
    treeModel = new QTreeModel(title);

    connect(treeModel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(dataChanged(QModelIndex,QModelIndex)));

    QTreeModelHandler handler(treeModel);
    QHHCParser parser;
    parser.parse(fileName,&handler);
}
HHCObject::~HHCObject()
{
    delete treeModel;
}
void HHCObject::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    qDebug()<<"HHC Data Changed";
}
void HHCObject::writeTreeItem(QTextStream& outStream,QTreeItem* item)
{
    (outStream)<<"<LI><OBJECT TYPE=\"text/sitemap\">\n";
    (outStream)<<"<PARAM NAME=\"Name\" VALUE=\"";
    (outStream)<<item->data(0).toString();
    (outStream)<<"\">\n";
    (outStream)<<"<PARAM NAME=\"Local\" VALUE=\"";
    (outStream)<<item->data(1).toString();
    (outStream)<<"\">\n";

    (outStream)<<"</OBJECT>\n";
    if(item->childCount()>0){
        (outStream)<<"<UL>\n";
        QList<QTreeItem*> list = item->childItemList();
        foreach(QTreeItem* item,list){
            writeTreeItem(outStream,item);
        }
        (outStream)<<"</UL>\n";
    }
}
void HHCObject::save()
{
    QFile file("e:/qtstudy/bin/ttttttttttttttttttttttt.txt");
     if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
         return;
    QTextStream outStream(&file);
    outStream.setCodec("gb2312");

    outStream<<"<html><head></head><body>\n";
    outStream<<"<OBJECT type=\"text/site properties\"><param name=\"Window Styles\" value=\"0x227\"></OBJECT>\n";
    outStream<<"<UL>\n";
    QTreeItem* root = treeModel->getRootItem();
//    writeTreeItem(outStream,list);
    QList<QTreeItem*> list = root->childItemList();
    foreach(QTreeItem* item,list){
        writeTreeItem(outStream,item);
    }
    outStream<<"</UL>\n";
    outStream<<"</BODY></HTML>\n";
}
void HHCObject::saveAs(const QString fileName){

}
