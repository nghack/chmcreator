#ifndef DELEGATE_H
#define DELEGATE_H

#include <QtGui>
#include "QTreeItem.h"
#include "qmodifyfiledialog.h"

//! [0]
class QButtonDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    QButtonDelegate(QString path,QObject *parent=0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
    QString filePath;
    QModifyFileDialog dialog;
private slots:
    void showDialog(){
        dialog.setModel(filePath);
        dialog.show();
    }
};
//! [0]

#endif
