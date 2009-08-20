#include "qcontentstreeview.h"

QContentsTreeView::QContentsTreeView()
{
    createActions();
}
QContentsTreeView::~QContentsTreeView()
{
    delete menu;
}
void QContentsTreeView::createActions()
{
     openAct = new QAction(tr("&Open"), this);
     openAct->setShortcut(tr("Ctrl+P"));
     openAct->setStatusTip(tr("Print the document"));
     connect(openAct, SIGNAL(triggered()), this, SLOT(print()));

     newAct = new QAction(tr("&New"), this);
     newAct->setShortcut(tr("Ctrl+N"));
     newAct->setStatusTip(tr("Create a new file"));
     connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

     addExistingAct = new QAction(tr("&Add"), this);
     addExistingAct->setShortcut(tr("Ctrl+A"));
     addExistingAct->setStatusTip(tr("Open an existing file"));
     connect(addExistingAct, SIGNAL(triggered()), this, SLOT(open()));

     copyAct = new QAction(tr("&Copy"), this);
     copyAct->setShortcut(tr("Ctrl+C"));
     copyAct->setStatusTip(tr("Save the document to disk"));
     connect(copyAct, SIGNAL(triggered()), this, SLOT(save()));

     pasteAct = new QAction(tr("&Paste"), this);
     pasteAct->setShortcut(tr("Ctrl+P"));
     pasteAct->setStatusTip(tr("Print the document"));
     connect(pasteAct, SIGNAL(triggered()), this, SLOT(print()));

     deleteAct = new QAction(tr("&Delete"), this);
     deleteAct->setShortcut(tr("Ctrl+P"));
     deleteAct->setStatusTip(tr("Print the document"));
     connect(deleteAct, SIGNAL(triggered()), this, SLOT(print()));

     renameAct = new QAction(tr("&Rename"), this);
     renameAct->setShortcut(tr("Ctrl+P"));
     renameAct->setStatusTip(tr("Print the document"));
     connect(renameAct, SIGNAL(triggered()), this, SLOT(print()));

     propertyAct = new QAction(tr("&Properties"), this);
     propertyAct->setShortcut(tr("Alt+Enter"));
     propertyAct->setStatusTip(tr("Properties of File"));
     connect(propertyAct, SIGNAL(triggered()), this, SLOT(print()));

     menu = new QMenu(this);

     menu->addAction(openAct);
     menu->addAction(newAct);
     menu->addAction(addExistingAct);
     menu->addAction(copyAct);
     menu->addAction(pasteAct);
     menu->addAction(deleteAct);
     menu->addAction(renameAct);
     menu->addAction(propertyAct);

}
void QContentsTreeView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        //QModelIndex index = currentIndex();
        //QTreeItem *item = static_cast<QTreeItem*>(index.internalPointer());
        menu->exec(event->globalPos());
//        if(item->nodeType()==1){//folder
//
//        }else{
//
//        }
    }

}
