#ifndef HHCOBJECT_H
#define HHCOBJECT_H

#include <QtGui>
#include "qTreeItem.h"
#include "QTreeModel.h"
#include "qhhchandler.h"
#include "QTreeModel.h"
#include "qtreemodelhandler.h"
#include "QHHCParser.h"
class HHCObject : public QObject
{
    Q_OBJECT
public:
    HHCObject(QString title,QString fileName);
    ~HHCObject();
    QTreeModel* getTreeModel(){return treeModel;}
    void save();
    void fromDir(int level,QString dir);
    void saveAs(const QString fileName);
private slots:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
private:
    void writeTreeItem(QTextStream& outStream,QTreeItem* item);
    QString title;
    QString fileName;
    QTreeModel* treeModel;
};

#endif // HHCOBJECT_H
