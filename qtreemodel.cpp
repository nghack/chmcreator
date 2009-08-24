#include <QtGui>

#include "qTreeItem.h"
#include "QTreeModel.h"

QTreeModel::QTreeModel(QString title,QObject *parent)
        : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << title<< "File";
    rootItem = new QTreeItem(rootData);

    parents << rootItem;
    indentations << 0;

    //addModelData(-4,title,"");
}

QTreeModel::~QTreeModel()
{
    delete rootItem;
}

int QTreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<QTreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}
//! [2]

//! [3]
QVariant QTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    //Node *node = nodeFromIndex(index);
    if (role == Qt::DecorationRole){
        QTreeItem *parentItem = static_cast<QTreeItem*>(index.internalPointer());

        if(index.column()!=0)
            return QVariant();
        QIcon icon;
        if(parentItem->childCount()>0){
            parentItem->setNodeType(1);
            icon.addPixmap(QPixmap(QString::fromUtf8(":/images/closeFolder.png")), QIcon::Normal, QIcon::Off);
            icon.addPixmap(QPixmap(QString::fromUtf8(":/images/openFolder.png")), QIcon::Normal, QIcon::On);
        }else{
            icon.addPixmap(QPixmap(QString::fromUtf8(":/images/page.png")), QIcon::Normal, QIcon::Off);
        }
        return icon;
    }
    if (role != Qt::DisplayRole)
        return QVariant();
    QTreeItem *item = static_cast<QTreeItem*>(index.internalPointer());

    return item->data(index.column());
}
QVariant QTreeModel::objectUrl(const QModelIndex &index) const
{
    if (!index.isValid())
        return QVariant();

    QTreeItem *item = static_cast<QTreeItem*>(index.internalPointer());

    return item->objectUrl();
}
//! [3]

//! [4]
Qt::ItemFlags QTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
//! [4]

//! [5]
QVariant QTreeModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}
//! [5]

//! [6]
QModelIndex QTreeModel::index(int row, int column, const QModelIndex &parent)
        const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    QTreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<QTreeItem*>(parent.internalPointer());

    QTreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}
//! [6]

//! [7]
QModelIndex QTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    QTreeItem *childItem = static_cast<QTreeItem*>(index.internalPointer());
    QTreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}
//! [7]

//! [8]
int QTreeModel::rowCount(const QModelIndex &parent) const
{
    QTreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<QTreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}
//! [8]

void QTreeModel::addModelData(int position,const QString& data,const QString& url)
{
    QList<QVariant> columnData;
    columnData<<data<<url;

    if (position > indentations.last()) {
       if (parents.last()->childCount() > 0) {
            parents << parents.last()->child(parents.last()->childCount()-1);
            indentations << position;
        }
//    } else if(position < indentations.last()){

    }else{
        while (position < indentations.last() && parents.count() > 0) {
            parents.pop_back();
            indentations.pop_back();
        }
    }
    // Append a new item to the current parent's list of children.
    parents.last()->appendChild(new QTreeItem(columnData, parents.last()));
}
bool QTreeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (!parent.isValid()){
        rootItem->removeRow(row);
        return true;
    }
    QTreeItem *item = static_cast<QTreeItem*>(parent.internalPointer());
    item->removeRow(row);
    return true;
}
