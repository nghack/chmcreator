#include "hhcobject.h"

HHCObject::HHCObject(QString title,QString fileName)
{
    this->title = title;
    this->fileName = fileName;

    treeModel = new QTreeModel(title);

    if(fileName.endsWith(".hhc")){
        QTreeModelHandler handler(treeModel);
        QHHCParser parser;
        parser.parse(fileName,&handler);
    }else{
        QFileInfo fileInfo(fileName);
        if(fileInfo.isDir())
            fromDir(0,fileName);
    }

    connect(treeModel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(dataChanged(QModelIndex,QModelIndex)));
}
void HHCObject::fromDir(int level,QString dir){
    QDir dirModel;
    dirModel.setCurrent(dir);
    QStringList list = dirModel.entryList();
    foreach(QString fileName,list){        
        if(fileName.compare(".")==0||fileName.compare("..")==0){
            continue;
        }
        QFileInfo fileInfo(fileName);
        if(fileInfo.isDir()){
            fromDir(level+4,fileName);
        }else{
           treeModel->addModelData(level, fileName,fileName);
        }
    }
}
HHCObject::~HHCObject()
{
    delete treeModel;
}
void HHCObject::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    qDebug()<<"HHC Data Changed";
    save();
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
    saveAs(fileName);
}
void HHCObject::saveAs(const QString fileName){
    QFile file(fileName);
     if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
         return;
    QTextStream outStream(&file);

    outStream<<"<html><head></head><body>\n";
    outStream<<"<OBJECT type=\"text/site properties\"><param name=\"Window Styles\" value=\"0x227\"></OBJECT>\n";
    outStream<<"<UL>\n";
    QTreeItem* root = treeModel->getRootItem();
//    writeTreeItem(outStream,list);
    QList<QTreeItem*> list = root->child(0)->childItemList();
    foreach(QTreeItem* item,list){
        writeTreeItem(outStream,item);
    }
    outStream<<"</UL>\n";
    outStream<<"</BODY></HTML>\n";
}
