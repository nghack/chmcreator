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
                                       const QModelIndex & index) const
{
    if(index.column()!=0){
        QPushButton *editor = new QPushButton(parent);
        connect(editor,SIGNAL(clicked()),this,SLOT(showDialog()));
        return editor;
    }else{
        QLineEdit *editor = new QLineEdit(parent);
        return editor;
    }
}
//! [1]

//! [2]
void QButtonDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    if(index.column()!=0){
        QTreeItem *item = static_cast<QTreeItem*>(index.internalPointer());
        QString value = item->objectUrl().toString();
    }else{
        QTreeItem *item = static_cast<QTreeItem*>(index.internalPointer());
        QString value = item->data(index.column()).toString();
        QLineEdit* edit = (QLineEdit*)editor;
        edit->setText(value);
    }
    //    QComboBox *spinBox = static_cast<QComboBox*>(editor);
}
//! [2]

//! [3]
void QButtonDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    if(index.column()==0){
        QLineEdit *spinBox = static_cast<QLineEdit*>(editor);
        model->setData(index, spinBox->text(), Qt::EditRole);
    }
}
//! [3]

//! [4]
void QButtonDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option, const QModelIndex & index) const
{
    if(index.column()!=0){
        QRect rect = option.rect;
        rect.setX(rect.x()+rect.width()-rect.height());
        rect.setWidth(rect.height());

        editor->setGeometry(rect);
    }else{
        editor->setGeometry(QRect(0,0,0,0));
    }
}
//! [4]
