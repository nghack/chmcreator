
#ifndef QTreeModel_H
#define QTreeModel_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class QTreeItem;

//! [0]
class QTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    QTreeModel(QString title,QObject *parent = 0);
    ~QTreeModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant objectUrl(const QModelIndex &index) const;
    void addModelData(int position,const QString& data,const QString& url);
    QList<QTreeItem*>& getTreeItemList(){return parents;}
    QTreeItem* getRootItem(){return rootItem;}
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
private:
    QTreeItem *rootItem;
    QList<QTreeItem*> parents;
    QList<int> indentations;
};
//! [0]

#endif
