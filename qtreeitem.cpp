/*
    QTreeItem.cpp

    A container for items of data supplied by the simple tree model.
*/

#include <QStringList>

#include "QTreeItem.h"

//! [0]
QTreeItem::QTreeItem(const QList<QVariant> &data, QTreeItem *parent)
{
    parentItem = parent;
    itemData = data;

    type = 0;
}
//! [0]
void QTreeItem::setData(int column,QVariant data)
{
    itemData.removeAt(column);
    itemData.insert(column,data);
}
//! [1]
QTreeItem::~QTreeItem()
{
    qDeleteAll(childItems);
}
//! [1]

//! [2]
void QTreeItem::appendChild(QTreeItem *item)
{
    childItems.append(item);
}
//! [2]

//! [3]
QTreeItem *QTreeItem::child(int row)
{
    return childItems.value(row);
}
//! [3]
int QTreeItem::indexOf(QTreeItem *child)
{
    return childItems.indexOf(child);
}
//! [3]

//! [4]
int QTreeItem::childCount() const
{
    return childItems.count();
}
//! [4]

//! [5]
int QTreeItem::columnCount() const
{
    return itemData.count();
}
//! [5]

//! [6]
QVariant QTreeItem::data(int column) const
{
    return itemData.value(column);
}
//! [6]

//! [7]
QTreeItem *QTreeItem::parent()
{
    return parentItem;
}
//! [7]

//! [8]
int QTreeItem::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<QTreeItem*>(this));

    return 0;
}
QVariant QTreeItem::objectUrl() const
{
    return itemData.value(1);
}
//! [8]
bool QTreeItem::removeRow(int row)
{
    childItems.removeAt(row);
    return true;
}
void QTreeItem::moveUp(int index)
{
    if(index>0&&index<itemData.size()){
        itemData.move(index,index-1);
    }
}
void QTreeItem::moveDown(int index)
{
    if(index>0&&index<(itemData.size()-1)){
        itemData.move(index,index+1);
    }
}
