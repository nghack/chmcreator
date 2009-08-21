#ifndef QTreeItem_H
#define QTreeItem_H

#include <QList>
#include <QVariant>

//! [0]
class QTreeItem
{
public:
    QTreeItem(const QList<QVariant> &data, QTreeItem *parent = 0);
    ~QTreeItem();

    void appendChild(QTreeItem *child);

    QTreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    QVariant objectUrl() const;
    QTreeItem *parent();
    int nodeType(){return type;}//1=folder,0=file
    void setNodeType(int nodeType){type = nodeType;}
    QList<QTreeItem*> childItemList(){return childItems;}
private:
    int type;    
    QList<QTreeItem*> childItems;
    QList<QVariant> itemData;
    QTreeItem *parentItem;
};
//! [0]

#endif
