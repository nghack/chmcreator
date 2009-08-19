#include <QtGui>

#include "delegate.h"


//! [0]
QButtonDelegate::QButtonDelegate(QString path,QObject *parent)
    : QItemDelegate(parent)
{
    filePath = path;
}
//! [0]

//! [1]
QWidget *QButtonDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/* index */) const
{
    QPushButton *editor = new QPushButton(parent);
    connect(editor,SIGNAL(clicked()),this,SLOT(showDialog()));
    return editor;
}
//! [1]

//! [2]
void QButtonDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    QTreeItem *item = static_cast<QTreeItem*>(index.internalPointer());

    QString value = item->objectUrl().toString();

//    QComboBox *spinBox = static_cast<QComboBox*>(editor);
}
//! [2]

//! [3]
void QButtonDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QPushButton *spinBox = static_cast<QPushButton*>(editor);
    //spinBox->interpretText();
    //QString value = spinBox->currentText();

    //model->setData(index, value, Qt::EditRole);
}
//! [3]

//! [4]
void QButtonDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    QRect rect = option.rect;
    rect.setX(rect.x()+rect.width()-rect.height());
    rect.setWidth(rect.height());

    editor->setGeometry(rect);
}
//! [4]
