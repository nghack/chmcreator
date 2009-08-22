#include "qcontentstreeview.h"
#include "mainwindow.h"
#include "global.h"

extern QSettings settings;

QContentsTreeView::QContentsTreeView(MainWindow* mainWindow)
{
    this->mainWindow = mainWindow;
    createActions();
}
QContentsTreeView::~QContentsTreeView()
{
    delete menu;
}
void QContentsTreeView::openFile(){
    QModelIndex index = currentIndex();//r(-1), c(-1), p(0), m(0) {}
    emit doubleClicked(index.sibling(index.row(),0));
}
void QContentsTreeView::newFile(){
    dialog.exec();
}
void QContentsTreeView::addExistFile(){
    QString fileName = QFileDialog::getOpenFileName(0,"Open");
    if(fileName.isEmpty())
        return;    
    QTreeItem* item = (QTreeItem*)currentIndex().internalPointer();
    QFileInfo fileInfo(fileName);    
    QString appPath = settings.value(APP_PATH).toString();
    appPath.append("/workspace/");
    QString project = settings.value(PROJECT_NAME).toString();
    appPath.append(project.left(project.indexOf('.')));
    appPath.append("/");
    appPath.append(fileInfo.fileName());

    QFile::copy(fileName,appPath);

    QList<QVariant> columnData;
    columnData<<fileInfo.fileName();
    columnData<<fileInfo.fileName();
    QTreeItem* newItem = new QTreeItem(columnData,item);
    item->appendChild(newItem);

    mainWindow->saveHHC();

    update(rootIndex());
}
void QContentsTreeView::copyFile(){}
void QContentsTreeView::pasteFile(){}
void QContentsTreeView::deleteFile()
{
    QModelIndex parent = currentIndex().parent();
//    if(!parent.isValid())
//        return;
    model()->removeRow(currentIndex().row(),parent);
    mainWindow->saveHHC();
    update(rootIndex());
}
void QContentsTreeView::renameFile(){}
void QContentsTreeView::property(){}
void QContentsTreeView::createActions()
{
    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcut(tr("Ctrl+P"));
    openAct->setStatusTip(tr("Print the document"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));

    newAct = new QAction(tr("&New"), this);
    newAct->setShortcut(tr("Ctrl+N"));
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    addExistingAct = new QAction(tr("&Add"), this);
    addExistingAct->setShortcut(tr("Ctrl+A"));
    addExistingAct->setStatusTip(tr("Open an existing file"));
    connect(addExistingAct, SIGNAL(triggered()), this, SLOT(addExistFile()));

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcut(tr("Ctrl+C"));
    copyAct->setStatusTip(tr("Save the document to disk"));
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copyFile()));

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcut(tr("Ctrl+P"));
    pasteAct->setStatusTip(tr("Print the document"));
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(pasteFile()));

    deleteAct = new QAction(tr("&Delete"), this);
    deleteAct->setShortcut(tr("Ctrl+P"));
    deleteAct->setStatusTip(tr("Print the document"));
    connect(deleteAct, SIGNAL(triggered()), this, SLOT(deleteFile()));

    renameAct = new QAction(tr("&Rename"), this);
    renameAct->setShortcut(tr("Ctrl+P"));
    renameAct->setStatusTip(tr("Print the document"));
    connect(renameAct, SIGNAL(triggered()), this, SLOT(renameFile()));

    propertyAct = new QAction(tr("&Properties"), this);
    propertyAct->setShortcut(tr("Alt+Enter"));
    propertyAct->setStatusTip(tr("Properties of File"));
    connect(propertyAct, SIGNAL(triggered()), this, SLOT(property1()));

    menu = new QMenu(this);

    menu->addAction(openAct);
    menu->addSeparator();
    menu->addAction(newAct);
    menu->addAction(addExistingAct);
    menu->addAction(copyAct);
    menu->addAction(pasteAct);
    menu->addSeparator();
    menu->addAction(deleteAct);
    menu->addAction(renameAct);
    menu->addSeparator();
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
